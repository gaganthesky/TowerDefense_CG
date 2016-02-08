
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <time.h>

#ifdef USEGLEW
#include <GL/glew.h>
#endif
#define GL_GLEXT_functionDeclarations

#include <GL/glut.h>
#include "basicSetup.h"
#include "define_all_structs.h"
#include "functionDeclarations.h"


extern int detectCollisions;
extern int lastShot;
extern shot shots[200];

extern int gameStarted;
extern int gamePaused;
extern int gameSpeed;
extern int lightPh;
extern int moveTowerTopsB;
extern int towerTh;


extern int debug;
extern char *windowName;
extern int windowHeight;
extern int windowWidth;
extern GLuint window, screen, sidebar;
extern GLvoid *fontStyle;

extern double asp;
extern double dim;
extern int th;
extern int ph;
extern int fov;
extern double ecX;
extern double ecY;
extern double ecZ;

extern int axes;
extern int grid;
extern int showAttackRadius;
extern int vals;

extern char *info;
extern int lives;
extern int money;
extern int scrolls;
extern int score;
extern int waveNumber;
extern int lastWave;

extern int mouseX, mouseY, mouseZ;

extern tower towers[DEF_CURRENT_OBJS_SIZE];
extern tower preview_tower;
extern point preview_points[DEF_CURRENT_OBJS_SIZE];
extern int preview;
extern int objectSelected;
extern int lastCurrentObject;
extern int renderMode;
extern int objectPicked;
extern int currentRed;
extern int currentGreen;
extern int currentBlue;
extern char *currentTowerName;
extern int currentTowerRange;
extern int currentTowerDamage;
extern int currentTowerFireRate;
extern int currentTowerCost;
extern char *currentTowerDescription;

extern wave waves[DEF_LAST_WAVE];
extern minion minions[DEF_MINION_PER_WAVE_SIZE];
extern int minionObj;
extern int minionObj1;
extern int minionTexture;

extern int light;
extern int distance;
extern int ambient;
extern int diffuse;
extern int emission;
extern int specular;
extern int shininess;
extern float shinyvec[1];
extern float lightY;
extern float white[];

extern unsigned int textures[17];
extern int currentTexture;
extern int currentTextureSelected;
extern int backgrounds[6];

extern float N[];
extern float E[];

extern GLfloat cube_v[][3];
extern pathCube pathCubes[];
extern pathCube fullPath[];
extern tower default_towers[10];
extern tower tower_data[16];