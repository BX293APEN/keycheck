TARGET			:= $(firstword $(MAKECMDGOALS))
ARG1			:= $(word 2, $(MAKECMDGOALS))
ARG2			:= $(word 3, $(MAKECMDGOALS))

CFLAGS			:= -pthread
WINFLAGS		:= -lwsock32 -lgdi32 -lmingw32
NOCONSOLEFLAG	:= -mwindows
OSENV			:=

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

run:
ifeq ($(ARG1),)
	@python
else ifeq ($(findstring .py, $(ARG1)), .py)
	python $(ARG1)
else ifeq ($(findstring .cpp, $(ARG1)), .cpp)
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