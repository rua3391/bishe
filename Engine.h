#ifndef ENGINE
#define ENGINE

#include "zSdk.h"
#include "zSingleton.h"

class Object;
class Light;
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
         * \brief 物件1 临时代码
         * 
         */
        Object *obj1;
        /**
         * \brief 物件2 临时代码
         * 
         */
        Object *obj2;
        /**
         * \brief 光源1 临时代码
         * 
         */
        Light *light; 
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
        GLFWwindow* init();
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