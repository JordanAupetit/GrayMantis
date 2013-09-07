#ifndef DEF_CUBE
#define DEF_CUBE


// Includes OpenGL

#include <GL/glew.h>



// Includes GLM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Includes

#include "Shader.h"

struct map_surface{

  glm::vec3 pos1;
  glm::vec3 pos2;
  
  GLuint texture;
  char type; // f = floor / w = wall

};

// Classe Cube

class Map
{
 public:

  Map();
  ~Map();

  void createMap();

  void afficher(glm::mat4 &projection, glm::mat4 &modelview);

  void charger();

 private:

  Shader m_shader;
  float *m_vertices;
  float *m_texture;
  GLuint m_vboID;
  int m_tailleVerticesBytes;
  int m_tailleCouleursBytes;
  GLuint m_vaoID;

  GLuint m_texture_id[2];

  map_surface* _surface;
  int _nb_surface;

  int floor_num;
  int wall_num;
  
    
};

#endif
