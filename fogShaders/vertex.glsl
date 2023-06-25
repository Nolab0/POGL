#version 330 core

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 uv;
layout(location = 2) in vec3 normal;
layout(location = 3) in vec3 color; // Added color attribute

out vec2 fragUV;
out vec3 fragNormal;
out vec3 fragColor; // Added color output
out float fogFactor;

void main() {
    gl_Position = projection * view * model * vec4(position, 1.0);
    fragUV = uv;
    fragNormal = normal;
    fragColor = color;

    // Calculate fog factor based on the vertex's distance from the camera
    float fogStart = 5.0;
    float fogEnd = 10.0;
    float fogDensity = 0.2;
    float fogDistance = length(gl_Position.xyz);
    fogFactor = clamp((fogDistance - fogStart) / (fogEnd - fogStart), 0.0, 1.0);
    fogFactor = 1.0 - exp(-fogDensity * fogDensity * fogDistance * fogDistance);
}
