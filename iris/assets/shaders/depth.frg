precision mediump float;

#define MAX_LIGHT_COUNT 8

#define LIGHT_TYPE_DIRECTIONAL 	1
#define LIGHT_TYPE_POINT 		2
#define LIGHT_TYPE_SPOT			3

#define POINT_LIGHT_CONSTANT 	1.0
#define POINT_LIGHT_LINEAR 		0.9
#define POINT_LIGHT_QUADRATIC	0.032

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_mvp;

uniform int u_lightCount;
uniform vec3 u_cameraPosition;

struct Material
{
    sampler2D mainTexture;
    sampler2D specularMap;
    sampler2D normalMap;
    float shininess;

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

float near = 0.1;
float far = 100.0;

float linearizeDepth(float p_depth)
{
	float z = p_depth * 2.0 - 1.0;
	return (2.0 * near * far) / (far + near - z * (far - near));
}

void main()
{
    //gl_FragColor = texture2D(material.mainTexture, v_texCoord).rgba * v_fragColor;
    //gl_FragColor = vec4(vec3(gl_FragCoord.z), 1.0);
	//gl_FragColor = vec4(vec3(texture2D(material.mainTexture, v_texCoord).r), 1.0);
	//gl_FragColor = texture2D(material.mainTexture, v_texCoord).rgba;
	//gl_FragColor = vec4(vec3(gl_FragCoord.z), 1.0);

	float depth = (linearizeDepth(gl_FragCoord.z) / far);
	gl_FragColor = vec4(vec3(depth), 1.0);
	
	//float depth = texture2D(material.mainTexture, v_texCoord).r;
	//gl_FragColor = vec4(vec3(depth), 1.0);
}
