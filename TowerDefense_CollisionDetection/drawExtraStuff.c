//Code for Path, Background etc.


#include "project.h"

void drawAllAlxes(void)
{

  const double len=5.0;

  if (axes) {
    glDisable(GL_LIGHTING);
    glColor3fv(white);
    glBegin(GL_LINES);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(len,0.0,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,len,0.0);
    glVertex3d(0.0,0.0,0.0);
    glVertex3d(0.0,0.0,len);
    glEnd();
    
    glRasterPos3d(len,0.0,0.0);
    print("X");
    glRasterPos3d(0.0,len,0.0);
    print("Y");
    glRasterPos3d(0.0,0.0,len);
    print("Z");
    glEnable(GL_LIGHTING);
  }

}

void drawRelevantParameters(void)
{
  if (vals) {
    glColor3fv(white);
    
    printAt(5,5,"Angle=%d,%d  Dim=%.1f FOV=%d Light=%s",
	    th,ph,dim,fov,light?"On":"Off");
    if (light) {
      printAt(5,45,"Distance=%d Elevation=%.1f",distance,lightY);
      printAt(5,25,"Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",
	      ambient,diffuse,specular,emission,shinyvec[0]);
    }
  }
}

void drawGrid(void)
{
  if (grid) {
    int i,j;
    glDisable(GL_LIGHTING);
    glColor3fv(white);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(2,1);
    glBegin(GL_LINES);
    
    for (i=-21;i<21;i+=2){
      for (j=-19;j<23;j+=40){
	glVertex3d(i,-2.8,j);
      }
    }
    
    for (i=-19;i<23;i+=2){
      for (j=-21;j<20;j+=40){
	glVertex3d(j,-2.8,i);
      }
    }
    glEnd();
    glDisable(GL_POLYGON_OFFSET_FILL);
    glEnable(GL_LIGHTING);
  }
}

void drawBackground(double D)
{
  glColor3fv(white);
  glEnable(GL_TEXTURE_2D);

  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_RIGHT]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(-D,-D,-D);
  glTexCoord2f(1,0); glVertex3f(+D,-D,-D);
  glTexCoord2f(1,1); glVertex3f(+D,+D,-D);
  glTexCoord2f(0,1); glVertex3f(-D,+D,-D);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_FRONT]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(+D,-D,-D);
  glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
  glTexCoord2f(1,1); glVertex3f(+D,+D,+D);
  glTexCoord2f(0,1); glVertex3f(+D,+D,-D);
  glEnd();
  
  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_LEFT]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(+D,-D,+D);
  glTexCoord2f(1,0); glVertex3f(-D,-D,+D);
  glTexCoord2f(1,1); glVertex3f(-D,+D,+D);
  glTexCoord2f(0,1); glVertex3f(+D,+D,+D);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_BACK]);
  glBegin(GL_QUADS);
  glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
  glTexCoord2f(1,0); glVertex3f(-D,-D,-D);
  glTexCoord2f(1,1); glVertex3f(-D,+D,-D);
  glTexCoord2f(0,1); glVertex3f(-D,+D,+D);
  glEnd();

  glBindTexture(GL_TEXTURE_2D,backgrounds[BACK_DOWN]);
  glBegin(GL_QUADS);
  glTexCoord2f(1,1); glVertex3f(+D,-D,-D);
  glTexCoord2f(0,1); glVertex3f(-D,-D,-D);
  glTexCoord2f(0,0); glVertex3f(-D,-D,+D);
  glTexCoord2f(1,0); glVertex3f(+D,-D,+D);
  glEnd();

  glDisable(GL_TEXTURE_2D);
}

void drawLight(void)
{

  if (light) {

    float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
    float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
    float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};

    float Position[]  = {lightY,distance*Sin(lightPh),distance*Cos(lightPh),1.0};

    glColor3fv(white);
    sphere(Position[0],Position[1],Position[2] , 0.1,0);

    glEnable(GL_NORMALIZE);

    glEnable(GL_LIGHTING);

    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
    glLightfv(GL_LIGHT0,GL_POSITION,Position);
  }
  else
    glDisable(GL_LIGHTING);
}

void drawBoard(void)
{
  board();
}


void drawPath(void)
{
  path();
}

// Draws the shots from the towers

