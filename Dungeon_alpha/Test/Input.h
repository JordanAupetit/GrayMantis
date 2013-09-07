#ifndef DEF_INPUT
#define DEF_INPUT

// Include

#include <GLFW/glfw3.h>

// Classe

class Input
{
 public:

  Input(GLFWwindow*);
  ~Input();
  
  void updateEvenements();
  bool terminer() const;
  void afficherPointeur(bool reponse) const;
  void capturerPointeur(bool reponse);

  bool getTouche(int) const;
  bool getBoutonSouris() const;
  bool mouvementSouris() const;

  int getX() const;
  int getY() const;

  int getXRel() const;
  int getYRel() const;


 private:
    
  bool _fixed_mouse;
  GLFWwindow* _context;


};

#endif

