#include "Camera.h"


Camera::Camera() : m_phi(0.0), m_theta(0.0), m_orientation(), m_axeVertical(0, 0, 1), m_deplacementLateral(), m_position(), m_pointCible()
{
  old_x = 0; old_y = 0;
}


Camera::Camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical) : m_phi(-35.26), m_theta(-135), m_orientation(), m_axeVertical(axeVertical),
                                                                                  m_deplacementLateral(), m_position(position), m_pointCible(pointCible)
{
  old_x = 0; old_y = 0;
  setPointcible(pointCible);
}

void Camera::setPosition(glm::vec3 position)
{
    // Mise à jour de la position
 
    m_position = position;
 
 
    // Actualisation du point ciblé
 
    m_pointCible = m_position + m_orientation;
}

void Camera::orienter(int xRel, int yRel)
{
  // Récupération des angles

  //printf("XREL : %d, YREL : %d\n", xRel, yRel);
 
  m_phi += -yRel * 0.2;
  m_theta += -xRel * 0.2;
 
 
  // Limitation de l'angle phi
 
  if(m_phi > 89.0)
    m_phi = 89.0;
 
  else if(m_phi < -89.0)
    m_phi = -89.0;

  //printf("phi : %f / theta : %f\n", m_phi, m_theta);

  // Conversion des angles en radian
 
  float phiRadian = m_phi * M_PI / 180;
  float thetaRadian = m_theta * M_PI / 180;
 
 
  // Calcul des coordonnées sphériques
 
  m_orientation.x = cos(phiRadian) * sin(thetaRadian);
  m_orientation.y = sin(phiRadian);
  m_orientation.z = cos(phiRadian) * cos(thetaRadian);

  // Calcul de la normale
 
  m_deplacementLateral = glm::cross(m_axeVertical, m_orientation);
  m_deplacementLateral = glm::normalize(m_deplacementLateral);
 
 
  // Calcul du point ciblé pour OpenGL
 
  m_pointCible = m_position + m_orientation;


}

void Camera::deplacer(Input const &input)
{
    // Avancée de la caméra

  if(input.getXRel() != old_x || input.getYRel() != old_y){
  orienter(input.getXRel(), input.getYRel());
  old_x = input.getXRel();old_y = input.getYRel();
  }

 
  if(input.getTouche(GLFW_KEY_W))
    {
  
      m_position = m_position + m_orientation * 0.2f;
      m_pointCible = m_position + m_orientation;

    }
 
 
  // Recul de la caméra
 
  if(input.getTouche(GLFW_KEY_S))
    {
      m_position = m_position - m_orientation * 0.2f;
      m_pointCible = m_position + m_orientation;
    }
 
 
  // Déplacement vers la gauche
 
  if(input.getTouche(GLFW_KEY_A))
    {
      m_position = m_position + m_deplacementLateral * 0.2f;
      m_pointCible = m_position + m_orientation;
    }
 
 
  // Déplacement vers la droite
 
  if(input.getTouche(GLFW_KEY_D))
    {
      m_position = m_position - m_deplacementLateral * 0.2f;
      m_pointCible = m_position + m_orientation;
    }
}

void Camera::lookAt(glm::mat4 &modelview)
{
    // Actualisation de la vue dans la matrice
 
    modelview = glm::lookAt(m_position, m_pointCible, m_axeVertical);
}

void Camera::setPointcible(glm::vec3 pointCible)
{
    // Calcul du vecteur orientation
 
    m_orientation = m_pointCible - m_position;
    m_orientation = glm::normalize(m_orientation);
 
 
    // Si l'axe vertical est l'axe X
 
    if(m_axeVertical.x == 1.0)
    {
        // Calcul des angles
 
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.y / cos(m_phi));
 
        if(m_orientation.y < 0)
            m_theta *= -1;
    }
 
 
    // Si c'est l'axe Y
 
    else if(m_axeVertical.y == 1.0)
    {
        // Calcul des angles
 
        m_phi = asin(m_orientation.y);
        m_theta = acos(m_orientation.z / cos(m_phi));
 
        if(m_orientation.z < 0)
            m_theta *= -1;
    }
 
 
    // Sinon c'est l'axe Z
 
    else
    {
        // Calcul des angles
 
        m_phi = asin(m_orientation.x);
        m_theta = acos(m_orientation.z / cos(m_phi));
 
        if(m_orientation.z < 0)
            m_theta *= -1;
    }
 
 
    // Conversion en degrés
 
    m_phi = m_phi * 180 / M_PI;
    m_theta = m_theta * 180 / M_PI;
}

Camera::~Camera()
{
 
}
