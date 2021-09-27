precision mediump float;

uniform mat4 u_modelMatrix;
uniform vec3 u_cameraPosition;

uniform sampler2D u_mainTexture;
uniform sampler2D u_normalMap;

uniform vec3 u_specularColor;
uniform float u_shininess;

uniform struct Light
{
	vec3 position;
	vec3 color;
	float intensity;
	float attenuation;
	float ambientCoefficient;
	float radius;
} light1, light2;

varying vec3 v_vertPos;
varying vec2 v_texCoord;
varying vec3 v_fragNormal;
varying vec4 v_fragColor;

varying vec3 v_tangent;
varying vec3 v_bitangent;
varying mat3 TBN;

vec3 surfaceNormal;
vec3 surfacePos;
vec4 surfaceColor;
vec3 surfaceToLight;
vec3 surfaceToCamera;

vec3 getDiffuseColor(Light p_light)
{
	float diffuseCoefficient = max(0.0, dot(surfaceNormal, surfaceToLight));
	vec3 diffuseColor = diffuseCoefficient * surfaceColor.rgb * p_light.color * p_light.intensity;
	return diffuseColor;
}

vec3 getSpecularColor(Light p_light)
{
	float specularCoefficient = 0.0;
	//if(diffuseCoefficient > 0.0)
	{
		vec3 incidenceVector = -surfaceToLight;
		vec3 reflectionVector = reflect(incidenceVector, surfaceNormal);
		float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
		specularCoefficient = pow(cosAngle, u_shininess);
	}
	
	vec3 specularColor = specularCoefficient * u_specularColor * p_light.color * p_light.intensity;
	return specularColor;
}

vec3 getSurfaceColor(Light p_light)
{
	//surfaceNormal = normalize(mat3(u_modelMatrix) * v_fragNormal);
	surfacePos = vec3(u_modelMatrix * vec4(v_vertPos, 1.0));
	surfaceColor = texture2D(u_mainTexture, v_texCoord).bgra;
	surfaceToLight = normalize(p_light.position - surfacePos);
	surfaceToCamera = normalize(u_cameraPosition - surfacePos);
	
	//surfaceNormal = normalize(TBN * texture2D(u_normalMap, v_texCoord).bgr * 2.0 - 1.0);
	surfaceNormal = normalize(texture2D(u_normalMap, v_texCoord).bgr * 2.0 - 1.0);
	
	vec3 diffuseColor = getDiffuseColor(p_light);
	vec3 specularColor = getSpecularColor(p_light);
	
	float normalToLightDot = dot(surfaceToLight, normalize(mat3(u_modelMatrix) * v_fragNormal));
	if(normalToLightDot <= 0.0)
	{
		diffuseColor = vec3(0.0);
		specularColor = vec3(0.0);
	}
	
	return diffuseColor + specularColor;
}

void main()
{
	vec3 light1NormalMap = getSurfaceColor(light1);
	vec3 light2NormalMap = getSurfaceColor(light2);
	
	gl_FragColor = vec4((surfaceColor.rgb * 0.5) + (light1NormalMap + light2NormalMap), 1.0);
	//gl_FragColor = vec4(surfaceNormal, 1.0);
}
