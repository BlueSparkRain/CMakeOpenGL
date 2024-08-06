#pragma once
#include"core.h"
#include<string>
class Shader
{
public :
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void begin();//开始使用给当前Shader

	void end();//结束使用给当前Shader

	void setFoat(const std::string& name, float value);

	void setVector3(const std::string& name, float x, float y, float z);

	void setInt(const std::string& name, int value);

private:
	void checkShaderErrors(GLuint traget, std::string type);

public:
	GLuint mProgram{ 0 };

		
	
};