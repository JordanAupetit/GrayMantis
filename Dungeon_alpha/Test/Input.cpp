#include "Input.h"
#include <stdio.h>


#define WIN_X 800
#define WIN_Y 600

bool k_z;
bool k_s;
bool k_d;
bool k_q;

int m_x;
int m_y;
int m_xRel;
int m_yRel;


void handleKeypress(GLFWwindow* window, int theKey, int scancode, int theAction, int mods){
  // If a key is pressed, toggle the relevant key-press flag
    if (theAction == GLFW_PRESS)
    {
 
        switch(theKey)
        {
        case 'Z':
	  k_z = true;
	  break;
 
        case 'S':
	  k_s = true;
	  break;
 
        case 'Q':
	  k_q = true;
	  break;
 
        case 'D':
	  k_d = true;
	  break;
 
        default:
	  // Do nothing...
            break;
        }
    }
    else // If a key is released, toggle the relevant key-release flag
    {
        switch(theKey)
        {
        case 'Z':
	  k_z = false;
	  break;
 
        case 'S':
	  k_s = false;
	  break;
 
        case 'Q':
	  k_q = false;
	  break;
 
        case 'D':
	  k_d = false;
	  break;
 
        default:
            // Do nothing...
            break;
        }
    }
}

void handleMouseMove(GLFWwindow* window, double mouseX, double mouseY){

  //m_xRel = 0;
  //m_yRel = 0;

  m_x = mouseX;
  m_y = mouseY;

  m_xRel = m_x - WIN_X / 2;
  m_yRel = m_y - WIN_Y / 2;
  //m_yRel = 0;

  //printf("x= %d / y= %d\n", m_xRel, m_yRel);

}

// Constructeur et Destructeur

Input::Input(GLFWwindow * c) : _context(c), _fixed_mouse(false)
{

  m_x = 0;
  m_y = 0;
  m_xRel = 0;
  m_yRel = 0;
  k_z = false;
  k_s = false;
  k_q = false;
  k_d = false;
  printf("Window is currently %d*%d\n", (int)WIN_X, (int)WIN_Y);

  // Specify the function which should execute when a key is pressed or released
  
  glfwSetKeyCallback(_context, &handleKeypress);
 
  // Specify the function which should execute when the mouse is moved
  
  glfwSetCursorPosCallback(_context, handleMouseMove);

}


Input::~Input()
{

}


// Méthodes

void Input::updateEvenements()
{
    // Pour éviter des mouvements fictifs de la souris, on réinitialise les coordonnées relatives

    //m_xRel = 0;
    //m_yRel = 0;

    //printf("UPDATE \n");


   if(_fixed_mouse)
     glfwSetCursorPos(_context, WIN_X/2, WIN_Y/2);

}


void Input::afficherPointeur(bool reponse) const
{
    if(reponse)
      glfwSetInputMode(_context,GLFW_CURSOR,GLFW_CURSOR_NORMAL);

    else
      glfwSetInputMode(_context,GLFW_CURSOR,GLFW_CURSOR_HIDDEN);
}


void Input::capturerPointeur(bool reponse)
{
  _fixed_mouse = reponse;

}



// Getters

bool Input::getTouche(int a) const
{
  //return m_touches[touche];
  return glfwGetKey(_context, a) == GLFW_PRESS;
}


bool Input::getBoutonSouris() const
{
  //return m_boutonsSouris[bouton];
  return 0;
}


bool Input::mouvementSouris() const
{
  //printf("MS x:%d | y:%d !!!\n", m_xRel, m_yRel);
    if(m_xRel == 0 && m_yRel == 0)
        return false;

    else
        return true;
}


// Getters concernant la position du curseur

int Input::getX() const
{
    return m_x;
}

int Input::getY() const
{
    return m_y;
}

int Input::getXRel() const
{
    return m_xRel;
}

int Input::getYRel() const
{
    return m_yRel;
}
