
#include "global.h"
#include "Core.h"

int main( void )
{

  g_core = new Core();
  g_core->initApp("lol", 800, 600);
    
    g_core->run();

    delete g_core;



return 0;
}
