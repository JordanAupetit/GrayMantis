#include "global.h"
#include "Core.h"
#include "Map.h"
#include <math.h>

#define _W_ 10.0f
#define _H_ 50.0f

// Permet d'�viter la r�-�criture du namespace glm::

using namespace glm;


// Macro utile au VBO

#ifndef BUFFER_OFFSET
 
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
 
#endif


void addFace(float* vertices, float* texture, int &i, int &j,
		float x1, float y1, float z1, 
		float x2, float y2, float z2){


  float rat_x = x2 - x1;
  float rat_y = y2 - y1;
  float rat_z = z2 - z1;

  float scale_floor = 0.75;
  float scale_wall = 0.75;

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

Map::Map() : m_vboID(0), m_tailleVerticesBytes(72 * sizeof(float)),m_tailleCouleursBytes(48 * sizeof(float)), m_vaoID(0)
{
  // Chargement du shader


  m_texture_id[0] = g_core->getTexture(8);
  m_texture_id[1] = g_core->getTexture(9);

  // Vertices temporaires
  
  float x1,y1,z1;
  float x2,y2,z2;

  x1 = 4.0f;
  y1 = 0.0f;
  z1 = 2.0f;

  x2 = 11.0f;
  y2 = 0.0f;
  z2 = 12.0f;

  map_surface tmp;
  tmp.pos1 = glm::vec3(4,0,2);
  tmp.pos2 = glm::vec3(11,0,12);
  tmp.type = 'f';
  tmp.texture = g_core->getTexture(8);


  _nb_surface = 61; //52
  floor_num = 4 * 13;
  wall_num = 4 * 48;


  _surface = new map_surface[_nb_surface];

 // wall


  _surface[13].pos1 = glm::vec3(11,0,6);
  _surface[13].pos2 = glm::vec3(11,5,2);

  _surface[14].pos1 = glm::vec3(11,0,2);
  _surface[14].pos2 = glm::vec3(4,5,2);

  _surface[15].pos1 = glm::vec3(11,0,12);
  _surface[15].pos2 = glm::vec3(11,5,9);

  _surface[16].pos1 = glm::vec3(4,0,12);
  _surface[16].pos2 = glm::vec3(11,5,12);

  _surface[17].pos1 = glm::vec3(4,0,2);
  _surface[17].pos2 = glm::vec3(4,5,12);

  _surface[18].pos1 = glm::vec3(46,0, 6);
  _surface[18].pos2 = glm::vec3(11,5, 6);

  _surface[19].pos1 = glm::vec3(11,0, 9);
  _surface[19].pos2 = glm::vec3(23,5, 9);

  _surface[20].pos1 = glm::vec3(26,0, 9);
  _surface[20].pos2 = glm::vec3(43,5, 9);

  _surface[21].pos1 = glm::vec3(23,0, 9);
  _surface[21].pos2 = glm::vec3(23,5, 20);

  _surface[22].pos1 = glm::vec3(26,0, 29);
  _surface[22].pos2 = glm::vec3(26,5, 9);

  _surface[23].pos1 = glm::vec3(26,0, 42);
  _surface[23].pos2 = glm::vec3(26,5, 33);

  _surface[24].pos1 = glm::vec3(23,0, 23);
  _surface[24].pos2 = glm::vec3(23,5, 42);

  _surface[25].pos1 = glm::vec3(23,0, 20);
  _surface[25].pos2 = glm::vec3(10,5, 20);

  _surface[26].pos1 = glm::vec3(10,0, 23);
  _surface[26].pos2 = glm::vec3(23,5, 23);

  _surface[27].pos1 = glm::vec3(43,0, 29);
  _surface[27].pos2 = glm::vec3(26,5, 29);

  _surface[28].pos1 = glm::vec3(26,0, 33);
  _surface[28].pos2 = glm::vec3(46,5, 33);

  _surface[29].pos1 = glm::vec3(23,0, 42);
  _surface[29].pos2 = glm::vec3(15,5, 42);

  _surface[30].pos1 = glm::vec3(15,0, 45);
  _surface[30].pos2 = glm::vec3(43,5, 45);


  _surface[31].pos1 = glm::vec3(10,0, 20);
  _surface[31].pos2 = glm::vec3(10,5, 17);

  _surface[32].pos1 = glm::vec3(10,0, 17);
  _surface[32].pos2 = glm::vec3(2,5, 17);

  _surface[33].pos1 = glm::vec3(2,0, 17);
  _surface[33].pos2 = glm::vec3(2,5, 28);

  _surface[34].pos1 = glm::vec3(2,0, 28);
  _surface[34].pos2 = glm::vec3(4,5, 28);

  _surface[35].pos1 = glm::vec3(7,0, 28);
  _surface[35].pos2 = glm::vec3(10,5, 28);

  _surface[36].pos1 = glm::vec3(10,0, 28);
  _surface[36].pos2 = glm::vec3(10,5, 23);



  _surface[37].pos1 = glm::vec3(4,0, 34);
  _surface[37].pos2 = glm::vec3(2,5, 34);

  _surface[38].pos1 = glm::vec3(2,0, 34);
  _surface[38].pos2 = glm::vec3(2,5, 47);

  _surface[39].pos1 = glm::vec3(2,0, 47);
  _surface[39].pos2 = glm::vec3(15,5, 47);
  
  _surface[40].pos1 = glm::vec3(15,0, 47);
  _surface[40].pos2 = glm::vec3(15,5, 45);

  _surface[41].pos1 = glm::vec3(15,0, 42);
  _surface[41].pos2 = glm::vec3(15,5, 34);

  _surface[42].pos1 = glm::vec3(15,0, 34);
  _surface[42].pos2 = glm::vec3(7,5, 34);

 

  _surface[43].pos1 = glm::vec3(4,0, 28);
  _surface[43].pos2 = glm::vec3(4,5, 34);

  _surface[44].pos1 = glm::vec3(7,0, 34);
  _surface[44].pos2 = glm::vec3(7,5, 28);



  _surface[45].pos1 = glm::vec3(43,0, 14);
  _surface[45].pos2 = glm::vec3(39,5, 14);

  _surface[46].pos1 = glm::vec3(50,0, 14);
  _surface[46].pos2 = glm::vec3(46,5, 14);

  _surface[47].pos1 = glm::vec3(39,0, 24);
  _surface[47].pos2 = glm::vec3(43,5, 24);

  _surface[48].pos1 = glm::vec3(46,0, 24);
  _surface[48].pos2 = glm::vec3(50,5, 24);

  _surface[49].pos1 = glm::vec3(39,0, 14);
  _surface[49].pos2 = glm::vec3(39,5, 24);

  _surface[50].pos1 = glm::vec3(50,0, 24);
  _surface[50].pos2 = glm::vec3(50,5, 14);



  _surface[51].pos1 = glm::vec3(43,0, 9);
  _surface[51].pos2 = glm::vec3(43,5, 14);

  _surface[52].pos1 = glm::vec3(46,0, 14);
  _surface[52].pos2 = glm::vec3(46,5, 6);

  _surface[53].pos1 = glm::vec3(43,0, 24);
  _surface[53].pos2 = glm::vec3(43,5, 29);

  _surface[54].pos1 = glm::vec3(46,0, 33);
  _surface[54].pos2 = glm::vec3(46,5, 24);



  _surface[55].pos1 = glm::vec3(50,0, 39);
  _surface[55].pos2 = glm::vec3(43,5, 39);

  _surface[56].pos1 = glm::vec3(43,0, 47);
  _surface[56].pos2 = glm::vec3(50,5, 47);

  _surface[57].pos1 = glm::vec3(43,0, 42);
  _surface[57].pos2 = glm::vec3(26,5, 42);

  _surface[58].pos1 = glm::vec3(50,0, 47);
  _surface[58].pos2 = glm::vec3(50,5, 39);

  _surface[59].pos1 = glm::vec3(43,0, 39);
  _surface[59].pos2 = glm::vec3(43,5, 42);

  _surface[60].pos1 = glm::vec3(43,0, 45);
  _surface[60].pos2 = glm::vec3(43,5, 47);

  // floor

  _surface[0].pos1 = glm::vec3(4,0,2);
  _surface[0].pos2 = glm::vec3(11,0,12);

  _surface[1].pos1 = glm::vec3(11,0,6);
  _surface[1].pos2 = glm::vec3(46,0,9);

  _surface[2].pos1 = glm::vec3(23,0,9);
  _surface[2].pos2 = glm::vec3(26,0,42);

  _surface[3].pos1 = glm::vec3(43,0,9);
  _surface[3].pos2 = glm::vec3(46,0,14);

  _surface[4].pos1 = glm::vec3(39,0,14);
  _surface[4].pos2 = glm::vec3(50,0,24);

  _surface[5].pos1 = glm::vec3(43,0,24);
  _surface[5].pos2 = glm::vec3(46,0,29);

  _surface[6].pos1 = glm::vec3(26,0,29);
  _surface[6].pos2 = glm::vec3(46,0,33);

  _surface[7].pos1 = glm::vec3(10,0,20);
  _surface[7].pos2 = glm::vec3(23,0,23);

  _surface[8].pos1 = glm::vec3(2,0,17);
  _surface[8].pos2 = glm::vec3(10,0,28);

  _surface[9].pos1 = glm::vec3(4,0,28);
  _surface[9].pos2 = glm::vec3(7,0,34);

  _surface[10].pos1 = glm::vec3(2,0,34);
  _surface[10].pos2 = glm::vec3(15,0,47);

  _surface[11].pos1 = glm::vec3(15,0,42);
  _surface[11].pos2 = glm::vec3(43,0,45);

  _surface[12].pos1 = glm::vec3(43,0,39);
  _surface[12].pos2 = glm::vec3(50,0,47);




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

  }


  printf("addface : ok \n");

  /*
  // vertex
  
  m_vertices[0] = x1;
  m_vertices[1] = y1;
  m_vertices[2] = z1;
 
  m_vertices[3] = x2;
  m_vertices[4] = y1;
  m_vertices[5] = z1;
 
  m_vertices[6] = x2;
  m_vertices[7] = y1;
  m_vertices[8] = z2;

  m_vertices[9] = x1; 
  m_vertices[10] = y1; 
  m_vertices[11] = z2;


  // texture

  m_texture[0] = 0;
  m_texture[1] = 0;

  m_texture[2] = 1;
  m_texture[3] = 0;

  m_texture[4] = 1;
  m_texture[5] = 1;

  m_texture[6] = 0;
  m_texture[7] = 1;
  */			
 
}


