
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Texture.h"
#include "ParticleSys.h"
#include "Util.h"
#include <time.h>
#include <math.h>

#define PI (3.141592653589793)

ParticleSystem::ParticleSystem()
  : _shader("Shaders/light_particle.vert", "Shaders/light_particle.frag")
{

  _start = NULL;
  _end = NULL;
  _maxParticle = 0;
  _curParticleAlive = 0;
  _particlePerSecond = 0;
  _texture = 0;
  
  _shader.charger();

}

ParticleSystem::ParticleSystem(GLuint tex_id)
  : _shader("Shaders/light_particle.vert", "Shaders/light_particle.frag"),
    _texture(tex_id)
{

  _start = NULL;
  _end = NULL;
  _maxParticle = 0;
  _curParticleAlive = 0;
  _particlePerSecond = 0;
  _texture = tex_id;
  TimeLastUpdate = -1.0f;
  EmissionResidue =  0.0f;

 /*
  initParticle(_start);
 
  Texture texture("PlasmaFlare.dds");
  texture.charger(true);

  _start->texture = texture.getID();

  _start->position = glm::vec3(0.0f, 0.0f, 0.0f);
  _start->velocity = glm::vec3(0.0f, 0.4f, 0.0f);

  _start->size = 1.0f;
  */
  _shader.charger();

  printf("Particle System initialized\n");

}

ParticleSystem::~ParticleSystem(){

  Particle_t* tmp = _start;

  while (tmp!=0) {
    Particle_t *tmp2 = tmp->next;
    del(tmp);
    delete tmp; tmp = 0;
    tmp = tmp2;
  }

}

void ParticleSystem::add(Particle_t* p){


  if (p == NULL) return;


  if (_end == NULL)
    {
      p->prev = NULL;
      p->next = NULL;
      _start = p;
      _end = p;
    }
  else 
    {
      p->prev = _end;
      p->next = NULL;
      _end->next = p;
      _end = p;
    }

}

void ParticleSystem::del(Particle_t* p){


  if (p == NULL) return;

  if (_start == p)_start = p->next;
  if (_end == p) _end = p->prev;


  if (p->next != NULL) p->next->prev = p->prev;
  else if (p->prev != NULL) p->prev->next = NULL;
  if (p->prev != NULL) p->prev->next = p->next;
  else if (p->next != NULL) p->next->prev = NULL;

}

bool ParticleSystem::updateParticle(Particle_t* p, float dt){

  if(p->elapsed_time > p->lifetime)
    return false;

  p->elapsed_time += dt;

  p->position += p->velocity * dt;
 
  p->r += _endColor.x * dt;// / p->lifetime;
  p->g += _endColor.y * dt;// / p->lifetime;
  p->b += _endColor.z * dt;// / p->lifetime;

  p->size += _endSize * dt;// / p->lifetime;

  p->size = glm::max(0.0f, p->size);
  p->r = glm::max(0.0f, p->r);
  p->g = glm::max(0.0f, p->g);
  p->b = glm::max(0.0f, p->b);
 		
  //if(p == _start)
  //   printf("ept : %f | dt : %f | r : %f / g : %f / b : %f\n", p->elapsed_time, dt, p->r, p->g, p->b);
 
  return true;

}

