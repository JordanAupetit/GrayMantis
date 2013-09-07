#include "Model.h"
#include "objloader.h"
#include <time.h>
#include <stdlib.h>
//#include "math_3d.h"



#ifndef BUFFER_OFFSET
#define BUFFER_OFFSET(offset) ((char*)NULL + (offset))
#endif


TrxModel::TrxModel(const char* name){


  if(!loadAssImp(name, _indices, _vertices, _uvs, _normals)){
    printf("error loading model \n");
    exit(-1);
  }


  if(glIsBuffer(VBO) == GL_TRUE)
    glDeleteBuffers(1, &VBO);

  if(glIsBuffer(IBO) == GL_TRUE)
    glDeleteBuffers(1, &IBO);

  v_size = _vertices.size() * sizeof(glm::vec3);
  u_size = _uvs.size() * sizeof(glm::vec2);
  i_size = _indices.size() * sizeof(unsigned short);

  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  	glBufferData(GL_ARRAY_BUFFER, v_size + u_size, 0, GL_STATIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, v_size, &_vertices[0]);
        glBufferSubData(GL_ARRAY_BUFFER, v_size, u_size, &_uvs[0]);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  
  glGenBuffers(1, &IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

  	glBufferData(GL_ELEMENT_ARRAY_BUFFER, i_size, &_indices[0], GL_STATIC_DRAW);
  
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	
  

}

TrxModel::~TrxModel(){


  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &IBO);


}

void TrxModel::draw(glm::mat4& projection, glm::mat4& modelview){


  // VBO

  
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(v_size));
	glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  
  
  // IBO


  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);


  // Draw the triangles !
  glDrawElements(
		 GL_TRIANGLES,      // mode
		 _indices.size(),    // count
		 GL_UNSIGNED_SHORT,   // type
		 (void*)0           // element array buffer offset
		 );

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  
  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(2);




}
