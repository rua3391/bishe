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

bool Engine::initObj(const std::string& path, const std::string &vertexfile, const std::string &fragmentfile)
{
	debug << "初始化物体" << path.c_str() << end;
	Object *object = new Object();
	std::vector<FLOAT> buf;
	loadObj(path, buf);
	if(!object->init(buf))
	{
		error << "物体初始化失败" << end;
		return false;
	}
	if(!object->initShader(vertexfile, fragmentfile))
	{
		error << "物体着色器初始化失败" << end;
		return false;
	}
	obj.emplace_back(object->id);
	return true;
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
	FLOAT tmp;
	fin >> tmp;
	container.push_back(tmp);
	while(!fin.eof())
	{
		fin >> tmp;
		container.push_back(tmp);
	}
	fin.close();
	return true;
}

bool Engine::initLight(const glm::vec3 &position)
{
	Light *_light = new Light();
	if(!_light)
	{
		error << "内存不足, 初始化光源失败" << end;
		return false;
	}
	if(!_light->init(position))
	{
		error << "光源初始化失败" << end;
		return false;
	}
	this->light.emplace_back(_light->id);
	return true;
}

int Engine::mainProcess(void)
{
	if(!initObj("model/cube", "shader/lighting.vert", "shader/lighting.frag"))
	{
		return -1;
	}
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(FLOAT), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(FLOAT), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	if(!initObj("model/cube","shader/light.vert", "shader/light.frag"))
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
	// std::vector<QWORD> id;
	// GObjManager::getInstance()->getEveryId(id);
	// std::copy(id.begin(), id.end(), std::ostream_iterator<QWORD, char>(std::cout, " "));
	Object *obj1 = GObjManager::getInstance()->operator[](0);
	if(!obj1)
	{
		error << "获取物件失败" << end;
		return -1;
	}
	Object *obj2 = GObjManager::getInstance()->operator[](1);
	if(!obj2)
	{
		error << "获取物件失败" << end;
		return -1;
	}
	Light *light1 = GLightManager::getInstance()->operator[](0);
	if(!light1)
	{
		error << "获取光源失败" << end;
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
