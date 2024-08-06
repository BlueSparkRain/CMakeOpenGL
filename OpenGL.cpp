#include<iostream>
using namespace std;
#include"glframework/core.h"
#include"glframework/shader.h"
#include<string>
#include<assert.h>//断言
#include"wrapper/checkError.h"
#include"application/Application.h"
#include"glframework/texture.h"

//-创建glfw窗体系统
//-加入窗口变化的事件回调
//-函数加载

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	//窗口变化响应
	glViewport(0, 0, width, height);
}

//key：字母按键码
//scancode：物理按键码
//action：按下还是抬起
//mods：是否有shift或ctrl
void keyCallBack(GLFWwindow* window,int key,int scancode,int action,int mods)
{
	//键盘消息回调函数
	//if(key==GLFW_KEY_W)
	//{
	//	//触发了W
	//}
	//if (action == GLFW_PRESS)
	//{
	//	//键位按下
	//}
	//if (action == GLFW_RELEASE)
	//{
	//	//键位抬起
	//}
	//if (mods == GLFW_MOD_CONTROL)
	//{
	//	//按下ctrl同时，按下了key
	//}
	//if (action == GLFW_MOD_SHIFT)
	//{
	//	//按下shift同时，按下了key
	//}
	
}

GLuint vao;
Shader* shader = nullptr;
Texture* texture = nullptr;
Texture* orangeTexture = nullptr;
Texture* waterTexture = nullptr;
Texture* grayTexture = nullptr;

void OnResize(int width,int height)
{
	GL_CALL(glViewport(0, 0, width, height));
	cout << "Resize" << endl;
}

void OnKey(int key,int action,int mods)
{

}


//弃用
void prepareVBO()
{
	//一个vbo申请出来后，其实还未分配显存
	GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));

	GL_CALL(glDeleteBuffers(1, &vbo));
}

//SingleBuffer策略
void prepareSingleBuffer()
{
	//1.准备顶点位置数据和颜色数据
	float positions[] = {
	   -0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f };
	float colors[] = {
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f };

	//	2.为位置或颜色数据各自生成一个vbo
	GLuint posVBO = 0,colorVBO = 0;
	glGenBuffers(1, & posVBO);
	glGenBuffers(1,& colorVBO);

	//3.给两个分开的vbo各自绑定并填充数据
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	//4.生成vao并且绑定
	GLuint vao = 0;
	glGenVertexArrays(1,&vao);

	glBindVertexArray(vao);//绑定

	//5.分别将位置、颜色属性的描述信息加入vao中
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);//只有绑定了posVBO，下面的属性描述才会与此vbo相关
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);//绑定colorVBO，下面的属性描述才会与此vbo相关
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);//解绑当前的vao
}
//InterleavedBuffer
void prepareInterleavedBuffer()
{
	float vertexs[] = {
	    -0.5f,-0.5f,0.0f,    0.5f,0.0f,0.0f,
		0.5f,-0.5f,0.0f,    0.0f,1.0f,0.1f,
		0.0f,0.5f,0.0f,     0.0f,0.0f,1.0f 
	};
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexs), vertexs, GL_STATIC_DRAW);

	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	//位置数据放到0号位
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//颜色数据放到1号位
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

	glBindVertexArray(0);//解绑当前的vao
}

/// <summary>
/// 准备好vao
/// </summary>
void prepareVAOForGLTriangles()
{
	float positions[] = {
		-0.5f,-0.5f,0.0f,  
		0.5f,-0.5f,0.0f,   
		0.0f,0.5f,0.0f,
		0.5f,0.5f,0.0f,
	   	0.8f,0.8f,0.0f,
		0.6f,0.2f,0.0f,
	};
	GLuint posVbo = 0;
	glGenBuffers(1, &posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	//位置数据放到0号位
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	

	glBindVertexArray(0);//解绑当前的vao
}
void prepare()
{
	float  vertices[] =
	{
	-0.5f,-0.5f,0.0f,
	 0.5f,-0.5f,0.0f,
	 0.0f, 0.5f,0.0f
	};

	//1.生成一个vbo
	GLuint vbo = 0;
	GL_CALL( glGenBuffers(1, &vbo));

	//2.绑定当前vbo，到opengl状态机的当前vbo插槽上
	//GL_ARRAY_BUFFER表示当前vbo这个插槽
	GL_CALL( glBindBuffer(GL_ARRAY_BUFFER, vbo));
		
    //3.向当前vbo传输数据，也是在开辟显存
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));


}



