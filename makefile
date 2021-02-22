.PHONY:clean proto
OBJS = Engine.o Camera.o Shader.o Texture.o Light.o Object.o GObjManager.o GLightManager.o Mesh.o Model.o
CC = g++
STANDARD = -std=c++11
TARGET = Engine.out
LIB = -lGLEW -lglfw -lGL -lprotobuf -lpthread -lhiredis -lassimp
SDK = sdk/*.h
LOG = log/
SHADER = shader/
DESKTOP = ../mnt/c/Users/12638/Desktop/
COMMON = common/
PROTO =  proto/
REDIS = redis-5.0.1/deps/hiredis/

all: $(TARGET)
$(TARGET):$(OBJS)
	$(CC) -g $(OBJS) -o $(TARGET) $(LIB) $(STANDARD)
Camera.o: Camera.cpp $(COMMON)cModule.h $(SDK)
	$(CC) -c -g Camera.cpp -o Camera.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Shader.o: Shader.cpp $(COMMON)cModule.h $(SDK) 
	$(CC) -c -g Shader.cpp -o Shader.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Texture.o: Texture.cpp $(COMMON)cModule.h $(SDK)
	$(CC) -c -g Texture.cpp -o Texture.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Light.o: Light.cpp $(COMMON)cModule.h $(SDK)
	$(CC) -c -g Light.cpp -o Light.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
GObjManager.o: GObjManager.cpp Object.cpp $(PROTO)Common.pb.cc $(SDK)
	$(CC) -c -g GObjManager.cpp -o GObjManager.o -I$(PROTO) -Isdk/ -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
GLightManager.o: GLightManager.cpp Light.cpp $(PROTO)Common.pb.cc $(SDK)
	$(CC) -c -g GLightManager.cpp -o GLightManager.o -I$(PROTO) -Isdk/ -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Object.o: Object.cpp Shader.cpp Texture.cpp Light.cpp $(COMMON)cModule.h $(SDK)
	$(CC) -c -g Object.cpp -o Object.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Mesh.o: Mesh.cpp $(COMMON)cModule.h $(SDK)
	$(CC) -c -g Mesh.cpp -o Mesh.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Model.o: Mesh.cpp Model.cpp $(COMMON)cModule.h $(SDK)
	$(CC) -c -g Model.cpp -o Model.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Engine.o: *.h *.cpp $(SDK) $(PROTO)
	$(CC) -c -g Engine.cpp -o Engine.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
proto:
	cd $(PROTO) && $(MAKE)
clean:
	rm -rf *.o Engine $(DESKTOP)code.tar.gz
rmtar:
	rm -rf $(DESKTOP)code.tar.gz
tar:
	tar -zcvf $(DESKTOP)code.tar.gz --exclude=stb_image.h\
		$(SDK) $(LOG) $(SHADER) $(COMMON) $(PROTO) *.h *.cpp makefile *.o $(TARGET)
test: test.cpp
	$(CC) -g test.cpp -o test $(STANDARD)
testing: testing.cpp
	$(CC) -g testing.cpp -o testing $(STANDARD)