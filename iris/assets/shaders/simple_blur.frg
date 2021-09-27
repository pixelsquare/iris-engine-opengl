precision mediump float;

uniform mat4 u_modelMatrix;
uniform mat4 u_viewMatrix;
uniform mat4 u_projectionMatrix;
uniform mat4 u_mvp;

uniform float u_time;

struct Material
{
    float shininess;
    vec4 color;

    sampler2D mainTexture;
    sampler2D specularMap;
    sampler2D normalMap;
    sampler2D displacementMap;

}; uniform Material material;

varying vec3 v_vertexPos;
varying vec2 v_texCoord;
varying vec4 v_fragColor;
varying vec3 v_fragNormal;

const float offset = 1.0 / 64.0;

void main()
{
    vec2 offsets[9];
    offsets[0] = vec2(-offset, offset);
    offsets[1] = vec2(0.0, offset);
    offsets[2] = vec2(offset, offset);
    offsets[3] = vec2(-offset, 0.0);
    offsets[4] = vec2(0.0, 0.0);
    offsets[5] = vec2(offset, 0.0);
    offsets[6] = vec2(-offset, -offset);
    offsets[7] = vec2(0.0, -offset);
    offsets[8] = vec2(offset, -offset);

    float blurAmt = 16.0;
    float kernel[9];
    kernel[0] = 1.0 / blurAmt;
    kernel[1] = 2.0 / blurAmt;
    kernel[2] = 1.0 / blurAmt;
    kernel[3] = 2.0 / blurAmt;
    kernel[4] = 4.0 / blurAmt;
    kernel[5] = 2.0 / blurAmt;
    kernel[6] = 1.0 / blurAmt;
    kernel[7] = 2.0 / blurAmt;
    kernel[8] = 1.0 / blurAmt;

    vec3 texture[9];
    for(int i = 0; i < 9; i++)
    {
        texture[i] = vec3(texture2D(material.mainTexture, v_texCoord.st + offsets[i]).rgb);
    }

    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    {
         col += texture[i] * kernel[i];
    }

    gl_FragColor = vec4(col, 1.0);
}
