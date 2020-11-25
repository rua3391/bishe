.PHONY:clean proto
OBJS = Engine.o Camera.o Shader.o Texture.o Light.o Object.o GObjManager.o GLightManager.o
CC = g++
STANDARD = -std=c++11
TARGET = Engine
LIB = -lGLEW -lglfw -lGL -lprotobuf -lpthread 
SDK = sdk/*.h
LOG = log/
SHADER = shader/
DESKTOP = ../../mnt/c/Users/12638/Desktop/
COMMON = common/
PROTO =  proto/
REDIS = redis-5.0.1/deps/hiredis/

all: $(TARGET)
$(TARGET):$(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LIB) $(STANDARD)
Camera.o: Camera.cpp $(COMMON)cModule.h $(SDK)
	$(CC) -c Camera.cpp -o Camera.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Shader.o: Shader.cpp $(COMMON)cModule.h $(SDK) 
	$(CC) -c Shader.cpp -o Shader.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Texture.o: Texture.cpp $(COMMON)cModule.h $(SDK)
	$(CC) -c Texture.cpp -o Texture.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Light.o: Light.cpp $(COMMON)cModule.h $(SDK)
	$(CC) -c Light.cpp -o Light.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
GObjManager.o: GObjManager.cpp Object.cpp $(PROTO)Common.pb.cc $(SDK)
	$(CC) -c GObjManager.cpp -o GObjManager.o -I$(PROTO) -Isdk/ -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
GLightManager.o: GLightManager.cpp Light.cpp $(PROTO)Common.pb.cc $(SDK)
	$(CC) -c GLightManager.cpp -o GLightManager.o -I$(PROTO) -Isdk/ -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Object.o: Object.cpp Shader.cpp Texture.cpp Light.cpp $(COMMON)cModule.h $(SDK)
	$(CC) -c Object.cpp -o Object.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
Engine.o: *.h *.cpp $(SDK) $(PROTO)
	$(CC) -c Engine.cpp -o Engine.o -Isdk/ -I$(PROTO) -I$(COMMON) -I$(REDIS) $(LIB) $(STANDARD)
proto:
	cd $(PROTO) && $(MAKE)
clean:
	rm -rf *.o Engine $(PROTO)*.h $(PROTO)*.cc $(DESKTOP)code.tar.gz
rmtar:
	rm -rf $(DESKTOP)code.tar.gz
tar:
	tar -czvf $(DESKTOP)code.tar.gz --exclude=stb_image.h\
		$(SDK) $(LOG) $(SHADER) $(COMMON) $(PROTO) *.h *.cpp makefile *.o Engine