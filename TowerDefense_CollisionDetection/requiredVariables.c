//Remaining variables and functions declared here

#include "project.h"

int debug=DEF_DEBUG;                             
char *windowName="Gagan Sharma CG Final Project - Collision Detection"; 
int windowHeight=DEF_WINDOW_HEIGHT;              
int windowWidth=DEF_WINDOW_WIDTH;                
GLuint window, screen, sidebar;                  

GLvoid *fontStyle=DEF_FONT_STYLE;        


double asp=DEF_ASP;      
double dim=DEF_DIM;      
int th=DEF_TH;           
int ph=DEF_PH;           
int fov=DEF_FOV;         
double ecX=DEF_ECX;      
double ecY=DEF_ECY;      
double ecZ=DEF_ECZ;      

int axes=DEF_AXES;       
int grid=DEF_GRID;       
int showAttackRadius=DEF_SHOW_ATTACK;
int vals=DEF_VALS;       

int detectCollisions = DEF_COLLISION; 
int lastShot=DEF_LAST_SHOT;
shot shots[200];                      

char *info=DEF_INFO;
int gameStarted=DEF_GAME_STARTED;       
int gamePaused=DEF_GAME_PAUSED;         
int gameSpeed=DEF_GAME_SPEED;           
int lightPh=DEF_L_PH;                   
int moveTowerTopsB=DEF_MOVE_TOWER_TOPS; 
int towerTh=DEF_TOWER_TH;               

int lives=DEF_LIVES;
int money=DEF_MONEY;
int scrolls=DEF_SCROLLS;
int score=DEF_SCORE;
int waveNumber=DEF_WAVE;
int lastWave=DEF_LAST_WAVE;

int mouseX=0;
int mouseY=0;
int mouseZ=0;


tower towers[DEF_CURRENT_OBJS_SIZE];    
tower preview_tower;                    
point preview_points[DEF_CURRENT_OBJS_SIZE];   
int preview=DEF_PREVIEW;                       
int objectSelected=DEF_OBJ_SEL;                
int lastCurrentObject=DEF_LAST_CURRENT_OBJECT; 
int renderMode=DEF_RENDER;                     
int objectPicked=DEF_OBJ_PICKED;               

int currentRed=DEF_CURRENT_RED;
int currentGreen=DEF_CURRENT_GREEN;
int currentBlue=DEF_CURRENT_BLUE;
char *currentTowerName=DEF_CURRENT_TOWER_NAME;
int currentTowerRange=DEF_CURRENT_TOWER_RANGE;
int currentTowerDamage=DEF_CURRENT_TOWER_DAMAGE;
int currentTowerFireRate=DEF_CURRENT_TOWER_FIRE_RATE;
int currentTowerCost=DEF_CURRENT_TOWER_COST;
char *currentTowerDescription=DEF_CURRENT_TOWER_DESCRIPTION;


wave waves[DEF_LAST_WAVE];                   
minion minions[DEF_MINION_PER_WAVE_SIZE];    
int minionObj=DEF_MINION_OBJ;                
int minionObj1=DEF_MINION_OBJ;                
int minionTexture=DEF_MINION_TEX;             

int light=DEF_LIGHT;          
int distance=DEF_DISTANCE;    
int ambient=DEF_AMBIENT;      
int diffuse=DEF_DIFFUSE;      
int emission=DEF_EMISSION;    
int specular=DEF_SPECULAR;    
int shininess=DEF_SHININESS;  
float shinyvec[1]={1};        
float lightY=DEF_L_Y;         
float white[]={1,1,1,1};


unsigned int textures[17];              
int currentTexture=TEX_DEFAULT;         
int currentTextureSelected=TEX_DEFAULT; 
int backgrounds[6];                     


float N[] = {0, -1, 0, 0};            
float E[] = {0, DEF_Y_FLOOR, 0, 0};   

GLfloat cube_v[][3] = {
  {-1.0,-1.0,-1.0},{+1.0,-1.0,-1.0},{+1.0,+1.0,-1.0},
  {-1.0,+1.0,-1.0},{-1.0,-1.0,+1.0},{+1.0,-1.0,+1.0},
  {+1.0,+1.0,+1.0},{-1.0,+1.0,+1.0}
};

