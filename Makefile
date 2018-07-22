include Makefile.param

TARGET := libmdd.so libmdd.a

####### DIR NAME ##################
DIR_SRC := src
DIR_MODULEBASE := $(DIR_SRC)/module_base
DIR_MODULEDUMMY := $(DIR_SRC)/module_dummy
DIR_REC_MUXER := $(DIR_SRC)/module_rec_muxer
###################################

DIRS_C := 
DIRS_C += $(wildcard $(DIR_SRC)/*.c)
DIRS_C += $(wildcard $(DIR_MODULEBASE)/*.c)
DIRS_C += $(wildcard $(DIR_MODULEDUMMY)/*.c)
DIRS_C += $(wildcard $(DIR_REC_MUXER)/*.c)

DIRS_CPP := 
DIRS_CPP += $(wildcard $(DIR_SRC)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_MODULEBASE)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_MODULEDUMMY)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_REC_MUXER)/*.cpp)

LIBOBJS_C := 
LIBOBJS_C += $(DIRS_C:%.c=%.o)

LIBOBJS_CPP := 
LIBOBJS_CPP += $(DIRS_CPP:%.cpp=%.o)


all:
	cd $(UTIL_TOOLS_DIR) && cd .. && make	#先进入util_tools目录将需要的工具接口编译成 obj（*.o）文件
	/bin/bash ./make_in_all_dirs.sh && make $(TARGET)


libmdd.so:
	$(CC)  $(CFLAGS)  $(LIBOBJS_C) $(LIBOBJS_CPP) $(LDFLAGS) -o  $@  -shared -fPIC
	$(STRIP)   $(STRIPFLAGS)  $@


libmdd.a:
	$(AR)  rv $@   $(LIBOBJS_C) $(LIBOBJS_CPP)
	$(STRIP)   $(STRIPFLAGS)  $@

clean:
	cd $(UTIL_TOOLS_DIR) && cd .. &&  make clean	#先进入util_tools目录将需要的工具接口编译成 obj（*.o）文件 
	/bin/bash ./clear_o_file.sh

depend:
	/bin/bash ./clear_d_file.sh

distclean:
	cd $(UTIL_TOOLS_DIR) &&  cd .. && make distclean	#先进入util_tools目录将需要的工具接口编译成 obj（*.o）文件
	/bin/bash ./clear_o_d_file.sh

install:
	cp 	src/*.h /home/share_disk/workspace/thirdlib/mdd/inc -rf
	cp 	*.so /home/share_disk/workspace/thirdlib/mdd/ -rf

.PHONY:$(TARGET)
.PHONY: clean
.PHONY: depend
.PHONY: distclean 
.PHONY: install 