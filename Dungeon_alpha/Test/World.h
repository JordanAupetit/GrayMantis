#ifndef _included_world_h
#define _included_world_h


#include <stdio.h>
#include <string.h>
#include <list>


class World
{


public:

World();


// --------- CREATE FUNCTIONS -------------

void        createWorld(const char*);
void        createPlayer();
void        createNPC();
void        createItem();



// --------- ADD FUNCTIONS -------------

void        addBullet();

void        addNPC();

// -------- UPDATE FUNCTIONS -----------

void update();


// -------- RENDER FUNCTIONS -----------

void            render();

void            renderWorld();


// --------- DISOLVE FUNCTIONS ---------------------

void            disolve();

void            disolve_dead_drop();
void            disolve_dead_NPC();
void            disolve_dead_bullet();


// ----------- GETTER -------------------

 int                generateUniqueID();



protected:


};

#endif
