//main function, in calls "initialize" and "initialize" calls further required functions


#include "project.h"

int main(int argc,char* argv[])
{
  glutInit(&argc,argv);
  
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
  
  glutInitWindowSize(windowWidth,windowHeight);

  window = glutCreateWindow(windowName);
  
  if (DEF_FULL_SCREEN)
  glutFullScreen();
  glutDisplayFunc(windowDisplay);
  glutReshapeFunc(windowReshape);
  glutSpecialFunc(windowSpecial);
  glutKeyboardFunc(windowKey);

  reset();
  initialize();

  redisplayAll();
  glutMainLoop();
  return 0;
}
