//This file also has code for star, spike etc that i didn't use.
//Came across various functions to write stars, spikes etc to decorate 
//towers or make different shapes of shots
//Although did not use it further


#include "project.h"

void pyramid(double x, double y, double z,
		    double dx, double dy, double dz,
		    double th)
{
  glPushMatrix();
  
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  cone(0,0,0, 1,1, 90);

  glPopMatrix();
}

void star(double x, double y, double z,
		 double dx, double dy, double dz,
		 double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  pyramid(0,0.5,0, 1,3,1, 0);
  glPushMatrix();
  glRotatef(-90,1,0,0);
  pyramid(0,0.5,0, 1,3,1, 90);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90,1,0,0);
  pyramid(0,0.5,0, 1,3,1, 0);
  glPopMatrix();

  glPushMatrix();
  glRotatef(-90,0,0,1);
  pyramid(0,0.5,0, 1,3,1, 90);
  glPopMatrix();

  glPushMatrix();
  glRotatef(90,0,0,1);
  pyramid(0,0.5,0, 1,3,1, -90);
  glPopMatrix();

  glPushMatrix();
  glRotatef(180,1,0,0);
  pyramid(0,0.5,0, 1,3,1, 0);
  glPopMatrix();

  glPopMatrix();
}

void spike(double x, double y, double z,
		  double r,double h,int deg,
		  double ox,double oy,double oz)
{
  currentTexture = textures[TEX_SPIKE];
  glPushMatrix();
  glRotated(oz,0,0,1);
  glRotated(oy,0,1,0);
  glRotated(ox,1,0,0);

  cone(x,y,z, r,h,deg);
  glPopMatrix();
  currentTexture = textures[TEX_DEFAULT];
}

void board(void)
{
  int i,j;
  glPushMatrix();

  if (renderMode == DEF_RENDER) {
    currentTexture = textures[TEX_GRASS];
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }

  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(2,1);
  glColor3f(1,1,1);
  glNormal3f(0,1,0);
  for (i=-DEF_D_FLOOR;i<DEF_D_FLOOR;i+=2){
    glBegin(GL_QUADS);
    for(j=-DEF_D_FLOOR;j<DEF_D_FLOOR;j+=2){
      glTexCoord2f(0,0); glVertex3f(i,DEF_Y_FLOOR,j);
      glTexCoord2f(1,0); glVertex3f(i,DEF_Y_FLOOR,j+2);
      glTexCoord2f(1,1); glVertex3f(i+2,DEF_Y_FLOOR,j+2);
      glTexCoord2f(0,1); glVertex3f(i+2,DEF_Y_FLOOR,j);
    }
    glEnd();
  }
  glDisable(GL_POLYGON_OFFSET_FILL);

  if  (renderMode == DEF_RENDER) {
    glDisable(GL_TEXTURE_2D);
    currentTexture = textures[TEX_DEFAULT];
  }
  glPopMatrix();
}

void pathBlock(pathCube p)
{
  glPushMatrix();

  if (renderMode == DEF_RENDER) {
    currentTexture = textures[p.texture];
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,currentTexture);
  }
  glEnable(GL_POLYGON_OFFSET_FILL);
  glPolygonOffset(1,1);
  glColor3f(1,1,1);
  glNormal3f(0,1,0);

  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(p.p.x-2, p.p.y, p.p.z-2);
  glTexCoord2f(1,0); glVertex3f(p.p.x-2, p.p.y, p.p.z+2);
  glTexCoord2f(1,1); glVertex3f(p.p.x+2, p.p.y, p.p.z+2);
  glTexCoord2f(0,1); glVertex3f(p.p.x+2, p.p.y, p.p.z-2);
  glEnd();

  glDisable(GL_POLYGON_OFFSET_FILL);

  if  (renderMode == DEF_RENDER) {
    glDisable(GL_TEXTURE_2D);
    currentTexture = textures[TEX_DEFAULT];
  }

  glPopMatrix();
}

void path(void)
{
  int i;
  glPushMatrix();
  
  for (i=0; i < DEF_PATH_LEN; i++) {
    pathBlock(pathCubes[i]);
  }
  currentTexture = textures[TEX_DEFAULT];
  glPopMatrix();
}


void wall(double x,double y,double z,
	  double dx,double dy,double dz,
	  double th)
{
  glPushMatrix();
  glTranslated(x,y,z);
  glRotated(th,0,1,0);
  glScaled(dx,dy,dz);

  currentTexture = textures[TEX_BRICK];
  
  cube(0,-2,0, 0.2,1,1, 0);
  cube(0,0,0, 0.2,1,1, 0);
  cube(0,2,0, 0.2,1,1, 0);
  cube(0,4,0, 0.2,1,1, 0);

  glPushMatrix();
  glTranslated(0,0,-2);
  cube(0,-2,0, 0.2,1,1, 0);
  cube(0,0,0, 0.2,1,1, 0);
  cube(0,2,0, 0.2,1,1, 0);
  cube(0,4,0, 0.2,1,1, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0,0,2);
  cube(0,-2,0, 0.2,1,1, 0);
  cube(0,0,0, 0.2,1,1, 0);
  cube(0,2,0, 0.2,1,1, 0);
  cube(0,4,0, 0.2,1,1, 0);
  glPopMatrix();

  
  glPushMatrix();
  glTranslated(1,4,0);
  glRotated(90,0,0,1);
  glRotated(90,1,0,0);
  cube(0,-2,0, 0.2,1,1, 0);
  cube(0,0,0, 0.2,1,1, 0);
  cube(0,2,0, 0.2,1,1, 0);
  glPopMatrix();

  glPushMatrix();
  glTranslated(0,5,0);
  cube(0,0,1.3, 0.2,1,0.7, 0);
  cube(0,0,-1.3, 0.2,1,0.7, 0);
  glPopMatrix();
  currentTexture = textures[TEX_DEFAULT];

  glPopMatrix();
}

// draws an individual shot

void shotModel(shot s)
{
  glPushMatrix();
  glTranslated(s.p.x, s.p.y, s.p.z);
  currentTexture = textures[s.texture];
  sphere(0,0,0, 0.5,towerTh);
  currentTexture = textures[TEX_DEFAULT];
  glPopMatrix();
}
void minionModel(minion m)
{
  glPushMatrix();
  glTranslated(m.translation.x,m.translation.y,m.translation.z);
  glRotated(m.rotation.y,0,1,0);
  glScaled(m.scale.x,m.scale.y,m.scale.z);
  glColor3f((double)m.rgb.r/100,(double)m.rgb.g/100,(double)m.rgb.b/100);
  glCallList(m.type);

  if (detectCollisions) {
    glColor3f(1,1,0);
    glTranslated(-2,4,-0.5);
    glutSolidSphere(5,16,16);
  }
  glColor3fv(white);

  glPopMatrix();
}

