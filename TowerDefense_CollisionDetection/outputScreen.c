#include "project.h"

void displayInit(void)
{
 
  setFont("helvetica", 18);

  glClearColor(0.8,0.8,0.8,0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
}

void displayEye(void)
{
  double Ex = -2*dim*Sin(th)*Cos(ph);
  double Ey = +2*dim        *Sin(ph);
  double Ez = +2*dim*Cos(th)*Cos(ph);
  gluLookAt(Ex+ecX,Ey,Ez+ecZ, ecX,ecY,ecZ , 0,Cos(ph),0);
}

void screenDisplay(void)
{

  displayInit();
  displayEye();

  drawScene();

  if (renderMode == DEF_SELECT) {
    processPicks();
    renderMode = DEF_RENDER;
  }
  else {
    glFlush();
    glutSwapBuffers();
  }
  
  errCheck("display sanity check");
}

void screenProject(double fov, double asp, double dim)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(fov,asp,dim/16,16*dim);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void screenReshape(int width, int height)
{
  asp = (height>0) ? (double)width/height : 1;
  windowHeight = height;

  glViewport(0,0, width,height);
  screenProject(fov,asp,dim);
}

void screenMouse(int btn, int state, int x, int y)
{
  point p;
  if ((btn != GLUT_LEFT_BUTTON || state != GLUT_DOWN)) 
    return;
  
  p = findPreviewPosition(x,y);
  mouseX = x;
  mouseY = y;
  renderMode = DEF_SELECT;

  if (objectSelected != DEF_OBJ_SEL && p.x != DEF_BAD_POINT) {
    int modifiers = glutGetModifiers();
    renderMode = DEF_RENDER;

    if (money >= tower_data[objectSelected-1].cost) {
      info = "cha-ching$ thanks buddy.";
      setCurrentTowerData(objectSelected);
    } else {
      info = "Not enough $$$.";
      objectSelected = DEF_OBJ_SEL;
      preview_tower.id = DEF_OBJ_SEL;
    }

    if (objectSelected != DEF_OBJ_SEL) {
      tower t = {objectSelected,objectSelected,1,
		 {p.x,p.y,p.z},{1,1,1},{0,0,0},currentTextureSelected,
		 {currentRed,currentGreen,currentBlue},

		 currentTowerName,1,currentTowerRange,currentTowerDamage,
		 currentTowerFireRate,0,currentTowerCost,"Description"};
      towers[lastCurrentObject] = t;
      modifyMoney(0,currentTowerCost);

      incrementCurrentRGB();

      if (debug) printf("just added object id: %d\n",lastCurrentObject);
      lastCurrentObject++;
      if (lastCurrentObject == DEF_CURRENT_OBJS_SIZE) lastCurrentObject = 0;

      if (modifiers != GLUT_ACTIVE_SHIFT) {
	objectSelected = DEF_OBJ_SEL;
	preview_tower.id = DEF_OBJ_SEL;
      }
    }
  }
  
  redisplayAll();
}

void screenPmotion(int x, int y)
{
  if (preview && objectSelected != DEF_OBJ_SEL) {
    point p = findPreviewPosition(x,y);
    if (p.x != DEF_BAD_POINT) {
      preview_tower.id = objectSelected;
      preview_tower.type = objectSelected;
      preview_tower.inPlay = 1;
      preview_tower.translation.x = p.x;
      preview_tower.translation.y = p.y;
      preview_tower.translation.z = p.z;
      preview_tower.texture = tower_data[objectSelected-1].texture;
      preview_tower.name = tower_data[objectSelected-1].name;
      preview_tower.range = tower_data[objectSelected-1].range;
      preview_tower.damage = tower_data[objectSelected-1].damage;
      preview_tower.fireRate = tower_data[objectSelected-1].fireRate;
      preview_tower.cost = tower_data[objectSelected-1].cost;

      redisplayAll();
    }
  }
}

