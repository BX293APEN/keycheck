TARGET			:= $(firstword $(MAKECMDGOALS))
ARG1			:= $(word 2, $(MAKECMDGOALS))
ARG2			:= $(word 3, $(MAKECMDGOALS))

CFLAGS			:= -pthread
WINFLAGS		:= -lwsock32 -lgdi32 -lmingw32
NOCONSOLEFLAG	:= -mwindows
OSENV			:=

CPPHEADER		:= ioset.hpp
CPPMODULE		:= $(CPPHEADER).gch
CPPMODULE_EXIST	:=

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
else ifeq ($(OSENV), Linux)
	CPPMODULE_EXIST := $(shell ls | grep ${CPPMODULE})
endif

run:
ifeq ($(ARG1),)
	@python

else ifeq ($(findstring .py, $(ARG1)), .py)
	python $(ARG1)

else ifeq ($(findstring .cpp, $(ARG1)), .cpp)
    ifneq (${CPPMODULE_EXIST}, ${CPPMODULE})
		g++ -x c++-header -g $(CPPHEADER) -o $(CPPMODULE)
    endif
    ifeq ($(OSENV), Windows)
		$(eval CFLAGS := $(CFLAGS) $(WINFLAGS))
    endif
    ifneq ($(ARG2), )
		$(eval CFLAGS := $(CFLAGS) $(NOCONSOLEFLAG))
    endif
	g++ -g $(ARG1) $(CFLAGS) -o $(ARG1:.cpp=.exe)

else ifeq ($(findstring .c, $(ARG1)), .c)
    ifeq ($(OSENV), Windows)
		$(eval CFLAGS := $(CFLAGS) $(WINFLAGS))
    endif
    ifneq ($(ARG2), )
		$(eval CFLAGS := $(CFLAGS) $(NOCONSOLEFLAG))
    endif
	gcc -g $(ARG1) $(CFLAGS) -o $(ARG1:.c=.exe)

endif
	@echo ERROR No.1 : Processing Complete
	@exit /b 1


cleanup:
ifeq ($(OSENV), Linux)
	@rm -f $(CPPMODULE) *.d
else ifeq ($(OSENV), Windows)
	@del $(CPPMODULE) *.d
else
	@echo Unknown OS
endif
	@echo Completed
