#ifndef Z_SDK_H
#define Z_SDK_H

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
#include<GL/glew.h>
#include<GLFW/glfw3.h>

#include <iostream>
#include <unordered_map>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <sstream>

#include "zType.h"
#include "zLog.h"

#define STB_IMAGE_IMPLEMENTATION
#define GLEW_STATIC
#define MAX_SIZE 2048
//安全删除指针
template <typename T>
inline void SAFE_DELETE(T* target){ if(target){ delete target; target = NULL;}}

//快速删除vector中元素
template<typename T>
inline void QUICK_RELEASE(std::vector<T> &target, DWORD position)
{
    target[position] = target.back();
    target.pop_back();
}

#endif