void prepareVAO()
{

	float  positions[] =
	{
	//菱形
	/* 0.0f, 0.5f,0.0f,
	-0.5f,0.0f,0.0f,
	 0.0f,-0.5f,0.0f,
	 0.5f,0.0f,0.0f,*/
		 
	//矩形
	 -0.5f,-0.5f,0.0f,
	  0.5f,-0.5f,0.0f,
	  0.5f, 0.5f,0.0f,
     -0.5f, 0.5f,0.0f,
	};



	float colors[] =
	{
	0.0f,1.0f,0.0f,
	1.0f,0.0f,0.0f,
	0.0f,0.0f,1.0f,
	1.0f,0.0f,0.0f,
	};

	float uvs[] =
	{
	 0.0f,0.0f,
	 1.0f,0.0f,
	 0.0f,1.0f,
	 1.0f,1.0f,
	};

	unsigned int indices[] =
	{
	0,1,2,
	2,3,0,

	};

	//VBO创建
	GLuint posVbo,colorVbo,uvVbo;
	glGenBuffers(1,&posVbo);
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

	glGenBuffers(1, &colorVbo);
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	glGenBuffers(1, &uvVbo);
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);

	//Ebo创建
	GLuint ebo = 0;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//Vao创建
	glGenVertexArrays(1, &vao);
	//绑定vao，以下操作只关联vao
	glBindVertexArray(vao);
	

	//动态获取在vao中的位置,这个分配的位置是根据属性的先后位置动态分配0，1，2.。。
	GLuint posLocation = glGetAttribLocation(shader->mProgram, "aPos");
	GLuint colorLocation = glGetAttribLocation(shader->mProgram, "aColor");

	//绑定vbo rbo 加入位置属性描述信息
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(posLocation);//位置数据放到0号位
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//绑定vbo rbo 加入颜色属性描述信息
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//绑定vbo rbo 加入uv属性描述信息
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


	//加入ebo到当前的vao
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	//清理掉当前vao里绑定的ebo
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//解绑vao
	glBindVertexArray(0);
}

void prepareShader()
{
	shader = new Shader("assets/shaders/vertex.glsl", "assets/shaders/fragment.glsl");
}


void prepareTexture()
{
	texture = new Texture("assets/textures/goku.jpg",0);

	waterTexture = new Texture("assets/textures/water.jpg ",0);
	orangeTexture = new Texture("assets/textures/orange.jpg ", 1);
	grayTexture = new Texture("assets/textures/gray.jpg ", 2);
}

void render()
{
	//执行opengl画布清理操作
	//GL_CALL(glClear(GL_COLOR_BUFFER_BIT););
	glClear(GL_COLOR_BUFFER_BIT);
	//渲染操作
	//1.绑定当前program
	shader->begin();

	////更新时间值
	shader->setFoat("time", glfwGetTime());
	shader->setFoat("speed", 10);

	//shader->setInt("sampler",0);
	shader->setInt("waterSampler", 0);
	shader->setInt("orangeSampler", 1);
	shader->setInt("noiseSampler", 2);
	
	//2.绑定当前vao
	glBindVertexArray(vao);
	
	//3.发出绘制指令
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	shader->end();
}

int main()
{
			
	if(!app->init(800, 600)) 
	{
		return -1;
	};
	
	app->setResizeCallback(OnResize);
	app->setKeyBoardCallback(OnKey);

	//设置openg视口以及清理颜色
	GL_CALL(glViewport(0, 0, 800, 600););
	
    GL_CALL(glClearColor(0.8f, 0.2f, 0.4f, 1););
	
	prepareShader();
	prepareVAO();
	prepareTexture();

	//执行窗体循环
	while (app->update())
	{
		render();
	}

	//退出前相关清理
	app->destroy();

	return 0;
}

