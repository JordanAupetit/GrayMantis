#ifndef DEF_CAMERA
#define DEF_CAMERA
 
 
// Includes GLM
 
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Input.h"
 
 
// Classe
 
class Camera
{
    public:
 
    Camera();
    Camera(glm::vec3 position, glm::vec3 pointCible, glm::vec3 axeVertical);
    ~Camera();

    void orienter(int, int);
    void deplacer(Input const&);
    void lookAt(glm::mat4&);
    void setPointcible(glm::vec3);
    void setPosition(glm::vec3 position);

    glm::vec3 m_position;
    glm::vec3 m_orientation;
    float m_phi;
    float m_theta;

    private:
 

 
    glm::vec3 m_axeVertical;
    glm::vec3 m_deplacementLateral;
 

    glm::vec3 m_pointCible;

    int old_x,old_y;

};
 
#endif
