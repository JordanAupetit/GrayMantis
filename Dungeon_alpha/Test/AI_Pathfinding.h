
/*
  
  getPath est la fonction appellée depuis NPC pour trouver un chemin d'un point A vers un point B, la fonction donne la liste des navmeshs à traverser.

  Input : 
  -------

  start : position de départ du NPC
  goal : position à atteindre
  path : tableau de pointeur sur Navmesh déclaré dynamiquement (~32 cases) ou tableau existant dans la classe NPC

  Ouput :
  -------

  valeur de retour : 1 si chemin trouvé, 0 sinon
  path : tableau contenant la liste des navmesh à traverser pour attendre l'objectif
  
  Autre :
  ------- 
  
  g_core._navmesh : Vecteur de tous les navmesh

  Algo de pathfinding : Dijkstra


  Implémentation :
  ----------------

  Le plus simple serait de créer un tableau de float qui représenterait le poids de chaque mesh en terme de distance

  

 */


int getPath(Navmesh** path, glm::vec3 start, glm::vec3 goal);
