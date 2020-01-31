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

uniform sampler2D texture_diffuse1;

layout( location = 0 ) out vec4 FragColor;

vec3 phongModel( vec4 position, vec3 norm ) 
{
    vec3 s = normalize(vec3(Light.Position - position));    
    vec3 v = normalize(-position.xyz);    
    vec3 r = reflect( -s, norm );    
    vec3 ambient = Light.La * Material.Ka;    
    float sDotN = max( dot(s,norm), 0.0 );    
    vec3 diffuse = Light.Ld * Material.Kd * sDotN;    
    vec3 spec = vec3(0.0);    
    if( sDotN > 0.0 )        
    {
        spec = Light.Ls * Material.Ks * pow( max( dot(r,v), 0.0 ), Material.Shininess );
    }
    return ambient + diffuse + spec; 
}

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
    vec3 ambient = objectColor * Ka;

    if(angle < cutoff)
    {
        float spotFactor = pow( dot(-s, Spot.direction), Spot.exponent);
        vec3 v = normalize(vec3(-Position));
        vec3 h = normalize(v+s);
        // return Normal;
        // return vec3(max(dot(s, Normal), 0), max(dot(s, Normal), 0), max(dot(s, Normal), 0));
        return ambient + spotFactor * Spot.intensity * (Kd * max(dot(s, Normal), 0) + Ks * pow(max(dot(h, Normal), 0), Shininess));
    }
    else
    {
        return ambient;
    }
}

void main()
{
    FragColor = vec4(ads(), 1);
}