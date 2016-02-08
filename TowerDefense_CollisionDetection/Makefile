# Target to build
TARGET := project

# GL Libraries
# LINUX
LIBS=-lglut -lGL -lGLU -lm
# OSX
#LIBS=-framework OpenGL -framework GLUT 

all: $(TARGET)

#  Generic compile rules
.c.o:
	gcc -c -O -Wall $<

#  Generic compile and link
%: %.c project.a
	gcc -Wall -O3 -o ./finalProject_CG $^ $(LIBS)

#  Delete unwanted files - Linux or OS/X
clean:;rm -f $(TARGET) *.o *.a .finalProject_CG *~

#  Create archive
project.a:requiredVariables.o debugCode.o loadTexBMP.o loadObj.o drawOpenGLshapes.o drawModels.o modelTower.o requiredFunctions.o mainSetup.o drawExtraStuff.o animationCode.o collision.o keyPresses.o outputScreen.o glutWindow.o sceneSetup.o
	ar -rcs project.a $^
