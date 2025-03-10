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
ifeq ($(TARGET),)
	@python

else ifeq ($(findstring .py, $(TARGET)), .py)
	python $(TARGET)

else ifeq ($(findstring .cpp, $(TARGET)), .cpp)
    ifneq (${CPPMODULE_EXIST}, ${CPPMODULE})
		g++ -x c++-header -g $(CPPHEADER) -o $(CPPMODULE)
    endif
    ifeq ($(OSENV), Windows)
		$(eval CFLAGS := $(CFLAGS) $(WINFLAGS))
    endif
    ifneq ($(OPTION), )
		$(eval CFLAGS := $(CFLAGS) $(NOCONSOLEFLAG))
    endif
	g++ -g $(TARGET) $(CFLAGS) -o $(TARGET:.cpp=.exe)

else ifeq ($(findstring .c, $(TARGET)), .c)
    ifeq ($(OSENV), Windows)
		$(eval CFLAGS := $(CFLAGS) $(WINFLAGS))
    endif
    ifneq ($(OPTION), )
		$(eval CFLAGS := $(CFLAGS) $(NOCONSOLEFLAG))
    endif
	gcc -g $(TARGET) $(CFLAGS) -o $(TARGET:.c=.exe)

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
