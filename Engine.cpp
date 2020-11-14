#include "Proto/Common.pb.h"

#include "Engine.h"
#include "Camera.h"
#include "Shader.h"
#include "Texture.h"

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

	GLFWwindow* window = glfwCreateWindow(1200, 960, "Engine", nullptr, nullptr);
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

void Engine::final()
{
    for(Shader *ptr : shader)
    {
        if(ptr)
        {
            ptr->final();
            SAFE_DELETE(ptr);
        }
    }
}

int main(void)
{
    //todo 主逻辑进程
	GLFWwindow *window = Engine::getInstance()->init();
	if(!window)
	{
		FATAL("窗口句柄初始化失败");
		return -1;
	}
	if(!Camera::getInstance()->init(glm::vec3(0, 0, 3.0f), -15.0f, 180.0f, glm::vec3(0, 1.0f, 0)))
	{
		FATAL("相机初始化失败");
		return -1;
	}
	Shader S, LightCube;
	if(!S.init("Shader/lighting.vert", "Shader/lighting.frag"))
	{
		FATAL("着色器初始化失败%s", "object");
		return -1;
	}
	if(!LightCube.init("Shader/light.vert", "Shader/light.frag"))
	{
		FATAL("着色器初始化失败%s", "light");
		return -1;
	}

	DEBUG("主进程初始化完毕");
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
	
	DWORD VAO, VBO;
	DWORD LightVAO;
	glGenVertexArrays(1, &VAO);
	glGenVertexArrays(1, &LightVAO);
	glGenBuffers(1, &VBO);
	//glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(LightVAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//S.uniformSet1i("Texture1", 0);
	//S.uniformSet1i("Texture2", 2);
	glm::mat4 model(1.0f);
	glm::mat4 view(1.0f);
	glm::mat4 projection(1.0f);
	FLOAT last_time = 0.0;
	while (!glfwWindowShouldClose(window)) 
	{
		Engine::getInstance()->processInput(window);
		// glClearColor(0.2, 0.3, 0.3, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		FLOAT cur_time = glfwGetTime();
		Engine::getInstance()->timepass = cur_time - last_time;
		last_time = cur_time;

		glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
		// lightPos.x = 1.0 + sin(glfwGetTime()) * 2.0f;
		// lightPos.y = sin(glfwGetTime() / 2.0f) * 1.0f;

		S.useProgram();
		glBindVertexArray(VAO);
		
		projection = glm::perspective(glm::radians(Camera::getInstance()->getCameraZoom()), (float)1200 / (float)960, 0.1f, 100.0f);
		view = Camera::getInstance()->getViewMatrix();

		S.uniformSetmat4("model", model);
		S.uniformSetmat4("view", view);
		S.uniformSetmat4("projection", projection);

		glm::vec3 lightColor;
		lightColor.x = sin(glfwGetTime() * 2.0f);
		lightColor.y = sin(glfwGetTime() * 0.7f);
		lightColor.z = sin(glfwGetTime() * 1.3f);

		glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // 降低影响
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.2f); // 很低的影响
		S.uniformSetvec3("L.position", lightPos);
		S.uniformSetvec3("L.ambientlight", ambientColor);
		S.uniformSetvec3("L.diffuselight", diffuseColor);
		S.uniformSetvec3("L.specularlight", 1.0f, 1.0f, 1.0f);
		S.uniformSetvec3("camerapos", Camera::getInstance()->getCameraPosition());
		S.uniformSetvec3("M.ambientcolor", 1.0f, 0.5f, 0.31f);
		S.uniformSetvec3("M.diffuse", 1.0f, 0.5f, 0.31f);
		S.uniformSetvec3("M.specular", 0.5f, 0.5f, 0.5f);
		S.uniformSet1f("M.shiness", 32.0f);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		LightCube.useProgram();
		glBindVertexArray(LightVAO);

		glm::mat4 lightmodel(1.0f);
		lightmodel = glm::translate(lightmodel, lightPos);
		lightmodel = glm::scale(lightmodel, glm::vec3(0.2f));

		LightCube.uniformSetmat4("model", lightmodel);
		LightCube.uniformSetmat4("view", view);
		LightCube.uniformSetmat4("projection", projection);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	Engine::getInstance()->final();
	return 0;
}


