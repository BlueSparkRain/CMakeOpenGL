#include "Application.h"
#include<glad/glad.h>
#include<GLFW/glfw3.h>

//初始化Application的静态变量
Application* Application::instnce = nullptr;

Application* Application::getInstance()
{
//如果已经实例化了，就直接返回
//否则先new出来再返回
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

	//初始化GLFW基本环境
	glfwInit();

	//设置主版本号，次版本号
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);

	//设置OpenGL启用核心模式（非立即渲染模式）
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//创建窗体对象
    mWindow = glfwCreateWindow(mWidth, mHeight, "OpenGLStudy", NULL, NULL);
	if(mWindow==NULL)
	{
		return false;
	}

	//设置当前窗口对象为OpenGL的绘制舞台
	glfwMakeContextCurrent(mWindow);

	//使用glad加载所有当前版本opengl的函数
	//将一个函数作为中介去加载opengl的函数
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		return false;
	}

	glfwSetFramebufferSizeCallback(mWindow, framBufferSizeCallback);

	//this就是当前全局唯一的Application对象
	//存储实例指针
	glfwSetWindowUserPointer(mWindow, this);

	//键盘响应
	//将静态函数舍之道glfw的监听KeyCallback之中
	glfwSetKeyCallback(mWindow, keyCallback);

	return true;
}

bool  Application::update()
{
	if (glfwWindowShouldClose(mWindow))
	{
		return false;
	}

	//接受并分发窗体消息
		//检查消息队列是否有需要处理的鼠标，键盘等消息
		//如果有，则将消息批量处理，清空队列
	glfwPollEvents();

	//切换双缓存
	glfwSwapBuffers(mWindow);
	return true;

}
void   Application::destroy()
{
	glfwTerminate();

}

 void Application::framBufferSizeCallback(GLFWwindow* window, int width, int height) 
{
	 //先拿出实例指针，比下方优雅
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