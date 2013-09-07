#include "global.h"
#include "Core.h"
#include "Entity.h"


Entity::Entity(ent_type e, glm::vec3 pos, glm::vec3 angle)
  : _type(e), _position(pos), id(g_core->generateID()),
    _pitch(angle.x),
    _yaw(angle.y),
    _roll(angle.z)
{
  printf("Entity created with ID : %d\n", id);
}


Entity::~Entity(){

 printf("entity deleted\n");

}
