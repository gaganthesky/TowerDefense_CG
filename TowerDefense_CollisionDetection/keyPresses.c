//All the key press events defined here


#include "project.h"


void windowDisplay(void)
{

  glClearColor(0.8, 0.8, 0.8, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glutSwapBuffers();
}

void windowKey(unsigned char key,int x,int y)
{
  if (key == 27) exit(0);
  
  else if (key == 32) { 
    if (gameStarted == DEF_GAME_STARTED) {
      gameStarted=1; 
      gamePaused=0;
      waveNumber=1;
      glutTime(1);
    } else {
  
      if (waveNumber < DEF_LAST_WAVE) {
	int i,inPlay = 0;
	for (i=0;i<Length(waves[waveNumber-1].m);i++){
	  if (waves[waveNumber-1].m[i].inPlay == 1) inPlay = 1;
	}
	if (inPlay == 0) waveNumber++;
      }
    }
  }
  else if (key == 'c' || key == 'C') showAttackRadius = 1-showAttackRadius;
  else if (key == 'p') gamePaused = 1-gamePaused;
  else if (key == '1') changeObjectSelected(OBJ_BASIC);
  else if (key == '2') changeObjectSelected(OBJ_ADV);
  else if (key == '3') changeObjectSelected(OBJ_CONE);
  else if (key == '4') changeObjectSelected(OBJ_ADV_CONE);
  else if (key == '5') changeObjectSelected(OBJ_SQUARE);
  redisplayAll();
}


void windowSpecial(int key,int x,int y)
{
  int modifiers = glutGetModifiers();
  
  if (modifiers == GLUT_ACTIVE_SHIFT) {
  
    if (key == GLUT_KEY_RIGHT) th += 5;
    else if (key == GLUT_KEY_LEFT) th -= 5;
    else if (key == GLUT_KEY_UP) ph += 5;
    else if (key == GLUT_KEY_DOWN) ph -= 5;
  }
  
  else {
  
    if (key == GLUT_KEY_RIGHT) ecZ -= .5;
    else if (key == GLUT_KEY_LEFT) ecZ += .5;
    else if (key == GLUT_KEY_UP) ecX -= .5;
    else if (key == GLUT_KEY_DOWN) ecX += .5;
  }
  
  th %= 360;
  ph %= 360;

  redisplayAll();
}

void windowReshape(int width,int height)
{
  windowHeight = height;
  windowWidth = width;

  glViewport(0,0,width,height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0,width,height,0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glutSetWindow(screen);
  glutPositionWindow(0, 0);
  glutReshapeWindow(windowWidth-DEF_SIDEBAR_WIDTH-DEF_SPACER, windowHeight);

  glutSetWindow(sidebar);
  glutPositionWindow(windowWidth-DEF_SIDEBAR_WIDTH,0);
  glutReshapeWindow(DEF_SIDEBAR_WIDTH,windowHeight);
}

