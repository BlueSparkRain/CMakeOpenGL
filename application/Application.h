#pragma once

#include<iostream>
//#include<GLFW/glfw3.h>
#define app Application::getInstance()
class GLFWwindow;

//1��װApplication��ʵ��һ��������
//2��Ա����������(Init  Update  Destroy)
//3��Ӧ�ص�������Resize��

//����һ������ָ��ResizeCallback
using ResizeCallback = void(*)(int width, int height);
//����һ������ָ��KeyBoardCallback
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

	//����һ��setResizeCallback���������ô���仯��Ӧ�ص�����
	void setResizeCallback(ResizeCallback callback) { mResizeCallback = callback; };
	//����һ��KeyBoardCallback���������ü�����Ӧ�ص�����
	void setKeyBoardCallback(KeyBoardCallback callback) { mKeyBoardCallback = callback; };

private:
	//����һ����̬�������ڼ���glfw����仯
	static void framBufferSizeCallback(GLFWwindow* window, int width, int height);
	//����һ����̬����������Ӧglfw�ļ����¼�
	static void  keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	static Application* instnce;
    uint32_t  mWidth{ 0 };
	uint32_t mHeight{ 0 };
	GLFWwindow* mWindow{ nullptr };

	//����һ��ResizeCallback���͵ĳ�Ա����
	ResizeCallback mResizeCallback{ nullptr };
	//����һ��KeyBoardCallback���͵ĳ�Ա����
	KeyBoardCallback mKeyBoardCallback{ nullptr};

	Application();//��̬�����ĳ�ʼ������cpp����

};


