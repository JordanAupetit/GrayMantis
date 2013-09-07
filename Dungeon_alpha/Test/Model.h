#ifndef DEF_MODEL
#define DEF_MODEL

// Includes OpenGL

#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Includes GLM

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>



class TrxModel
{
 public:

  //Model();
  TrxModel(const char*);
  ~TrxModel();
  
  //load(const char* = NULL);
  void draw(glm::mat4&, glm::mat4&);


 private:
    
  char 				_name[255];

  std::vector<unsigned short> 	_indices;
  std::vector<glm::vec3> 	_vertices;
  std::vector<glm::vec2> 	_uvs;
  std::vector<glm::vec3> 	_normals;

  GLuint _vertexArrayID;

  GLuint _vertexbuffer;
  GLuint _uvbuffer;
  GLuint _normalbuffer;
  GLuint _elementbuffer;

  GLuint VBO;
  GLuint IBO;

  int v_size;
  int u_size;
  int i_size;

};

#endif
