#include "global.h"
#include "Core.h"
#include "Map.h"
#include <unistd.h>
#include <math.h>

#define _W_ 10.0f
#define _H_ 50.0f

#define PI 3.14159265359

// Permet d'éviter la ré-écriture du namespace glm::

using namespace glm;

// Macro utile au VBO

#ifndef BUFFER_OFFSET
 
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
 
#endif


 // ------------------------- BREAKABLE MANAGER -----------------------------

Breakable* Map::addBreakable(Breakable* newBreakable){

  if(newBreakable == NULL) return NULL;

  if(_endBreakable == NULL){

    newBreakable->prev = NULL;
    newBreakable->next = NULL;
    _startBreakable = newBreakable;
    _endBreakable = newBreakable;

  } else {

    newBreakable->prev = _endBreakable;
    newBreakable->next = NULL;
    _endBreakable->next = newBreakable;
    _endBreakable = newBreakable;

  }

  printf("Breakable Added\n");

  return newBreakable;

}

void Map::delBreakable(Breakable* oldBreakable){


  if (oldBreakable == NULL) return;

  // переустанавливаем указатели...
  if (_startBreakable == oldBreakable) _startBreakable = oldBreakable->next;
  if (_endBreakable == oldBreakable) _endBreakable = oldBreakable->prev;


  if (oldBreakable->next != NULL) oldBreakable->next->prev = oldBreakable->prev;
  else if (oldBreakable->prev != NULL) oldBreakable->prev->next = NULL;
  if (oldBreakable->prev != NULL) oldBreakable->prev->next = oldBreakable->next;
  else if (oldBreakable->next != NULL) oldBreakable->next->prev = NULL;

}

void Map::updateAllBreakable(float a){

  if(_startBreakable == NULL) return;

  for(Breakable* b = _startBreakable; b != NULL; b = b->next)
    b->update(a);

}

void Map::renderAllBreakable(glm::mat4& p, glm::mat4& m){

  for(Breakable* b = _startBreakable; b != NULL; b = b->next)
    b->draw(p,m);

}


void addFace(float* vertices, float* texture, int &i, int &j,
		float x1, float y1, float z1, 
		float x2, float y2, float z2){


  float rat_x = x2 - x1;
  float rat_y = y2 - y1;
  float rat_z = z2 - z1;

  float scale_floor = 0.25;
  float scale_wall = 0.25;

  float ratio;
  float norm;



  // vertice


  if(y1 == y2){

  vertices[i++] = x1;
  vertices[i++] = y1;
  vertices[i++] = z1;
 
  vertices[i++] = x2;
  vertices[i++] = y1;
  vertices[i++] = z1;
 
  vertices[i++] = x2;
  vertices[i++] = y1;
  vertices[i++] = z2;

  vertices[i++] = x1; 
  vertices[i++] = y1; 
  vertices[i++] = z2;

  }
  else
  if(z1 == z2){

  vertices[i++] = x1;
  vertices[i++] = y1;
  vertices[i++] = z1;
 
  vertices[i++] = x2;
  vertices[i++] = y1;
  vertices[i++] = z1;
 
  vertices[i++] = x2;
  vertices[i++] = y2;
  vertices[i++] = z1;

  vertices[i++] = x1; 
  vertices[i++] = y2; 
  vertices[i++] = z1;

  }
  else
  if(x1 == x2){

  vertices[i++] = x1;
  vertices[i++] = y1;
  vertices[i++] = z1;
 
  vertices[i++] = x1;
  vertices[i++] = y1;
  vertices[i++] = z2;
 
  vertices[i++] = x1;
  vertices[i++] = y2;
  vertices[i++] = z2;

  vertices[i++] = x1; 
  vertices[i++] = y2; 
  vertices[i++] = z1;

  }
  else
    printf("this face will not be added !\n");


  // texture



  if(y1 == y2){

    ratio = rat_x;
    norm = rat_z;
    ratio *= scale_floor;
    norm *= scale_floor;

  }
  else if(x1 == x2){
    ratio = rat_z;
    norm = rat_y;
    ratio *= scale_wall;
    norm *= scale_wall;
  }
  else{ // z1 == z2

    ratio = rat_x;
    norm = rat_y;
    ratio *= scale_wall;
    norm *= scale_wall;

  }


  texture[j++] = 0.0f;
  texture[j++] = 0.0f;

  texture[j++] = ratio;
  texture[j++] = 0.0f;

  texture[j++] = ratio;
  texture[j++] = norm; 

  texture[j++] = 0.0;
  texture[j++] = norm;


}
		