bool ParticleSystem::update(float dt){

  if (TimeLastUpdate < 0.0f) {TimeLastUpdate = dt;return true;}


  float TimeDelta = dt - TimeLastUpdate;

  if (TimeDelta == 0.0f) return true;

  TimeLastUpdate = dt;

  _curParticleAlive = 0;

  Particle_t *tmp = _start;
  while (tmp!=0){
    
    Particle_t *tmp2 = tmp->next;

    if (updateParticle(tmp, TimeDelta))
      {
	_curParticleAlive++;
      }
    else
      {
	del(tmp);
	delete tmp; tmp = 0;
      }
    tmp = tmp2;
  }

  //printf("ParticleAlive : %d\n", _curParticleAlive);

  float ParticlesNeeded = _particlePerSecond * TimeDelta + EmissionResidue;

  
  _particleCreated = (int)ParticlesNeeded;

  EmissionResidue = ParticlesNeeded - _particleCreated;


  if ( _particleCreated > 0 ){

    if ( _particleCreated > _particlePerSecond) _particleCreated = _particlePerSecond;

    while ( _particleCreated > 0){

      Particle_t *p = NULL;
      p = new Particle_t; if (p == NULL) return true;

      initParticle(p);

      p->texture = _texture;
      p->elapsed_time = 0.0f;


      p->r = (getRandomValue((int)(_minColor.x*10), (int)(_maxColor.x*10)))/10.0f;
      p->g = (getRandomValue((int)(_minColor.y*10), (int)(_maxColor.y*10)))/10.0f;
      p->b = (getRandomValue((int)(_minColor.z*10), (int)(_maxColor.z*10)))/10.0f;
      p->a = _maxAlpha;

      p->position = _position;
      //p->velocity = _maxVelocity;

      p->velocity.x = (getRandomValue((int)(_minVelocity.x*10), (int)(_maxVelocity.x*10)))/10.0f;
      p->velocity.y = (getRandomValue((int)(_minVelocity.y*10), (int)(_maxVelocity.y*10)))/10.0f;
      p->velocity.z = (getRandomValue((int)(_minVelocity.z*10), (int)(_maxVelocity.z*10)))/10.0f;

      p->lifetime = (getRandomValue((int)(_minLifeTime*10), (int)(_maxLifeTime*10)))/10.0f;
      p->size = (getRandomValue((int)(_minSize*10), (int)(_maxSize*10)))/10.0f;
      p->rotation = (getRandomValue((int)(_minRotation*100), (int)(_maxRotation*100)))/100.0f;
 ;


      // p->velocity.z = _minVelocity.z + (rand() % ((int)(_maxVelocity.z*10) - ((int)(_minVelocity.z*10)))) / 10.0f;

      add(p);
      _particleCreated--;

    }

  }

  return true;

}


