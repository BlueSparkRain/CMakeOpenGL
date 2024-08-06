#version 440 core
out vec4 FragColor;

in vec3 color;
in vec2 uv;
in vec3 position;

uniform float time;
uniform vec3 uColor;

uniform sampler2D sampler;
//将sampler当做一个int整数，通过外界输入0,1,2，...15等数字
//一个sampler是被三角形上所有像素所公用的，所以是uniform类型
uniform sampler2D waterSampler;
uniform sampler2D orangeSampler;
uniform sampler2D noiseSampler;


void main() 
{
  
 //FragColor=texture(sampler,uv);//texture采样函数，返回vec4
 vec4 waterColor=texture(waterSampler,uv);
 vec4 orangeColor=texture(orangeSampler,uv);
 vec4 noiseColor=texture(noiseSampler,uv);

 vec4 blendColor=orangeColor*(1-noiseColor.r)+waterColor*noiseColor.r;

 float weight=1-noiseColor.r;

 //mix(Color1,Color2,(后者的)weight);
 vec4 mixColor=mix(waterColor,orangeColor,weight);



 FragColor=vec4(mixColor.rgb,1.0f);

};