// Constructeur et Destructeur

Map::Map(GLuint* tex) :  m_vboID(0), m_tailleVerticesBytes(72 * sizeof(float)),m_tailleCouleursBytes(48 * sizeof(float)), m_vaoID(0),
			 _startBreakable(NULL),
			 _endBreakable(NULL)
{
  // Chargement du shader

  printf("map...\n");

  printf("map2...\n");

  m_texture_id[0] = tex[0];
  m_texture_id[1] = tex[1];

  printf("texture id : %d\n", m_texture_id);

  

  // Vertices temporaires
  
  float x1,y1,z1;
  float x2,y2,z2;

  x1 = 4.0f;
  y1 = 0.0f;
  z1 = 2.0f;

  x2 = 11.0f;
  y2 = 0.0f;
  z2 = 12.0f;


  _nb_surface = 1; //52
  floor_num = 1;
  wall_num = 0;


  _surface = new map_surface[_nb_surface];

 // wall

  // floor

  _surface[0].pos1 = glm::vec3(0.0f,0.0f,0.0f);
  _surface[0].pos2 = glm::vec3(150.0f,0.0f,150.0f);

  m_vertices = new float[12 * _nb_surface]; 
  m_texture = new float[8 * _nb_surface]; 
  m_tailleVerticesBytes = _nb_surface * 12 * sizeof(float);
  m_tailleCouleursBytes = _nb_surface * 8 * sizeof(float);
  
  int i = 0;
  int j = 0;

  printf("addface : ... \n");

  for(int a = 0; a < _nb_surface; a++){

    map_surface s = _surface[a];

    addFace(m_vertices, m_texture, i, j, 
	  s.pos1.x, s.pos1.y, s.pos1.z,
	  s.pos2.x, s.pos2.y, s.pos2.z);

    printf("addFace(vert, m_texture, %d, %d, %f, %f, %f, %f, %f, %f);\n",
	   i,j,s.pos1.x, s.pos1.y, s.pos1.z,s.pos2.x, s.pos2.y, s.pos2.z);

  }


  printf("addface : ok \n");

}


Map::~Map()
{

  // Destruction du VBO
 
  glDeleteBuffers(1, &m_vboID);

    // Destruction du VAO
 
  glDeleteVertexArrays(1, &m_vaoID);

  //for(map_surface* tmp = _surface; tmp != NULL; tmp++)
  delete _surface;

  delete m_vertices;
  delete m_texture;


 for(Breakable* p = _startBreakable; p != NULL; p = p->next){

   p->dumpInfo();
   delete p;
   
 }

}


void Map::charger()
{
  printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
  // Destruction d'un éventuel ancien VBO
 
  if(glIsBuffer(m_vboID) == GL_TRUE)
    glDeleteBuffers(1, &m_vboID);
  // Génération de l'ID
 
  glGenBuffers(1, &m_vboID);

  // Verrouillage du VBO
 
  glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

  glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCouleursBytes, 0, GL_STATIC_DRAW);
 
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes, m_vertices);
  glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCouleursBytes, m_texture);
 
  // Déverrouillage de l'objet
 
  glBindBuffer(GL_ARRAY_BUFFER, 0);


  // VAO

  // Destruction d'un éventuel ancien VAO
 
  if(glIsVertexArray(m_vaoID) == GL_TRUE)
    glDeleteVertexArrays(1, &m_vaoID);

  glGenVertexArrays(1, &m_vaoID);

  // Verrouillage du VAO
 
  glBindVertexArray(m_vaoID);
 
 
  // Vide pour le moment
 
 
  glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
 
 
  // Accès aux vertices dans la mémoire vidéo
 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glEnableVertexAttribArray(0);
 
 
  // Accès aux couleurs dans la mémoire vidéo
 
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVerticesBytes));
  glEnableVertexAttribArray(1);
 
 
  // Déverrouillage du VBO
 
  glBindBuffer(GL_ARRAY_BUFFER, 0);
 
 
  // Déverrouillage du VAO
 
  glBindVertexArray(0);

}

