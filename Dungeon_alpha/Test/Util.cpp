#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <time.h>
#include <math.h>


#include "Util.h"


int getRandomValue(int min, int max){

  if(min == max)
    return min;
  else
    return( min + (rand() % (max - min)) );

}