pathCube pathCubes[] = {
  {{25,-3,-1},  TEX_STREET1,90, DEF_NORTH},
  {{21,-3,-1},  TEX_STREET1,90, DEF_NORTH}, {{17,-3,-1},  TEX_STREET1,90, DEF_NORTH},
  {{13,-3,-1},  TEX_STREET6,270,DEF_EAST},  {{13,-3,-5},  TEX_STREET2,0,  DEF_EAST},
  {{13,-3,-9},  TEX_STREET2,0,  DEF_EAST},  {{13,-3,-13}, TEX_STREET2,0,  DEF_EAST},
  {{13,-3,-17}, TEX_STREET4,90, DEF_NORTH}, {{9,-3,-17},  TEX_STREET1,90, DEF_NORTH},
  {{5,-3,-17},  TEX_STREET3,180,DEF_WEST},  {{5,-3,-13},  TEX_STREET2,180,DEF_WEST},
  {{5,-3,-9},   TEX_STREET2,180,DEF_WEST},  {{5,-3,-5},   TEX_STREET2,180,DEF_WEST},
  {{5,-3,-1},   TEX_STREET2,180,DEF_WEST},  {{5,-3,3},    TEX_STREET2,180,DEF_WEST},
  {{5,-3,7},    TEX_STREET6,270,DEF_SOUTH}, {{9,-3,7},    TEX_STREET1,270,DEF_SOUTH},
  {{13,-3,7},   TEX_STREET1,270,DEF_SOUTH}, {{17,-3,7},   TEX_STREET4,90, DEF_WEST},
  {{17,-3,11},  TEX_STREET2,0,  DEF_WEST},  {{17,-3,15},  TEX_STREET5,0,  DEF_NORTH},
  {{13,-3,15},  TEX_STREET1,90, DEF_NORTH}, {{9,-3,15},   TEX_STREET1,90, DEF_NORTH},
  {{5,-3,15},   TEX_STREET1,90, DEF_NORTH}, {{1,-3,15},   TEX_STREET1,90, DEF_NORTH},
  {{-3,-3,15},  TEX_STREET6,270,DEF_EAST},  {{-3,-3,11},  TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,7},   TEX_STREET2,0,  DEF_EAST},  {{-3,-3,3},   TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,-1},  TEX_STREET2,0,  DEF_EAST},  {{-3,-3,-5},  TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,-9},  TEX_STREET2,0,  DEF_EAST},  {{-3,-3,-13}, TEX_STREET2,0,  DEF_EAST},
  {{-3,-3,-17}, TEX_STREET4,90, DEF_NORTH}, {{-7,-3,-17}, TEX_STREET1,90, DEF_NORTH},
  {{-11,-3,-17},TEX_STREET3,180,DEF_WEST},  {{-11,-3,-13},TEX_STREET2,180,DEF_WEST},
  {{-11,-3,-9}, TEX_STREET2,180,DEF_WEST},  {{-11,-3,-5}, TEX_STREET2,180,DEF_WEST},
  {{-11,-3,-1}, TEX_STREET2,180,DEF_WEST},  {{-11,-3,3},  TEX_STREET2,180,DEF_WEST},
  {{-11,-3,7},  TEX_STREET2,180,DEF_WEST},  {{-11,-3,11}, TEX_STREET5,0,  DEF_NORTH},
  {{-15,-3,11}, TEX_STREET1,90, DEF_NORTH}, {{-19,-3,11}, TEX_STREET1,90, DEF_NORTH}
};

pathCube fullPath[2200];


tower default_towers[10] = {

  {0,OBJ_BASIC,1,{17,0,-17},{1,1,1},{0,0,0},TEX_BRICK,{5,5,5},
   "Basic",1,5, 3,4,0,10,"Description"},
  {0,OBJ_FIRE,1,{9,0,-13},{1,1,1},{0,0,0},TEX_BRICK,{10,5,5},
   "Basic",1,12,4,3,0,40,"Description"},
  {0,OBJ_FIRE2,1,{9,0,-3},{1,1,1},{0,0,0},TEX_BRICK,{15,5,5},
   "Basic",1,12,6,3,0,45,"Description"},
  {0,OBJ_ICE,1,{20,0,3},{1,1,1},{0,0,0},TEX_BRICK,{20,5,5},
   "Basic",1,12,5,4,0,50,"Description"},
  {0,OBJ_EARTH,1,{13,0,10},{1,1,1},{0,0,0},TEX_BRICK,{25,5,5},
   "Basic",1,10,8,6,0,60,"Description"},
  {0,OBJ_POISON2,1,{17,0,-10},{1,1,1},{0,0,0},TEX_BRICK,{30,5,5},
   "Basic",1,12,8,3,0,75,"Description"},
};


