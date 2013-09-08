#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#include <math.h>

#include <GL/glew.h>

#include "Util.h"



int getRandomValue(int min, int max){

  if(min == max)
    return min;
  else
    return( min + (rand() % (max - min)) );

}

void drawLine(glm::mat4& p, glm::mat4 m, glm::vec3 p1, glm::vec3 p2, glm::vec3 col, Shader* shd){


  glUseProgram(shd->getProgramID());


  glUniformMatrix4fv(glGetUniformLocation(shd->getProgramID(), "projection"), 1, GL_FALSE, glm::value_ptr(p));
  glUniformMatrix4fv(glGetUniformLocation(shd->getProgramID(), "modelview"), 1, GL_FALSE, glm::value_ptr(m));


  float vertices[] = {p1.x, p1.y, p1.z, p2.x, p2.y, p2.z};
  float color[] = {col.x, col.y, col.z, col.x, col.y, col.z};

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, color);
  glEnableVertexAttribArray(1);

  glDrawArrays(GL_LINES, 0, 2);

  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(0);

  glUseProgram(0);


}
