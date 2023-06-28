#version 330 core

in vec2 fragUV;
in vec3 fragNormal;
in vec3 fragColor;
in float fogStartDistance;
in float fragTemperature;

out vec4 color;

void main() {
    vec3 fogColor = vec3(0.7, 0.7, 0.7);

    float fogDistance = gl_FragCoord.z / gl_FragCoord.w;
    float modifiedFogFactor = clamp((fogDistance - fogStartDistance) / fogStartDistance, 0.0, 1.0);

    color = mix(vec4(fragColor, 1.0), vec4(fogColor, 1.0), modifiedFogFactor);

    if (fragTemperature > 0.0){
        color = vec4(color.r * (1 + fragTemperature / 100), color.g, color.b, 1.0);
    }
    if (fragTemperature < 0.0){
        color = vec4(color.r, color.g, color.b  * (1 + -fragTemperature / 100), 1.0);
    }
}
