cc=clang

PLATFORM_ARCH         = $(shell uname -s)
PLATFORM_ARCH_LINUX   = Linux
PLATFORM_ARCH_DARWIN  = Darwin
PLATFORM_ARCH_FREEBSD = FreeBSD

# 输出类型配置
TARGET_TYPE_BIN = BINARY
TARGET_TYPE_LIB = STATIC
TARGET_TYPE_DLL = SHARED

# ** 项目配置区 **
#    输出文件名称
TARGET_NAME     = sparrow
#    输出文件类型
TARGET_TYPE     = ${TARGET_TYPE_DLL}
#    输出文件后缀 [自动判别]
TARGET_NAME_EXT =
#    安装位置
INSTALL_PATH    = /usr/local/sparrow

TARGET_OBJECTS_DIR := ./obj
TARGET_HEADERS_DIR := ./include
TARGET_SOURCES_DIR := ./source
TARGET_BINARY_DIR  := ./bin
TARGET_LIBRARY_DIR := ./lib

TARGET_SOURCES = $(wildcard ${TARGET_SOURCES_DIR}/*.cpp)
TARGET_OBJECTS = $(patsubst %.cpp,${TARGET_OBJECTS_DIR}/%.o,$(notdir ${TARGET_SOURCES}))
TARGET_HEADERS = $(wildcard $(TARGET_HEADERS_DIR)/*.h)

TARGET_LIBS = -lstdc++ -lcpp -larguments -lmodel -lmodule -lioevent
# 链接标志
TARGET_LIB_PIC_SHARED  = -fPIC
TARGET_LIB_PIC_STATIC  = 
TARGET_LIB_PIC_BINARY  = -fPIE
TARGET_LIB_FLAG_SHARED = -shared
TARGET_LIB_FLAG_STATIC =
# 自动判别
TARGET_LIB_PIC  = 
TARGET_LIB_FLAG = 

CFLAGS   = -Wall -fvisibility=hidden -I${TARGET_HEADERS_DIR}
CXXFLAGS = -std=c++11

# 平台检测 -- DARWIN
ifeq (${PLATFORM_ARCH},${PLATFORM_ARCH_DARWIN})
   ifeq (${TARGET_TYPE},${TARGET_TYPE_BIN})
       TARGET_LIB_FLAG :=
       TARGET_LIB_PIC  := ${TARGET_LIB_PIC_BINARY}
       TARGET_LD_FLAGS += 
       TARGET_NAME_EXT := 
       TARGET_NAME     := ${TARGET_NAME}.${TARGET_NAME_EXT}
   endif
   ifeq (${TARGET_TYPE},${TARGET_TYPE_LIB})
       TARGET_LIB_FLAG :=
       TARGET_LIB_PIC  := ${TARGET_LIB_PIC_STATIC}
       TARGET_LD_FLAGS += 
       TARGET_NAME_EXT := a
       TARGET_NAME     := ${TARGET_NAME}.${TARGET_NAME_EXT}
   endif
   ifeq (${TARGET_TYPE},${TARGET_TYPE_DLL})
       TARGET_LIB_FLAG := ${TARGET_LIB_FLAG_SHARED}
       TARGET_LIB_PIC  := ${TARGET_LIB_PIC_SHARED}
       TARGET_LD_FLAGS += -dynamiclib
       TARGET_NAME_EXT := dylib
       TARGET_NAME     := ${TARGET_NAME}.${TARGET_NAME_EXT}
   endif
endif
# 平台检测 -- LINUX
ifeq (${PLATFORM_ARCH},${PLATFORM_ARCH_LINUX})
   ifeq (${TARGET_TYPE},${TARGET_TYPE_BIN})
       TARGET_LIB_FLAG :=
       TARGET_LIB_PIC  := ${TARGET_LIB_PIC_BINARY}
       TARGET_LD_FLAGS +=
       TARGET_NAME_EXT :=
       TARGET_NAME     := ${TARGET_NAME}.${TARGET_NAME_EXT}
   endif
   ifeq (${TARGET_TYPE},${TARGET_TYPE_LIB})
       TARGET_LIB_FLAG :=
       TARGET_LIB_PIC  := ${TARGET_LIB_PIC_STATIC}
       TARGET_LD_FLAGS +=
       TARGET_NAME_EXT := a
       TARGET_NAME     := ${TARGET_NAME}.${TARGET_NAME_EXT}
   endif
   ifeq (${TARGET_TYPE},${TARGET_TYPE_DLL})
       TARGET_LIB_FLAG := ${TARGET_LIB_FLAG_SHARED}
       TARGET_LIB_PIC  := ${TARGET_LIB_PIC_SHARED}
       TARGET_LD_FLAGS += 
       TARGET_NAME_EXT := so
       TARGET_NAME     := ${TARGET_NAME}.${TARGET_NAME_EXT}
   endif
endif

# 平台检测 -- FreeBSD
ifeq (${PLATFORM_ARCH},${PLATFORM_ARCH_FreeBSD})
   ifeq (${TARGET_TYPE},${TARGET_TYPE_BIN})
       TARGET_LIB_FLAG :=
       TARGET_LIB_PIC  := ${TARGET_LIB_PIC_BINARY}
       TARGET_LD_FLAGS +=
       TARGET_NAME_EXT :=
       TARGET_NAME     := ${TARGET_NAME}.${TARGET_NAME_EXT}
   endif
   ifeq (${TARGET_TYPE},${TARGET_TYPE_LIB})
       TARGET_LIB_FLAG :=
       TARGET_LIB_PIC  := ${TARGET_LIB_PIC_STATIC}
       TARGET_LD_FLAGS +=
       TARGET_NAME_EXT := a
       TARGET_NAME     := ${TARGET_NAME}.${TARGET_NAME_EXT}
   endif
   ifeq (${TARGET_TYPE},${TARGET_TYPE_DLL})
       TARGET_LIB_FLAG := ${TARGET_LIB_FLAG_SHARED}
       TARGET_LIB_PIC  := ${TARGET_LIB_PIC_SHARED}
       TARGET_LD_FLAGS += 
       TARGET_NAME_EXT := so
       TARGET_NAME     := ${TARGET_NAME}.${TARGET_NAME_EXT}
   endif
endif

#${TARGET_LIBRARY_DIR}/${TARGET_NAME} : $(TARGET_OBJECTS) $(THIRDS_OBJECTS)
#	cc ${TARGET_LD_FLAGS} ${TARGET_LIB_PIC} ${TARGET_LIB_FLAG} -o $@ $(TARGET_OBJECTS) ${TARGET_LIBS}
 
#${TARGET_OBJECTS_DIR}/%.o : $(TARGET_SOURCES_DIR)/%.cpp
#	cc ${CFLAGS} ${CXXFLAGS} -c $< -o $@ ${TARGET_LIB_PIC}

YOUSHOULDMAKEITALL:arg model module io qr diff sparrow

SPARROW_LIBS = -lstdc++

sparrow : obj/sparrow.o
	cc -o bin/sparrow obj/sparrow.o ${IO_LIBS}
obj/sparrow.o : main/sparrow.cpp
	cc ${CFLAGS} ${CXXFLAGS} -c main/sparrow.cpp -o obj/sparrow.o

# DIFF
# 
DIFF_LIBS = -lstdc++ -larguments -lxdiff
#
diff : ./obj/diff.o
	cc -o bin/diff ./obj/diff.o ${DIFF_LIBS}
./obj/diff.o:./main/diff.cpp
	cc ${CFLAGS} ${CXXFLAGS} -c ./main/diff.cpp -o ./obj/diff.o

# QR
#
QR_LIBS = -lstdc++ -larguments -lqr -ldl

qr : ./obj/qr.o
	    cc -o bin/qr ./obj/qr.o -ldl -lqr ${QR_LIBS}
./obj/qr.o:./main/qr.cpp
	    cc ${CFLAGS} ${CXXFLAGS} -c ./main/qr.cpp -o ./obj/qr.o
# IO
#
IO_LIBS = -lstdc++ -larguments -lmodel -lmodule -lioevent

io : obj/io.o
	    cc -o bin/io obj/io.o ${IO_LIBS}
obj/io.o : main/io.cpp
	    cc ${CFLAGS} ${CXXFLAGS} -c main/io.cpp -o obj/io.o

# Module
#
MODULE_LIBS = -lstdc++ -lmodel -lmodule -lioevent

module : obj/module.o
	    cc -o bin/module obj/module.o ${MODULE_LIBS}
obj/module.o : main/module.cpp
	    cc ${CFLAGS} ${CXXFLAGS} -c main/module.cpp -o obj/module.o

# Model
#
MODEL_LIBS = -lstdc++ -lmodel

model : obj/model.o
	cc -o bin/model obj/model.o ${MODEL_LIBS}
obj/model.o : main/model.cpp
	cc ${CFLAGS} ${CXXFLAGS} -c main/model.cpp -o obj/model.o

# Arguments
#
ARGUMENTS_LIBS = -lstdc++ -larguments

arg : obj/arguments.o
	    cc -o bin/arg obj/arguments.o ${ARGUMENTS_LIBS}
obj/arguments.o : main/arguments.cpp
	    cc ${CFLAGS} ${CXXFLAGS} -c main/arguments.cpp -o obj/arguments.o
clean   :
	rm ${TARGET_OBJECTS_DIR}/*.o
	rm ${TARGET_BINARY_DIR}/*
