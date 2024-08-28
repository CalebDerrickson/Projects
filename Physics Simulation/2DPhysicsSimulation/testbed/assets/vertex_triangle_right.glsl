#version 330 core

// Attribute locations
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 color;
out vec3 ourColor;

uniform mat4 transform; // set in code

void main() {
    gl_Position = transform * vec4(aPos, 1.0);

    ourColor = vec3(0.0, 1.0, 0.0);
}