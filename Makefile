CC = /usr/bin/g++

#OPENGL LIBS FOR LINUX
GLLIB :=  -lGL -lGLU -lglut

#COMPILER FLAGS
CCFLAGS :=

INCDIR := -I/usr/include
LDLIBS := $(GLLIB)

TARGET = bezier
OBJS = bezier.o


all: $(TARGET)


$(TARGET): $(OBJS)
	$(CC)  $^ $(CCFLAGS) $(LDLIBS)  -o $@

%.o : %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $(INCDIR) $<

clean:
	rm -rf $(OBJS) $(TARGET)

