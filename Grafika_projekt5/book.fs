#version 400

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;
in vec4 ShadowCoord;

struct SpotLightInfo
{
    vec4 position;
    vec3 intensity;
    vec3 direction;
    float exponent;
    float cutoff;
};

uniform SpotLightInfo Spot;
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shininess;

uniform vec3 ViewPosition;
uniform float FogIntensity;
uniform float FogStart;
uniform float FogEnd;

uniform sampler2D texture_diffuse1;

uniform sampler2DShadow ShadowMap;

layout( location = 0 ) out vec4 FragColor;



vec3 ads()
{
    // return Normal;
    vec4 objectColor4 = texture(texture_diffuse1, TexCoords);
    if(objectColor4.a<0.7)
        discard;
    vec3 objectColor = vec3(objectColor4);

    vec3 s = normalize( vec3( Spot.position ) - Position );
    float angle = acos( dot(-s, Spot.direction) );
    float cutoff = radians( clamp( Spot.cutoff, 0, 90 ) );
    vec3 ambient = Ka;

    if(true)
    {
        // float spotFactor = pow( (dot(-s, Spot.direction), Spot.exponent);
        // float spotFactor = cutoff-angle;
        // vec3 v = normalize(vec3(-Position));
        // vec3 h = normalize(v+s);
        // vec3 specular = spotFactor * Spot.intensity * Kd * max(dot(s, Normal), 0);
        // vec3 diffuse = spotFactor * Spot.intensity* Ks * pow(max(dot(h, Normal), 0), Shininess);
        vec3 specular = ambient;
        vec3 diffuse = ambient;

        float shadow = textureProj(ShadowMap, ShadowCoord);
        // return vec3(shadow, shadow, shadow);

        return objectColor * ambient + objectColor * shadow * ambient;
    }
    else
    {
        return objectColor * ambient;
    }
}

float fog(vec3 viewPos, vec3 pos)
{
    return min((FogEnd - length(viewPos - pos)) / (FogEnd - FogStart), 1);
}

void main()
{
    vec4 c = vec4(ads(), 1);
    FragColor = FogIntensity*fog(ViewPosition, Position)*c + (1 - FogIntensity)*c;
}