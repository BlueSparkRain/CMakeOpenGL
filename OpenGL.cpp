#include<iostream>
using namespace std;
#include"glframework/core.h"
#include"glframework/shader.h"
#include<string>
#include<assert.h>//����
#include"wrapper/checkError.h"
#include"application/Application.h"
#include"glframework/texture.h"

//-����glfw����ϵͳ
//-���봰�ڱ仯���¼��ص�
//-��������

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	//���ڱ仯��Ӧ
	glViewport(0, 0, width, height);
}

//key����ĸ������
//scancode����������
//action�����»���̧��
//mods���Ƿ���shift��ctrl
void keyCallBack(GLFWwindow* window,int key,int scancode,int action,int mods)
{
	//������Ϣ�ص�����
	//if(key==GLFW_KEY_W)
	//{
	//	//������W
	//}
	//if (action == GLFW_PRESS)
	//{
	//	//��λ����
	//}
	//if (action == GLFW_RELEASE)
	//{
	//	//��λ̧��
	//}
	//if (mods == GLFW_MOD_CONTROL)
	//{
	//	//����ctrlͬʱ��������key
	//}
	//if (action == GLFW_MOD_SHIFT)
	//{
	//	//����shiftͬʱ��������key
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


//����
void prepareVBO()
{
	//һ��vbo�����������ʵ��δ�����Դ�
	GLuint vbo = 0;
    GL_CALL(glGenBuffers(1, &vbo));

	GL_CALL(glDeleteBuffers(1, &vbo));
}

//SingleBuffer����
void prepareSingleBuffer()
{
	//1.׼������λ�����ݺ���ɫ����
	float positions[] = {
	   -0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f };
	float colors[] = {
		1.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,
		0.0f,0.0f,1.0f };

	//	2.Ϊλ�û���ɫ���ݸ�������һ��vbo
	GLuint posVBO = 0,colorVBO = 0;
	glGenBuffers(1, & posVBO);
	glGenBuffers(1,& colorVBO);

	//3.�������ֿ���vbo���԰󶨲��������
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

	//4.����vao���Ұ�
	GLuint vao = 0;
	glGenVertexArrays(1,&vao);

	glBindVertexArray(vao);//��

	//5.�ֱ�λ�á���ɫ���Ե�������Ϣ����vao��
	glBindBuffer(GL_ARRAY_BUFFER, posVBO);//ֻ�а���posVBO����������������Ż����vbo���
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);//��colorVBO����������������Ż����vbo���
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	glBindVertexArray(0);//���ǰ��vao
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
	//λ�����ݷŵ�0��λ
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	//��ɫ���ݷŵ�1��λ
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));

	glBindVertexArray(0);//���ǰ��vao
}

/// <summary>
/// ׼����vao
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
	//λ�����ݷŵ�0��λ
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	

	glBindVertexArray(0);//���ǰ��vao
}
void prepare()
{
	float  vertices[] =
	{
	-0.5f,-0.5f,0.0f,
	 0.5f,-0.5f,0.0f,
	 0.0f, 0.5f,0.0f
	};

	//1.����һ��vbo
	GLuint vbo = 0;
	GL_CALL( glGenBuffers(1, &vbo));

	//2.�󶨵�ǰvbo����opengl״̬���ĵ�ǰvbo�����
	//GL_ARRAY_BUFFER��ʾ��ǰvbo������
	GL_CALL( glBindBuffer(GL_ARRAY_BUFFER, vbo));
		
    //3.��ǰvbo�������ݣ�Ҳ���ڿ����Դ�
	GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));


}



void prepareVAO()
{

	float  positions[] =
	{
	//����
	/* 0.0f, 0.5f,0.0f,
	-0.5f,0.0f,0.0f,
	 0.0f,-0.5f,0.0f,
	 0.5f,0.0f,0.0f,*/
		 
	//����
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

	//VBO����
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

	//Ebo����
	GLuint ebo = 0;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	//Vao����
	glGenVertexArrays(1, &vao);
	//��vao�����²���ֻ����vao
	glBindVertexArray(vao);
	

	//��̬��ȡ��vao�е�λ��,��������λ���Ǹ������Ե��Ⱥ�λ�ö�̬����0��1��2.����
	GLuint posLocation = glGetAttribLocation(shader->mProgram, "aPos");
	GLuint colorLocation = glGetAttribLocation(shader->mProgram, "aColor");

	//��vbo rbo ����λ������������Ϣ
	glBindBuffer(GL_ARRAY_BUFFER, posVbo);
	glEnableVertexAttribArray(posLocation);//λ�����ݷŵ�0��λ
	glVertexAttribPointer(posLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//��vbo rbo ������ɫ����������Ϣ
	glBindBuffer(GL_ARRAY_BUFFER, colorVbo);
	glEnableVertexAttribArray(colorLocation);
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	//��vbo rbo ����uv����������Ϣ
	glBindBuffer(GL_ARRAY_BUFFER, uvVbo);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);


	//����ebo����ǰ��vao
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	//�������ǰvao��󶨵�ebo
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//���vao
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
	//ִ��opengl�����������
	//GL_CALL(glClear(GL_COLOR_BUFFER_BIT););
	glClear(GL_COLOR_BUFFER_BIT);
	//��Ⱦ����
	//1.�󶨵�ǰprogram
	shader->begin();

	////����ʱ��ֵ
	shader->setFoat("time", glfwGetTime());
	shader->setFoat("speed", 10);

	//shader->setInt("sampler",0);
	shader->setInt("waterSampler", 0);
	shader->setInt("orangeSampler", 1);
	shader->setInt("noiseSampler", 2);
	
	//2.�󶨵�ǰvao
	glBindVertexArray(vao);
	
	//3.��������ָ��
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

	//����openg�ӿ��Լ�������ɫ
	GL_CALL(glViewport(0, 0, 800, 600););
	
    GL_CALL(glClearColor(0.8f, 0.2f, 0.4f, 1););
	
	prepareShader();
	prepareVAO();
	prepareTexture();

	//ִ�д���ѭ��
	while (app->update())
	{
		render();
	}

	//�˳�ǰ�������
	app->destroy();

	return 0;
}

