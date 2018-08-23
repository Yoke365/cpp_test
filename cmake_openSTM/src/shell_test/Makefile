# = 是最基本的赋值
# := 是覆盖之前的值
# ?= 是如果没有被赋值过就赋予等号后面的值
# += 是添加等号后面的值

# make DEFINE_VRE=true OPT=define 
# make DEFINE_VRE=true OPT=add 
# make DEFINE_VRE=true OPT=recover  
# make DEFINE_VRE= OPT=define 
# make DEFINE_VRE= OPT=add 
# make DEFINE_VRE= OPT=recover 

ifdef DEFINE_VRE
    VRE = “Hello World!”
else
endif

ifeq ($(OPT),define)
    VRE ?= “Hello World! First!”
endif

ifeq ($(OPT),add)
    VRE += “Kelly!”
endif

ifeq ($(OPT),recover)
    VRE := “Hello World! Again!”
endif

all:
	@echo $(VRE)