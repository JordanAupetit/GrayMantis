#include "global.h"
#include "Core.h"
#include "NPCSoldier.h"
#include "glm/gtx/rotate_vector.hpp"


NPCSoldier::NPCSoldier(ent_type e, glm::vec3 pos)
  : NPC(e, pos)
{

  _model = g_core->getModel(0);
  _speed = 1.0f;

}


NPCSoldier::~NPCSoldier(){

 printf("NPCSoldier deleted\n");

}

bool NPCSoldier::update(float dt){

  float aa = _pitch * 180.0f / 3.14f;
  _velocity = glm::rotateY(glm::vec3(1.0f, 0.0f, 0.0f), aa);

  _position += _velocity * _speed * dt;

  return true;

}

void NPCSoldier::draw(glm::mat4& projection, glm::mat4& modelview){

  glm::vec4 light_ambiant;
  
  light_ambiant.x = 1.0f;
  light_ambiant.y = 1.0f;
  light_ambiant.z = 1.0f;
  light_ambiant.w = 1.0f;

 glm::mat4 modelview_save = modelview;

  float aa = _pitch * 180.0f / 3.14f;
 
  modelview = glm::translate(modelview, _position);
  modelview = glm::rotate(modelview, aa , glm::vec3(0, 1, 0));

  Shader* shdr = &(g_core->_GLSL_texture_light);

  glUseProgram(shdr->getProgramID());

  glUniformMatrix4fv(glGetUniformLocation(shdr->getProgramID(), "u_projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(shdr->getProgramID(), "u_modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
  glUniform4fv(glGetUniformLocation(shdr->getProgramID(), "light"), 1, glm::value_ptr(light_ambiant));

  GLuint texture;

  glBindTexture(GL_TEXTURE_2D, g_core->getTexture(10));

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_BACK);

  _model->draw(projection, modelview);

  //glDisable(GL_CULL_FACE);

  glUseProgram(0);

  modelview = modelview_save;

  //drawAxis(projection, modelview, _position, _shader, _targ_vector);

  glBindTexture(GL_TEXTURE_2D, 0);

}