Map::~Map()
{

  // Destruction du VBO
 
  glDeleteBuffers(1, &m_vboID);

    // Destruction du VAO
 
  glDeleteVertexArrays(1, &m_vaoID);


  delete _surface;

  delete m_vertices;
  delete m_texture;


}


void Map::charger()
{
  printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
  // Destruction d'un �ventuel ancien VBO
 
  if(glIsBuffer(m_vboID) == GL_TRUE)
    glDeleteBuffers(1, &m_vboID);
  // G�n�ration de l'ID
 
  glGenBuffers(1, &m_vboID);

  // Verrouillage du VBO
 
  glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

  glBufferData(GL_ARRAY_BUFFER, m_tailleVerticesBytes + m_tailleCouleursBytes, 0, GL_STATIC_DRAW);
 
  glBufferSubData(GL_ARRAY_BUFFER, 0, m_tailleVerticesBytes, m_vertices);
  glBufferSubData(GL_ARRAY_BUFFER, m_tailleVerticesBytes, m_tailleCouleursBytes, m_texture);
 
  // D�verrouillage de l'objet
 
  glBindBuffer(GL_ARRAY_BUFFER, 0);


  // VAO

  // Destruction d'un �ventuel ancien VAO
 
  if(glIsVertexArray(m_vaoID) == GL_TRUE)
    glDeleteVertexArrays(1, &m_vaoID);

  glGenVertexArrays(1, &m_vaoID);

  // Verrouillage du VAO
 
  glBindVertexArray(m_vaoID);
 
 
  // Vide pour le moment
 
 
  glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
 
 
  // Acc�s aux vertices dans la m�moire vid�o
 
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
  glEnableVertexAttribArray(0);
 
 
  // Acc�s aux couleurs dans la m�moire vid�o
 
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(m_tailleVerticesBytes));
  glEnableVertexAttribArray(1);
 
 
  // D�verrouillage du VBO
 
  glBindBuffer(GL_ARRAY_BUFFER, 0);
 
 
  // D�verrouillage du VAO
 
  glBindVertexArray(0);

}

