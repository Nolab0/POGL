#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float fogStart;
uniform float temperature;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 color;

out vec2 fragUV;
out vec3 fragNormal;
out vec3 fragColor;
out float fogStartDistance;
out float fragTemperature;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    fragUV = uv;
    fragNormal = normal;
    fragColor = color;
    fogStartDistance = fogStart;
    fragTemperature = temperature;
}