void ParticleSystem::draw(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 & camPos){

  glUseProgram(_shader.getProgramID());

  glDepthMask(GL_FALSE);



  glm::mat4 projection_modelview = projection * modelview;


  int drawCount = 0;
  Particle_t *tmp = _start;

  glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramID(), "u_projection"), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramID(), "u_modelview"), 1, GL_FALSE, glm::value_ptr(modelview));
  //glUniformMatrix4fv(glGetUniformLocation(_shader.getProgramID(), "projection_modelview"), 1, GL_FALSE, glm::value_ptr(projection_modelview));
  // glUniform3fv(glGetUniformLocation(_shader.getProgramID(), "u_pos"), 1, glm::value_ptr(tmp->position));


  while (tmp!=0){

    Particle_t *tmp2 = tmp->next;
    drawCount++;
    tmp = tmp2;
   
  }

  //printf("camPos = x:%f y:%f z:%f\n", camPos.x, camPos.y, camPos.z);

  float dist = 1.414213562;
  float a_c1 = 225 * PI / 180;
  float a_c2 = 315 * PI / 180;
  float a_c3 =  45 * PI / 180;
  float a_c4 = 135 * PI / 180;

  

  if(drawCount > 0){

    //printf("drawCount : %d\n", drawCount);

    float* vertices = new float[4*3*drawCount];
    float* couleurs = new float[4*3*drawCount];
    float coordTexture[4*2*drawCount];
    float* particleSysData = new float[4*4*drawCount];

    //glVertex3f(-1.0, -1.0,0);
    //      glVertex3f(1.0, -1.0,0);
    //      glVertex3f(1.0, 1.0,0);
    //	glVertex3f(-1.0, 1.0,0);

    int i = 0;
    int j = 0;
    int k = 0;
    int l = 0;

    Particle_t *tmp = _start;

    while(tmp!=NULL){

      Particle_t *tmp2 = tmp->next;

      //float r_cos = cosf(tmp->rotation);
      //float r_sin = sinf(tmp->rotation);
      float a,b;

      //r_cos = r_sin = dist = 1.0f;

      vertices[i++] = dist*cosf(a_c1 + tmp->rotation);//-1.0f;//
      vertices[i++] = dist*sinf(a_c1 + tmp->rotation);//-1.0f;//     
      vertices[i++] = 0.0f;
      couleurs[j++] = tmp->r;
      couleurs[j++] = tmp->g;
      couleurs[j++] = tmp->b;
      coordTexture[l++] = 0.0f;
      coordTexture[l++] = 0.0f;
      particleSysData[k++] = tmp->position.x;
      particleSysData[k++] = tmp->position.y;
      particleSysData[k++] = tmp->position.z;
      particleSysData[k++] = tmp->size;

      vertices[i++] = dist*cosf(a_c2 + tmp->rotation);             //1.0f;//
      vertices[i++] = dist*sinf(a_c2 + tmp->rotation);             //-1.0f;// 
      vertices[i++] = 0.0f;
      couleurs[j++] = tmp->r;
      couleurs[j++] = tmp->g;
      couleurs[j++] = tmp->b;
      coordTexture[l++] = 1.0f;
      coordTexture[l++] = 0.0f;
      particleSysData[k++] = tmp->position.x;
      particleSysData[k++] = tmp->position.y;
      particleSysData[k++] = tmp->position.z;
      particleSysData[k++] = tmp->size;

      vertices[i++] = dist*cosf(a_c3 + tmp->rotation);                        //1.0f;//
      vertices[i++] = dist*sinf(a_c3 + tmp->rotation);                        //1.0f;//
      vertices[i++] = 0.0f;
      couleurs[j++] = tmp->r;
      couleurs[j++] = tmp->g;
      couleurs[j++] = tmp->b;
      coordTexture[l++] = 1.0f;
      coordTexture[l++] = 1.0f;
      particleSysData[k++] = tmp->position.x;
      particleSysData[k++] = tmp->position.y;
      particleSysData[k++] = tmp->position.z;
      particleSysData[k++] = tmp->size;
  
      vertices[i++] = dist*cosf(a_c4 + tmp->rotation);           //-1.0f;
      vertices[i++] = dist*sinf(a_c4 + tmp->rotation);            //1.0f;
      //printf("c4x : %f | c4y : %f\n", a, b); 
      vertices[i++] = 0.0f;
      couleurs[j++] = tmp->r;
      couleurs[j++] = tmp->g;
      couleurs[j++] = tmp->b;
      coordTexture[l++] = 0.0f;
      coordTexture[l++] = 1.0f;
      particleSysData[k++] = tmp->position.x;
      particleSysData[k++] = tmp->position.y;
      particleSysData[k++] = tmp->position.z;
      particleSysData[k++] = tmp->size;

      tmp = tmp2;

    }

    //printf("etape 2\n");

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vertices);
    glEnableVertexAttribArray(0);

    //printf("etape 2b\n");

 
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, couleurs);
    glEnableVertexAttribArray(1);


    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, coordTexture);
    glEnableVertexAttribArray(2);

    //printf("etape 2c\n");

    glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 0, particleSysData);
    glEnableVertexAttribArray(3);


    //printf("etape 2d\n");

    glBindTexture(GL_TEXTURE_2D, _start->texture);

    glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE,GL_ONE);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);


    glDrawArrays(GL_QUADS, 0, 4*drawCount);

    glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_BLEND);

    // Désactivation des tableaux Vertex Attrib
  
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    //printf("delete\n");

    delete [] vertices; vertices = NULL;
    delete [] couleurs; couleurs = NULL;
    delete [] particleSysData; particleSysData = NULL;

  }

  glDepthMask(GL_TRUE);

  glUseProgram(0);

  //printf("end\n");
}
