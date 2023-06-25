#version 330 core

in vec2 fragUV;
in vec3 fragNormal;
in float fogFactor;
in vec3 fragColor;

out vec4 color;

void main() {

    vec3 fogColor = vec3(0.7, 0.7, 0.7);

    float fogStartDistance = 15.0;
    //float fogStartDistance = 500.0;
    float fogDistance = gl_FragCoord.z / gl_FragCoord.w;
    float modifiedFogFactor = clamp((fogDistance - fogStartDistance) / fogStartDistance, 0.0, 1.0);

    color = mix(vec4(fragColor, 1.0), vec4(fogColor, 1.0), modifiedFogFactor);
}
