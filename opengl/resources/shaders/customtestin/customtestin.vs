#version 330 core

layout(location = 0) in vec3 Pos;
layout(location = 1) in float Scale;

void main() {
    gl_Position = vec4(Scale*Pos.x, Scale*Pos.y, Pos.z, 1.0);
}