SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = lib/
GLEW_LIB = /usr/lib

CPP_FILES := $(wildcard src/*.cpp)
OBJECT_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
CC = clang++
CFLAGS = -stdlib=libc++ -Weverything -Wextra -ggdb -O0
LDFLAGS=  -framework GLUT -framework OpenGL -framework Cocoa -lpthread
TARGET = kitxen

INC_PATH =
LIB_PATH = $(LIB_DIR)libSOIL.a

$(TARGET): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(LIB_PATH) $(LDFLAGS) $(INC_PATH) $^ -o $(TARGET) 

obj/%.o: src/%.cpp
	$(CC) $(CC_FLAGS) -c -std=c++11 -stdlib=libc++ -ggdb -Wno-deprecated -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECT_FILES) *~