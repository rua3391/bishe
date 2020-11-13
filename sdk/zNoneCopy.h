#ifndef Z_NONE_COPY
#define Z_NONE_COPY

/**
 * \brief 禁用拷贝构造函数和赋值构造函数
 * 
 */ 
class zNoneCopy
{
    protected:
        /**
         * \brief 构造函数
         * 
         */ 
        zNoneCopy() {};
        /**
         * \brief 析构函数
         * 
         */
        ~zNoneCopy() {}; 
    protected:
        /**
         * \brief 禁用拷贝构造
         * 
         */
        zNoneCopy(const zNoneCopy& copy) = delete;
        /**
         * \brief 禁用赋值构造
         * 
         */
        zNoneCopy& operator = (const zNoneCopy& copy) = delete;  
};

#endif