#include "Common.pb.h"

#include "Engine.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"
#include "Object.h"
#include "Light.h"
#include "GobjManager.h"

Engine::Engine() : 
	_first(true), 
	_lastx(0.0), 
	_lasty(0.0), 
	screenx(1200), 
	screeny(960)
{
	obj1 = new Object();
	obj2 = new Object();
	light = new Light(glm::vec3(1.2f, 1.0f, 2.0f));
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
    if (_first) {
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
    if (glfwGetKey(windows, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(windows, true);
	}
	if (glfwGetKey(windows, GLFW_KEY_W) == GLFW_PRESS) {
		Camera::getInstance()->processKeybordMovement(FORWARD, timepass);
	}
	else if (glfwGetKey(windows, GLFW_KEY_S) == GLFW_PRESS) {
		Camera::getInstance()->processKeybordMovement(BACK, timepass);
	}
	else if (glfwGetKey(windows, GLFW_KEY_D) == GLFW_PRESS) {
		Camera::getInstance()->processKeybordMovement(RIGHT, timepass);
	}
	else if (glfwGetKey(windows, GLFW_KEY_A) == GLFW_PRESS) {
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

int Engine::mainProcess(void)
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
	DEBUG("初始化obj1");
	if(!obj1->init(vertex, sizeof(vertex) / sizeof(FLOAT), "shader/lighting.vert", "shader/lighting.frag"))
	{
		FATAL("物体初始化失败");
		return -1;
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(FLOAT), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(FLOAT), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	DEBUG("初始化obj2");
	if(!obj2->init(vertex, sizeof(vertex) / sizeof(FLOAT), "shader/light.vert", "shader/light.frag"))
	{
		FATAL("物体初始化失败");
		return -1;
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(FLOAT), (void *)0);
	glEnableVertexAttribArray(0);

	FLOAT last_time = 0.0;
	while (!glfwWindowShouldClose(window)) 
	{
		Engine::getInstance()->processInput(window);
		// glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FLOAT cur_time = glfwGetTime();
		Engine::getInstance()->timepass = cur_time - last_time;
		last_time = cur_time;

		obj1->bindObject();
		obj1->setPosition();
		glm::vec3 lightColor(sin(cur_time * 2.0f), sin(cur_time * 0.7f), sin(cur_time * 1.3f));
		light->setDiffuseLight(lightColor * glm::vec3(0.5f));
		light->setAmbientLight(lightColor * glm::vec3(0.5f) * glm::vec3(0.2f));
		light->setSpecularLight(glm::vec3(1.0f, 1.0f, 1.0f));
		
		obj1->setColor(light->getLight());
		obj1->setMaterial(glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(1.0f, 0.5f, 0.31f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		obj2->bindObject();
		obj2->updateModel(light->getPosition(), 0.0f, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.2f));
		obj2->setPosition();
		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void Engine::final()
{
	if(obj1)
	{
    	obj1->final();
		SAFE_DELETE(obj1);
	}
	if(obj2)
	{
		obj2->final();
		SAFE_DELETE(obj2);
	}
}

int main(void)
{
	GLFWwindow *window = Engine::getInstance()->init();
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
