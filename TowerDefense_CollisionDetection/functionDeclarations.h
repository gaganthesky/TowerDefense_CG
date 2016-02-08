//Declaring all functions


void setFont(char* name, int size);
void printv(va_list args, const char* format);
void print(const char* format , ...);
void printAt(int x,int y, const char* format , ...);
void errCheck(char* where);
void fatal(const char* format, ...);

unsigned int loadTexBMP(char* file);

int loadOBJ(char* file);

void square(int s, int a, int b, int c, int d);
void cube(double x,double y,double z,
	  double dx,double dy,double dz,
	  double th);
void vertex(double th, double ph);
void circle(int r);
void sphere(double x,double y,double z,double r,double rot);
void cone(double x,double y,double z, double r, double h,int deg);
void cylinder(double x,double y,double z,
	      double r,double h);

void pyramid(double x, double y, double z,
	     double dx, double dy, double dz,
	     double th);
void star(double x, double y, double z,
	  double dx, double dy, double dz,
	  double th);
void spike(double x, double y, double z,
	   double r,double h,int deg,
	   double ox,double oy,double oz);
void board(void);
void pathBlock(pathCube p);
void path(void);
void crate(double x, double y, double z,
	   double dx,double dy,double dz,
	   double th);
void crates(double x, double y, double z,
	    double dx,double dy,double dz,
	    double th);
void evergreenTree1(double x, double y, double z,
		    double dx,double dy,double dz,
		    double th);
void evergreenTree2(double x, double y, double z,
		    double dx,double dy,double dz,
		    double th);
void evergreenForest(double x, double y, double z,
		     double dx,double dy,double dz,
		     double th);
void evergreenForest1(double x, double y, double z,
		      double dx,double dy,double dz,
		      double th);
void wall(double x, double y, double z,
	  double dx,double dy,double dz,
	  double th);
void keep(double x, double y, double z,
	  double dx,double dy,double dz,
	  double th);
void shotModel(shot s);
void minionModel(minion m);

void defenceTower(tower t);

void changeObjectSelected(int newObjectSelected);
void setCurrentTowerData(int type);
point findMousePosition(int x, int y);
point findPreviewPosition(int x, int y);
void idle(void);
void incrementCurrentRGB(void);
void processPicks(void);
void redisplayAll(void);
void reset(void);

void initialize(void);
void initTextures(void);
void initBackground(void);
void initObjs(void);
void initMinions(void);
void initShots(void);
void initWaves(void);
void initPath(void);
void initPreviewPoints(void);
void initDefaultTowers(void);
void screenInit(void);
void sidebarInit(void);

void drawAllAlxes(void);
void drawRelevantParameters(void);
void drawGrid(void);
void drawBackground(double d);
void drawLight(void);
void drawBoard(void);
void drawPath(void);
void drawShots(void);
void drawMinions(void);
void drawObjects(void);
void drawScene(void);

void glutTime(int toggle);
void moveMinion(int k, int i, int j);
void moveMinions(void);
void moveBalls(void);
void moveTowerTops(void);

void checkCollisions(void);
void checkTowerRange(void);

void windowDisplay(void);
void windowKey(unsigned char key,int x,int y);
void windowSpecial(int key,int x,int y);
void windowReshape(int width, int height);
void windowVisible(int vis);

void displayInit(void);
void displayEye(void);
void screenDisplay(void);
void screenProject(double fov, double asp, double dim);
void screenReshape(int width, int height);
void screenMouse(int btn, int state, int x, int y);
void screenPmotion(int x, int y);

void sidebarRow(int x, int y, int obj, char* text);
void sidebarDisplay(void);
void sidebarReshape(int width, int height);
void sidebarMouse(int btn, int state, int x, int y);

int calculateDamageToMinion(int k, int j, int i);
void canUserBuyTower(int newObjectSelected);
void modifyLives(int die, int damage);
void modifyMoney(int what, int amount);
void modifyScore(int k);
void removeMinion(int k, int j);
void removeBall(int i);
