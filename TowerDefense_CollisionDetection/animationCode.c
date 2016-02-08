//Basic Animation functions

#include "project.h"

void glutTime(int toggle)
{
  if (gameStarted) {
    if (gamePaused != DEF_GAME_PAUSED) {
      moveTowerTops();
      moveBalls();
      checkCollisions();
      moveMinions();
      checkCollisions();
      checkTowerRange();
    }
    glutTimerFunc(50,glutTime,0);
  }
  redisplayAll();
}


void moveMinion(int k, int i, int j)
{
  waves[k].m[i].translation.x = fullPath[j].p.x;
  waves[k].m[i].translation.z = fullPath[j].p.z;
  waves[k].m[i].rotation.y = fullPath[j].dir;
}


void moveMinions(void)
{
  int i,j,k;
  
  //  for (k=0;k<waveNumber;k++) {
  for(k=waveNumber-1;k==waveNumber-1;k++) {
    
    for (i=0;i<Length(waves[k].m);i++) {
      int speed = waves[k].m[i].speed;
      int damage = waves[k].m[i].damage;
      
      
      for (j=0;j<(DEF_PATH_LEN*DEF_FULL_PATH_LEN);j += speed) {
	
	if (waves[k].m[i].inPlay == 1 && 
	    waves[k].m[i].translation.x <= -15 &&
	    waves[k].m[i].translation.z == 11) {
	
	  modifyLives(1, damage);
	  waves[k].m[i].inPlay = 0;
	  break;
	}

	
	if (i == 0) {
	
	  if (waves[k].m[i].translation.x > 25) {
	    moveMinion(k,i,0);
	    break;
	  }
	 
	  else if(waves[k].m[i].translation.x == fullPath[j-speed].p.x &&
		  waves[k].m[i].translation.z == fullPath[j-speed].p.z) {
	    moveMinion(k,i,j);
	    break;
	  }
	}
	
	else {
	
	  if (fabs(waves[k].m[i-1].translation.x - waves[k].m[i].translation.x) > 
	      ((waves[k].m[i].scale.x)*20) || 
	      fabs(waves[k].m[i-1].translation.z - waves[k].m[i].translation.z) > 0) {
	    if (waves[k].m[i].translation.x > 25){
	      moveMinion(k,i,0);
	      break;
	    }
	   
	    else if(waves[k].m[i].translation.x == fullPath[j-speed].p.x &&
		    waves[k].m[i].translation.z == fullPath[j-speed].p.z) {
	      moveMinion(k,i,j);
	      break;
	    }
	  } 
	} 
      } 
    } 
  } 
}


void moveBall(int i, int j, int k)
{
  //The balls move in respect to the current position of targetted minion

  point target = waves[j].m[k].translation;
  point origin = shots[i].p;
  double xFactor=0.0, zFactor=0.0;
  if (target.x > origin.x)
    xFactor = 0.5;
  else if (target.x == origin.x)
    xFactor = 0.0;
  else if (target.x < origin.x)
    xFactor = -0.5;

  if (target.z > origin.z)
    zFactor = 0.5;
  else if (target.z == origin.z)
    zFactor = 0.0;
  else if (target.z < origin.z)
    zFactor = -0.5;

  shots[i].p.x += xFactor;
  shots[i].p.z += zFactor;
}

void moveBalls(void)
{
  int i,j;
  for (i=0;i<lastShot;i++){
    //    shot s = shots[i];
    for (j=0;j<Length(waves[waveNumber-1].m);j++) {
      if (waves[waveNumber-1].m[j].inPlay) {
	moveBall(i,waveNumber-1,j);
	break;
      } 
    } 
  } 
}

void moveTowerTops(void) 
{
  if (moveTowerTopsB) 
    towerTh = (towerTh+2)%360;
}
