#ifndef DEF_NPC
#define DEF_NPC

// Includes OpenGL

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Entity.h"
#include "Model.h"

class NPC : public Entity
{

 public:

  NPC(ent_type e, glm::vec3);
  virtual ~NPC() = 0;

  virtual bool update(float) = 0;
  virtual void draw(glm::mat4&, glm::mat4&) = 0;

 
 protected:

  int _health;
  float _speed;

  // model

  TrxModel* _model;

  // vector
  
  glm::vec3 _velocity;

};
#endif
