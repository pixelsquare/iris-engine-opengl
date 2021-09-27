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

varying vec3 v_vertexPos;
varying vec2 v_texCoord;
varying vec4 v_fragColor;
varying vec3 v_fragNormal;

void main()
{
    gl_FragColor = texture2D(material.mainTexture, v_texCoord).rgba * v_fragColor;
}
