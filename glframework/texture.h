#pragma once;
#include"core.h"
#include<string>
class Texture
{
public :
	Texture(const std::string& path,unsigned int unit);
	~Texture();

	void bind();//绑定函数，将texture挂到状态机的当前2D纹理上
private :
	GLuint mTexture{ 0 };
	 int mWidth{ 0 };
     int mHeight{ 0 };
	unsigned int mUnit{ 0 }; 

};