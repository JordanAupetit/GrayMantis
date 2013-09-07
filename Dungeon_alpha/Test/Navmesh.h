#ifndef DEF_NAVMESH
#define DEF_NAVMESH

// Includes OpenGL

#include <GL/glew.h>

// Includes GLM
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Navmesh
{

 public:

  Navmesh(glm::vec3, float, float);
  ~Navmesh();

  bool update(float);
  void draw(glm::mat4&, glm::mat4&);

  glm::vec3 getPos() const{return _position;}
 
 protected:

  float         vertice[12];
  float         color[12];

  glm::vec3 		_position;
  glm::vec3     _center;
  float         _width;
  float         _height;

  Navmesh*      _top;
  Navmesh*      _left;
  Navmesh*      _right;
  Navmesh*      _bottom;

};
#endif
