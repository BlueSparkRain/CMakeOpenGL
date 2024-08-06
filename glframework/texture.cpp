#include"texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include"../application/stb_image.h"


Texture::Texture(const std::string& path, unsigned int unit)
{
	mUnit = unit;
	//stbImage读取图片
	int  channeles;

	//反转y轴
	stbi_set_flip_vertically_on_load(true);

	unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &channeles, STBI_rgb_alpha);

	//2.生成纹理并且激活单元绑定
	glGenTextures(1, &mTexture);
	//激活纹理单元
	glActiveTexture(GL_TEXTURE0 + mUnit);
	//绑定纹理对象（这里绑的是0号单元）
	glBindTexture(GL_TEXTURE_2D, mTexture);

	//3,传输纹理数据,开辟显存
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//4.释放数据***
	stbi_image_free(data);

	//设置纹理的过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	//设置纹理的包裹方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);//U
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);//V
};
Texture:: ~Texture()
{
	if(mTexture!=0)
	{
		glDeleteTextures(1, &mTexture);
	
	}


};
void  Texture::bind()
{
	//先切换纹理单元，再绑定texture对象
	glActiveTexture(GL_TEXTURE + mUnit);
	glBindTexture(GL_TEXTURE_2D, mTexture);

}