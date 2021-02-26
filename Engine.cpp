#include "Common.pb.h"

#include "Engine.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Light.h"
#include "GObjManager.h"
#include "GLightManager.h"
#include "Model.h"

Engine::Engine() : 
	_first(true), 
	_lastx(400), 
	_lasty(400), 
	screenx(800), 
	screeny(800),
	window(NULL),
	_deleter(),
	_client(new zTcpClient(), _deleter)
{
}

Engine::~Engine()
{
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* windows, DFLOAT xpos, DFLOAT ypos)
{
	Engine::getInstance()->processMouseCallback(windows, xpos, ypos);
}

void scrollCallback(GLFWwindow* windows, DFLOAT xoffset, DFLOAT yoffset)
{
	Engine::getInstance()->processScrollCallback(windows, xoffset, yoffset);
}

void Engine::processMouseCallback(GLFWwindow* windows, DFLOAT xpos, DFLOAT ypos)
{
    if (_first) 
	{
		_lastx = xpos;
		_lasty = ypos;
		_first = false;
	}
	DFLOAT xoffset = xpos - _lastx;
	DFLOAT yoffset = _lasty - ypos;

	// debug << "xpos" << xpos << " " << "ypos" << ypos <<end; 
	_lastx = xpos;
	_lasty = ypos;

	Camera::getInstance()->processMouseMovement(xoffset, yoffset);
}

void Engine::processScrollCallback(GLFWwindow* windows, DFLOAT xoffset, DFLOAT yoffset)
{
    Camera::getInstance()->processScrollEvent(yoffset);
}

void Engine::processInput(GLFWwindow* windows)
{
    if (glfwGetKey(windows, GLFW_KEY_ESCAPE) == GLFW_PRESS) 
	{
		glfwSetWindowShouldClose(windows, true);
	}
	if (glfwGetKey(windows, GLFW_KEY_W) == GLFW_PRESS) 
	{
		Camera::getInstance()->processKeybordMovement(FORWARD, timepass);
	}
	else if (glfwGetKey(windows, GLFW_KEY_S) == GLFW_PRESS) 
	{
		Camera::getInstance()->processKeybordMovement(BACK, timepass);
	}
	else if (glfwGetKey(windows, GLFW_KEY_D) == GLFW_PRESS)
	{
		Camera::getInstance()->processKeybordMovement(RIGHT, timepass);
	}
	else if (glfwGetKey(windows, GLFW_KEY_A) == GLFW_PRESS) 
	{
		Camera::getInstance()->processKeybordMovement(LEFT, timepass);
	}
}

GLFWwindow* Engine::init()
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(screenx, screeny, "Engine", nullptr, nullptr);
	if(window == NULL)
	{
		error << "窗口句柄初始化失败" <<end;
		return NULL;
	}
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) 
	{
		error << "glew inited failed" << end;
		glfwTerminate();
		return NULL;
	}
	glEnable(GL_DEPTH_TEST);
	_client->init("121.4.253.6", 5005);//云服务器ip及端口
    return window;
}

Object* Engine::initObj(const std::string& path, const std::string &vertexfile, const std::string &fragmentfile)
{
	debug << "初始化物体" << path.c_str() << end;
	Object *object = new Object();
	std::vector<FLOAT> buf;
	loadObj(path, buf);
	if(!object->init(buf))
	{
		error << "物体初始化失败" << end;
		return nullptr;
	}
	if(!object->initShader(vertexfile, fragmentfile))
	{
		error << "物体着色器初始化失败" << end;
		return nullptr;
	}
	return object;
}

bool Engine::loadObj(const std::string& path, std::vector<FLOAT> &container)
{
	std::ifstream fin;
	fin.open(path, std::ios_base::in);
	if(!fin.is_open())
	{
		error << "物件模型路径不存在, 加载模型失败" << end;
		return false;
	}
	std::istream_iterator<FLOAT> in(fin), eof;
	while(in != eof)
	{
		container.push_back(*in++);
	}
	fin.close();
	return true;
}

