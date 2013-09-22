#ifndef _included_Core_hpp
#define _included_Core_hpp


#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Shader.h"
#include "Model.h"
#include "Camera.h"
//#include "Beam.h"
//#include "Projectil.h"
//#include "Laser.h"
#include "Navmesh.h"
#include "Map.h"


using namespace std;


class World;

class Core
{

 protected:

  // --------------- ID -----------------------

  int id;

  // ---------- main ressources ------------------


  GLFWwindow* 	      _context;
  World*              _world;

  Camera*             _camera;


  // ----------------------------------

  int                 _win_H;
  int                 _win_W;
  std::string         _titreFenetre;

  // ------------- map ---------------------

  Map*		      _level;

  // ------------ manager -----------

  std::vector<GLuint> _img_manager;
  std::vector<TrxModel*>  _model_manager;

  //Beam* startBeam;
  //Beam* endBeam;

  //ParticleSystem* startParticleSystem;
  //ParticleSystem* endParticleSystem;

  //Projectil* startProjectil;
  //Projectil* endProjectil;



 public:

  std::vector<Navmesh>  _navmesh;

  // ------------ shaders --------------

  Shader _GLSL_3Dbasic;
  Shader _GLSL_particle;
  Shader _GLSL_beam;
  Shader _GLSL_texture_light;
  Shader _GLSL_color3D;

  // CONSTRUCTOR

  Core();

  int 			generateID() {return id++;}

  // ---------- ENGINE ------------------

  void      initApp(const char*,int, int);
  bool      initGL();
  void      initWorld();
  void      run();
  void      render();


// -------- LOAD FUNCTIONS -------------

 void       loadTextures();
 void       loadModels();
 void       loadShaders();
 void	    loadNavmesh();


  // ---------- IMG MANAGER-------------

 void       addTexture(const char*);
 GLuint     getTexture(int);

 // ---------- MODEL MANAGER -----------

 void       addModel(const char*);
 TrxModel*     getModel(int);

 // ---------- PARTICLE MANAGER -----------

 // void		addParticleSystem(ParticleSystem* );
 // void		delParticleSystem(ParticleSystem* );
 // void		updateAllParticleSystem(float);
 // void		renderAllParticleSystem(glm::mat4&, glm::mat4&);

 // ---------- BEAM MANAGER -----------

 // void		addBeam(Beam* );
 // void		delBeam(Beam* );
 // void		updateAllBeam(float);
 // void		renderAllBeam(glm::mat4&, glm::mat4&);

 // ---------- PROJ MANAGER -----------

 // void		addProjectil(Projectil* );
 // void		delProjectil(Projectil* );
 // void		updateAllProjectil(float, float);
 // void		renderAllProjectil(glm::mat4&, glm::mat4&);

 // ---------- NAVM MANAGER -----------

 void			renderAllNavmesh(glm::mat4&, glm::mat4&);


  // ---------- SETTER ------------------


  // ---------- GETTER -------------------

  World*              getWorld();
  GLFWwindow*         getApp();
  Camera*	      getCamera();
  void                getInfo();


  //  --------- DEBBUGER -------------------


  ~Core();

};
#endif
