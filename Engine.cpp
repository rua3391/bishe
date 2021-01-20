#include "Common.pb.h"

#include "Engine.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Light.h"
#include "GObjManager.h"
#include "GLightManager.h"

Engine::Engine() : 
	_first(true), 
	_lastx(0.0), 
	_lasty(0.0), 
	screenx(1200), 
	screeny(960)
{
}

Engine::~Engine()
{

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
	DFLOAT yoffset = ypos - _lasty;
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

GLFWwindow* Engine::initWindow()
{
    glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(screenx, screeny, "Engine", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetScrollCallback(window, scrollCallback);

	glewExperimental = true;
	if (glewInit() != GLEW_OK) 
	{
		error << "glew inited failed" << end;
		glfwTerminate();
		return NULL;
	}
	glViewport(0, 0, 1200, 960);
	glEnable(GL_DEPTH_TEST);
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(FLOAT), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(FLOAT), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(FLOAT), (void *)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);
	obj1->initDiffuseTexture("pic/box.png", 0);
	obj1->initSpecularTexture("pic/box_specular.png", 1);

	Object *obj2 = initObj("model/cube","shader/light.vert", "shader/light.frag");
	if(!obj2)
	{
		return -1;
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(FLOAT), (void *)0);
	glEnableVertexAttribArray(0);

	Light *light1 = initLight(glm::vec3(1.2f, 1.0f, 2.0f), Point);
	if(!light1)
	{
		return -1;
	}
	FLOAT last_time = 0.0;
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
	while (!glfwWindowShouldClose(window)) 
	{
		Engine::getInstance()->processInput(window);
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FLOAT cur_time = glfwGetTime();
		Engine::getInstance()->timepass = cur_time - last_time;
		last_time = cur_time;

		light1->setDiffuseLight(glm::vec3(0.2f, 0.2f, 0.2f));
		light1->setAmbientLight(glm::vec3(0.5f, 0.5f, 0.5f));
		light1->setSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));
		light1->setLightConstant(1.0f);
		light1->setLightLinear(0.09f);
		light1->setLightQuadratic(0.032f);

		obj1->bindObject();
		obj1->setAmbient(glm::vec3(1.0f, 0.5f, 0.31f));
		obj1->setDiffuse(glm::vec3(1.0f, 0.5f, 0.31f));
		obj1->setSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		obj1->setShiness(32.0f);
		for (DWORD i = 0; i < 10; i++)
        {
            obj1->translate(cubePositions[i]);
            obj1->rotate(20.0f * i, glm::vec3(1.0f, 0.3f, 0.5f));
			obj1->reflectPosition();
			obj1->refelctMaterial();
			obj1->refelctLight(light1);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

		obj2->bindObject();
		obj2->translate(light1->getPosition());
		obj2->scaling(glm::vec3(0.2f));
		obj2->reflectPosition();
		obj2->getShader()->uniformSetvec3("color", glm::vec3(1.0f));
		glDrawArrays(GL_TRIANGLES, 0, 36);

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
}

int main(void)
{
	if(Engine::getInstance()->initWindow() == NULL)
	{
		fatal << "窗口初始化失败" << end;
		return -1;
	}
	if(!Camera::getInstance()->init(glm::vec3(0, 0, 3.0f), -15.0f, 180.0f, glm::vec3(0, 1.0f, 0)))
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
