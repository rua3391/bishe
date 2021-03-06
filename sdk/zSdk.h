#ifndef Z_SDK_H
#define Z_SDK_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>
#include <algorithm>
#include <functional>
#include <iterator>
#include <unordered_map>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <sstream>
#include <fstream>
#include <initializer_list>
#include <typeinfo>
#include <bitset>
#include <memory>
#include <utility>
#include <type_traits>
#include <signal.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

#include "zType.h"
#include "zLog.h"

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
