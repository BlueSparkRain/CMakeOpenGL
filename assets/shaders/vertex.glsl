#version 440 core
in vec3 aPos;
in vec3 aColor;
layout(location=2)in vec2 aUV;

out vec3 color;
out vec2 uv;

uniform float time;
uniform float speed;

void main() 
{
float dx=0.3;
float offset=sin(time*speed)*dx;

//gl_Position = vec4(aPos.x+offset,aPos.y + offset,aPos.z+offset, 1.0);
gl_Position = vec4(aPos.x,aPos.y,aPos.z, 1.0);

//UVÆ«ÒÆÖµ
float deltaU=time*0.3f;

color=aColor;
uv= vec2( aUV.x+deltaU,aUV.y);

};

	
