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

void main()
{
	//surfaceNormal = normalize(mat3(u_modelMatrix) * v_fragNormal);
	surfacePos = vec3(u_modelMatrix * vec4(v_vertPos, 1.0));
	surfaceColor = texture2D(u_mainTexture, v_texCoord).bgra;
	surfaceToLight = normalize(light1.position - surfacePos);
	surfaceToCamera = normalize(u_cameraPosition - surfacePos);
	
	surfaceNormal = normalize(texture2D(u_normalMap, v_texCoord).bgr * 2.0 - 1.0);
	
	float diffuseCoefficient = max(0.0, dot(surfaceNormal, surfaceToLight));
	vec3 diffuseColor = diffuseCoefficient * surfaceColor.rgb * light1.color * light1.intensity;
	
	float specularCoefficient = 0.0;
	//if(diffuseCoefficient > 0.0)
	{
		vec3 incidenceVector = -surfaceToLight;
		vec3 reflectionVector = reflect(incidenceVector, surfaceNormal);
		float cosAngle = max(0.0, dot(surfaceToCamera, reflectionVector));
		specularCoefficient = pow(cosAngle, u_shininess);
	}
	
	vec3 specularColor = specularCoefficient * u_specularColor * light1.color * light1.intensity;	
	
	float normalToLightDot = dot(surfaceToLight, normalize(mat3(u_modelMatrix) * v_fragNormal));
	if(normalToLightDot < 0.0)
	{
		diffuseColor = vec3(0.0);
		specularColor = vec3(0.0);
	}

	mat3 modelMatrixView3 = mat3(u_modelMatrix);	
	vec3 cameraSpaceNormal = modelMatrixView3 * normalize(v_fragNormal);
	vec3 cameraSpaceTangent = modelMatrixView3 * normalize(v_tangent);
	vec3 cameraSpaceBitangent = modelMatrixView3 * normalize(v_bitangent);
	
	mat3 tbn = mat3(cameraSpaceTangent, cameraSpaceBitangent, cameraSpaceNormal);
	
	//gl_FragColor = vec4(vec3(v_bitangent * v_tangent * v_fragNormal), 1.0);
	//gl_FragColor = vec4(normalize(tbn * texture2D(u_normalMap, v_texCoord).bgr * 2.0 - 1.0), 1.0);
	gl_FragColor = vec4((surfaceColor.rgb * 0.5) + diffuseColor + specularColor, 1.0);
	//gl_FragColor = vec4(surfaceNormal, 1.0);
}
