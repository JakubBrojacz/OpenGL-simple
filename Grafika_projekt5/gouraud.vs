#version 400

layout (location = 0) in vec3 vPosition;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec2 vTexCoords;

out vec2 TexCoords;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;
uniform mat4 ShadowMatrix;

struct SpotLightInfo
{
    vec4 position;
    vec3 intensity;
    vec3 direction;
    float exponent;
    float cutoff;
};

uniform SpotLightInfo Spot[3];
uniform SpotLightInfo Sun;
uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;
uniform float Shininess;

uniform int mode;

uniform vec3 ViewPosition;
uniform float FogIntensity;
uniform float FogStart;
uniform float FogEnd;

uniform sampler2D texture_diffuse1;

out vec4 Intensity;

float attenuation(float dist)
{
    return 1 + 0.007 * dist + 0.0002 * dist * dist;
}

vec3 ads(vec3 Normal, vec3 Position)
{
    vec3 ambient = Ka;
    vec3 specular = vec3(0);
    vec3 diffuse = vec3(0);

    // // sun
    { 
        vec3 lightDirection = normalize( vec3( Sun.direction ) );
        vec3 v = normalize(vec3(-Position));
        vec3 r = reflect(-lightDirection, Normal);
        diffuse += Sun.intensity * Kd * max(dot(lightDirection, Normal), 0);
        specular += Sun.intensity * Ks * pow(max(dot(r, v), 0), Shininess);
    }

    // reflector
    for(int i=0;i<3;i++)
    {
        vec3 lightDirection = normalize( vec3( Spot[i].position ) - Position );
        float angle = acos( dot(-lightDirection, Spot[i].direction) );
        float cutoff = radians( clamp( Spot[i].cutoff, 0, 90 ) );

        float spotFactorSpecular = pow( dot(-lightDirection, Spot[i].direction), Spot[i].exponent);
        float spotFactor = cutoff-angle;
        float lightDistance = length( vec3( Spot[i].position ) - Position);
        vec3 spotFinalIntensity = spotFactor * Spot[i].intensity / attenuation(lightDistance);
        vec3 spotFinalIntensitySpecular = spotFactorSpecular * Spot[i].intensity / attenuation(lightDistance);
                
        vec3 viewDirection = normalize(ViewPosition - vec3(Position));
        if(mode == 0)
        {
            // return viewDirection;

            vec3 h = normalize(lightDirection + viewDirection);
            specular += spotFinalIntensitySpecular * Ks * pow(max(dot(h, Normal), 0), Shininess);
        }
        else
        {
            vec3 reflectDir = reflect(-lightDirection, Normal);
            float reflectAngle = max(dot(reflectDir, viewDirection), 0);
            // return viewDirection;
            // return reflectDir;
            // return vec3(max(dot(reflectDir, viewDirection), 0), max(dot(reflectDir, viewDirection), 0), max(dot(reflectDir, viewDirection), 0));
            specular += spotFinalIntensitySpecular * Ks * pow(reflectAngle, Shininess);
            // return specular;
        }

        if(angle < cutoff)
        {
            
            
            
            
            diffuse += spotFinalIntensity * Kd * max(dot(lightDirection, Normal), 0);
        }
    }

    return clamp((ambient + specular + diffuse), 0, 1);
}

float fog(vec3 viewPos, vec3 pos)
{
    return min((FogEnd - length(viewPos - pos)) / (FogEnd - FogStart), 1);
}

void main()
{
    vec3 Normal = normalize(NormalMatrix*vNormal);
    vec3 Position = vec3(ModelViewMatrix * vec4(vPosition, 1));
    TexCoords = vTexCoords;
    
    Intensity = vec4(ads(Normal, Position), 1);
    Intensity = FogIntensity*fog(ViewPosition, Position)*Intensity + (1 - FogIntensity)*Intensity;

    gl_Position = MVP * vec4(vPosition, 1);
}