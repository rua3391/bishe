#include "Camera.h"
// sdk database 


Camera::Camera() :
	cModule("CAMERA"), 
	_zoom(45.0f), 
	_speed(3.5f), 
	_sensitivity(0.03f)
{
}

Camera::~Camera()
{	
}

bool Camera::init(glm::vec3 position, glm::vec3 target, glm::vec3 upward)
{
	worldup = upward;
	_position = position;
	forward = glm::normalize(target - position);
	right = glm::normalize(glm::cross(forward, worldup));
	up = glm::normalize(glm::cross(forward, right));
	debug("摄像机初始化成功");
	return true;
}

bool Camera::init(glm::vec3 position, float pitch, float yaw, glm::vec3 upward)
{
	worldup = upward;
	_position = position;
	_pitch = pitch;
	_yaw = yaw;

	forward.x = glm::cos(glm::radians(_pitch)) * glm::sin(glm::radians(_yaw));
	forward.y = glm::sin(glm::radians(_pitch));
	forward.z = glm::cos(glm::radians(_pitch)) * glm::cos(glm::radians(_yaw));

	right = glm::normalize(glm::cross(worldup, forward));
	up = glm::normalize(glm::cross(right, forward));
	debug("摄像机初始化成功");
	return true;
}

void Camera::serialize(void *out)
{
	//todo
}

void Camera::unserialize()
{
	//todo
}

void Camera::final()
{
	//do nothing
}

glm::mat4 Camera::getViewMatrix() 
{
	return glm::lookAt(_position, _position + forward, worldup);
}

void Camera::processMouseMovement(DFLOAT xoffset, DFLOAT yoffset) 
{
	xoffset *= _sensitivity;
	yoffset *= _sensitivity;
	_pitch -= yoffset;
	_yaw -= xoffset;
	if (_pitch > 89.0f)
		_pitch = 89.0f;
	if (_pitch < -89.0f)
		_pitch = -89.0f;
	_updateCameraVector();
}

void Camera::processScrollEvent(DFLOAT yoffset) 
{
	_zoom -= yoffset;
	if (_zoom < 1.0f) 
	{
		_zoom = 1.0f;
	}
	if (_zoom > 45.0f) 
	{
		_zoom = 45.0f;
	}
}

void Camera::processKeybordMovement(CameraMove direction, FLOAT delta_time) 
{
	FLOAT v = delta_time * _speed;
	if(direction >= CameraMove_Max)
	{
		error("摄像机移动方向非法");
		return;
	}
	if (direction == FORWARD) 
	{
		_position += forward * v;
	}
	else if (direction == BACK) 
	{
		_position -= forward * v;
	}
	else if (direction == LEFT) 
	{
		_position += right * v;
	}
	else 
	{
		_position -= right * v;
	}
	//Position.y = 0.0f;//这条让这个摄像机固定在xoz平面，成为一个fps类型摄像头，不能随意飞行
}

void Camera::_updateCameraVector() 
{
	forward.x = glm::cos(glm::radians(_pitch)) * glm::sin(glm::radians(_yaw));
	forward.y = glm::sin(glm::radians(_pitch));						  
	forward.z = glm::cos(glm::radians(_pitch)) * glm::cos(glm::radians(_yaw));
	right = glm::normalize(glm::cross(worldup, forward));
	up = glm::normalize(glm::cross(right, forward));
}

glm::vec3& Camera::getCameraPosition()
{
	return _position; 
}

FLOAT Camera::getCameraZoom()
{
	return _zoom;
}
