SRC_DIR = src/
OBJ_DIR = obj/
LIB_DIR = lib/

CPP_FILES := $(wildcard src/*.cpp)
OBJECT_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
CC = g++
CFLAGS = -Wall -Wextra -ggdb -O0
LDFLAGS= -framework GLUT -framework OpenGL -framework Cocoa -lpthread
TARGET = kitxen

INC_PATH =
LIB_PATH = $(LIB_DIR)libSOIL.a

$(TARGET): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INC_PATH) $(LIB_PATH) $^ -o $(TARGET) 

obj/%.o: src/%.cpp
	g++ $(CC_FLAGS) -c -ggdb -o $@ $<

clean:
	rm -f $(TARGET) $(OBJECT_FILES) *~