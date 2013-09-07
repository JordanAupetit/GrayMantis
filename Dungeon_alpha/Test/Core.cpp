#include <math.h>
#include "global.h"
#include "Core.h"
#include "World.h"
#include <time.h>
#include <string>
#include <iostream>

#include "Input.h"
#include "Texture.h"
#include "Model.h"
#include "NPCSoldier.h"
#include "Navmesh.h"



using namespace glm;

#define PI (3.141592653589793)


#ifndef BUFFER_OFFSET
 
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
 
#endif

void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}


Core::Core()
:   _context(NULL),
    _world(NULL),
    _camera(NULL),
    _GLSL_3Dbasic("Shaders/texture.vert","Shaders/texture.frag"),
    _GLSL_particle("Shaders/light_particle.vert","Shaders/light_particle.frag"),
    _GLSL_beam("Shaders/beam.vert","Shaders/beam.frag"),
    _GLSL_texture_light("Shaders/texture_light.vert","Shaders/texture_light.frag"),
    _GLSL_color3D("Shaders/couleur3D.vert", "Shaders/couleur3D.frag")
    /*startBeam(NULL),
    endBeam(NULL),
    startParticleSystem(NULL),
    endParticleSystem(NULL),
    startProjectil(NULL),
    endProjectil(NULL)*/

 

{
}

   //_GLSL_texture_light("Shaders/texture_light.vert","Shaders/texture_light.frag"),
    //_level("Shaders/texture_light.vert","Shaders/texture_light.frag", NULL),

// ----------------------------------- ENGINE ---------------------------------------------------


void Core::initApp(const char* name, int x, int y){


  _win_H = y;
  _win_W = x;
  _titreFenetre = name;




  // ------------ INIT GLFW ------------------

  // Initialize GLFW
  if( !glfwInit() )
    {
      exit(EXIT_FAILURE);
    }

  
  glfwSetErrorCallback(error_callback);

  if(!(_context = glfwCreateWindow(_win_W, _win_H,"title",NULL, NULL))){
    glfwTerminate();
    exit(-1);
  }

  glfwMakeContextCurrent(_context);
  glfwSetWindowPos(_context, 0, 0);

  // ------------ INIT OGL ---------------

  if(!initGL())
    exit(-1);

  printf("INIT : OK\n");

  // loading

  loadTextures();
  loadModels();
  loadShaders();

  initWorld();

}

bool Core::initGL(){

  srand(time(NULL));

  GLenum initialisationGLEW( glewInit() );

  if(initialisationGLEW != GLEW_OK)
    {
      // On affiche l'erreur grâce à la fonction : glewGetErrorString(GLenum code)
 
      std::cout << "Erreur d'initialisation de GLEW : " << glewGetErrorString(initialisationGLEW) << std::endl;return false;

    }

  return true;

}

void Core::initWorld(){



}

void Core::run() {

 glEnable(GL_DEPTH_TEST);

  // FPS COUNTER

  unsigned int frameRate (1000 / 50);
  double debutBoucle = 0, finBoucle = 0, tempsEcoule = 0;

  tempsEcoule = 0.016;

  // Matrices
 
  mat4 projection;
  mat4 modelview;
 
 
  // Initialisation
 
  projection = perspective(70.0, (double) _win_W / _win_H, 0.1, 100.0);
  modelview = mat4(1.0);

  // Variables
 
  bool running = GL_TRUE;

  float angle(0.0);
 
  Input inp(_context);

  // Caméra mobile
 
  _camera = new Camera(vec3(3, 3, 3), vec3(0, 0, 0), vec3(0, 1, 0));
  inp.afficherPointeur(false);
  inp.capturerPointeur(true);

  GLuint tex_lib[2];
  tex_lib[0] = getTexture(3);
  tex_lib[1] = getTexture(2);

  // map

  Map* _level = new Map();

  // npc

  NPCSoldier soldier(ENT_NPC_SOLDIER, glm::vec3(5,0,5));

  // NavMesh


  Navmesh nav(glm::vec3(4,0,2), 7, 10);

  while( running ){

    //if(trx_ps._particlePerSecond > 0) trx_ps._particlePerSecond--;

    debutBoucle = glfwGetTime();
    //printf("getTime :%f\n", debutBoucle);
    inp.updateEvenements();
      
    _camera->deplacer(inp);

    // OpenGL rendering goes here...
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

    _camera->lookAt(modelview);


    mat4 sauvegardeModelview = modelview;

    // ---------------------- UPDATE -----------------------------

    soldier.update(tempsEcoule);

    // ----------------------- RENDER --------------------------
       
    _level->afficher(projection, modelview);
    soldier.draw(projection, modelview);
    nav.draw(projection, modelview);

    modelview = sauvegardeModelview;

    // Swap front and back rendering buffers
    glfwSwapBuffers(_context);
    glfwPollEvents();


    // Check if ESC key was pressed or window was closed
    running = !glfwGetKey(_context, GLFW_KEY_ESCAPE ); //glfwGetWindowAttrib( GLFW_OPENED );

    finBoucle =  glfwGetTime();
    tempsEcoule = finBoucle - debutBoucle;

    char winname[25];
    sprintf(winname, "FabApp - FPS : %4.2f \0", 1/tempsEcoule); 
    glfwSetWindowTitle(_context, winname);

    //printf("fps : %f\n", 1/tempsEcoule);

  }

  delete _level;
  glfwDestroyWindow(_context);
  glfwTerminate();


}


