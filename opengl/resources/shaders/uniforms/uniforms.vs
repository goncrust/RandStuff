#version 330 core
#extension GL_ARB_explicit_uniform_location : enable

layout(location = 0) in vec3 Pos;
layout(location = 0) uniform float Scale;

void main() {
    gl_Position = vec4(Scale*Pos.x, Scale*Pos.y, Pos.z, 1.0);
}