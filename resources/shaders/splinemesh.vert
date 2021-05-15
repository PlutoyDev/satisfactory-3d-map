#version 450

struct SplineSegment {
    vec4 p0;
    vec4 p1;
    vec4 t0;
    vec4 t1;
    float length;
    float _padding1_;
    float _padding2_;
    float _padding3_;
};

struct SplineMeshInstance {
    int id;
    int offset0;
    int offset1;
    int _padding1_;
    float t0;
    float t1;
    float _padding2_;
    float _padding3_;
};

layout(std430, binding = 0) readonly buffer Segments { SplineSegment segments[]; };
layout(std430, binding = 1) readonly buffer Instances { SplineMeshInstance instances[]; };

uniform mat4 projMx;
uniform mat4 viewMx;

layout(location = 0) in vec3 in_position;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex_coord;

out vec3 position;
out vec3 normal;
out vec2 tex_coord;
flat out int id;

void deCasteljau(vec3 b0, vec3 b1, vec3 b2, vec3 b3, float t, out vec3 p, out vec3 forward) {
    vec3 b01 = mix(b0, b1, t);
    vec3 b11 = mix(b1, b2, t);
    vec3 b21 = mix(b2, b3, t);

    vec3 b02 = mix(b01, b11, t);
    vec3 b12 = mix(b11, b21, t);

    p = mix(b02, b12, t);
    forward = normalize(b12 - b02);
}

void main() {
    const SplineMeshInstance instance = instances[gl_InstanceID];

    // TODO get x range of model
    // x position relative to model in range [0, 1]
    float modelPos = clamp(in_position.x / 2.0f, 0.0f, 1.0f);
    // x position of current vertex along spline
    float splinePos = instance.t0 + modelPos * (instance.t1 - instance.t0);

    // Determine spline segment
    int segmentIdx = instance.offset0;
    while (splinePos > segments[segmentIdx].length && segmentIdx < instance.offset1 - 1) {
        splinePos -= segments[segmentIdx].length;
        segmentIdx++;
    }

    const SplineSegment segment = segments[segmentIdx];

    const float t = clamp(splinePos / segment.length, 0.0f, 1.0f);

    // Bezier control points
    const vec3 b0 = segment.p0.xyz;
    const vec3 b3 = segment.p1.xyz;
    // Unreal Engine seems to use cubic Hermite splines, convert to Bezier control points.
    const vec3 b1 = b0 + segment.t0.xyz / 3.0f;
    const vec3 b2 = b3 - segment.t1.xyz / 3.0f;

    // De Casteljau
    vec3 p;
    vec3 forward;
    deCasteljau(b0, b1, b2, b3, t, p, forward);

    // TODO need global context for nice up direction
    vec3 up = vec3(0.0f, 0.0f, 1.0f);
    if (abs(abs(dot(forward, up)) - 1.0f) < 0.01f) {
        up = vec3(0.0f, 1.0f, 0.0f);
    }
    vec3 left = normalize(cross(up, forward));
    up = normalize(cross(forward, left));

    vec3 world_pos = p + in_position.y * left + in_position.z * up;
    gl_Position = projMx * viewMx * vec4(world_pos, 1.0f);
    position = world_pos;
    normal = in_normal.x * forward + in_normal.y * left + in_normal.z * up;
    tex_coord = in_tex_coord;
    id = instance.id;
}
