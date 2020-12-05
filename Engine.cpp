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
		ERROR("glew inited failed");
		glfwTerminate();
		return NULL;
	}
	glViewport(0, 0, 1200, 960);
	glEnable(GL_DEPTH_TEST);
    return window;
}

bool Engine::initObj(const std::string &vertexfile, const std::string &fragmentfile)
{
	FLOAT vertex[] =
	{
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	DEBUG("初始化物体");
	Object *object = new Object();
	if(!object->init(vertex, sizeof(vertex) / sizeof(FLOAT), vertexfile, fragmentfile))
	{
		FATAL("物体初始化失败");
		return false;
	}
	obj.emplace_back(object->id);
	return true;
}

bool Engine::initLight(const glm::vec3 &position)
{
	Light *_light = new Light();
	_light->init(position);
	this->light.emplace_back(_light->id);
	return true;
}

int Engine::mainProcess(void)
{
	if(!initObj("shader/lighting.vert", "shader/lighting.frag"))
	{
		return -1;
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(FLOAT), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(FLOAT), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	if(!initObj("shader/light.vert", "shader/light.frag"))
	{
		return -1;
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(FLOAT), (void *)0);
	glEnableVertexAttribArray(0);

	if(!initLight(glm::vec3(1.2f, 1.0f, 2.0f)))
	{
		return -1;
	}
	FLOAT last_time = 0.0;
	Object *obj1 = GObjManager::getInstance()->get(obj[0]);
	if(!obj1)
	{
		ERROR("获取物件失败");
		return -1;
	}
	Object *obj2 = GObjManager::getInstance()->get(obj[1]);
	if(!obj2)
	{
		ERROR("获取物件失败");
		return -1;
	}
	Light *light1 = GLightManager::getInstance()->get(light[0]);
	if(!light1)
	{
		ERROR("获取光源失败");
		return -1;
	}
	while (!glfwWindowShouldClose(window)) 
	{
		Engine::getInstance()->processInput(window);
		// glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FLOAT cur_time = glfwGetTime();
		Engine::getInstance()->timepass = cur_time - last_time;
		last_time = cur_time;

		glm::vec3 lightColor(sin(cur_time * 2.0f), sin(cur_time * 0.7f), sin(cur_time * 1.3f));
		light1->setDiffuseLight(lightColor * glm::vec3(0.5f));
		light1->setAmbientLight(lightColor * glm::vec3(0.5f) * glm::vec3(0.2f));
		light1->setSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));

		obj1->bindObject();
		obj1->setAmbient(glm::vec3(1.0f, 0.5f, 0.31f));
		obj1->setDiffuse(glm::vec3(1.0f, 0.5f, 0.31f));
		obj1->setSpecular(glm::vec3(0.5f, 0.5f, 0.5f));
		obj1->setShiness(32.0f);
		obj1->setColor(light1->getLight());
		obj1->reflectPosition();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		obj2->bindObject();
		obj2->translate(light1->getPosition());
		obj2->scaling(glm::vec3(0.2f));
		obj2->reflectPosition();
		obj2->getShader()->uniformSetvec3("color", lightColor);
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
		FATAL("窗口初始化失败");
		return -1;
	}
	if(!Camera::getInstance()->init(glm::vec3(0, 0, 3.0f), -15.0f, 180.0f, glm::vec3(0, 1.0f, 0)))
	{
		FATAL("相机初始化失败");
		return -1;
	}
	DEBUG("主进程初始化完毕");
	Engine::getInstance()->mainProcess();
	DEBUG("主进程结束");
	Engine::getInstance()->final();
	DEBUG("资源释放完毕");
	return 0;
}
