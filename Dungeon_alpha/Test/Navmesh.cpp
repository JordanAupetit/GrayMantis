#include "global.h"
#include "Core.h"
#include "Navmesh.h"
#include "Util.h"



Navmesh::Navmesh(glm::vec3 pos, float w, float h, float red, float green, float blue)
  : _position(pos), _width(w), _height(h), _center(pos.x + _height/2, 0, pos.z + _width/2),
  	_top(NULL), _left(NULL), _right(NULL), _bottom(NULL)
{
  printf("Navmesh created\n");

  vertice[0] = pos.x;
  vertice[1] = 0.1;
  vertice[2] = pos.z;

  vertice[3] = pos.x + _width;
  vertice[4] = 0.1;
  vertice[5] = pos.z;

  vertice[6] = pos.x + _width;
  vertice[7] = 0.1;
  vertice[8] = pos.z + _height;

  vertice[9] = pos.x;
  vertice[10] = 0.1;
  vertice[11] = pos.z + _height;



  float r,g,b;

  // On peux passer une couleur en paramètre ou en avoir une aléatoire

  if(red != -1)
    r = red;
  else
    r = getRandomValue(1, 10)/10.0f;

  if(green != -1)
    g = green;
  else
    g = getRandomValue(1, 10)/10.0f;

  if(blue != -1)
    b = blue;
  else
    b = getRandomValue(1, 10)/10.0f;

  printf(" %f : %f : %f\n", r, g, b);

  color[0] = r;
  color[1] = g;
  color[2] = b;

  color[3] = r;
  color[4] = g;
  color[5] = b;

  color[6] = r;
  color[7] = g;
  color[8] = b;

  color[9] = r;
  color[10] = g;
  color[11] = b;

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
 	glEnableVertexAttribArray(1);


    glBlendFunc(GL_SRC_ALPHA,GL_ONE);
    glEnable(GL_BLEND);
    
  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);
glDrawArrays(GL_QUADS, 0, 4);
  //glDisable(GL_CULL_FACE);

    glDisable(GL_BLEND);

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glUseProgram(0);


  drawLine(projection, modelview, _center, glm::vec3(_center.x, _center.y + 1, _center.z), glm::vec3(0.0f, 0.0f, 0.0f) ,shdr);


}

void Navmesh::setTop(Navmesh* n)
{
  _top = n;
}

void Navmesh::setLeft(Navmesh* n)
{
  _left = n;
}

void Navmesh::setRight(Navmesh* n)
{
  _right = n;
}

void Navmesh::setBottom(Navmesh* n)
{
  _bottom = n;
}

