#ifndef DEF_ENTITY
#define DEF_ENTITY

// Includes OpenGL

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


enum ent_type { ENT_NULL, ENT_NPC_SOLDIER, ENT_BREAKABLE };

class Entity
{

 public:

  Entity(ent_type, glm::vec3, glm::vec3);
  virtual ~Entity() = 0;

  virtual bool update(float) = 0;
  virtual void draw(glm::mat4&, glm::mat4&) = 0;


  glm::vec3 getPos() const{return _position;}
 
 protected:

  ent_type 		_type;
  glm::vec3 		_position;
  float 		_pitch;
  float			_yaw;
  float			_roll;
  int 			id;



};
#endif
