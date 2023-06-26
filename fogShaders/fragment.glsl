#version 330 core

in vec2 fragUV;
in vec3 fragNormal;
in vec3 fragColor;
in float fogStartDistance;

out vec4 color;

void main() {
    vec3 fogColor = vec3(0.7, 0.7, 0.7);

    float fogDistance = gl_FragCoord.z / gl_FragCoord.w;
    float modifiedFogFactor = clamp((fogDistance - fogStartDistance) / fogStartDistance, 0.0, 1.0);

    color = mix(vec4(fragColor, 1.0), vec4(fogColor, 1.0), modifiedFogFactor);
}
