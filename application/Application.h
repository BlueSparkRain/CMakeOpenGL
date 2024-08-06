#pragma once

#include<iostream>
//#include<GLFW/glfw3.h>
#define app Application::getInstance()
class GLFWwindow;

//1封装Application，实现一个单例类
//2成员变量及函数(Init  Update  Destroy)
//3相应回调函数（Resize）

//声明一个函数指针ResizeCallback
using ResizeCallback = void(*)(int width, int height);
//声明一个函数指针KeyBoardCallback
using KeyBoardCallback = void(*)(int key, int action, int mods);

class Application
{
	
public:
	~Application();
	static Application* getInstance();

	bool init(const int& width=800, const int& height=600);
	bool update();
	void destroy();

	uint32_t  getWidth() const { return mWidth; }
	uint32_t  getHeight() const { return mHeight; }

	//声明一个setResizeCallback函数，设置窗体变化响应回调函数
	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; };
	//声明一个KeyBoardCallback函数，设置键盘响应回调函数
	void setKeyBoardCallback(KeyBoardCallback callback) { mKeyBoardCallback = callback; };

private:
	//声明一个静态函数用于监听glfw窗体变化
	static void framBufferSizeCallback(GLFWwindow* window, int width, int height);
	//声明一个静态函数用于响应glfw的键盘事件
	static void  keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	static Application* instnce;
    uint32_t  mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };

	//声明一个ResizeCallback类型的成员变量
	ResizeCallback mResizeCallback{ nullptr };
	//声明一个KeyBoardCallback类型的成员变量
	KeyBoardCallback mKeyBoardCallback{ nullptr};

	Application();//静态变量的初始化放在cpp里做

};


