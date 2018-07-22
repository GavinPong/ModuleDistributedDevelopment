include ../../Makefile.param

#Additional flags

INCLUDE_DIRS += -I./
INCLUDE_DIRS += -I../
INCLUDE_DIRS += -I$(UTIL_TOOLS_DIR)/base64
INCLUDE_DIRS += -I$(UTIL_TOOLS_DIR)/cJSON
INCLUDE_DIRS += -I$(UTIL_TOOLS_DIR)/cross_platform
INCLUDE_DIRS += -I$(UTIL_TOOLS_DIR)/error
INCLUDE_DIRS += -I$(UTIL_TOOLS_DIR)/filefunc
INCLUDE_DIRS += -I$(UTIL_TOOLS_DIR)/inirw
INCLUDE_DIRS += -I$(UTIL_TOOLS_DIR)/list
INCLUDE_DIRS += -I$(UTIL_TOOLS_DIR)/log
INCLUDE_DIRS += -I$(UTIL_TOOLS_DIR)/strfunc

LIBRARY_DIRS += -L./
LIBRARY_DIRS += -L$(UTIL_TOOLS_DIR)

DIR_C :=
DIR_C +=$(wildcard *.c)


DIR_CPP :=
DIR_CPP +=$(wildcard *.cpp)

LIBOBJ :=
LIBOBJ +=$(patsubst %.c,%.o,$(DIR_C))
LIBOBJ +=$(patsubst %.cpp,%.o,$(DIR_CPP))	

#C部分指定宏用
CFLAGS += -DPLATFORM=1
#C++部分指定宏用 
CXXFLAGS += 
#链接库名称
LDFLAGS += -lpthread -lstdc++
#编译选项
LOPTION += 

all:
	$(CC) -c  $(INCLUDE_DIRS) $(DIR_C) $(DIR_CPP)  $(CFLAGS) $(CXXFLAGS) $(LOPTION)

MAKEDEPEND =$(CC) -MM -MT
DEF_C = $(DIR_C:.c=.d)
DEF_CPP = $(DIR_CPP:.cpp=.d)

$(DEF_C):%.d:%.c
	$(MAKEDEPEND) $(<:.c=.o) $< $(INCLUDE_DIRS) > $@ $(CFLAGS)

$(DEF_CPP):%.d:%.cpp
	$(MAKEDEPEND) $(<:.cpp=.o) $< $(INCLUDE_DIRS) > $@ $(CFLAGS)

include $(DEF_C) $(DEF_CPP)

.PHONY:depend
depend:
	rm -rf $(DEF_C)
	rm -rf $(DEF_CPP)
	$(MAKE) $(DEF_C)
	$(MAKE) $(DEF_CPP)


.PHONY:clean
clean:
	rm -rf $(LIBOBJ) $(DEF_C)  $(DEF_CPP)
	

