//Functions used for game play are declared here

#include "project.h"

void changeObjectSelected(int newObjectSelected)
{
  objectSelected = newObjectSelected;
  preview_tower.id = objectSelected;
  preview_tower.translation.x = -255;
  preview_tower.translation.y = -255;
  preview_tower.translation.z = -255;
  setCurrentTowerData(objectSelected);
}


void setCurrentTowerData(int type)
{
  currentTextureSelected = tower_data[type-1].texture;
  currentTowerName = tower_data[type-1].name;
  currentTowerRange = tower_data[type-1].range;
  currentTowerDamage = tower_data[type-1].damage;
  currentTowerFireRate = tower_data[type-1].fireRate;
  currentTowerCost = tower_data[type-1].cost;
  currentTowerDescription = tower_data[type-1].description;
}

point findMousePosition(int x, int y)
{
  point point;
  GLfloat winX, winY, winZ;
  GLdouble posX, posY, posZ;
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];

  glGetIntegerv(GL_VIEWPORT, viewport);
  glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
  glGetDoublev(GL_PROJECTION_MATRIX, projection);

  winX = (float)x;
  winY = (float)viewport[3]-(float)y-1;
 
  glReadPixels(x, (int)winY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );

 
  gluUnProject( winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);

 
  if (debug) {
    printf("\nobject selected: %d\n", objectSelected);
    printf("x y: %d %d\n", x, y);
    printf("vp : %d %d\n", viewport[2], viewport[3]);
    printf("win: %f %f %f\n", winX, winY, winZ);
    printf("pos: %f %f %f\n", posX, posY, posZ);
  }

  point.x = posX;
  point.y = posY;
  point.z = posZ;

  return point;
}

point findPreviewPosition(int x, int y)
{
  point p = findMousePosition(x,y);
  point returnP;
  int finalX = (int)p.x;
  int finalZ = (int)p.z;
  int i,j,exists;

  returnP.x = DEF_BAD_POINT;
  returnP.y = DEF_BAD_POINT;
  returnP.z = DEF_BAD_POINT;
  exists = 0;


  for (i=0; i < DEF_CURRENT_OBJS_SIZE; i++) {

    if (finalX >= (preview_points[i].x-2) && finalX <= (preview_points[i].x+2) &&
	finalZ >= (preview_points[i].z-2) && finalZ <= (preview_points[i].z+2)) {

      for(j=0; j < Length(towers);j++) {
	if (towers[j].translation.x == preview_points[i].x &&
	    towers[j].translation.z == preview_points[i].z) {

	  exists = 1;
	  break;
	}
      }

      if (!exists) {
	returnP.x = preview_points[i].x;
	returnP.y = 0;
	returnP.z = preview_points[i].z;
	return returnP;
      }
    }
  }
  return returnP;
}

void incrementCurrentRGB(void)
{
  currentRed += 10;
  if (currentRed > 255) {
    currentRed = 5;
    currentGreen += 10;
    if (currentGreen > 255) {
      currentGreen = 5;
      currentBlue += 10;
      if (currentBlue > 255) {
	currentBlue = 5;
      }
    }
  }
}


void processPicks(void)
{
  int i;
  GLint viewport[4];
  GLubyte pixel[3];
  glGetIntegerv(GL_VIEWPORT,viewport);
  glReadPixels(mouseX,viewport[3]-mouseY,1,1,GL_RGB,GL_UNSIGNED_BYTE,(void *)pixel);
  if (debug) printf("R:%d  G:%d  B:%d\n",pixel[0],pixel[1],pixel[2]);
  for (i = 0; i < Length(towers); i++){
    GLint red,green,blue;
    red = towers[i].rgb.r;
    green = towers[i].rgb.g;
    blue = towers[i].rgb.b;

    if (pixel[0] == red && pixel[1] == green && pixel[2] == blue) {
      objectPicked = i;
      setCurrentTowerData(towers[i].type);
      break;
    }

    else {
      objectPicked = DEF_OBJ_PICKED;
    }
  }
}

void redisplayAll(void)
{
  glutSetWindow(screen);


  screenReshape(windowWidth-DEF_SIDEBAR_WIDTH-DEF_SPACER, windowHeight);
  glutPostRedisplay();

  glutSetWindow(sidebar);
  sidebarReshape(windowWidth, windowHeight);
  glutPostRedisplay();
}

void reset()
{
  int i;

  fontStyle = DEF_FONT_STYLE;

  asp  = DEF_ASP;
  dim  = DEF_DIM;
  th   = DEF_TH;
  ph   = DEF_PH;
  fov  = DEF_FOV;
  ecX  = DEF_ECX;
  ecY  = DEF_ECY;
  ecZ  = DEF_ECZ;  

  axes = DEF_AXES;
  grid = DEF_GRID;
  vals = DEF_VALS;

  detectCollisions = DEF_COLLISION;
  lastShot = DEF_LAST_SHOT;

  gameStarted    = DEF_GAME_STARTED;
  gamePaused     = DEF_GAME_PAUSED;
  gameSpeed      = DEF_GAME_SPEED;
  lightPh        = DEF_L_PH;
  moveTowerTopsB = DEF_MOVE_TOWER_TOPS;
  towerTh        = DEF_TOWER_TH;

  lives      = DEF_LIVES;
  money      = DEF_MONEY;
  scrolls    = DEF_SCROLLS;
  waveNumber = DEF_WAVE;
  lastWave   = DEF_LAST_WAVE;

  for (i=0;i<DEF_CURRENT_OBJS_SIZE;i++) {
    towers[i].id = 0;
    towers[i].type = 0;
    towers[i].translation.x = 0;
    towers[i].translation.y = 0;
    towers[i].translation.z = 0;
    towers[i].texture = 0;
    towers[i].rgb.r = 0;
    towers[i].rgb.g = 0;
    towers[i].rgb.b = 0;
  }
  preview_tower.id = 0;
  preview_tower.type = 0;
  preview_tower.translation.x = 0;
  preview_tower.translation.y = 0;
  preview_tower.translation.z = 0;
  preview_tower.texture = 0;
  preview_tower.name = "preview";

  preview           = DEF_PREVIEW;
  objectSelected    = DEF_OBJ_SEL;
  lastCurrentObject = DEF_LAST_CURRENT_OBJECT;
  renderMode        = DEF_RENDER;
  objectPicked      = DEF_OBJ_PICKED;
  currentRed   = DEF_CURRENT_RED;
  currentGreen = DEF_CURRENT_GREEN;
  currentBlue  = DEF_CURRENT_BLUE;

  initWaves();

  light     = DEF_LIGHT;
  distance  = DEF_DISTANCE;
  ambient   = DEF_AMBIENT;
  diffuse   = DEF_DIFFUSE;
  emission  = DEF_EMISSION;
  specular  = DEF_SPECULAR;
  shininess = DEF_SHININESS;
  lightY    = DEF_L_Y;

  currentTexture = TEX_DEFAULT;
  currentTextureSelected = TEX_DEFAULT;
}
