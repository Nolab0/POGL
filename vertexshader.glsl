#version 330 core

in vec4 position;

void main() {
    gl_Position = position;
    gl_Position.y *= -1.0; // Flip the y-coordinate
}