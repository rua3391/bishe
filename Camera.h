#ifndef  CAMERA_H
#define  CAMERA_H

#include "zSingleton.h"
#include "cModule.h"

/**
 * \brief 摄像机移动方向枚举
 * 
 */ 
enum CameraMove {
	FORWARD			= 0,		//前 
	BACK			= 1, 		//后
	LEFT			= 2, 		//左
	RIGHT			= 3,		//右

	CameraMove_Max	= 5			
};

/*
 * \brief 摄像机类
 */
class Camera : public zSingletonBase<Camera>, public cModule
{
	public:
		/**
		 * \brief 构造函数
		 * 
		 */
		Camera();
		/**
		 * \brief 析构函数
		 * 
		 */
		~Camera();
	public: 
		/**
		 * \brief 初始化
		 * \param position 摄像机位置 
		 * \param target 目标物件位置 
		 * \param worldup 世界坐标系z(y)轴方向
		 * 
		 */ 
		bool init(const glm::vec3 &position, const glm::vec3 &target, const glm::vec3 &upward);
		/**
		 * \brief 初始化
		 * \param position 摄像机位置 
		 * \param pitch 摄像机仰角 
		 * \param yaw 摄像机yaw角 
		 * \param worldup 世界坐标系z(y)轴方向
		 * 
		 */ 
		bool init(const glm::vec3 &position, FLOAT pitch, FLOAT yaw, const glm::vec3 &upward);
		/**
		 * \brief 序列化
		 * 
		 */
		void serialize(void *out);
		/**
		 * \brief 反序列化
		 * 
		 */
		void unserialize();
		/**
		 * \brief 释放资源
		 * 
		 */
		void final();
	public:   
		/**
		 * \brief 获取摄像头变换矩阵
		 * 
		 */
		glm::mat4 getViewMatrix();
		/**
		 * \brief 处理鼠标移动事件
		 * \param xoffset x轴偏移
		 * \param yoffset y轴偏移
		 * 
		 */
		void processMouseMovement(DFLOAT xoffset, DFLOAT yoffset);
		/**
		 * \brief 处理鼠标滚轮事件
		 * \param 滚轮偏移
		 * 
		 */
		void processScrollEvent(DFLOAT yoffset);
		/**
		 * \brief 处理键盘移动事件
		 * \param 移动方向
		 * \param 移动时间
		 * 
		 */
		void processKeybordMovement(CameraMove direction, FLOAT delta_time);
		/**
		 * \brief 获取摄像机位置坐标
		 * \return 摄像机位置坐标
		 * 
		 */ 
		glm::vec3& getCameraPosition();
		/**
		 * \brief 获取摄像机正对方向
		 * 
		 */
		glm::vec3& getCameraForward(); 
		/**
		 * \brief 获取摄像机焦距
		 * \return zoom值
		 * 
		 */
		FLOAT getCameraZoom();
		/**
		 * \brief 设置灵敏度
		 * 
		 */
		inline void setSensitivity(FLOAT sensitivity) {_sensitivity = sensitivity;}
		/**
		 * \brief 设置移动速度
		 * 
		 */
		inline void setSpeed(FLOAT speed) {_speed = speed;}  
	private:
		/**
		 * \brief 摄像机右方
		 * 
		 */
		glm::vec3 _right;
		/**
		 * \brief 摄像机的上方
		 * 
		 */
		glm::vec3 _up;
		/**
		 * \brief 世界坐标系
		 * 
		 */
		glm::vec3 _worldup;
		/**
		 * \brief 摄像机目标方向
		 * 
		 */
		glm::vec3 _forward;
		/**
		 * \brief 更新摄像机向量
		 * 
		 */
		void _updateCameraVector();
		/**
		 * \brief 摄像机位置
		 * 
		 */
		glm::vec3 _position;
		/**
		 * \brief pitch角
		 * 
		 */
		FLOAT _pitch;
		/**
		 * \brief Yaw角
		 * 
		 */
		FLOAT _yaw;
		/**
		 * \brief zoom角
		 * 
		 */
		FLOAT _zoom;
		/**
		 * \brief 摄像机移动速度
		 * 
		 */
		FLOAT _speed;
		/**
		 * \brief 鼠标灵敏度
		 * 
		 */
		FLOAT _sensitivity;
};

#endif