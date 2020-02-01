#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoords;
out vec4 ShadowCoord;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;
uniform mat4 ShadowMatrix;

void main()
{
    Normal = normalize(NormalMatrix*vNormal);
    Position = vec3(ModelViewMatrix * vec4(vPosition, 1));
    TexCoords = vTexCoords;
    ShadowCoord = ShadowMatrix * vec4(vPosition, 1.0);
    gl_Position = MVP * vec4(vPosition, 1);
}