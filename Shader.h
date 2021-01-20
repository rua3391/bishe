#ifndef SHADER_H
#define SHADER_H

#include "cModule.h"
/*
 * \brief Shader类
 * 
 */ 
class Shader : public cModule
{
	public:
		/**
		 * \brief 构造函数
		 * 
		 */ 
		Shader();
		/**
		 * \brief 析构函数
		 * 
		 */ 
		~Shader();
		/**
		 * \brief 使用此Shader程序
		 * 
		 */
		void useProgram();
		/**
		 * \brief 初始化shader
		 * \param vertex_file 顶点着色器文件路径 
		 * \param fragment_file 片元着色器文件路径
		 * \return 初始化是否成功
		 * 
		 */ 
		bool init(const std::string &vertex_file, const std::string &fragment_file);
		/**
		 * \brief 序列化 
		 * 
		 */
		void serialize(void* out);
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
		/**
		 * \brief 设置Shader中uniform SDWORD变量值
		 * \param name uniform变量名字 
		 * \param num SDWORD值 
		 * 
		 */
		void uniformSet1i(const std::string &name, SDWORD num);
		/**
		 * \brief 设置Shader中uniform SDWORD变量值
		 * \param name uniform变量名字 
		 * \param num DWORD值
		 *  
		 */
		void uniformSet1ui(const std::string& name, DWORD num); 
		/**
		 * \brief 设置Shader中uniform float变量值
		 * \param name uniform变量名字 
		 * \param num float值 
		 * 
		 */
		void uniformSet1f(const std::string &name, FLOAT num);
		/**
		 * \brief 设置Shader中uniform bool类型变量值
		 * \param name uniform变量名字 
		 * \param value value值
		 *  
		 */
		void uniformSetBool(const std::string &name, bool value);
		/**
		 * \brief 设置Shader中uniform SDWORD变量值
		 * \param name uniform变量名字 
		 * \param num SDWORD值 
		 * 
		 */
		void uniformSetInt(const std::string &name, SDWORD num);
		/**
		 * \brief 设置Shader中uniform float变量值
		 * \param name uniform变量名字 
		 * \param num float值 
		 * 
		 */
		void uniformSetFloat(const std::string &name, FLOAT num);
		/**
		 * \brief 设置Shader中uniform vec2向量变量值
		 * \param name uniform变量名字 
		 * \param x x值 
		 * \param y y值 
		 * 
		 */
		void uniformSetvec2(const std::string &name, FLOAT x, FLOAT y);
		/**
		 * \brief 设置Shader中uniform vec2向量变量值
		 * \param name uniform变量名字 
		 * \param target vec2向量 
		 * 
		 */
		void uniformSetvec2(const std::string &name, const glm::vec2 &target);
		/**
		 * \brief 设置Shader中uniform vec3向量变量值
		 * \param name uniform变量名字 
		 * \param x x值 
		 * \param y y值 
		 * \param z z值 
		 * 
		 */
		void uniformSetvec3(const std::string &name, FLOAT x, FLOAT y, FLOAT z);
		/**
		 * \brief 设置Shader中uniform vec3向量变量值
		 * \param name uniform变量名字 
		 * \param target vec3向量 
		 * 
		 */
		void uniformSetvec3(const std::string &name, const glm::vec3 &target);
		/**
		 * \brief 设置Shader中uniform vec4向量变量值
		 * \param name uniform变量名字 
		 * \param x x值 
		 * \param y y值 
		 * \param z z值 
		 * \param w w值
		 * 
		 */
		void uniformSetvec4(const std::string &name, FLOAT x, FLOAT y, FLOAT z, FLOAT w);
		/**
		 * \brief 设置Shader中uniform vec4向量变量值
		 * \param name uniform变量名字
		 * \param target vec4向量
		 * 
		 */ 
		void uniformSetvec4(const std::string &name, const glm::vec4 &target);
		/**
		 * \brief 设置Shader中uniform mat4变量值
		 * \param name uniform变量名字 
		 * \param matrix 二阶矩阵 
		 * 
		 */
		void uniformSetmat2(const std::string &name, const glm::mat2 &matrix);
		/**
		 * \brief 设置Shader中uniform mat4变量值
		 * \param name uniform变量名字 
		 * \param matrix 三阶矩阵 
		 * 
		 */
		void uniformSetmat3(const std::string &name, const glm::mat3 &matrix);
		/**
		 * \brief 设置Shader中uniform mat4变量值
		 * \param name uniform变量名字 
		 * \param matrix 四阶矩阵 
		 * 
		 */
		void uniformSetmat4(const std::string &name, const glm::mat4 &matrix);
	private:
		/**
		 * \brief Shader program id
		 * 
		 */ 
		DWORD _ID;
		/**
		 * \brief 检查Shader程序编译是否完成
		 * \param id 着色器或shader程序id
		 * \param type 检查类型 编译或链接状态
		 * \return 编译是否成功
		 * 
		 */ 
		bool _checkCompile(DWORD id, const std::string& type);
};

#endif