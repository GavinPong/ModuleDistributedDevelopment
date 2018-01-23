include Makefile.param

TARGET := libmdd.so libmdd.a

####### DIR NAME ##################
DIR_SRC := src
DIR_MODULEBASE := $(DIR_SRC)/module_base
DIR_MODULEDUMMY := $(DIR_SRC)/module_dummy
DIR_MODULEID := $(DIR_SRC)/module_id
###################################

DIRS_C := 
DIRS_C += $(wildcard $(DIR_SRC)/*.c)
DIRS_C += $(wildcard $(DIR_MODULEBASE)/*.c)
DIRS_C += $(wildcard $(DIR_MODULEDUMMY)/*.c)
DIRS_C += $(wildcard $(DIR_MODULEID)/*.c)

DIRS_CPP := 
DIRS_CPP += $(wildcard $(DIR_SRC)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_MODULEBASE)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_MODULEDUMMY)/*.cpp)
DIRS_CPP += $(wildcard $(DIR_MODULEID)/*.cpp)

LIBOBJS_C := 
LIBOBJS_C += $(DIRS_C:%.c=%.o)

LIBOBJS_CPP := 
LIBOBJS_CPP += $(DIRS_CPP:%.cpp=%.o)


all:
	/bin/bash ./make_in_all_dirs.sh && make $(TARGET)


libmdd.so:
	$(CC)  $(CFLAGS)  $(LIBOBJS_C) $(LIBOBJS_CPP) $(LDFLAGS) -o  $@  -shared -fPIC
	$(STRIP)   $(STRIPFLAGS)  $@


libmdd.a:
	$(AR)  rv $@   $(LIBOBJS_C) $(LIBOBJS_CPP)
	$(STRIP)   $(STRIPFLAGS)  $@

clean: 
	/bin/bash ./clear_o_file.sh

depend:
	/bin/bash ./clear_d_file.sh

distclean:
	/bin/bash ./clear_o_d_file.sh
	

.PHONY:$(TARGET)
.PHONY: clean
.PHONY: depend
.PHONY: distclean 