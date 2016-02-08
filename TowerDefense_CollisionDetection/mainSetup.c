//Initilizing main functions

#include "project.h"


void initialize(void)
{
  sidebarInit();
  screenInit();
  initTextures();
  initBackground();
  initObjs();
  initMinions();
  initWaves();
  initShots();
  initPath();
  initPreviewPoints();
  initDefaultTowers();
}

void initTextures(void)
{
  
  textures[TEX_BRICK]     = loadTexBMP("textures/txBrick14.bmp");
  textures[TEX_SPIKE]     = loadTexBMP("textures/txFloor4.bmp");
  textures[TEX_BRICK2]    = loadTexBMP("textures/txBrick13.bmp");
  textures[TEX_STREET1]   = loadTexBMP("textures/Road1.bmp");
  textures[TEX_STREET2]   = loadTexBMP("textures/Road2.bmp");
  textures[TEX_STREET3]   = loadTexBMP("textures/Road3.bmp");
  textures[TEX_STREET4]   = loadTexBMP("textures/Road4.bmp");
  textures[TEX_STREET5]   = loadTexBMP("textures/Road5.bmp");
  textures[TEX_STREET6]   = loadTexBMP("textures/Road6.bmp");
}

void initBackground(void)
{
  backgrounds[BACK_LEFT] = loadTexBMP("textures/despicableme_12_720.bmp");
  backgrounds[BACK_BACK] = loadTexBMP("textures/DESM2SG01_DM2_S0300_P0020_0114_P5160R.bmp");
  backgrounds[BACK_DOWN] = loadTexBMP("textures/txFloor2.bmp");
}

void initObjs(void)
{
  minionObj = loadOBJ("OBJs/minion.obj");
  minionObj1 = loadOBJ("OBJs/minion.obj");
  //minionObj1 = loadOBJ("OBJs/minion.obj");
  //minionTexture = loadMaterial("OBJs/minion.mtl");
  //minionObj1 = loadOBJ("OBJs/ArmyPilot.obj");
}

void initMinions(void)
{
  
  minion m0 = {0,minionObj,{26,-2,-0.5},
	       {1,1,1},{0,270,0},1,{255,255,0},
	       "minion1",1,5,5,1,1};
  minion m1 = {1,minionObj1,{26,-2,-0.5},
         {1,1,1},{0,270,0},1,{0,0,255},
         "minion2",1,5,5,1,1};
  int i;
  for (i=0;i<DEF_MINION_PER_WAVE_SIZE;i++) {
    if(i%2 == 0)
    minions[i] = m0;
    else
    minions[i] = m1;
  }
}

void initWaves()
{
  wave wave = {0,1};
  int i,k;

  for (k=0;k<Length(waves);k++) {
    //for (i=0;i<Length(minions);i++) {
    for (i=0;i<Length(minions);i++) {
      
      /*minions[i].scale.x = (k+1)*0.1;
      minions[i].scale.y = (k+1)*0.1;
      minions[i].scale.z = (k+1)*0.1;*/

      minions[i].scale.x = 1*0.15;
      minions[i].scale.y = 1*0.15;
      minions[i].scale.z = 1*0.15;

      
      minions[i].damage += k;
      minions[i].health += (15*k);
      minions[i].money  += (5*k);
      
      /*minions[i].rgb.r = 27+k*10+i*02;
      minions[i].rgb.g = 0+k*10+i*02;
      minions[i].rgb.b = 0+k*10+i*02;*/
     /* if(i%2 == 0)
      {
        minions[i].rgb.r = 255;
        minions[i].rgb.g = 255;
        minions[i].rgb.b = 25;
      }

      else
      {
        minions[i].rgb.r = 25;
        minions[i].rgb.g = 25;
        minions[i].rgb.b = 112;

      }*/
        
      
      if (k < 3)
	    minions[i].speed = 5-k;
      /* minimum speed of 2 */
      else 
	    minions[i].speed = 2;

      /* default wave length is 10, for each of 0-4 waves decrement by 2 */
      if (i >= (DEF_MINION_PER_WAVE_SIZE-2*k)) {
	    minions[i].inPlay = 0;
      }

      wave.m[i] = minions[i];
    }
    waves[k] = wave;
  }
}

