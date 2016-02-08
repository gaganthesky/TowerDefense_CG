//modeling the Tower

#include "project.h"

void defenceTower(tower t)
{
  glPushMatrix();
  glTranslated(t.translation.x,t.translation.y,t.translation.z);
  glRotated(t.rotation.y,0,1,0);
  glScaled(t.scale.x,t.scale.y,t.scale.z);
  currentTexture = textures[t.texture];

  cylinder(0,0,0, 1,3);
  cylinder(0,3,0, 1.5,1);
  cylinder(0,4,0, 1.2,1);

  currentTexture = textures[TEX_DEFAULT];

  if (t.range > -1 && showAttackRadius) {
    circle(t.range);
  }
  glPopMatrix();
}
