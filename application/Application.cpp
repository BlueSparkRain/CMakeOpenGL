#include "Application.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//��ʼ��Application�ľ�̬����
Application* Application::instnce = nullptr;

Application* Application::getInstance()
{
//����Ѿ�ʵ�����ˣ���ֱ�ӷ���
//������new�����ٷ���
	if(instnce==nullptr)
	{
		instnce = new Application();
	}
	return instnce;
}

Application::Application()
{

}
Application::~Application()
{

}

bool  Application::init(const int& width,const int& height) {

	mWidth = width;
	mHeight = height;

	//��ʼ��GLFW��������
	glfwInit();

	//�������汾�ţ��ΰ汾��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	//����OpenGL���ú���ģʽ����������Ⱦģʽ��
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//�����������
    mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGLStudy", NULL, NULL);
	if(mWindow==NULL)
	{
		return false;
	}

	//���õ�ǰ���ڶ���ΪOpenGL�Ļ�����̨
	glfwMakeContextCurrent(mWindow);

	//ʹ��glad�������е�ǰ�汾opengl�ĺ���
	//��һ��������Ϊ�н�ȥ����opengl�ĺ���
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	glfwSetFramebufferSizeCallback(mWindow, framBufferSizeCallback);

	//this���ǵ�ǰȫ��Ψһ��Application����
	//�洢ʵ��ָ��
	glfwSetWindowUserPointer(mWindow, this);

	//������Ӧ
	//����̬������֮��glfw�ļ���KeyCallback֮��
	glfwSetKeyCallback(mWindow, keyCallback);

	return true;
}

bool  Application::update()
{
	if (glfwWindowShouldClose(mWindow))
	{
		return false;
	}

	//���ܲ��ַ�������Ϣ
		//�����Ϣ�����Ƿ�����Ҫ�������꣬���̵���Ϣ
		//����У�����Ϣ����������ն���
	glfwPollEvents();

	//�л�˫����
	glfwSwapBuffers(mWindow);
	return true;

}
void   Application::destroy()
{
	glfwTerminate();

}

 void Application::framBufferSizeCallback(GLFWwindow* window, int width, int height) 
{
	 //���ó�ʵ��ָ�룬���·�����
	 Application*self=(Application*) glfwGetWindowUserPointer(window);
	 if (self->mResizeCallback != nullptr) 
	 {
		 self->mResizeCallback(width, height);
	 }

	/* if(Application::getInstance()->mResizeCallback!=nullptr)
	 Application::getInstance()->mResizeCallback(width, height);*/

}

 void  Application::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
 {
	 Application* self = (Application*)glfwGetWindowUserPointer(window);
	 if (self->mKeyBoardCallback != nullptr)
	 {
		 self->mKeyBoardCallback(key, action, mods);
	 }
 }