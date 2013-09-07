
#include "Particle.h"
#include "Shader.h"
#include <GL/glew.h>

class ParticleSystem
{

 public:


  ParticleSystem();
  ParticleSystem(GLuint tex_id);
  ~ParticleSystem();

  bool update(float);
  void draw(glm::mat4 &projection, glm::mat4 &modelview, glm::vec3 &camPos);

  void add(Particle_t* );
  void del(Particle_t* );

  bool updateParticle(Particle_t*, float);
  

  GLuint _texture;
  
  Particle_t * _start;
  Particle_t * _end;

  float TimeLastUpdate;
  float EmissionResidue;

  // general

  int _maxParticle;
  int _curParticleAlive;
  int _particleCreated;
  int _particlePerSecond;
  


  // attrib

  float _minSize;
  float _maxSize;
  glm::vec3 _minColor;
  glm::vec3 _maxColor;
  float _minAlpha;
  float _maxAlpha;
  float _minLifeTime;
  float _maxLifeTime;
  float _minRotation;
  float _maxRotation;

  // operation

  float _startSize;
  float _endSize;
  glm::vec3 _startColor;
  glm::vec3 _endColor;
  float _startAlpha;
  float _endAlpha;

  // movement

  glm::vec3 _minVelocity;
  glm::vec3 _maxVelocity;

 private:

  glm::vec3 _position;
  Shader _shader;

  bool updateParticle(float);
  


};


