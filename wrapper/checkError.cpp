#include "checkError.h"
#include<glad/glad.h>
#include<string>
#include <assert.h>
using namespace std;
#include<iostream>

void checkError()
{
	GLenum errorcode = glGetError();
	string error = "";

	if (errorcode != GL_NO_ERROR) {
		switch (errorcode)
		{
		case GL_INVALID_ENUM: error = "INVALID_ENUM";
			break;
		case GL_INVALID_VALUE: error = "INVALID_VALUE";
			break;
		case GL_INVALID_OPERATION: error = "INVALID_OPERATION";
			break;
		case GL_OUT_OF_MEMORY: error = "OUT_OF_MEMORY";
			break;

		default:
			error = "UNKNOWN";
			break;

		}
		cout << error << endl;

		//assert��������һ���꣬����ݴ����bool���������Ƿ�ֹͣ��falseʱ�����
		assert(false);
	}
}