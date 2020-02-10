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

layout( location = 0 ) out vec4 FragColor;

float attenuation(float dist)
{
    return 1 + 0.007 * dist + 0.0002 * dist * dist;
}

vec3 ads()
{
    // return Normal;
    vec4 objectColor4 = texture(texture_diffuse1, TexCoords);
    if(objectColor4.a<0.7)
        discard;
    vec3 objectColor = vec3(objectColor4);

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

        if(angle < cutoff)
        {
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
            
            diffuse += spotFinalIntensity * Kd * max(dot(lightDirection, Normal), 0);
        }
    }

    return clamp(objectColor * (ambient + specular + diffuse), 0, 1);
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