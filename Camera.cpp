#include "Common.pb.cc"

#include "Camera.h"

Camera::Camera() :
	cModule("CAMERA"), 
	_zoom(45.0f), 
	_speed(3.5f), 
	_sensitivity(0.2f),
	_yaw(-90.0f),
	_pitch(0.0f)
{
}

Camera::~Camera()
{	
}

bool Camera::init(const glm::vec3 &position, FLOAT pitch, FLOAT yaw, const glm::vec3 &upward)
{
	_worldup = upward;
	_position = position;
	_pitch = pitch;
	_yaw = yaw;

	_updateCameraVector();
	debug("摄像机初始化成功");
	return true;
}

void Camera::serialize(void *out)
{
	Proto::Common::CameraProto camera;
	camera.add_position(_position.x);
	camera.add_position(_position.y);
	camera.add_position(_position.z);
	camera.add_worldup(_worldup.x);
	camera.add_worldup(_worldup.y);
	camera.add_worldup(_worldup.z);
	camera.set_pitch(_pitch);
	camera.set_yaw(_yaw);

	camera.SerializeToArray(out, MAX_SIZE);
}

void Camera::unserialize()
{
	char buffer[MAX_SIZE] = {0};
	readFromRedis(buffer);
	Proto::Common::CameraProto camera;
	camera.ParseFromArray(buffer, MAX_SIZE);
	
	glm::vec3 pos(camera.position(0), camera.position(1), camera.position(2));
	glm::vec3 worldup(camera.worldup(0), camera.worldup(1), camera.worldup(2));
	FLOAT pitch = camera.pitch();
	FLOAT yaw = camera.yaw();
	this->init(pos, pitch, yaw, worldup);
}

void Camera::final()
{
	//do nothing
}

glm::mat4 Camera::getViewMatrix() 
{
	return glm::lookAt(_position, _position + _forward, _up);
}

void Camera::processMouseMovement(DFLOAT xoffset, DFLOAT yoffset) 
{
	xoffset *= _sensitivity;
	yoffset *= _sensitivity;
	_pitch += yoffset;
	_yaw += xoffset;
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
		_position += _forward * v;
	}
	else if (direction == BACK) 
	{
		_position -= _forward * v;
	}
	else if (direction == LEFT) 
	{
		_position -= _right * v;
	}
	else if (direction == RIGHT)
	{
		_position += _right * v;
	}
	//Position.y = 0.0f;//这条让这个摄像机固定在xoz平面，成为一个fps类型摄像头，不能随意飞行
}

void Camera::_updateCameraVector() 
{
	glm::vec3 front;
	front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	front.y = sin(glm::radians(_pitch));
	front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_forward = glm::normalize(front);
	_right = glm::normalize(glm::cross(_forward, _worldup));
	_up    = glm::normalize(glm::cross(_right, _forward));
}

glm::vec3& Camera::getCameraPosition()
{
	return _position; 
}

FLOAT Camera::getCameraZoom()
{
	return _zoom;
}

glm::vec3& Camera::getCameraForward()
{
	return _forward;
}