Light* Engine::initLight(const glm::vec3 &position, LightType type)
{
	Light *_light = new Light(type);
	if(!_light)
	{
		error << "内存不足, 初始化光源失败" << end;
		return nullptr;
	}
	if(!_light->init(position))
	{
		error << "光源初始化失败" << end;
		return nullptr;
	}
	return _light;
}

int Engine::mainProcess(void)
{
	Object *obj1 = initObj("model/cube", "shader/lighting.vert", "shader/lighting.frag");
	if(!obj1)
	{
		return -1;
	}
	obj1->initDiffuseTexture("pic/test.jpg", 0);
	obj1->initSpecularTexture("pic/box_specular.png", 1);

	Object *obj2 = initObj("model/cube","shader/light.vert", "shader/light.frag");
	if(!obj2)
	{
		return -1;
	}

	glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
	glm::vec3 pointLightPositions[] = {
        glm::vec3( 0.7f,  0.2f,  2.0f),
        glm::vec3( 2.3f, -3.3f, -4.0f),
        glm::vec3(-4.0f,  2.0f, -12.0f),
        glm::vec3( 0.0f,  0.0f, -3.0f)
    };
	// Light *spotlight = initLight(Camera::getInstance()->getCameraPosition(), Spot);
	// Light *directionLight = initLight(glm::vec3(-0.2f, -1.0f, -0.3f), Direction);
	Light *PointLight1 = initLight(pointLightPositions[0], Point);
	// Light *PointLight2 = initLight(pointLightPositions[1], Point);
	// Light *PointLight3 = initLight(pointLightPositions[2], Point);
	// Light *PointLight4 = initLight(pointLightPositions[3], Point);
	Model *model1 = new Model();
	model1->loadModel("model/tail/Tails.obj");

	FLOAT last_time = 0.0;
	while (!glfwWindowShouldClose(window)) 
	{
		Engine::getInstance()->processInput(window);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FLOAT cur_time = glfwGetTime();
		Engine::getInstance()->timepass = cur_time - last_time;
		last_time = cur_time;

		// 点光源设置
		// spotlight->setAmbientLight(glm::vec3(0.1f, 0.1f, 0.1f));
		// spotlight->setDiffuseLight(glm::vec3(0.8f, 0.8f, 0.8f));
		// spotlight->setSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));
		// spotlight->setLightConstant(1.0f);
		// spotlight->setLightLinear(0.09f);
		// spotlight->setLightQuadratic(0.032f);
		// spotlight->setLightCutoff(glm::cos(glm::radians(12.5f)));
		// spotlight->setLightOutCutoff(glm::cos(glm::radians(17.5f)));
		// spotlight->setLightDirection(Camera::getInstance()->getCameraForward());
		// spotlight->setLightPosition(Camera::getInstance()->getCameraPosition());
		//平行光设置
		// directionLight->setLightDirection(glm::vec3(-0.2f, -1.0f, -0.3f));
		// directionLight->setAmbientLight(glm::vec3(0.05f, 0.05f, 0.05f));
        // directionLight->setDiffuseLight(glm::vec3(0.4f, 0.4f, 0.4f));
        // directionLight->setSpecularLight(glm::vec3(0.5f, 0.5f, 0.5f));
		// //四个点光源设置
		PointLight1->setAmbientLight(glm::vec3(0.05f, 0.05f, 0.05f));
        PointLight1->setDiffuseLight(glm::vec3(0.8f, 0.8f, 0.8f));
        PointLight1->setSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));
        PointLight1->setLightConstant(1.0f);
        PointLight1->setLightLinear(0.09);
        PointLight1->setLightQuadratic(0.032);

		// PointLight2->setAmbientLight(glm::vec3(0.05f, 0.05f, 0.05f));
        // PointLight2->setDiffuseLight(glm::vec3(0.8f, 0.8f, 0.8f));
        // PointLight2->setSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));
        // PointLight2->setLightConstant(1.0f);
        // PointLight2->setLightLinear(0.09);
        // PointLight2->setLightQuadratic(0.032);

		// PointLight3->setAmbientLight(glm::vec3(0.05f, 0.05f, 0.05f));
        // PointLight3->setDiffuseLight(glm::vec3(0.8f, 0.8f, 0.8f));
        // PointLight3->setSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));
        // PointLight3->setLightConstant(1.0f);
        // PointLight3->setLightLinear(0.09);
        // PointLight3->setLightQuadratic(0.032);

		// PointLight4->setAmbientLight(glm::vec3(0.05f, 0.05f, 0.05f));
        // PointLight4->setDiffuseLight(glm::vec3(0.8f, 0.8f, 0.8f));
        // PointLight4->setSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));
        // PointLight4->setLightConstant(1.0f);
        // PointLight4->setLightLinear(0.09);
        // PointLight4->setLightQuadratic(0.032);

		// obj1->bindObject();
		// obj1->setShiness(32.0f);
		// obj1->translate(glm::vec3(1.0, 0.0, 0.0));
		// obj1->scaling(glm::vec3(0.5f, 0.5f, 0.5f));
		// obj1->reflectPosition();
		// obj1->reflectMaterial();
		// obj1->reflectLight();
		// obj1->draw();
		// obj1->translate(glm::vec3(-1.0, 0.0, -4.0));
		// obj1->rotate(20.0f, glm::vec3(1.0f,0.3f, 0.5f));
		// obj1->reflectPosition();
		// obj1->reflectMaterial();
		// obj1->reflectLight();
		// obj1->draw();
		// obj2->bindObject();
		// obj2->translate(pointLightPositions[0]);
		// obj2->scaling(glm::vec3(0.2f));
		// obj2->reflectPosition();
		// obj2->getShader()->uniformSetvec3("color", glm::vec3(1.0f));
		// obj2->draw();
		// for (DWORD i = 0; i < 10; ++i)
        // {
        //     obj1->translate(cubePositions[i]);
        //     obj1->rotate(20.0f * i, glm::vec3(1.0f, 0.3f, 0.5f));
		// 	obj1->reflectPosition();
		// 	obj1->reflectMaterial();
		// 	obj1->reflectLight();
        //     obj1->draw();
        // }
		// for (DWORD i = 0; i < 4; ++i)
		// {
		// 	obj2->bindObject();
		// 	obj2->translate(pointLightPositions[i]);
		// 	obj2->scaling(glm::vec3(0.2f));
		// 	obj2->reflectPosition();
		// 	obj2->getShader()->uniformSetvec3("color", glm::vec3(1.0f));
		// 	obj2->draw();
		// }
		model1->translate(glm::vec3(0.0f, 0.0f, 0.0f));
		model1->scaling(glm::vec3(0.5f, 0.5f, 0.5f));
		model1->drawModel();
		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void Engine::final()
{
	Camera::getInstance()->final();
	GObjManager::getInstance()->final();
	GLightManager::getInstance()->final();
	std::string msg1 = "客户端进程已结束";
	_client->tcpWrite(msg1.c_str(), msg1.size());
}

void Terminate(SDWORD i)
{
	Engine::getInstance()->final();
	exit(0);
}

void ingSingal()
{
	for(int i = 0; i < 100; ++i)
	{
		signal(i, SIG_IGN);
	}
	signal(SIGINT, Terminate);
	signal(SIGTERM, Terminate);
}

int main(void)
{
	ingSingal();
	if(Engine::getInstance()->init() == NULL)
	{
		fatal << "窗口初始化失败" << end;
		return -1;
	}
	if(!Camera::getInstance()->init(glm::vec3(0, 0, 3.0f), 0.0f, -90.0f, glm::vec3(0, 1.0f, 0)))
	{
		fatal << "相机初始化失败" << end;
		return -1;
	}
	debug << "主进程初始化完毕" << end;
	Engine::getInstance()->mainProcess();
	debug << "主进程结束" << end;
	Engine::getInstance()->final();
	debug << "资源释放完毕" << end;
	return 0;
}
