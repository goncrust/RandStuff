#version 330 core

in vec3 Pos;
uniform float ScaleX;
uniform float ScaleY;

void main() {
    gl_Position = vec4(ScaleX*Pos.x, ScaleY*Pos.y, Pos.z, 1.0);
}