#version 330 core

out vec4 fragColor;

in vec4 color;
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixVal;

void main() {
    // fragColor = texture(texture1, TexCoord);
    vec4 color1 = texture(texture1, TexCoord);
    vec4 color2 = texture(texture2, TexCoord);

    fragColor = mix(color1, color2, mixVal);

}