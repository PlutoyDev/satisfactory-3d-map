#include "MapWindow.h"

#include <filesystem>

#include <glm/gtc/matrix_inverse.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include <tiny_gltf.h>

#include "Utils/ResourceUtils.h"

namespace {
    void drawObjectTreeGui(const Satisfactory3DMap::SaveGame::SaveNode& n) {
        for (const auto& child : n.childNodes) {
            std::string counts =
                " (A:" + std::to_string(child.second.numActors) + " O:" + std::to_string(child.second.numObjects) + ")";
            if (ImGui::TreeNode((child.first + counts).c_str())) {
                drawObjectTreeGui(child.second);
                ImGui::TreePop();
            }
        }
        for (const auto& obj : n.objects) {
            if (obj.second->type() == 1) {
                ImGui::Text("[A] %s", obj.first.c_str());
            } else {
                ImGui::Text("[O] %s", obj.first.c_str());
            }
        }
    }
} // namespace

Satisfactory3DMap::MapWindow::MapWindow()
    : BaseWindow("Satisfactory3DMap"),
      mouseX_(0.0),
      mouseY_(0.0),
      cameraControlMode_(Camera::MouseControlMode::None),
      camera_(8000.0f),
      projMx_(glm::mat4(1.0f)) {

    fbo_ = std::make_unique<glowl::FramebufferObject>(width_, height_, glowl::FramebufferObject::DEPTH32F);
    fbo_->createColorAttachment(GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE); // color
    fbo_->createColorAttachment(GL_RGBA32F, GL_RGBA, GL_FLOAT);       // normals
    fbo_->createColorAttachment(GL_R32I, GL_RED_INTEGER, GL_INT);     // pick id
    fbo_->bind();
    if (!fbo_->checkStatus(GL_FRAMEBUFFER)) {
        throw std::runtime_error(fbo_->getLog());
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    try {
        shaderQuad_ = std::make_unique<glowl::GLSLProgram>(glowl::GLSLProgram::ShaderSourceList{
            {glowl::GLSLProgram::ShaderType::Vertex, getStringResource("shaders/quad.vert")},
            {glowl::GLSLProgram::ShaderType::Fragment, getStringResource("shaders/quad.frag")}});
    } catch (glowl::GLSLProgramException& e) { std::cerr << e.what() << std::endl; }

    const std::vector<float> quadVertices{0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f};
    const std::vector<GLushort> quadIndices{0, 1, 2, 3};
    glowl::Mesh::VertexInfoList<float> vertexInfoList{{quadVertices, {8, {{2, GL_FLOAT, GL_FALSE, 0}}}}};
    meshQuad_ = std::make_unique<glowl::Mesh>(
        vertexInfoList, quadIndices, GL_UNSIGNED_SHORT, GL_STATIC_DRAW, GL_TRIANGLE_STRIP);

    worldRenderer_ = std::make_unique<WorldRenderer>();
    modelRenderer_ = std::make_unique<ModelRenderer>();

    resizeEvent(width_, height_);

    glEnable(GL_DEPTH_TEST);
}

Satisfactory3DMap::MapWindow::~MapWindow() {
    glDisable(GL_DEPTH_TEST);
}

void Satisfactory3DMap::MapWindow::openSave(const std::string& filename) {
    if (filename.empty()) {
        return;
    }
    std::filesystem::path filepath(filename);
    if (!std::filesystem::exists(filepath) || !std::filesystem::is_regular_file(filepath)) {
        std::cerr << "No regular file given!" << std::endl;
        return;
    }
    savegame_ = std::make_unique<SaveGame>(filepath);
    savegame_->printHeader();

    modelRenderer_->loadSave(*savegame_);
}

void Satisfactory3DMap::MapWindow::render() {
    renderGui();
    renderFbo();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shaderQuad_->use();
    shaderQuad_->setUniform("projMxQuad", glm::ortho(0.0f, 1.0f, 0.0f, 1.0f));
    shaderQuad_->setUniform("invProjMx", glm::inverse(projMx_));
    shaderQuad_->setUniform("invViewMx", glm::inverse(camera_.viewMx()));

    glActiveTexture(GL_TEXTURE0);
    fbo_->bindColorbuffer(0);
    shaderQuad_->setUniform("texAlbedo", 0);

    glActiveTexture(GL_TEXTURE1);
    fbo_->bindColorbuffer(1);
    shaderQuad_->setUniform("texNormal", 1);

    glActiveTexture(GL_TEXTURE2);
    fbo_->bindDepthbuffer();
    shaderQuad_->setUniform("texDepth", 2);

    meshQuad_->draw();

    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

void Satisfactory3DMap::MapWindow::renderGui() {
    ImGuiID dockspaceId = ImGui::DockSpaceOverViewport(
        nullptr, ImGuiDockNodeFlags_NoDockingInCentralNode | ImGuiDockNodeFlags_PassthruCentralNode);

    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open")) {}
        ImGui::EndMenu();
    }
    ImGui::EndMainMenuBar();

    static bool firstRun = true;
    if (firstRun) {
        firstRun = false;
        ImGui::DockBuilderRemoveNode(dockspaceId);
        ImGui::DockBuilderAddNode(dockspaceId, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(dockspaceId, ImGui::GetMainViewport()->Size);

        ImGuiID dockIdLeft = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Left, 0.2f, nullptr, &dockspaceId);
        ImGuiID dockIdRight = ImGui::DockBuilderSplitNode(dockspaceId, ImGuiDir_Right, 0.25f, nullptr, &dockspaceId);

        ImGui::DockBuilderDockWindow("Save Game", dockIdLeft);
        ImGui::DockBuilderDockWindow("Rendering", dockIdRight);
        ImGui::DockBuilderFinish(dockspaceId);
    }

    ImGui::Begin("Save Game");
    if (savegame_ != nullptr) {
        drawObjectTreeGui(savegame_->root());
    } else {
        ImGui::Text("No Save Game loaded!");
    }
    ImGui::End();

    ImGui::Begin("Rendering");
    ImGui::Text("%.1f FPS (%.3f ms/frame)", ImGui::GetIO().Framerate, 1000.0f / ImGui::GetIO().Framerate);
    ImGui::End();
}

void Satisfactory3DMap::MapWindow::renderFbo() {
    fbo_->bind();
    glClear(GL_DEPTH_BUFFER_BIT);
    GLubyte clearColor0[4]{0, 0, 0, 255};
    GLfloat clearColor1[4]{0.0f, 0.0f, 0.0f, 0.0f};
    GLint clearColor2[1]{-1};
    glClearTexImage(fbo_->getColorAttachment(0)->getName(), 0, GL_RGBA, GL_UNSIGNED_BYTE, clearColor0);
    glClearTexImage(fbo_->getColorAttachment(1)->getName(), 0, GL_RGBA, GL_FLOAT, clearColor1);
    glClearTexImage(fbo_->getColorAttachment(2)->getName(), 0, GL_RED_INTEGER, GL_INT, clearColor2);

    worldRenderer_->render(projMx_, camera_.viewMx());

    if (savegame_ != nullptr) {
        modelRenderer_->render(projMx_, camera_.viewMx());
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Satisfactory3DMap::MapWindow::resizeEvent(int width, int height) {
    if (width < 1 || height < 1) {
        return;
    }

    glViewport(0, 0, width, height);

    float aspect = static_cast<float>(width_) / static_cast<float>(height_);
    projMx_ = glm::perspective(glm::radians(45.0f), aspect, 1.0f, 10000.0f);

    fbo_->resize(width, height);
}

void Satisfactory3DMap::MapWindow::mouseButtonEvent(int button, int action, int mods) {
    cameraControlMode_ = Camera::MouseControlMode::None;
    if (action == GLFW_PRESS && mods == 0) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            cameraControlMode_ = Camera::MouseControlMode::Left;
        } else if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
            cameraControlMode_ = Camera::MouseControlMode::Middle;
        } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            cameraControlMode_ = Camera::MouseControlMode::Right;
        }
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS && mods == 0) {
        int id = 0;
        fbo_->bindToRead(2);
        glReadPixels(static_cast<GLint>(mouseX_), static_cast<GLint>(height_ - mouseY_), 1, 1, GL_RED_INTEGER, GL_INT,
            reinterpret_cast<void*>(&id));
        glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
        std::cout << "ID: " << id << std::endl;
        if (id >= 0 && id < savegame_->saveObjects().size()) {
            const auto& object = savegame_->saveObjects()[id];
            std::cout << "  " << object->className() << std::endl;
            std::cout << "  " << object->reference().pathName() << std::endl;
        }
    }
}

void Satisfactory3DMap::MapWindow::mouseMoveEvent(double xpos, double ypos) {
    if (cameraControlMode_ != Camera::MouseControlMode::None) {
        double oldX = 2.0 * mouseX_ / static_cast<double>(width_) - 1.0;
        double oldY = 1.0 - 2.0 * mouseY_ / static_cast<double>(height_);
        double newX = 2.0 * xpos / static_cast<double>(width_) - 1.0;
        double newY = 1.0 - 2.0 * ypos / static_cast<double>(height_);
        camera_.mouseMoveControl(cameraControlMode_, oldX, oldY, newX, newY);
    }
    mouseX_ = xpos;
    mouseY_ = ypos;
}

void Satisfactory3DMap::MapWindow::mouseScrollEvent(double xoffset, double yoffset) {
    camera_.mouseScrollControl(xoffset, yoffset);
}

void Satisfactory3DMap::MapWindow::dropEvent(const std::vector<std::string>& paths) {
    if (paths.size() != 1) {
        std::cerr << "Can only read a single file!" << std::endl;
    }
    openSave(paths[0]);
}
