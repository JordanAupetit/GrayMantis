#ifndef DEF_TEXTURE
#define DEF_TEXTURE
 
 
// Include
 
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <SOIL/SOIL.h>


class Texture
{
    public:
 
  Texture();
  Texture(std::string fichierImage);
  Texture(int largeur, int hauteur, GLenum format, GLenum formatInterne, bool textureVide);
  Texture(Texture const &textureACopier);
  Texture& operator=(Texture const &);
  ~Texture();
  bool charger(bool = false);
  GLuint getID() const;
  void setFichierImage(const std::string &fichierImage);
  void chargerTextureVide();
 
 
 private:
 
  GLuint m_id;
  std::string m_fichierImage;

  int m_largeur;
  int m_hauteur;
  GLenum m_format;
  GLenum m_formatInterne;
  bool m_textureVide;

};
#endif
