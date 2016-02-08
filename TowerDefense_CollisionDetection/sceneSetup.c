//Scene Setup

#include "project.h"

int calculateDamageToMinion(int k, int j, int i)
{
  waves[k].m[j].health -= shots[i].damage;
  return waves[k].m[j].health;
}

void canUserBuyTower(int newObjectSelected)
{
  if (money >= tower_data[objectSelected-1].cost) {
    info = "cha-ching$ thanks buddy.";
    setCurrentTowerData(objectSelected);
  } else {
    info = "Not enough $$$.";
    objectSelected = DEF_OBJ_SEL;
    preview_tower.id = DEF_OBJ_SEL;
  }
}

void modifyLives(int die, int damage)
{
  if (die) {
    lives -= damage;
  }
  else {

    lives++;
  }
}

void modifyMoney(int what, int amount)
{

  if (what == 0) {
    money -= amount;
  }

  else if (what == 1) {
    money += amount;
  }

  else if (what == 2) {
    money += amount;
  }
}

void modifyScore(int k)
{
  score += waveNumber*5;
}

void removeMinion(int k, int j)
{
  waves[k].m[j].inPlay = 0;
  modifyScore(k+1);
  modifyMoney(1,waves[k].m[j].money);
}

void removeBall(int i)
{
  shot s = {0,{-255,-255,-255},TEX_DEFAULT,0};
  shots[i] = s;
}


