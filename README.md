2020/11/10 新增-日志功能 zLog.h\n
2020/11/10 新增-redis服务器客户端脚本 redisserver.sh
2020/11/10 新增-redis客户端启动脚本 rediscli.sh 
2020/11/11 新增-模块基类, 将shader和camera划为模块 cModule.h
2020/11/11 功能调整-调整日志功能, 提供模块和非模块写日志方法 zLog.h
2020/11/11 新增-redis交互基类 zRedis.h
2020/11/11 功能调整-模块基类 增加与protobuf交互接口 cModule.h
2020/11/11 新增-protobuf
2020/11/12 功能调整-序列化和反序列化功能调整, 模块接入redis cModule.h Camera.h Camera.cpp Shader.h Shader.cpp
2020/11/12 优化-makefile文件优化, include可省略绝对路径
2020/11/12 优化-主进程初始化逻辑调整, 补全日志
2020/11/13 优化-着色器类优化, 主函数优化
2020/11/13 新增-纹理类 Texture.h Texture.cpp
