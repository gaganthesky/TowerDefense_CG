//Code to check collsions

#include "project.h"


//Check main COllision Detection.
//A sphere is created around minion's centre and that sphere is treated as the object to collide with the balls

void checkCollisions(void)
{
  int i,j;
  
  for (i=0;i<Length(shots);i++) {
    shot s = shots[i];
    if (s.inPlay)   //s is a struct that maintains attributes of balls, inplay is an integer in struct tower that contains 0 & 1 and maintains if minion is in range of that tower

    {
      for (j=0;j<Length(waves[waveNumber-1].m);j++) {
	if (waves[waveNumber-1].m[j].inPlay) {
	  point origin = s.p;
	  point target = waves[waveNumber-1].m[j].translation;
	  point tScale = waves[waveNumber-1].m[j].scale;
	  double distance = sqrt((origin.x-target.x)*(origin.x-target.x)+
				 (origin.z-target.z)*(origin.z-target.z));
	  if (distance < 5*tScale.x) {

	    int health = calculateDamageToMinion(waveNumber-1,j,i);
	    removeBall(i);
	    if (health <= 0) removeMinion(waveNumber-1,j);

		printf("\nshot  i     :%d\n",i);
		printf("shot  loc  x:%f\n",origin.x);
		printf("shot  loc  y:%f\n",origin.y);
		printf("shot  loc  z:%f\n",origin.z);
		printf("minion j    :%d\n",j);
		printf("minion loc x:%f\n",target.x);
		printf("minion loc y:%f\n",target.y);
		printf("minion loc z:%f\n",target.z);
		printf("minion scale:%f\n",tScale.x);
		printf("distance    :%f\n",distance);
	    
	    break;
	  }
	}
      }
    }
  }
}
//Circle around tower's centre is its range to hit

void checkTowerRange(void)
{
  int i,j;
  for (i=0;i<Length(towers);i++) {
    if (towers[i].inPlay) {

      time_t fireShot;
      double timeDiff;
      fireShot = time(NULL);
      timeDiff = difftime(fireShot,towers[i].lastFired);
      if (towers[i].lastFired == 0 || timeDiff > towers[i].fireRate) {
	for (j=0;j<Length(waves[waveNumber-1].m);j++) {
	  if (waves[waveNumber-1].m[j].inPlay) {
	    point origin = towers[i].translation;
	    point target = waves[waveNumber-1].m[j].translation;
	    point tScale = waves[waveNumber-1].m[j].scale;
	    double distance = sqrt((origin.x-target.x)*(origin.x-target.x)+
				   (origin.z-target.z)*(origin.z-target.z)) - tScale.x;

	    if (distance < towers[i].range) {
	      shot s = {1,{origin.x,origin.y,origin.z},towers[i].texture,towers[i].damage};
	      time_t shotFired;
	      shots[lastShot] = s;
	      shotFired = time(NULL);
	      towers[i].lastFired = shotFired;
	      lastShot++;
      	      
	
	      break;
	    } 
	  }
	}
      } 
    } 
  } 
}
