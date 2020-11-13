#include "Shader.h"
#include<fstream>
#include<sstream>

//sdk database

Shader::Shader() : 
	cModule("SHADER"),
	_ID(0)
{
	
}

Shader::~Shader() 
{
}

bool Shader::init(std::string vertex_file, std::string fragment_file)
{
	std::fstream vshader_file, fragshader_file;//文件输入输出流
	std::string vertex_code, fragment_code;//顶点着色器片元着色器代码

	vshader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragshader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	std::stringstream vertex_stream;
	debug("绑定顶点着色器文件");
	vshader_file.open(vertex_file);
	if (!vshader_file.is_open()) 
	{
		error("vertex shader opened failed");
		return false;
	}
	vertex_stream << vshader_file.rdbuf();
	vertex_code = vertex_stream.str();
	const char* vertex_shader = vertex_code.c_str();
	DWORD vertex = 0;
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertex_shader, NULL);
	glCompileShader(vertex);
	if(!_checkCompile(vertex, "vertex"))
		return false;
	
	std::stringstream fragment_stream;
	debug("绑定片元着色器文件");
	fragshader_file.open(fragment_file);
	if (!fragshader_file.is_open()) 
	{
		error("fragment shader opened failed");
		return false;
	}
	fragment_stream << fragshader_file.rdbuf();
	fragment_code = fragment_stream.str();
	const char* fragment_shader = fragment_code.c_str();
	DWORD fragment = 0;
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragment_shader, NULL);
	glCompileShader(fragment);
	if(!_checkCompile(fragment, "fragment"))
		return false;

	_ID = glCreateProgram();
	glAttachShader(_ID, vertex);
	glAttachShader(_ID, fragment);
	glLinkProgram(_ID);
	if(!_checkCompile(_ID, "program"))
		return false;
	
	debug("着色器程序初始化成功");
	
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	vshader_file.close();
	fragshader_file.close();

	return true;
}

void Shader::serialize(void *out)
{
	//todo
}

void Shader::unserialize()
{
	//todo
}

void Shader::final()
{
	glDeleteProgram(_ID);
}

bool Shader::_checkCompile(DWORD id, const std::string& type) 
{
	GLint success;
	GLchar infoLog[1024];
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);
	if (type != "program")
	{
		glGetShaderiv(id, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(id, 1024, NULL, infoLog);
			error("SHADER_COMPILATION_ERROR of type: %s \n %s \n ----------------------------------------", type.c_str(), infoLog);
			return false;
		}
	}
	else
	{
		glGetProgramiv(id, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(id, 1024, NULL, infoLog);
			error("SHADER_PROGRAME_LINKING_ERROR of type: %s \n %s \n ----------------------------------------", type.c_str(), infoLog);
			return false;
		}
	}
	return true;
}


void Shader::useProgram()
{
	glUseProgram(_ID);
}

void Shader::uniformSetvec4(const std::string &name, FLOAT x, FLOAT y, FLOAT z, FLOAT w) 
{
	DWORD location = glGetUniformLocation(_ID, name.c_str());
	glUniform4f(location, x, y, z, w);
}

void Shader::uniformSetvec3(const std::string &name, FLOAT x, FLOAT y, FLOAT z) 
{
	DWORD location = glGetUniformLocation(_ID, name.c_str());
	glUniform3f(location, x, y, z);
}

void Shader::uniformSetvec3(const std::string &name, glm::vec3 &target) 
{
	DWORD location = glGetUniformLocation(_ID, name.c_str());
	glUniform3fv(location, 1, &target[0]);
}

void Shader::uniformSet1f(const std::string& name, FLOAT num) 
{
	DWORD location = glGetUniformLocation(_ID, name.c_str());
	glUniform1f(location, num);
}

void Shader::uniformSet1i(const std::string &name, DWORD num)
{
	DWORD location = glGetUniformLocation(_ID, name.c_str());
	glUniform1i(location, num);
}

void Shader::uniformSetmat4(const std::string &name, glm::mat4 &matrix)
{
	DWORD location = glGetUniformLocation(_ID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}