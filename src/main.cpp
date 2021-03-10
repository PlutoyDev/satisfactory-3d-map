#include <iostream>
#include <string>

#include "MapWindow/MapWindow.h"
#include "SaveGame/SaveGame.h"

#ifdef _WIN32
#include <Windows.h>
#include <cstdio>
#endif

int main(int argc, char* argv[]) {
#ifdef _WIN32
    // Set console output to UTF-8, https://stackoverflow.com/a/45622802
    SetConsoleOutputCP(CP_UTF8);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif

    std::cout << "[Satisfactory3DMap]" << std::endl;
    if (argc != 2) {
        std::cout << "Usage: Satisfactory3DMap <filename>" << std::endl;
        return 1;
    }
    std::string filename(argv[1]);

    try {
        Satisfactory3DMap::SaveGame s(filename);
        s.printHeader();

        Satisfactory3DMap::MapWindow window;
        window.run();
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "Exception: Unknown error!" << std::endl;
        return 1;
    }

    return 0;
}
