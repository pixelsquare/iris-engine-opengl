precision mediump float;

uniform sampler2D u_mainTexture;

varying vec3 v_vertPos;
varying vec2 v_texCoord;
varying vec3 v_fragNormal;
varying vec4 v_fragColor;

void main()
{
	gl_FragColor = texture2D(u_mainTexture, v_texCoord).bgra * v_fragColor;
}