// M�thodes

void Map::afficher(glm::mat4 &projection, glm::mat4 &modelview)
{


  glm::vec4 light_ambiant;
  
  light_ambiant.x = 1.0f;
  light_ambiant.y = 1.0f;
  light_ambiant.z = 1.0f;
  light_ambiant.w = 1.0f;

  Shader* glsl = &g_core->_GLSL_texture_light;

    // Activation du shader
 
    glUseProgram(glsl->getProgramID());
 
 
        // Envoi des vertices
 
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, m_vertices);
        glEnableVertexAttribArray(0);
 
 
        // Envoi des coordonn�es de texture
 
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, m_texture);
        glEnableVertexAttribArray(2);
 
 
        // Envoi des matrices
 
        glUniformMatrix4fv(glGetUniformLocation(glsl->getProgramID(), "u_projection"), 1, GL_FALSE, value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(glsl->getProgramID(), "u_modelview"), 1, GL_FALSE, value_ptr(modelview));
	      glUniform4fv(glGetUniformLocation(glsl->getProgramID(), "light"), 1, value_ptr(light_ambiant));

 
 
        // Verrouillage de la texture
 
 
 
        // Rendu

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);


	// draw floor only

	glBindTexture(GL_TEXTURE_2D, m_texture_id[0]);
 
        glDrawArrays(GL_QUADS, 0, floor_num);

	// draw wall only

	glBindTexture(GL_TEXTURE_2D, m_texture_id[1]);

	glDrawArrays(GL_QUADS, floor_num, wall_num);

 
	glDisable(GL_CULL_FACE);
 
        // D�verrouillage de la texture
 
        glBindTexture(GL_TEXTURE_2D, 0);
 
 
        // D�sactivation des tableaux
 
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(0);
 
 
    // D�sactivation du shader
 
    glUseProgram(0);

  

}

