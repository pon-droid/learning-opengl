PKGS=glfw3 glm

CXX=$(CROSS)g++
LD=$(CROSS)ld
AR=$(CROSS)ar
PKG_CONFIG=$(CROSS)pkg-config

CFLAGS=-Wall -Wno-pedantic -std=c++14 `$(PKG_CONFIG) --cflags --static $(PKGS)`
LIBS=`$(PKG_CONFIG) --libs --static $(PKGS)`




gl: main.cpp
	$(CXX) $(CFLAGS) -o gl main.cpp $(LIBS)