/////////////////////////////////////////// GETTER ////////////////////////////////////////////////////////////////

void Core::getInfo(){

 cout << " info ... " << endl;

}

World* Core::getWorld() {

    return _world;

}

GLFWwindow* Core::getApp(){

    return _context;
}

Camera*   Core::getCamera() {

 return _camera;

}



Core::~Core(){


  //delete _context;
cout << "_context ----------------[DELETED] " << endl;
//delete _world;
cout << "_world --------------[DELETED] " << endl;
delete _camera;
cout << "_camera ---------------[DELETED] " << endl;


 int ent_deleted = 0;

 for (unsigned int i = 0; i < _model_manager.size();){

   delete (_model_manager[i]);
   _model_manager[i] = NULL;
   _model_manager.erase(_model_manager.begin() + i);
   ent_deleted++;
 }

 printf("[DELETED] -- %d models\n", ent_deleted);

 // ent_deleted = 0;

 // for(Projectil* p = startProjectil; p != NULL; p = p->next){

 //   delete p;
 //   ent_deleted++;
 // }

printf("[DELETED] -- %d projectil\n", ent_deleted);
 

cout << "CORE DELETED !" << endl;




}

////////////////////////////////////// IMG MAN ///////////////////////////////////:

GLuint Core::getTexture(int a){

    return _img_manager[a];


}

void Core::addTexture(const char* name){

  printf("loading image \"%s\" : ", name);
  
  Texture texture(name);
  if(texture.charger()){

    printf("ok\n");
    _img_manager.push_back(texture.getID());


  }else{

    printf("failed\n");
    exit(-1);


  }


}



////////////////////////////////////// MODEL MAN ///////////////////////////////////:

TrxModel* Core::getModel(int a){

    return _model_manager[a];


}

void Core::addModel(const char* name){


  _model_manager.push_back(new TrxModel(name));
  printf("loading model \"%s\" :", name);
  printf("\t\t [ok]\n");


}

//  //////////////////////////////////// PARTICLE MAN ///////////////////////////////////

// void Core::addParticleSystem(ParticleSystem* newParticleSystem){

//   if(newParticleSystem == NULL) return;

//   if(endParticleSystem == NULL){

//     newParticleSystem->prev = NULL;
//     newParticleSystem->next = NULL;
//     startParticleSystem = newParticleSystem;
//     endParticleSystem = newParticleSystem;

//   } else {

//     newParticleSystem->prev = endParticleSystem;
//     newParticleSystem->next = NULL;
//     endParticleSystem->next = newParticleSystem;
//     endParticleSystem = newParticleSystem;

//   }

//   printf("ParticleSystem Added\n");

// }

// void Core::delParticleSystem(ParticleSystem* oldParticleSystem){

//   if (oldParticleSystem == NULL) return;

//   // переустанавливаем указатели...
//   if (startParticleSystem == oldParticleSystem) startParticleSystem = oldParticleSystem->next;
//   if (endParticleSystem == oldParticleSystem) endParticleSystem = oldParticleSystem->prev;


//   if (oldParticleSystem->next != NULL) oldParticleSystem->next->prev = oldParticleSystem->prev;
//   else if (oldParticleSystem->prev != NULL) oldParticleSystem->prev->next = NULL;
//   if (oldParticleSystem->prev != NULL) oldParticleSystem->prev->next = oldParticleSystem->next;
//   else if (oldParticleSystem->next != NULL) oldParticleSystem->next->prev = NULL;

// }

// void Core::updateAllParticleSystem(float a){

//   for(ParticleSystem* b = startParticleSystem; b != NULL; b = b->next)
//     b->update(a);

// }

// void Core::renderAllParticleSystem(glm::mat4& p, glm::mat4& m){
 
//   for(ParticleSystem* b = startParticleSystem; b != NULL; b = b->next)
//     b->draw(p,m);

// }

//  //////////////////////////////////// BEAM MAN ///////////////////////////////////

