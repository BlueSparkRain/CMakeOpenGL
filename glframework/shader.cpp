
#include "shader.h"
#include "../wrapper/checkError.h"

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{

	//����װ��shader�����ַ���������string
	std::string vertexCode;
	std::string fragmentCode;
	//�������ڶ�ȡvs��fs�ļ���inFileStream
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//��֤ifstrem���������ʱ������׳��쳣
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		//���ļ�
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		//���ļ��������е��ַ������뵽stringStream����
		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//�ر��ļ�
		vShaderFile.close();
		fShaderFile.close();

		//���ַ�����stringStream�ж�ȡ������ת����codeString����
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch(std::ifstream::failure& e)
	{
		std::cout << "Error:Shader File Error:" << e.what() <<std::endl;

	}
	const char* vertexShaderSource = vertexCode.c_str();
	const char* fragmentShaderSource = fragmentCode.c_str();

	//1.����shader����
	GLuint  vertex, fragment;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	//2.Ϊshader��������shader����
	glShaderSource(vertex, 1, &vertexShaderSource, NULL);
	glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

	int success = 0;
	char infoLog[1024];

	//3.ִ��shader�������
	glCompileShader(vertex);
	//��������
	checkShaderErrors(vertex,"COMPILE");

	glCompileShader(fragment);

	checkShaderErrors(fragment, "COMPILE");
	//4.������һ��program����
	mProgram = glCreateProgram();

	//5.��vs��fs����õĽ���ŵ�program���������
	glAttachShader(mProgram, vertex);
	glAttachShader(mProgram, fragment);

	//6.ִ��program���Ӳ������γ����տ�ִ��shader����
	glLinkProgram(mProgram);

	//������Ӵ���
	checkShaderErrors(mProgram, "LINK");

	//����
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}


Shader::~Shader(){}


//��ʼʹ�ø���ǰShader
void Shader:: begin() {
	GL_CALL( glUseProgram(mProgram));
}


//����ʹ�ø���ǰShader
void Shader:: end() {
    GL_CALL(glUseProgram(0));
}


void Shader:: setFoat(const std::string& name, float value)
{
	//1.ͨ�������õ�uniform������λ��Location
	GLint location = glGetUniformLocation(mProgram, name.c_str());

	//2.ͨ��Location����Uniform������ֵ
	glUniform1f(location, value);


}

void  Shader::setVector3(const std::string& name, float x, float y, float z)
{
	//1.ͨ�������õ�uniform������λ��Location
	GLint location = GL_CALL( glGetUniformLocation(mProgram, name.c_str()));

	//2.ͨ��Location����Uniform������ֵ
	GL_CALL(glUniform3f(location, x,y,z));
}

void Shader::setInt(const std::string& name, int value)
{
	// 1.ͨ�������õ�uniform������λ��Location
		GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
	//2.ͨ��Location����Uniform������ֵ
		glUniform1i(location, value);
}

void Shader::checkShaderErrors(GLuint target, std::string type)
{
	int success = 0;
	char infoLog[1024];
	if (type == "COMPILE")
	{
		//��������
		glGetShaderiv(target, GL_COMPILE_STATUS, &success);
		if (!success)//�﷨����
		{
			glGetShaderInfoLog(target, 1024, NULL, infoLog);
			std::cout << "Error:shader compile error " << "\n" << infoLog << std::endl;
		}


	}
	else if (type == "LINK")
	{
		glGetProgramiv(target, GL_LINK_STATUS, &success);
		if (!success)//�﷨����
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

