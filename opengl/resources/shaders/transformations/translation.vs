#version 330 core

layout(location = 0) in vec3 Pos;
uniform mat4 TranslationMatrix;

void main() {
    gl_Position = TranslationMatrix * vec4(Pos.x, Pos.y, Pos.z, 1.0);
                                    //vec4(Pos, 1.0)
}