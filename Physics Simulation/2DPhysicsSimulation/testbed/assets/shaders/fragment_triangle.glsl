#version 330 core

out vec4 fragColor;

in vec4 color;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;

void main() {
    fragColor = texture(texture1, TexCoord);
}