tower tower_data[16] = {

  {0,OBJ_FIRE,1,{0,0,0},{1,1,1},{0,0,0},TEX_FIRE,{5,5,5},
   "Fire",1,          10,4,3,0,40,"Just your typical fire tower"},
  {0,OBJ_FIRE2,1,{0,0,0},{1,1,1},{0,0,0},TEX_FIRE,{5,5,5},
   "Advanced Fire",1, 12,6,3,0,45,"Just your typical fire tower - with spikes!"},

  {0,OBJ_ICE,1,{0,0,0},{1,1,1},{0,0,0},TEX_ICE,{5,5,5},
   "Ice",1,           10,5,4,0,50,"Just your typical ice tower"},
  {0,OBJ_ICE2,1,{0,0,0},{1,1,1},{0,0,0},TEX_ICE,{5,5,5},
   "Advanced Ice",1,  12,7,4,0,55,"Just your typical ice tower - with spikes!"},

  {0,OBJ_EARTH,1,{0,0,0},{1,1,1},{0,0,0},TEX_EARTH,{5,5,5},
   "Earth",1,         10,8,6,0,60,"Just your typical earth tower"},
  {0,OBJ_EARTH2,1,{0,0,0},{1,1,1},{0,0,0},TEX_EARTH,{5,5,5},
   "Advanced Earth",1,12,8,6,0,60,"Just your typical earth tower - with spikes!"},

  {0,OBJ_POISON,1,{0,0,0},{1,1,1},{0,0,0},TEX_POISON,{5,5,5},
   "Poison",1,         10,6,3,0,70,"Just your typical poison tower"},
  {0,OBJ_POISON2,1,{0,0,0},{1,1,1},{0,0,0},TEX_POISON,{5,5,5},
   "Advanced Poison",1,12,8,3,0,75,"Just your typical poison tower - with spikes!"},

  {0,OBJ_BASIC,1,{0,0,0},{1,1,1},{0,0,0},TEX_BRICK,{5,5,5},
   "Basic",1,           5,3,4,0,10,"A basic tower"},
  {0,OBJ_ADV,1,{0,0,0},{1,1,1},{0,0,0},TEX_BRICK,{5,5,5},
   "Advanced",1,        7,4,4,0,15,"A basic tower - with spikes!"},

  {0,OBJ_CONE,1,{0,0,0},{1,1,1},{0,0,0},TEX_BRICK,{5,5,5},
   "Cone",1,            7,6,4,0,20,"A cone tower"},
  {0,OBJ_ADV_CONE,1,{0,0,0},{1,1,1},{0,0,0},TEX_BRICK,{5,5,5},
   "Advanced Cone",1,   9,6,4,0,25,"A cone tower - with spikes!"},

  {0,OBJ_SQUARE,1,{0,0,0},{1,1,1},{0,0,0},TEX_BRICK,{5,5,5},
   "Square",1,          9,6,3,0,30,"A square tower"},
  {0,OBJ_ADV_SQUARE,1,{0,0,0},{1,1,1},{0,0,0},TEX_BRICK,{5,5,5},
   "Advanced Square",1, 10,6,3,0,35,"A square tower - with spikes!"},
  /* Pyramid not implemented yet */
  {0,OBJ_PYRAMID,1,{0,0,0},{1,1,1},{0,0,0},TEX_BRICK,{5,5,5},
   "Pyramid",1,         1,1,1,0,1,"A pyramid tower"},
  {0,OBJ_ADV_PYRAMID,1,{0,0,0},{1,1,1},{0,0,0},TEX_BRICK,{5,5,5},
   "Advanced Pyramid",1,1,1,1,0,1,"A pyramid tower - with spikes!"}
};