precision mediump float;

uniform sampler2D u_mainTexture;
uniform sampler2D u_normalMap;

uniform mat4 u_modelMatrix;

varying vec3 v_vertexPos;
varying vec2 v_texCoord;
varying vec4 v_fragColor;
varying vec3 v_fragNormal;

void main()
{
    gl_FragColor = v_fragColor;
}