void initShots()
{
  shot s = {0,{0,0,0},TEX_DEFAULT,0};
  int i;
  for (i=0;i<200;i++) {
    shots[i] = s;
  }
}

void initPath(void)
{
  int i,j;
  pathCube currentPath, nextPath, addedPath;
  double moveFactor = 0.08;
  fullPath[0] = pathCubes[0];

  for (i=0;i<(DEF_PATH_LEN-1);i++) {
    addedPath = currentPath = pathCubes[i];
    nextPath = pathCubes[i+1];

    for (j=0;j<DEF_FULL_PATH_LEN;j++) {

      if (currentPath.p.x > nextPath.p.x) addedPath.p.x -= moveFactor;
      else if (currentPath.p.x < nextPath.p.x) addedPath.p.x += moveFactor;

      if (currentPath.p.z > nextPath.p.z) addedPath.p.z -= moveFactor;
      else if (currentPath.p.z < nextPath.p.z) addedPath.p.z += moveFactor;
      fullPath[i*50+j] = addedPath;
    }
  }
}

void initPreviewPoints(void)
{
  point valid_points[DEF_CURRENT_OBJS_SIZE] = {

    {17,0,-17},{17,0,-13},{17,0,-9},{17,0,-5},{17,0,3},{17,0,19},
    {13,0,3},{13,0,11},{13,0,19},
    {9,0,-13},{9,0,-9},{9,0,-5},{9,0,-1},{9,0,3},{9,0,11},{9,0,19},
    {5,0,11},{5,0,19},
    {1,0,-17},{1,0,-13},{1,0,-9},{1,0,-5},{1,0,-1},{1,0,3},{1,0,7},{1,0,11},{1,0,19},
    {-3,0,19},
    {-7,0,-13},{-7,0,-9},{-7,0,-5},{-7,0,-1},{-7,0,3},{-7,0,7},{-7,0,11},{-7,0,15},{-7,0,19},
    {-11,0,15},{-11,0,19},
    {-15,0,-17},{-15,0,-13},{-15,0,-9},{-15,0,-5},{-15,0,-1},{-15,0,3},{-15,0,7},{-15,0,15},{-15,0,19},
    {-19,0,-17},{-19,0,-13},{-19,0,-9},{-19,0,-5},{-19,0,-1},{-19,0,3},{-19,0,7},{-19,0,15},{-19,0,19},
  };
  int i;
  for (i = 0; i < Length(valid_points); i++) {
    preview_points[i].x = valid_points[i].x;
    preview_points[i].y = valid_points[i].y;
    preview_points[i].z = valid_points[i].z;
  }
}

void initDefaultTowers(void)
{
  int i;
  for (i=0;i<Length(default_towers);i++) {
    towers[i] = default_towers[i];
  }
  lastCurrentObject = 6;
  currentRed = 35;
}

void screenInit(void)
{

  screen = glutCreateSubWindow(window, 0, 0, 
			       windowWidth-DEF_SIDEBAR_WIDTH-DEF_SPACER,
			       windowHeight-DEF_SPACER);
  glutDisplayFunc(screenDisplay);
  glutReshapeFunc(screenReshape);
  glutMouseFunc(screenMouse);
  glutPassiveMotionFunc(screenPmotion);

  glutKeyboardFunc(windowKey);
  glutSpecialFunc(windowSpecial);
}

void sidebarInit(void)
{

  sidebar = glutCreateSubWindow(window, windowWidth-DEF_SIDEBAR_WIDTH, 0, 
				DEF_SIDEBAR_WIDTH, windowHeight);
  glutDisplayFunc(sidebarDisplay);
  glutReshapeFunc(sidebarReshape);
  glutMouseFunc(sidebarMouse);

  glutKeyboardFunc(windowKey); 
  glutSpecialFunc(windowSpecial);
}

