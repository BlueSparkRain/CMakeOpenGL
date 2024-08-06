#pragma once;
#include"core.h"
#include<string>
class Texture
{
public :
	Texture(const std::string& path,unsigned int unit);
	~Texture();

	void bind();//�󶨺�������texture�ҵ�״̬���ĵ�ǰ2D������
private :
	GLuint mTexture{ 0 };
	 int mWidth{ 0 };
     int mHeight{ 0 };
	unsigned int mUnit{ 0 }; 

};