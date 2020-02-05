#version 400

in vec3 Position;
in vec3 Normal;
in vec2 TexCoords;

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

layout( location = 0 ) out vec4 FragColor;

float attenuation(float dist)
{
    return 1 + 0.045 * dist + 0.0075 * dist * dist;
}

vec3 ads()
{
    // return Normal;
    vec4 objectColor4 = texture(texture_diffuse1, TexCoords);
    if(objectColor4.a<0.7)
        discard;
    vec3 objectColor = vec3(objectColor4);

    vec3 lightDirection = normalize( vec3( Spot.position ) - Position );
    float angle = acos( dot(-lightDirection, Spot.direction) );
    float cutoff = radians( clamp( Spot.cutoff, 0, 90 ) );
    vec3 ambient = Ka;

    if(angle < cutoff)
    {
        // float spotFactor = pow( dot(-lightDirection, Spot.direction), Spot.exponent);
        float spotFactor = cutoff-angle;
        vec3 viewDirection = normalize(ViewPosition - vec3(-Position));
        vec3 halfwayDirection = normalize(viewDirection+lightDirection);
        vec3 reflectDirection = reflect(-lightDirection, Normal);
        float lightDistance = length( vec3( Spot.position ) - Position);
        vec3 spotFinalIntensity = spotFactor * Spot.intensity / attenuation(lightDistance);
        vec3 diffuse  = spotFinalIntensity * Kd * max(dot(lightDirection, Normal), 0);
        vec3 specular = spotFinalIntensity * Ks * pow(max(dot(viewDirection, reflectDirection), 0),Shininess);

        return objectColor * ambient + objectColor * specular + diffuse;
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