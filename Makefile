SRCS		= rrt/camera.cpp rrt/primitive.cpp rrt/ray.cpp rrt/hit.cpp \
			  rrt/image.cpp rrt/renderer.cpp rrt/scene.cpp rrt/shader.cpp \
			  rrt/math.cpp rrt/surface.cpp rrt/geom.cpp \
			  rrt/matrix4.cpp rrt/transform.cpp \
			  primitive/cube.cpp primitive/plane.cpp primitive/sphere.cpp \
			  primitive/triangle.cpp primitive/mesh.cpp

OBJS		= ${SRCS:%.cpp=%.o}
BIN			= scenes/snooker scenes/cornell meshtest

BOOST		= /opt/local
BOOSTINC	= $(BOOST)/include
BOOSTLIB	= $(BOOST)/lib
BOOSTLIBS	= -lboost_thread-mt -lboost_system-mt

GD			= /opt/local
GDLIBS		= -lassimp -lgd -lpng -ljpeg -lz

CPPFLAGS	= -I$(BOOSTINC) -I$(CURDIR)
CXXFLAGS	= -g -O3 -Wall -Wextra -std=c++11
LDFLAGS		= -Wl,-rpath,$(BOOSTLIB) -L$(BOOSTLIB)
LIBS		= $(BOOSTLIBS) $(GDLIBS)

all:		$(BIN)

scenes/snooker:		scenes/snooker.o $(OBJS)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ scenes/snooker.o $(OBJS) $(LIBS)

scenes/cornell:		scenes/cornell.o $(OBJS)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ scenes/cornell.o $(OBJS) $(LIBS)

scenes/meshtest:	scenes/meshtest.o $(OBJS)
		$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ scenes/meshtest.o $(OBJS) $(LIBS)

clean:
		$(RM) $(BIN) $(OBJS) scenes/*.o
