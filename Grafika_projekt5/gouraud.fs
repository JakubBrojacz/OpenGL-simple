#version 400

in vec4 Intensity;
in vec2 TexCoords;

uniform sampler2D texture_diffuse1;

layout( location = 0 ) out vec4 FragColor;


void main()
{
    vec4 objectColor = texture(texture_diffuse1, TexCoords);
    if(objectColor.a<0.7)
        discard;

    FragColor = objectColor * Intensity;
}