void drawShots(void)
{
  int i;
  for (i=0;i<Length(shots);i++) {
    if (shots[i].inPlay == 1) shotModel(shots[i]);
  }
}

void drawMinions(void)
{
  int i,k;
  for (k=0;k<waveNumber;k++) {
    for (i=0;i<Length(waves[k].m);i++) {
      if (waves[k].m[i].inPlay == 1) minionModel(waves[k].m[i]);
    }
  }
}

//  draw the current objects (towers)


void drawObjects(void)
{
  int i;

  if (preview_tower.id != DEF_OBJ_SEL) {
    tower t = {preview_tower.id,preview_tower.type,preview_tower.inPlay,
	       {preview_tower.translation.x,preview_tower.translation.y,preview_tower.translation.z},
	       {1,1,1},{0,0,0},preview_tower.texture,{1,1,1},
	       preview_tower.name,1,preview_tower.range,preview_tower.damage,
	       preview_tower.fireRate,0,preview_tower.cost};

    showAttackRadius = 1;
    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE,GL_ONE_MINUS_DST_COLOR);
    if (t.type == OBJ_BASIC) defenceTower(t);
    else if (t.type == OBJ_ADV) defenceTower(t);
    else if (t.type == OBJ_CONE) defenceTower(t);
    else if (t.type == OBJ_ADV_CONE) defenceTower(t);
    else if (t.type == OBJ_SQUARE) defenceTower(t);
    else if (t.type == OBJ_ADV_SQUARE) defenceTower(t);
    else if (t.type == OBJ_FIRE) defenceTower(t);
    else if (t.type == OBJ_FIRE2) defenceTower(t);
    else if (t.type == OBJ_ICE) defenceTower(t);
    else if (t.type == OBJ_ICE2) defenceTower(t);
    else if (t.type == OBJ_EARTH) defenceTower(t);
    else if (t.type == OBJ_EARTH2) defenceTower(t);
    else if (t.type == OBJ_POISON) defenceTower(t);
    else if (t.type == OBJ_POISON2) defenceTower(t);
    glDisable(GL_BLEND);
    showAttackRadius = 0;
  }

  for (i = 0; i < Length(towers); i++) {
    if (towers[i].inPlay) {
      tower t = {0,towers[i].type,towers[i].inPlay,
		 {towers[i].translation.x,towers[i].translation.y,towers[i].translation.z},
		 {1,1,1},{0,0,0},towers[i].texture,
		 {towers[i].rgb.r,towers[i].rgb.g,towers[i].rgb.b},
		 towers[i].name,towers[i].level,towers[i].range,towers[i].damage,
		 towers[i].fireRate,towers[i].lastFired,towers[i].cost,towers[i].description};

      if (renderMode == DEF_SELECT) {
	glDisable(GL_DITHER);
	glDisable(GL_LIGHTING);
	glColor3ub(towers[i].rgb.r,towers[i].rgb.g,towers[i].rgb.b);
      }
      if (t.type == OBJ_BASIC) defenceTower(t);
      else if (t.type == OBJ_ADV) defenceTower(t);
      else if (t.type == OBJ_CONE) defenceTower(t);
      else if (t.type == OBJ_ADV_CONE) defenceTower(t);
      else if (t.type == OBJ_SQUARE) defenceTower(t);
      else if (t.type == OBJ_ADV_SQUARE) defenceTower(t);
      else if (t.type == OBJ_FIRE) defenceTower(t);
      else if (t.type == OBJ_FIRE2) defenceTower(t);
      else if (t.type == OBJ_ICE) defenceTower(t);
      else if (t.type == OBJ_ICE2) defenceTower(t);
      else if (t.type == OBJ_EARTH) defenceTower(t);
      else if (t.type == OBJ_EARTH2) defenceTower(t);
      else if (t.type == OBJ_POISON) defenceTower(t);
      else if (t.type == OBJ_POISON2) defenceTower(t);
      
      if (renderMode == DEF_SELECT) {
	glEnable(GL_DITHER);
	glEnable(GL_LIGHTING);
      }
    }
  }
}

//draws the entire scene

void drawScene(void)
{
  if (renderMode == DEF_RENDER) {
    drawAllAlxes();
    drawGrid();
    drawRelevantParameters();
    drawBackground(3.5*dim);
    drawLight();
    
    drawBoard();
    drawPath();
    drawShots();
  }
  drawMinions();
  drawObjects();
  
}
