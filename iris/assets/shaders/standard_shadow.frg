precision mediump float;

#define MAX_LIGHT_COUNT 8

#define LIGHT_TYPE_DIRECTIONAL  1
#define LIGHT_TYPE_POINT        2
#define LIGHT_TYPE_SPOT         3

#define POINT_LIGHT_CONSTANT    1.0
#define POINT_LIGHT_LINEAR      0.9
#define POINT_LIGHT_QUADRATIC   0.032

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_mvp;

uniform float u_time;
uniform int u_lightCount;
uniform vec3 u_cameraPosition;

struct Material
{
    float shininess;
    vec4 color;

    sampler2D mainTexture;
    sampler2D specularMap;
    sampler2D normalMap;
    sampler2D displacementMap;
	sampler2D shadowMap;

}; uniform Material material;

struct Light
{
    int type;

    mat4 viewMatrix;
    mat4 projectionMatrix;
    mat4 lightSpaceMatrix;

    vec3 position;
    vec3 direction;

    vec4 color;
    float range;
    float intensity;

    float spotAngleInner;
    float spotAngleOuter;

    float ambientStrength;

    vec4 specularColor;
    float specularStrength;

}; uniform Light light[MAX_LIGHT_COUNT];

varying vec3 v_vertexPos;
varying vec2 v_texCoord;
varying vec4 v_fragColor;
varying vec3 v_fragNormal;

varying vec3 v_tangent;
varying vec3 v_bitangent;
varying mat3 v_tbn;

varying vec4 v_shadowCoord;

// Local Vars

vec3 surfaceNormal;
vec3 surfacePos;
vec4 surfaceColor;
vec3 surfaceToLight;
vec3 surfaceToCamera;

vec3 tangentNormal;
vec3 tangentPos;
vec3 tangentToLight;
vec3 tangentToCamera;

vec4 getAmbientColor(Light p_light)
{
    return vec4(vec3(p_light.ambientStrength * p_light.color * p_light.intensity), 1.0);
}

vec4 getDiffuseColor(Light p_light)
{
    float diffuseColor = max(dot(surfaceNormal, surfaceToLight), 0.0);
    return vec4(vec3(diffuseColor * p_light.color * p_light.intensity), 1.0);
}

vec4 getSpecularColor(Light p_light)
{
    vec4 specularColor = texture2D(material.specularMap, v_texCoord).bgra;

    vec3 incidenceVector = -surfaceToLight;
    vec3 reflectionVector = reflect(incidenceVector, surfaceNormal);

    float cosineAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
    float specular = pow(cosineAngle, p_light.specularStrength);
    return vec4(vec3(specularColor * material.shininess * specular * p_light.specularColor * p_light.intensity), 1.0);
}

float CalculateShadow(vec4 p_fragPosLightSpace)
{
	vec3 projCoords = p_fragPosLightSpace.xyz / p_fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;
	float closestDepth = texture2D(material.shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	float shadow = currentDepth > closestDepth ? 1.0 : 0.5;
	return shadow;
}

vec4 getSurfaceColor(Light p_light)
{
    vec4 finalColor = vec4(1.0, 0.0, 1.0, 1.0);

    surfacePos      = vec3(u_modelMatrix * vec4(v_vertexPos, 1.0));
    surfaceColor    = texture2D(material.mainTexture, v_texCoord).bgra;

    if(p_light.type == LIGHT_TYPE_DIRECTIONAL)
    {
        surfaceToLight = normalize(p_light.direction);
    }
    else
    {
        surfaceToLight  = normalize(p_light.position - surfacePos);
    }

    surfaceToCamera = normalize(u_cameraPosition - surfacePos);
    surfaceNormal   = normalize(mat3(u_modelMatrix) * v_fragNormal);

    tangentToLight = normalize(v_tbn * surfaceToLight);
    tangentToCamera = normalize(v_tbn * surfaceToCamera);

    tangentNormal = normalize(texture2D(material.normalMap, v_texCoord).bgr * 2.0 - 1.0);
    tangentNormal = normalize(v_tbn * tangentNormal);

    //surfaceToLight = tangentToLight;
    //surfaceToCamera = tangentToCamera;
    surfaceNormal = tangentNormal;

    vec4 ambientColor = getAmbientColor(p_light);
    vec4 diffuseColor = getDiffuseColor(p_light);
    vec4 specularColor = getSpecularColor(p_light);

    if(p_light.type == LIGHT_TYPE_POINT || p_light.type == LIGHT_TYPE_SPOT)
    {
        float distance = length(p_light.position - surfacePos) / p_light.range;
        float attenuation = 1.0 / (POINT_LIGHT_CONSTANT + POINT_LIGHT_LINEAR *
                            distance + POINT_LIGHT_QUADRATIC * (distance * distance));

        ambientColor *= attenuation;
        diffuseColor *= attenuation;
        specularColor *= attenuation;

        if(p_light.type == LIGHT_TYPE_SPOT)
        {
            float innerAngle = cos(radians(p_light.spotAngleInner));
            float outerAngle = cos(radians(p_light.spotAngleOuter));

            float theta = dot(surfaceToLight, normalize(p_light.direction));
            float epsilon = innerAngle - outerAngle;
            float intensity = clamp((theta - outerAngle) / epsilon, 0.0, 1.0);

            ambientColor *= intensity;
            diffuseColor *= intensity;
            specularColor *= intensity;
        }
    }	
	
	//float visibility = 1.0;
	//if(texture2D(material.shadowMap, v_shadowCoord.xy).z < v_shadowCoord.r)
	//{
	//	visibility = 0.1;
	//}

	float shadow = CalculateShadow(v_shadowCoord);
    vec4 lightColor = diffuseColor + specularColor;
    finalColor = ambientColor + (1.0 - shadow) * lightColor * surfaceColor * v_fragColor * material.color;
	
    return finalColor;
}

vec4 getFinalColor()
{
    vec4 finalColor = vec4(1.0, 0.0, 1.0, 1.0);

    finalColor = vec4(0.0);
    for(int i = 0; i < u_lightCount; i++)
    {
        finalColor += getSurfaceColor(light[i]);
    }

    return finalColor;
}

void main()
{
    gl_FragColor = getFinalColor();
	//gl_FragColor = texture2D(material.shadowMap, v_shadowCoord.xy).rgba;
	//gl_FragColor = vec4(texture2D(material.shadowMap, v_shadowCoord.xy).zzz, 1.0);
	//gl_FragColor = vec4(v_shadowCoord.rrr, 1.0);
	//gl_FragColor = vec4(texture2D(material.shadowMap, v_texCoord).rrr, 1.0);
}
