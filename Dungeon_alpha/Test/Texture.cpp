#include "Texture.h"
#include <stdio.h>


// Constructeur

// Constructeur par défaut
 
Texture::Texture() : m_id(0), m_fichierImage(""), m_largeur(0), m_hauteur(0), m_format(0), m_formatInterne(0), m_textureVide(false)
{
 
}
 
 
// Autre constructeur
 
Texture::Texture(std::string fichierImage) : m_id(0), m_fichierImage(fichierImage), m_largeur(0), m_hauteur(0), m_format(0), m_formatInterne(0), m_textureVide(false)
{
 
}

Texture::Texture(int largeur, int hauteur, GLenum format, GLenum formatInterne, bool textureVide) : m_id(0), m_fichierImage(""), m_largeur(largeur),
                 m_hauteur(hauteur), m_format(format), m_formatInterne(formatInterne), m_textureVide(textureVide)
{
 
}

Texture::Texture(Texture const &textureACopier)
{
    // Copie de la texture
 
    m_fichierImage = textureACopier.m_fichierImage;

    m_largeur = textureACopier.m_largeur;
    m_hauteur = textureACopier.m_hauteur;
    m_format = textureACopier.m_format;
    m_formatInterne = textureACopier.m_formatInterne;
    m_textureVide = textureACopier.m_textureVide;

     
    if(m_textureVide && glIsTexture(textureACopier.m_id) == GL_TRUE)
      chargerTextureVide();  
    else
      charger();
}
 
 
// Destructeur
 
Texture::~Texture()
{
 
}
 
 
// Méthodes
 
bool Texture::charger(bool dds)
{

  if(!dds){

 
    m_id = SOIL_load_OGL_texture
      (
       m_fichierImage.c_str(),
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y //| SOIL_FLAG_NTSC_SAFE_RGB// | SOIL_FLAG_COMPRESS_TO_DXT 
 
       );

 

  }
  else{

    m_id = SOIL_load_OGL_texture
      (
       m_fichierImage.c_str(),
       SOIL_LOAD_AUTO,
       SOIL_CREATE_NEW_ID,
       SOIL_FLAG_DDS_LOAD_DIRECT
 
       );

  }


  if(m_id == 0){
    printf("faid to load texture : %s\n", m_fichierImage.c_str());
    return false;
  }

  glBindTexture(GL_TEXTURE_2D, m_id);

  //The texture wraps over the edges (repeats) in the x direction
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);

  //The texture wraps over the edges (repeats) in the y direction
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
 
  glBindTexture(GL_TEXTURE_2D, 0);



  return true;

}
 
 
GLuint Texture::getID() const
{
    return m_id;
}
 
 
void Texture::setFichierImage(const std::string &fichierImage)
{
    m_fichierImage = fichierImage;
}


void Texture::chargerTextureVide()
{
    // Destruction d'une éventuelle ancienne texture
 
    if(glIsTexture(m_id) == GL_TRUE)
        glDeleteTextures(1, &m_id);
 
 
    // Génération de l'ID
 
    glGenTextures(1, &m_id);

    // Verrouillage
 
    glBindTexture(GL_TEXTURE_2D, m_id);
 
 
    glTexImage2D(GL_TEXTURE_2D, 0, m_formatInterne, m_largeur, m_hauteur, 0, m_format, GL_UNSIGNED_BYTE, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
 
    // Déverrouillage
 
    glBindTexture(GL_TEXTURE_2D, 0);

}

Texture& Texture::operator=(Texture const &textureACopier)
{
    // Copie des attributs
     
    m_fichierImage = textureACopier.m_fichierImage;
     
    m_largeur = textureACopier.m_largeur;
    m_hauteur = textureACopier.m_hauteur;
    m_format = textureACopier.m_format;
    m_formatInterne = textureACopier.m_formatInterne;
    m_textureVide = textureACopier.m_textureVide;
     
     
    // Si la texture est vide, alors on appelle la méthode chargerTextureVide()
     
    if(m_textureVide && glIsTexture(textureACopier.m_id) == GL_TRUE)
        chargerTextureVide();
     
     
    // Sinon, on appelle la méthode charger() par défaut
     
    else if(glIsTexture(textureACopier.m_id) == GL_TRUE)
        charger();
 
 
    // Retour du pointeur *this
 
    return *this;
}