// void Core::addBeam(Beam* newBeam){

//   if(newBeam == NULL) return;

//   if(endBeam == NULL){

//     newBeam->prev = NULL;
//     newBeam->next = NULL;
//     startBeam = newBeam;
//     endBeam = newBeam;

//   } else {

//     newBeam->prev = endBeam;
//     newBeam->next = NULL;
//     endBeam->next = newBeam;
//     endBeam = newBeam;

//   }

//   printf("Beam Added\n");

// }

// void Core::delBeam(Beam* oldBeam){

//   if (oldBeam == NULL) return;

//   // переустанавливаем указатели...
//   if (startBeam == oldBeam) startBeam = oldBeam->next;
//   if (endBeam == oldBeam) endBeam = oldBeam->prev;


//   if (oldBeam->next != NULL) oldBeam->next->prev = oldBeam->prev;
//   else if (oldBeam->prev != NULL) oldBeam->prev->next = NULL;
//   if (oldBeam->prev != NULL) oldBeam->prev->next = oldBeam->next;
//   else if (oldBeam->next != NULL) oldBeam->next->prev = NULL;

// }

// void Core::updateAllBeam(float a){

//   for(Beam* b = startBeam; b != NULL; b = b->next)
//     b->update();

// }

// void Core::renderAllBeam(glm::mat4& p, glm::mat4& m){
 
//   for(Beam* b = startBeam; b != NULL; b = b->next)
//     b->render(p,m);

// }

//  //////////////////////////////////// PROJECTIL MAN ///////////////////////////////////

// void Core::addProjectil(Projectil* newProjectil){

//   if(newProjectil == NULL) return;

//   if(endProjectil == NULL){

//     newProjectil->prev = NULL;
//     newProjectil->next = NULL;
//     startProjectil = newProjectil;
//     endProjectil = newProjectil;

//   } else {

//     newProjectil->prev = endProjectil;
//     newProjectil->next = NULL;
//     endProjectil->next = newProjectil;
//     endProjectil = newProjectil;

//   }

//   printf("Projectil Added\n");

// }

// void Core::delProjectil(Projectil* oldProjectil){

//   if (oldProjectil == NULL) return;

//   // переустанавливаем указатели...
//   if (startProjectil == oldProjectil) startProjectil = oldProjectil->next;
//   if (endProjectil == oldProjectil) endProjectil = oldProjectil->prev;


//   if (oldProjectil->next != NULL) oldProjectil->next->prev = oldProjectil->prev;
//   else if (oldProjectil->prev != NULL) oldProjectil->prev->next = NULL;
//   if (oldProjectil->prev != NULL) oldProjectil->prev->next = oldProjectil->next;
//   else if (oldProjectil->next != NULL) oldProjectil->next->prev = NULL;

// }

// void Core::updateAllProjectil(float a, float c){

//   //for(Projectil* b = startProjectil; b != NULL; b = b->next)
//   //  b->update(a,c);


//   Projectil* b = startProjectil;
//   while (b != NULL){

//     if(b->update(a,c))
//       b = b->next;
//     else{
//       Projectil* del = b;
//       b = b->next;
//       delProjectil(del);
//       delete del;

//     }



//   }


// }

// void Core::renderAllProjectil(glm::mat4& p, glm::mat4& m){
 
//   for(Projectil* b = startProjectil; b != NULL; b = b->next)
//     b->draw(p,m);

// }

////////////////////////////////////////// LOAD //////////////////////////////////

void Core::loadShaders(){

printf("\n== LOADING SHADER ==\n\n");
  _GLSL_3Dbasic.charger();
  _GLSL_particle.charger();
  _GLSL_beam.charger();
  _GLSL_texture_light.charger();
  _GLSL_color3D.charger();
  printf("\n");

}

void Core::loadTextures(){

  printf("\n== LOADING TEXTURE ==\n\n");
  addTexture("texture/laser.bmp");          		//0
  addTexture("texture/Particle.bmp");       		//1
  addTexture("texture/castle_wall_texture.png");        //2
  addTexture("texture/grid_grey.png");       		//3
  addTexture("texture/door.png");       		//4
  addTexture("texture/tower_texture.png");      	//5
  addTexture("texture/wall_texture.png");       	//6
  addTexture("texture/gate_texture.png");       	//7
  addTexture("texture/DarkerGreyStoneFloor.jpg");		//8
  addTexture("texture/castle_wall_texture.png");				//9
  addTexture("texture/soldier_texture.png");        //10 
  printf("\n");

}

void Core::loadModels(){

  printf("== LOADING MODEL ==\n\n");

  addModel("model/soldier.obj");

  printf("\n");
 

}
