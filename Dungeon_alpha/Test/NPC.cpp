#include "global.h"
#include "Core.h"
#include "NPC.h"


NPC::NPC(ent_type e, glm::vec3 pos)
  : Entity(e,pos,glm::vec3(_pitch, 0, 0))
{

  _health = 0;

}


NPC::~NPC(){

 printf("NPC deleted\n");

}
