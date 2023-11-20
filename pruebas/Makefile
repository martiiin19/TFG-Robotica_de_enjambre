
define COMPILAR
$(2) : $(3) $(4)
	$(1) -c -o $(2) $(3) $(5)
endef

define C2O
$(patsubst %.c, %.o,$(patsubst %.cpp, %.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

define C2H
$(patsubst %.c, %.h,$(patsubst %.cpp, %.hpp,$(1)))
endef

APP			:= game
CCFLAGS 	:= -Wall -pedantic -m64 -std=c++20 -Iz#-fsanitize=address
CC			:= g++
MKDIR		:= mkdir -p
SRC			:= src
OBJ			:= obj
LIBS		:= -Ilib -lX11 -lXext -lxml2 -lz -licuuc #-Ilib/libtmx/include 

LIBRERIAS	:=  lib/libraylib.a lib/libtmx/libtmx.a lib/libtmx/libz.a 

ALLCPPS		:= $(shell find src/ -type f -iname *.cpp)
ALLCS		:= $(shell find src/ -type f -iname *.c)
ALLCPPSOBJ	:= $(patsubst %.cpp,%.o,$(ALLCPPS))
OBJALL 		:= $(foreach F,$(ALLCPPS) $(ALLCS),$(call C2O,$(F)))
SUBDIRS		:= $(shell find src/ -type d)
OBJSUBDIRS	:= $(patsubst $(SRC)%,$(OBJ)%,$(SUBDIRS))


.PHONY: dir

$(APP) : $(OBJSUBDIRS) $(ALLCPPSOBJ)
	$(CC) -o $(APP) $(OBJALL) $(LIBS) $(LIBRERIAS)
#	$(CC) $(SRC)/main.cpp -c -o $(OBJ)/main.o $(CCFLAGS)

$(foreach F,$(ALLCPPS),$(eval $(call COMPILAR,$(CC),$(call C2O,$(F)),$(F),$(call C2H,$(F)),$(CCFLAGS) )))

%.o : %.cpp
	$(CC) -o $(patsubst $(SRC)%,$(OBJ)%,$@) -c $^ $(CCFLAGS)

dir :
	$(info $(SUBDIRS))
	$(info $(OBJSUBDIRS))
	$(info $(ALLCPPSOBJ))

$(OBJSUBDIRS) :
	$(MKDIR) $(OBJSUBDIRS)

clean :
	rm -f $(OBJALL)