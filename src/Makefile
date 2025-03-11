COMMAND			:= $(firstword $(MAKECMDGOALS))
TARGET			:= $(word 2, $(MAKECMDGOALS))
OPTION			:= $(word 3, $(MAKECMDGOALS))

CFLAGS			:= -pthread
WINFLAGS		:= -lwsock32 -lgdi32 -lmingw32
NOCONSOLEFLAG	:= -mwindows
OSENV			:=

CPPHEADER		:= ioset.hpp
CPPMODULE		:= $(CPPHEADER).gch
CPPMODULE_EXIST	:=

RC				:= icon.rc
RC_EXIST		:=
RCMODULE		:=

ifeq ($(OS),Windows_NT)
	OSENV := Windows
else
	UNAME_OS := $(shell uname -s)
	ifeq ($(UNAME_OS),Linux)
		OSENV := Linux
	else
		OSENV := Unknown
	endif
endif

ifeq ($(OSENV), Windows)
	CPPMODULE_EXIST := $(shell dir /b | findstr ${CPPMODULE})
	RC_EXIST        := $(shell dir /b | findstr ${RC})
else ifeq ($(OSENV), Linux)
	CPPMODULE_EXIST := $(shell ls | grep ${CPPMODULE})
	RC_EXIST        := $(shell dir /b | findstr ${RC})
endif

run:
ifeq ($(TARGET),)
	@python

else ifeq ($(findstring .py, $(TARGET)), .py)
	python $(TARGET)

else ifeq ($(findstring .cpp, $(TARGET)), .cpp)
    ifeq (${RC_EXIST}, ${RC})
		$(eval RCMODULE		:= $(RC:.rc=.res))
		windres $(RC) -O coff -o $(RCMODULE)
        # -O : 形式指定  coff : Common Object File Format
    endif
    ifneq (${CPPMODULE_EXIST}, ${CPPMODULE})
		g++ -x c++-header -g $(CPPHEADER) -o $(CPPMODULE)
    endif
    ifeq ($(OSENV), Windows)
		$(eval CFLAGS := $(CFLAGS) $(WINFLAGS))
    endif
    ifneq ($(OPTION), )
		$(eval CFLAGS := $(CFLAGS) $(NOCONSOLEFLAG))
    endif
	g++ -g $(TARGET) $(RCMODULE) $(CFLAGS) -o $(TARGET:.cpp=.exe)

else ifeq ($(findstring .c, $(TARGET)), .c)
    ifeq (${RC_EXIST}, ${RC})
		$(eval RCMODULE		:= $(RC:.rc=.res))
		windres $(RC) -O coff -o $(RCMODULE)
    endif
    ifeq ($(OSENV), Windows)
		$(eval CFLAGS := $(CFLAGS) $(WINFLAGS))
    endif
    ifneq ($(OPTION), )
		$(eval CFLAGS := $(CFLAGS) $(NOCONSOLEFLAG))
    endif
	gcc -g $(TARGET) $(RCMODULE) $(CFLAGS) -o $(TARGET:.c=.exe)

endif
	@echo ERROR No.1 : Processing Complete
	@exit /b 1


cleanup:
ifeq ($(OSENV), Linux)
	@rm -f $(CPPMODULE) *.d *.res
else ifeq ($(OSENV), Windows)
	@del $(CPPMODULE) *.d *.res
else
	@echo Unknown OS
endif
	@echo Completed
