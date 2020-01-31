#version 330 core
out vec4 FragColor;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec4 FragPosLightSpace;
    vec2 TexCoords;
} fs_in;

uniform sampler2D shadowMap;
uniform samplerCube depthMap;

uniform sampler2D texture_diffuse1;

uniform vec3 lightPos;
uniform vec3 lightPosCar;
uniform vec3 viewPos;
uniform vec3 lightColor;

uniform float far_plane;


float ShadowCalculationCar(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    //if(closestDepth==1.0)
    //    return 1.0;
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPosCar - fs_in.FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    float shadow = currentDepth - bias > closestDepth  ? 1.0 : currentDepth;
    // PCF
    //float shadow = 0.0;
    //vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    //for(int x = -1; x <= 1; ++x)
    //{
    //    for(int y = -1; y <= 1; ++y)
    //    {
    //        float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
    //        shadow += currentDepth - bias > pcfDepth  ? 1.0 : currentDepth;        
    //    }    
    //}
    //shadow /= 9.0;
    
    // keep the shadow at 1.0 when outside the far_plane region of the light's frustum.
    //if(projCoords.z > 1.0)
    //    shadow = 1.0;
    if(projCoords.z < 0.1)
        shadow = 1.0;
        
    return shadow;
}


float ShadowCalculation(vec3 fragPos)
{
    // get vector between fragment position and light position
    vec3 fragToLight = fragPos - lightPos;
    // use the fragment to light vector to sample from the depth map    
    float closestDepth = texture(depthMap, fragToLight).r;
    // it is currently in linear range between [0,1], let's re-transform it back to original depth value
    closestDepth *= far_plane;
    // now get current linear depth as the length between the fragment and light position
    float currentDepth = length(fragToLight);
    // test for shadows
    float bias = 0.5; // we use a much larger bias since depth is now in [near_plane, far_plane] range
    float shadow = currentDepth -  bias > closestDepth ? 1.0 : currentDepth;
    return shadow;
}

void main()
{           
    vec4 objectColor4 = texture(texture_diffuse1, fs_in.TexCoords);
    if(objectColor4.a<0.7)
        discard;
    vec3 objectColor = vec3(objectColor4);
    vec3 normal = normalize(fs_in.Normal);
    // ambient
    //vec3 ambient = vec3(0,0,0);
    vec3 ambient =  0.3*objectColor;
    // diffuse
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * lightColor;
    vec3 lightDirCar = normalize(lightPosCar - fs_in.FragPos);
    float diffCar = max(dot(lightDirCar, normal), 0.0);
    vec3 diffuseCar = diffCar * lightColor;
    // specular
    vec3 viewDir = normalize(viewPos - fs_in.FragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    spec = pow(max(dot(normal, halfwayDir), 0.0), 64.0);
    vec3 specular = spec * lightColor;    
    // calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPos);                      
    float shadowCar = ShadowCalculationCar(fs_in.FragPosLightSpace);                      
    ///float shadow = min(ShadowCalculationCar(fs_in.FragPosLightSpace), ShadowCalculation(fs_in.FragPos));                     
    vec3 lightingCar =  objectColor;     
    vec3 lighting =  objectColor;     
    //vec3 lighting = (1.0 - shadow) * objectColor;     
    
    //FragColor = vec4(lighting, 1.0);
    //FragColor = vec4(lightingCar, 1.0);
    //FragColor = vec4((2.5-length(viewPos-fs_in.FragPos)/2)*max(lighting, lightingCar), 1.0);
    FragColor = vec4(max(lighting, lightingCar), 1.0);
    //FragColor = vec4(ambient, 1.0);
}
