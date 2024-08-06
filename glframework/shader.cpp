
#include "shader.h"
#include "../wrapper/checkError.h"

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	//声明装入shader代码字符串的两个string
	std::string vertexCode;
	std::string fragmentCode;
	//声明用于读取vs和fs文件的inFileStream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//保证ifstrem遇到问题的时候可以抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		//将文件输入流中的字符串输入到stringStream里面
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//关闭文件
		vShaderFile.close();
		fShaderFile.close();

		//将字符串从stringStream中读取出来，转化到codeString当中
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure& e)
	{
		std::cout << "Error:Shader File Error:" << e.what() <<std::endl;

	}
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	//1.创建shader程序
	GLuint  vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//2.为shader程序输入shader代码
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

	int success = 0;
	char infoLog[1024];

	//3.执行shader代码编译
	glCompileShader(vertex);
	//检查编译结果
	checkShaderErrors(vertex,"COMPILE");

	glCompileShader(fragment);

	checkShaderErrors(fragment, "COMPILE");
	//4.创建按一个program盒子
	mProgram = glCreateProgram();

	//5.将vs和fs编译好的结果放到program这个盒子里
	glAttachShader(mProgram, vertex);
	glAttachShader(mProgram, fragment);

	//6.执行program链接操作，形成最终可执行shader程序
	glLinkProgram(mProgram);

	//检查链接错误
	checkShaderErrors(mProgram, "LINK");

	//清理
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


Shader::~Shader(){}


//开始使用给当前Shader
void Shader:: begin() {
	GL_CALL( glUseProgram(mProgram));
}


//结束使用给当前Shader
void Shader:: end() {
    GL_CALL(glUseProgram(0));
}


void Shader:: setFoat(const std::string& name, float value)
{
	//1.通过名称拿到uniform变量的位置Location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//2.通过Location更新Uniform变量的值
	glUniform1f(location, value);


}

void  Shader::setVector3(const std::string& name, float x, float y, float z)
{
	//1.通过名称拿到uniform变量的位置Location
	GLint location = GL_CALL( glGetUniformLocation(mProgram, name.c_str()));

	//2.通过Location更新Uniform变量的值
	GL_CALL(glUniform3f(location, x,y,z));
}

void Shader::setInt(const std::string& name, int value)
{
	// 1.通过名称拿到uniform变量的位置Location
		GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
	//2.通过Location更新Uniform变量的值
		glUniform1i(location, value);
}

void Shader::checkShaderErrors(GLuint target, std::string type)
{
	int success = 0;
	char infoLog[1024];
	if (type == "COMPILE")
	{
		//检查编译结果
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success)//语法错误
		{
			glGetShaderInfoLog(target, 1024, NULL, infoLog);
			std::cout << "Error:shader compile error " << "\n" << infoLog << std::endl;
		}


	}
	else if (type == "LINK")
	{
		glGetProgramiv(target, GL_LINK_STATUS, &success);
		if (!success)//语法错误
		{
			glGetProgramInfoLog(target, 1024, NULL, infoLog);
			std::cout << "Error:shader Link error " << "\n" << infoLog << std::endl;
		}
	}
	else
	{
		std::cout << "ERROR:Check Shader errors Type is Wrong" << std::endl;

	}

}

