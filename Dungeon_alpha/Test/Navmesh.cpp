#include "global.h"
#include "Core.h"
#include "Navmesh.h"
#include "Util.h"



Navmesh::Navmesh(glm::vec3 pos, float w, float h, float red, float green, float blue)
  : _position(pos), _width(w), _height(h), _center(pos.x + (w/2), 0, pos.z + (h/2)),
  	_top(NULL), _left(NULL), _right(NULL), _bottom(NULL)
{
  printf("Navmesh created\n");

  _dist_top = -1;
  _dist_bottom = -1;
  _dist_left = -1;
  _dist_right = -1;

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

  /*
  _center.x = pos.x + (_width / 2);
  _center.y = 0;
  _center.z = pos.z + (_height / 2);
  */


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


  drawLine(projection, modelview, _center, glm::vec3(_center.x, _center.y + 1, _center.z), glm::vec3(1.0f, 0.0f, 1.0f) ,shdr);

  // debug -- link
  
  glm::vec3 dbg_color = glm::vec3(1.0f, 0.0f, 1.0f);

  if(_top){
    
    glm::vec3 p1 = glm::vec3(_center.x, _center.y + 0.2, _center.z);
    glm::vec3 p2 = glm::vec3(_top->getCenter().x, _top->getCenter().y + 0.2, _top->getCenter().z);

    drawLine(projection, modelview, p1, p2, dbg_color ,shdr);

  }
  if(_bottom){
    
    glm::vec3 p1 = glm::vec3(_center.x, _center.y + 0.6, _center.z);
    glm::vec3 p2 = glm::vec3(_bottom->getCenter().x, _bottom->getCenter().y + 0.6, _bottom->getCenter().z);

    drawLine(projection, modelview, p1, p2, dbg_color ,shdr);

  }
  if(_left){
    
    glm::vec3 p1 = glm::vec3(_center.x, _center.y + 0.4, _center.z);
    glm::vec3 p2 = glm::vec3(_left->getCenter().x, _left->getCenter().y + 0.4, _left->getCenter().z);

    drawLine(projection, modelview, p1, p2, dbg_color ,shdr);

  }
  if(_right){
    
    glm::vec3 p1 = glm::vec3(_center.x, _center.y + 0.8, _center.z);
    glm::vec3 p2 = glm::vec3(_right->getCenter().x, _right->getCenter().y + 0.8, _right->getCenter().z);

    drawLine(projection, modelview, p1, p2, dbg_color ,shdr);

  }


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

void Navmesh::computeDistance(){

  if(_top)
    _dist_top = sqrt(pow(_center.x - _top->getPos().x, 2) + pow(_center.z - _top->getPos().z, 2));
  if(_left)
    _dist_left = sqrt(pow(_center.x - _left->getPos().x, 2) + pow(_center.z - _left->getPos().z, 2));
  if(_right)
    _dist_right = sqrt(pow(_center.x - _right->getPos().x, 2) + pow(_center.z - _right->getPos().z, 2));
  if(_bottom)
    _dist_bottom = sqrt(pow(_center.x - _bottom->getPos().x, 2) + pow(_center.z - _bottom->getPos().z, 2));

}
