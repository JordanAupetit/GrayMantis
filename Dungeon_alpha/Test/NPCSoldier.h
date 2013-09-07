#ifndef DEF_NPC_SOLDIER
#define DEF_NPC_SOLDIER

// Includes OpenGL

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Entity.h"
#include "NPC.h"

class NPCSoldier : public NPC
{

 public:

  NPCSoldier(ent_type e, glm::vec3);
  virtual ~NPCSoldier();

  virtual bool update(float);
  virtual void draw(glm::mat4&, glm::mat4&);

 
 protected:

  int lol;

};
#endif