// Méthodes

void Map::loadMap(const char* filepath){

  FILE * file = fopen(filepath, "r");
  if( file == NULL ){
    printf("Error %s : not found\n", filepath);
    return;
  }

  while(1){


    char lineHeader[128];
    int res = fscanf(file, "%s", lineHeader);
    if (res == EOF)
      break; // EOF = End Of File. Quit the loop.

    int brkt;
    float x,y,z,p,yaw,r;

    //fscanf(file, "%s", brkt);
    fscanf(file, "%f %f %f %f %f %f\n", &x, &y, &z, &p, &yaw, &r);
    //printf("-> %s <- %.2f - %.2f - %.2f === %.2f - %.2f - %.2f\n", lineHeader, x,y,z,p,yaw,r);

    p = p * PI / 180;
    yaw = yaw * PI / 180;
    r = r * PI / 180;

    switch(lineHeader[0]){

    case 't' : addBreakable(new Breakable(ENT_BREAKABLE,glm::vec3(x,y,z),glm::vec3(p,yaw,r),BRK_TOWER));break;
    case 'w' : addBreakable(new Breakable(ENT_BREAKABLE,glm::vec3(x,y,z),glm::vec3(p,yaw,r),BRK_WALL));break;
    case 'f' : addBreakable(new Breakable(ENT_BREAKABLE,glm::vec3(x,y,z),glm::vec3(p,yaw,r),BRK_DOOR_FRAME));break;
    defaut : printf("import erreur : %c\n", lineHeader[0]);
    }

  }



}

void Map::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{


  glm::vec4 light_ambiant;
  
  light_ambiant.x = 1.0f;
  light_ambiant.y = 1.0f;
  light_ambiant.z = 1.0f;
  light_ambiant.w = 1.0f;

  // Activation du shader
 
  
  Shader* shdr = &g_core->_GLSL_texture_light;

  glUseProgram(shdr->getProgramID());
    

  // Envoi des vertices
 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
  glEnableVertexAttribArray(0);

  // Envoi des coordonnées de texture
 
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_texture);
  glEnableVertexAttribArray(2);
 
 
  // Envoi des matrices
 
  glUniformMatrix4fv(glGetUniformLocation(shdr->getProgramID(), "u_projection"), 1, GL_FALSE, value_ptr(projection));
  glUniformMatrix4fv(glGetUniformLocation(shdr->getProgramID(), "u_modelview"), 1, GL_FALSE, value_ptr(modelview));
  glUniform4fv(glGetUniformLocation(shdr->getProgramID(), "light"), 1, value_ptr(light_ambiant));

 
 
  // Verrouillage de la texture
 
 
 
  // Rendu

  //glEnable(GL_CULL_FACE);
  //glCullFace(GL_FRONT);


  // draw floor only

  glBindTexture(GL_TEXTURE_2D, m_texture_id[0]);
 
  glDrawArrays(GL_QUADS, 0, 4);

  // draw wall only

  //glBindTexture(GL_TEXTURE_2D, m_texture_id[1]);

  //glDrawArrays(GL_QUADS, floor_num, wall_num);

 
  //glDisable(GL_CULL_FACE);
 
  // Déverrouillage de la texture
 
  glBindTexture(GL_TEXTURE_2D, 0);
 
 
  // Désactivation des tableaux
 
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(0);
 
 
  // Désactivation du shader
 
  glUseProgram(0);

  renderAllBreakable(projection, modelview);

}

