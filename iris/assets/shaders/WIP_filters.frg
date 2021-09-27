precision mediump float;

uniform sampler2D u_mainTexture;
uniform sampler2D u_normalMap;

uniform mat4 u_modelMatrix;

varying vec3 v_vertexPos;
varying vec2 v_texCoord;
varying vec4 v_fragColor;
varying vec2 v_fragNormal;

varying float v_zDepth;

const float offset = 1.0 / 300.0;
vec2 offsets[9];
float kernel[9];


void main()
{
	//gl_FragColor = texture2D(u_mainTexture, v_texCoord).rgba * v_fragColor;
	
	//float gray = dot(texture2D(u_mainTexture, v_texCoord).rgb, vec3(0.199, 0.587, 0.114));
	//gl_FragColor = vec4(gray, gray, gray, 1.0) * v_fragColor;
	
	//vec4 texelColor = texture2D(u_mainTexture, v_texCoord).rgba;
	//vec4 scaledColor = texelColor * vec4(0.3, 0.59, 0.11, 1.0);
	//float luminance = scaledColor.r + scaledColor.g + scaledColor.b;
	//gl_FragColor = vec4(vec3(luminance), texelColor.a);
	
	vec4 texelColor = texture2D(u_mainTexture, v_texCoord).rgba;
	//gl_FragColor = vec4(vec3(1.0 - texelColor.rgb), texelColor.a);
	
	//float avg = (texelColor.r + texelColor.g + texelColor.b) / 3.0;
	//gl_FragColor = vec4(vec3(avg), 1.0);
	
	//float avg = 0.2126 * texelColor.r + 0.7152 * texelColor.g + 0.0722 * texelColor.b;
	//gl_FragColor = vec4(vec3(avg), 1.0);	

	offsets[0] = vec2(-offset,  offset); // top-left
	offsets[1] = vec2( 0.0,    offset); // top-center
	offsets[2] = vec2( offset,  offset); // top-right
	offsets[3] = vec2(-offset,  0.0);   // center-left
	offsets[4] = vec2( 0.0,    0.0);   // center-center
	offsets[5] = vec2( offset,  0.0);   // center-right
	offsets[6] = vec2(-offset, -offset); // bottom-left
	offsets[7] = vec2( 0.0,   -offset); // bottom-center
	offsets[8] = vec2( offset, -offset);  // bottom-right
	
	//kernel[0] = -1.0;
	//kernel[1] = -1.0;
	//kernel[2] = -1.0;
	//kernel[3] = -1.0;
	//kernel[4] =  9.0;
	//kernel[5] = -1.0;
	//kernel[6] = -1.0;
	//kernel[7] = -1.0;
	//kernel[8] = -1.0;
	
	kernel[0] = 1.0 / 36.0;
	kernel[1] = 2.0 / 36.0;
	kernel[2] = 1.0 / 36.0;
	kernel[3] = 2.0 / 36.0;
	kernel[4] = 4.0 / 36.0;
	kernel[5] = 2.0 / 36.0;
	kernel[6] = 1.0 / 36.0;
	kernel[7] = 2.0 / 36.0;
	kernel[8] = 1.0 / 36.0;
	
	//kernel[0] = 1.0;
	//kernel[1] = 1.0;
	//kernel[2] = 1.0;
	//kernel[3] = 1.0;
	//kernel[4] = 8.0;
	//kernel[5] = 1.0;
	//kernel[6] = 1.0;
	//kernel[7] = 1.0;
	//kernel[8] = 1.0;
	
	vec3 sampleTex[9];
	for(int i = 0; i < 9; i++)
	{
		sampleTex[i] = vec3(texture2D(u_mainTexture, v_texCoord.xy + offsets[i]));
	}
	
	vec3 col = vec3(0.0);
	for(int i = 0; i < 9; i++)
	{
		col += sampleTex[i] * kernel[i];
	}

	gl_FragColor = vec4(vec3(col), 1.0);
}
