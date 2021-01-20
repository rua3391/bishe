#ifndef ENGINE
#define ENGINE

#include "zSdk.h"
#include "zSingleton.h"
#include "Light.h"

class Object;
class Engine : public zSingletonBase<Engine>
{
    public:
        /**
         * \brief 构造函数
         * 
         */ 
        Engine();
        /**
         * \brief 析构函数
         * 
         */
        ~Engine();
    public:
        /**
         * \brief 处理键盘输入消息
         * 
         */
        void processInput(GLFWwindow* windows);
        /**
         * \brief 处理鼠标消息
         * 
         */ 
        void processMouseCallback(GLFWwindow* windows, DFLOAT xpos, DFLOAT ypos);
        /**
         * \brief 处理鼠标滚轮消息
         * 
         */ 
        void processScrollCallback(GLFWwindow* windows, DFLOAT xoffset, DFLOAT yoffset);
        /**
         * \brief 主进程
         * 
         */
        int mainProcess(void); 
        /**
         * \brief 移动时间差
         * 
         */
        FLOAT timepass;
    public:
        /**
         * \brief 初始化资源 及三个变换矩阵
         * \return 窗口句柄指针
         * 
         */ 
        GLFWwindow* initWindow();
        /**
         * \brief 初始化物件 
         * \param path 物件模型顶点属性数据
         * \param vertexfile 顶点着色器路径
         * \param fragmentfile 片元着色器路径
         * \return 物件id
         * 
         */
        Object* initObj(const std::string& path, const std::string &vertexfile, const std::string &fragmentfile);
        /**
         * \brief 加载物件模型信息
         * \param path 模型路径
         * \param container 存放模型信息的容器
         * \return 加载物件模型是否成功
         * 
         */
        bool loadObj(const std::string &path, std::vector<FLOAT> &container);
        /**
         * \brief 初始化光源
         * \param position 光源位置
         * \param type 光源类型
         * 
         */ 
        Light* initLight(const glm::vec3 &position, LightType type = Simple);
        /**
         * \brief 销毁资源
         * 
         */  
        void final();
    public:
        /**
         * \brief 屏幕宽度
         * 
         */
        DWORD screenx;
        /**
         * \brief 屏幕高度
         * 
         */
        DWORD screeny;  
    private:
        /**
         * \brief 第一次移动
         * 
         */  
        bool _first;
        /**
         * \brief 上一次结束时x坐标
         * 
         */
        DFLOAT _lastx;
        /**
         * \brief 上一次结束时y坐标
         * 
         */
        DFLOAT _lasty;
        /**
         * \brief 窗口句柄
         * 
         */
        GLFWwindow *window; 
};

#endif