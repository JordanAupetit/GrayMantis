#include "global.h"
#include "Core.h"
#include "Navmesh.h"


Navmesh::Navmesh(glm::vec3 pos, float w, float h)
  : _position(pos), _width(w), _height(h), _center(_width/2, 0, _height/2),
  	_top(NULL), _left(NULL), _right(NULL), _bottom(NULL)
{
  printf("Navmesh created\n");

  vertice[0] = pos.x;
  vertice[1] = 1;
  vertice[2] = pos.z;

  vertice[3] = pos.x + _width;
  vertice[4] = 1;
  vertice[5] = pos.z;

  vertice[6] = pos.x + _width;
  vertice[7] = 1;
  vertice[8] = pos.z + _height;

  vertice[9] = pos.x;
  vertice[10] = 1;
  vertice[11] = pos.z + _height;


  color[0] = 0.0f;
  color[1] = 0.6f;
  color[2] = 0.7f;

  color[3] = 0.0f;
  color[4] = 0.6f;
  color[5] = 0.7f;

  color[6] = 0.0f;
  color[7] = 0.6f;
  color[8] = 0.7f;

  color[9] = 0.0f;
  color[10] = 0.6f;
  color[11] = 0.7f;

}


Navmesh::~Navmesh(){

 printf("navmesh deleted\n");

}

bool Navmesh::update(float dt){


	return true;
}

void Navmesh::draw(glm::mat4& projection, glm::mat4& modelview){



  Shader* shdr = &(g_core->_GLSL_color3D);

  glUseProgram(shdr->getProgramID());

  glUniformMatrix4fv(glGetUniformLocation(shdr->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(shdr->getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(modelview));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertice);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, color);
 	glEnableVertexAttribArray(2);


    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glEnable(GL_BLEND);
    
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);
glDrawArrays(GL_QUADS, 0, 4);
  //glDisable(GL_CULL_FACE);

    glDisable(GL_BLEND);

  glUseProgram(0);



  //drawAxis(projection, modelview, _position, _shader, _targ_vector);


}
