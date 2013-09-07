#include <fstream>
#include "Core.h"
#include "global.h"
#include "World.h"
#include "Bullet.h"
#include "tinyxml.h"
#include "Weapon.h"
#include "Menu.h"

#define zoneAffichable 5

#define DEBUG_PRINT 0


World::World()
: _nextUniqueID(0)
{

}

int World::generateUniqueID() {


    return ++_nextUniqueID;


}

void World::createWorld(const char* lvlname){

   /* int nbColonnes = 20;
    int nbLignes = 20;

    _matrice = new tile*[nbColonnes];

	for(int i=0; i<nbColonnes; i++)
		_matrice[i] = new tile[nbLignes];

    for(int i = 0; i < nbColonnes; i++)
        for(int j = 0; j < nbLignes; j ++){

            _matrice[i][j].spr.setTexture(*(g_core->getImageManager()->getImage(1)));
            _matrice[i][j].spr.setPosition(i*100, j*100);
            //spr.setTextureRect(sf::IntRect(ipos.x, ipos.y, ipos.x + _frameW, ipos.y + _frameH));
            //spr.setOrigin(idim.x / 2, idim.y / 2);

        }*/

//    printf("test1\n");
    parseMapTmx("map/Map1.tmx", &_matrice);

    // generation area

    _area[0].pos = sf::Vector2f(0,0);
    _area[1].pos = sf::Vector2f(_mapSize.x / 3, 0);
    _area[2].pos = sf::Vector2f(2 * _mapSize.x / 3, 0);
    _area[3].pos = sf::Vector2f(0 , _mapSize.y / 3);
    _area[4].pos = sf::Vector2f(_mapSize.x / 3, _mapSize.y / 3);
    _area[5].pos = sf::Vector2f(2 * _mapSize.x / 3, _mapSize.y / 3);
    _area[6].pos = sf::Vector2f(0 , 2 * _mapSize.y / 3);
    _area[7].pos = sf::Vector2f(_mapSize.x / 3, 2 * _mapSize.y / 3);
    _area[8].pos = sf::Vector2f(2 * _mapSize.x / 3, 2 * _mapSize.y / 3);

    for(int i = 0; i < 9; i++){

        _area[i].dim = sf::Vector2f(_mapSize.x / 3, _mapSize.y / 3);
    }

    _mapSize.x = _mapSize.x / 100;
    _mapSize.y = _mapSize.y / 100;

}

void World::createPlayer() {

    printf("s1\n");

    _team1.p = NULL;




    _team1.p = new Player(Actor(17, sf::Vector2f(0, 0), sf::Vector2f(0,0), sf::Vector2f(50,50),
                                100,
                               200, &_team1));

    _team1.ai.push_back(new NPC(Actor(17, sf::Vector2f(200, 200), sf::Vector2f(0,0), sf::Vector2f(50,50),100,200, &_team1)));
    //_team1.ai.push_back(new NPC(Actor(17, sf::Vector2f(300, 200), sf::Vector2f(0,0), sf::Vector2f(50,50),100,200, &_team1)));

    _team2.ai.push_back(new NPC(Actor(17, sf::Vector2f(200, 100), sf::Vector2f(50,0), sf::Vector2f(50,50),100,200, &_team2)));
    _team2.ai.push_back(new NPC(Actor(17, sf::Vector2f(100, 100), sf::Vector2f(50,0), sf::Vector2f(50,50),100, 200, &_team2)));
    //_team2.ai.push_back(new NPC(Actor(17, sf::Vector2f(300, 100), sf::Vector2f(50,0), sf::Vector2f(50,50),100, 200, &_team2)));

    _r_spawner[0] = new RessourceSpawner(23, sf::Vector2f(-200, -200), sf::Vector2f(0,0), sf::Vector2f(140,140), IT_IRON, 0);
    _r_spawner[1] = NULL;
    _r_spawner[2] = NULL;

printf("--- vector ----- \n");

    for(unsigned int i = 0; i < _drop.size(); i++)
        printf("%p\n", _drop[i]);



    _team1.crafter = new Crafter(24, sf::Vector2f(200, 100), sf::Vector2f(0,0), sf::Vector2f(50,50));
    _team2.crafter = new Crafter(24, sf::Vector2f(200, 700), sf::Vector2f(0,0), sf::Vector2f(50,50));

    _team1.base = new HQ(25, sf::Vector2f(400, 100), sf::Vector2f(0,0), sf::Vector2f(100,100), 100, &_team1);
_team2.base = new HQ(25, sf::Vector2f(400, 700), sf::Vector2f(0,0), sf::Vector2f(100,100), 100, &_team2);
}

/////////////////////////////////// ADD ////////////////////////////////////////

void World::addNPC(sf::Vector2f pos, team* tm, npc_type nt){


    tm->ai.push_back(new NPC(Actor(17, pos, sf::Vector2f(50,0), sf::Vector2f(50,50),100,200, tm), nt));


}

void World::addBullet(Item_t it,sf::Vector2f pos,  float angle, float dmgmult, Actor* own, team* tm){

    int img_id;
    sf::Vector2f sizeB;

    switch(it){

        case IT_PISTOL : img_id = 18; sizeB.x = 14; sizeB.y = 2; break;
        case IT_THROW_AXE : img_id = 10; sizeB.x = 35; sizeB.y = 24; break;
        case IT_SHOTGUN : img_id = 18; sizeB.x = 14; sizeB.y = 2; break;
        case IT_SMG : img_id = 18; sizeB.x = 14; sizeB.y = 2; break;
        case IT_PLASMA : img_id = 2; sizeB.x = 25; sizeB.y = 25; break;
        case IT_RPG : img_id = 2; sizeB.x = 25; sizeB.y = 25; break;

        default : img_id = 2;
    }

    tm->proj.push_back(Bullet(img_id, pos, sf::Vector2f(0,0), sizeB, it, angle, dmgmult, own));

}

Drop* World::addDrop(const sf::Vector2f& pos, const Item_t& it, bool s){

    int id_img = 0;
    sf::Vector2f sizeD;

    switch(it){

        case IT_IRON : id_img = 19; sizeD.x = 32; sizeD.y = 13; break;
        case IT_GOLD : id_img = 20; sizeD.x = 32; sizeD.y = 13; break;
        case IT_RUBY : id_img = 21; sizeD.x = 32; sizeD.y = 13; break;
        case IT_EMERALD : id_img = 22; sizeD.x = 32; sizeD.y = 13; break;
        case IT_BAT : id_img = 8; sizeD.x = 97; sizeD.y = 14; break;
        case IT_PISTOL : id_img = 9; sizeD.x = 32; sizeD.y = 8; break;
        case IT_THROW_AXE : id_img = 10; sizeD.x = 35; sizeD.y = 24; break;
        case IT_CHAINSAW : id_img = 11; sizeD.x = 68; sizeD.y = 28; break;
        case IT_SHOTGUN : id_img = 12; sizeD.x = 49; sizeD.y = 14; break;
        case IT_SMG : id_img = 13; sizeD.x = 49; sizeD.y = 10; break;
        case IT_KATANA : id_img = 14; sizeD.x = 90; sizeD.y = 8; break;
        case IT_PLASMA : id_img = 15; sizeD.x = 67; sizeD.y = 18; break;
        case IT_RPG : id_img = 16; sizeD.x = 115; sizeD.y = 18; break;
        default : break;

    }


    Drop* d = NULL;

    if(!s){

         Crafter* c,*c2;
         c = g_core->getWorld()->getTeam1()->crafter;
         c2 = g_core->getWorld()->getTeam2()->crafter;

         if((it > 0 && it < 5) &&
            pos.x > c->getPos().x - 150 &&
            pos.x < c->getPos().x + 150 &&
            pos.y > c->getPos().y - 150 &&
            pos.y < c->getPos().y + 150)
                c->putIn(it);
        else
        if((it > 0 && it < 5) &&
                pos.x > c2->getPos().x - 150 &&
                pos.x < c2->getPos().x + 150 &&
                pos.y > c2->getPos().y - 150 &&
                pos.y < c2->getPos().y + 150)
                c2->putIn(it);
        else{
            d = new Drop(id_img, pos, sf::Vector2f(0,0), sizeD, it, s);
            _drop.push_back(d);
        }

    }
    else{
        d = new Drop(id_img, pos, sf::Vector2f(0,0), sizeD, it, s);
        _drop.push_back(d);
    }

    return d;

}


void World::update(){

    #if DEBUG_PRINT == 1

    printf("T1\n");

    #endif

    _team1.p->update();
    _r_spawner[0]->update();

    // UPDATE BULLET

    for (unsigned int i = 0; i < _drop.size(); i++)
        _drop[i]->update();

#if DEBUG_PRINT == 1
    printf("T2\n");
    #endif

    for (list<Bullet>::iterator it = _team1.proj.begin(); it != _team1.proj.end(); ++it){

        it->update();
        for(vector<NPC*>::iterator it2 = _team2.ai.begin(); it2 != _team2.ai.end(); ++it2){

            if(g_core->dot_in_circle(it->getPos(), (*it2)->getPos(), 25)){
                //printf("touche !\n");
                (*it2)->damage(it->getDamage());
                (*it2)->setTarget(it->getOwner());
                it = _team1.proj.erase(it);
            break;
            }
        }
    }

#if DEBUG_PRINT == 1
    printf("T3\n");
    #endif

    for (list<Bullet>::iterator it = _team2.proj.begin(); it != _team2.proj.end(); ++it){

        it->update();

        if(g_core->dot_in_circle(it->getPos(), g_core->getWorld()->getTeam1()->p->getPos(), 25)){
            //printf("touche player\n");
            g_core->getWorld()->getTeam1()->p->damage(it->getDamage());
            it = _team2.proj.erase(it);
            break;

        }
        else{
            for(vector<NPC*>::iterator it1 = _team1.ai.begin(); it1 != _team1.ai.end(); ++it1){

                if(g_core->dot_in_circle(it->getPos(), (*it1)->getPos(), 25)){
                    //printf("touche !\n");
                    (*it1)->damage(it->getDamage());
                    (*it1)->setTarget(it->getOwner());
                    it = _team2.proj.erase(it);
                break;
                }
            }
        }
    }

#if DEBUG_PRINT == 1
    printf("T4\n");
#endif

    for(vector<NPC*>::iterator it2 = _team2.ai.begin(); it2 != _team2.ai.end(); ++it2){
        (*it2)->update();
    }

#if DEBUG_PRINT == 1
    printf("T5\n");
#endif
    for(vector<NPC*>::iterator it1 = _team1.ai.begin(); it1 != _team1.ai.end(); ++it1){
        (*it1)->update();
    }

#if DEBUG_PRINT == 1
    printf("T6\n");
#endif
}

//////////////////////////////////////////////////////////////// PURGE THE UNDEAD //////////////////////////////////////////////////////////////////////////:

void World::disolve(){

  ////////////////////////////////////
  //          PURGE                 //
  ////////////////////////////////////

    disolve_dead_drop();
    disolve_dead_NPC();
    disolve_dead_bullet();



}

void World::disolve_dead_bullet(){


    for (list<Bullet>::iterator it = _team1.proj.begin(); it != _team1.proj.end();){

        if(it->getKilled()){
            it = _team1.proj.erase(it);
        }
        else
            ++it;
    }

    for (list<Bullet>::iterator it = _team2.proj.begin(); it != _team2.proj.end();){

        if(it->getKilled()){
            it = _team2.proj.erase(it);
        }
        else
            ++it;
    }


}

void World::disolve_dead_NPC(){

#if DEBUG_PRINT == 1
printf("T9b\n");
#endif

for(vector<NPC*>::iterator it1 = _team1.ai.begin(); it1 != _team1.ai.end();){
    if((*it1)->getKilled()){
        delete (*it1);
        *it1 = NULL;
        it1 = _team1.ai.erase(it1);
    }
    else
        ++it1;
}


#if DEBUG_PRINT == 1
printf("T9b.5\n");
#endif

for(vector<NPC*>::iterator it2 = _team2.ai.begin(); it2 != _team2.ai.end();){
    if((*it2)->getKilled()){
        delete (*it2);
        *it2 = NULL;
        it2 = _team2.ai.erase(it2);
    }
    else
        ++it2;
}

#if DEBUG_PRINT == 1
printf("T10\n");
#endif

}

void World::disolve_dead_drop(){

    for (unsigned int i = 0; i < _drop.size();){

        if(_drop[i]->getKilled()){

            if(_drop[i]->getGenerated()){

                for(int j = 0; j < 9; j++){

                    if((_r_spawner[0]->getMatrice())[j] == _drop[i]){
                        //printf("match address detected : \n");
                        _r_spawner[0]->getMatrice()[j] = NULL;
                        //_r_spawner[0]->restartTimer();
                    }

                }

            }

            delete (_drop[i]);
            _drop[i] = NULL;
            _drop.erase(_drop.begin() + i);

        }
        else
        ++i;

  }


}


///////////////////////////////////////////////////////////////////// RENDER ///////////////////////////////////////////////////////////////////////////

void World::render(){

    //renderWorld();
    _team1.base->render();
    _team2.base->render();
    _team1.crafter->render();
    _team2.crafter->render();
    _r_spawner[0]->render();
    for (unsigned int i = 0; i < _drop.size(); i++)
        _drop[i]->render();

#if DEBUG_PRINT == 1
    printf("T8\n");
#endif

    for(vector<NPC*>::iterator it1 = _team1.ai.begin(); it1 != _team1.ai.end(); ++it1){
        (*it1)->render();
    }

#if DEBUG_PRINT == 1
    printf("T8.5\n");
#endif

    for(vector<NPC*>::iterator it2 = _team2.ai.begin(); it2 != _team2.ai.end(); ++it2){
        (*it2)->render();
    }

#if DEBUG_PRINT == 1
    printf("T9\n");
#endif

    _team1.p->render();
    centerCamera();

    //////////////////// Mini update (doit être fait avant render de bullet)/////////////////////

 _b[0] = g_core->getView()->getCenter().x - g_core->getWinSize().x/2 - 2;
 _b[1] = g_core->getView()->getCenter().y - g_core->getWinSize().y/2 - 2;
 _b[2] = g_core->getView()->getCenter().x + g_core->getWinSize().x/2 + 2;
 _b[3] = g_core->getView()->getCenter().y + g_core->getWinSize().y/2 + 2;

    /////////////////////////////////////////////////////////////////////////////////////////////

    for (list<Bullet>::iterator it = _team1.proj.begin(); it != _team1.proj.end(); ++it){

        it->render();
    }

    for (list<Bullet>::iterator it = _team2.proj.begin(); it != _team2.proj.end(); ++it){

        it->render();
    }

    sf::RectangleShape rectangle;

    for(int i =0; i < 9; i++){
        rectangle.setSize(_area[i].dim);
        rectangle.setFillColor(sf::Color::Transparent);
        rectangle.setOutlineColor(sf::Color::Red);
        rectangle.setOutlineThickness(2.0f);
        rectangle.setPosition(_area[i].pos);

        g_core->getApp()->draw(rectangle);
    }


}

    int convertToIndex(float a, int LARGEUR_TILE){
        return((int)(a/LARGEUR_TILE));
    }

    int convertToView(int a, int LARGEUR_TILE){
        return(a*LARGEUR_TILE);
    }

void World::renderWorld() {

    int indexPlayerI = convertToIndex(_team1.p->getPos().x, 100);
    int indexPlayerJ = convertToIndex(_team1.p->getPos().y, 100);

    /* Les nombre en dessous permettent de déterminer la distance ou lon affiche la map autour du héro */

    float visionI = zoneAffichable, visionJ = zoneAffichable;

    int idPImoins = indexPlayerI - visionI;
    int idPIplus = indexPlayerI + visionI;
    int idPJmoins = indexPlayerJ - visionJ;
    int idPJplus = indexPlayerJ + visionJ;

    if(idPImoins < 0)
        idPImoins = 0;

    if(idPIplus > _mapSize.x)
        idPIplus = _mapSize.x;

    if(idPJmoins < 0)
        idPJmoins = 0;

    if(idPJplus > _mapSize.y)
        idPJplus = _mapSize.y;

    for(int j=idPJmoins; j<idPJplus; j++)
            for(int i=idPImoins; i<idPIplus; i++)
                    g_core->getApp()->draw(_matrice[i][j].spr);

}


void World::centerCamera() {

g_core->getView()->setCenter(getTeam1()->p->getPos());

//g_core->getView()->setCenter(getTeam1()->ai[0]->getPos());
}



///////////////////////////////////////////////////////////// EPURAGE /////////////////////////////////////////////////////////////////////////////////////////


bool World::insideScreen(int x, int y, int w, int h, int margin) const
{
    //v2d_t cam = level_editmode() ? editor_camera : camera_get_position();
    float a[4] = { x, y, x+w, y+h };
    float b[4] = {
        g_core->getView()->getCenter().x - g_core->getWinSize().x/2 - margin,
        g_core->getView()->getCenter().y - g_core->getWinSize().y/2 - margin,
        g_core->getView()->getCenter().x + g_core->getWinSize().x/2 + margin,
        g_core->getView()->getCenter().y + g_core->getWinSize().y/2 + margin
    };


    //sf::Shape rect(sf::Shape::Rectangle(b[0],b[1],b[2],b[3],sf::Color::Blue,3,sf::Color::Blue));
    //rect.EnableFill(false);
    //g_core->getApp()->Draw(rect);

    return g_core->bounding_box(a,b);
}

bool World::insideScreenPoint(int x, int y, int mar) const{

    if(x > _b[0] && x < _b[2] && y > _b[1] && y < _b[3]){

        return true;

    }
    return false;

}

Player*         World::getPlayerTeam1(){return _team1.p;}
Player*         World::getPlayerTeam2(){return NULL;}

 team*   World::getTeam1(){return &_team1;}
 team*   World::getTeam2(){return &_team2;}

 NPC*   World::getNPCTeam1(int a){return NULL;}
 NPC*   World::getNPCTeam2(int a){return NULL;}

Item*   World::getItemFromIT(const Item_t& it){

sf::Vector2f p(0,0);

switch(it){

case IT_IRON : return new Ressource(19, p, sf::Vector2f(0,0), sf::Vector2f(32,13),IT_IRON);
case IT_GOLD : return new Ressource(20, p, sf::Vector2f(0,0), sf::Vector2f(32,13),IT_GOLD);
case IT_RUBY : return new Ressource(21, p, sf::Vector2f(0,0), sf::Vector2f(32,13),IT_RUBY);
case IT_EMERALD : return new Ressource(22, p, sf::Vector2f(0,0), sf::Vector2f(32,13),IT_EMERALD);
case IT_BAT : return new Weapon(8, p, sf::Vector2f(0,0), sf::Vector2f(97,14),IT_BAT);
case IT_BAT_SUPER : return new Weapon(8, p, sf::Vector2f(0,0), sf::Vector2f(97,14),IT_BAT);
case IT_PISTOL : return new Weapon(9, p, sf::Vector2f(0,0), sf::Vector2f(32,8),IT_PISTOL);
case IT_PISTOL_SUPER : return new Weapon(9, p, sf::Vector2f(0,0), sf::Vector2f(32,8),IT_PISTOL);
case IT_THROW_AXE : return new Weapon(10, p, sf::Vector2f(0,0), sf::Vector2f(35,24),IT_THROW_AXE);
case IT_THROW_AXE_SUPER : return new Weapon(10, p, sf::Vector2f(0,0), sf::Vector2f(35,24),IT_THROW_AXE);
case IT_CHAINSAW : return new Weapon(11, p, sf::Vector2f(0,0), sf::Vector2f(68,28),IT_CHAINSAW);
case IT_CHAINSAW_SUPER : return new Weapon(11, p, sf::Vector2f(0,0), sf::Vector2f(68,28),IT_CHAINSAW);
case IT_SHOTGUN : return new Weapon(12, p, sf::Vector2f(0,0), sf::Vector2f(49,14),IT_SHOTGUN);
case IT_SHOTGUN_SUPER : return new Weapon(12, p, sf::Vector2f(0,0), sf::Vector2f(49,14),IT_SHOTGUN);
case IT_SMG : return new Weapon(13, p, sf::Vector2f(0,0), sf::Vector2f(49,10),IT_SMG);
case IT_SMG_SUPER : return new Weapon(13, p, sf::Vector2f(0,0), sf::Vector2f(49,10),IT_SMG);
case IT_KATANA : return new Weapon(14, p, sf::Vector2f(0,0), sf::Vector2f(170,8),IT_KATANA); //90 8
case IT_KATANA_SUPER : return new Weapon(14, p, sf::Vector2f(0,0), sf::Vector2f(170,8),IT_KATANA);
case IT_PLASMA : return new Weapon(15, p, sf::Vector2f(0,0), sf::Vector2f(67,18),IT_PLASMA);
case IT_PLASMA_SUPER : return new Weapon(15, p, sf::Vector2f(0,0), sf::Vector2f(67,18),IT_PLASMA);
case IT_RPG : return new Weapon(16, p, sf::Vector2f(0,0), sf::Vector2f(115,19),IT_RPG);
case IT_RPG_SUPER : return new Weapon(16, p, sf::Vector2f(0,0), sf::Vector2f(115,19),IT_RPG);

default : return NULL;

}

}


void World::parseMapTmx(string map, tile*** Matrice){

    // Récupération des données dans le fichier TMX (Tiled Map Editor) / Traitement XML


    // ================= OUVERTURE ======================

    TiXmlDocument document(map.c_str());
    if(!document.LoadFile()){//si on n'arrive pas à charger le fichier
        cout << "error : N°" << document.ErrorId() << " : " << document.ErrorDesc() << endl;
        //return 1;
    }
    else{
        cout << " Ouverture reussie " << endl;
    }


    TiXmlHandle handle(&document);
    string source, elemName, colonnes, lignes, largeur, hauteur;

    int nbColonnes = 0, nbLignes = 0, largeurTile = 0, hauteurTile = 0;

    // on recherche les enfants Direct de Map
    TiXmlElement *element = handle.FirstChildElement().FirstChildElement().Element();


    // ==== On récupère les informations sur la Map (colonnes, lignes) et les tiles (taille) =====

    int i = 0;
    while (element){
        //cout << element->Value() << endl; //l'atribut nom
        //cout << element->GetText() << endl;//Le texte entre les balises

        elemName = element->Value();

        if(elemName == "layer"){

            colonnes = element->Attribute("width");
            lignes = element->Attribute("height");

            nbColonnes = atoi(colonnes.c_str());
            nbLignes = atoi(lignes.c_str());

            _mapSize = sf::Vector2f(nbColonnes * 100, nbLignes * 100);
        }
        else if(elemName == "tileset"){

            largeur = element->Attribute("tilewidth");
            hauteur = element->Attribute("tileheight");

            largeurTile = atoi(largeur.c_str());
            hauteurTile = atoi(hauteur.c_str());

        }

        element = element->NextSiblingElement(); // aller à l'élément suivant
        i++;

    }

    // On crée la Matrice avec le nb de colonnes et de lignes déterminés précédemment

    cout << "nb colonnes : " << nbColonnes << " nb lignes : " << nbLignes << endl;

    (*Matrice) = 0;

    (*Matrice) = new tile*[nbColonnes];

	for(int i=0; i<nbColonnes; i++)
		(*Matrice)[i] = new tile[nbLignes];

    // ----------------------------------------------------------------------------


    // ======== On recherche les enfants de Data (donc toutes les tiles) ==========
    element = handle.FirstChildElement().FirstChildElement("layer").FirstChildElement("data").FirstChildElement().Element();

    i = 0;
    int j = 0;

    while (element){

        if(i < nbColonnes){

            string value = element->Attribute("gid"); // Numéro de la Tile

            (*Matrice)[i][j].num = atoi(value.c_str());

            i++; // On passe a la tile suivante
            element = element->NextSiblingElement(); // aller à l'élément suivant
        }
        else{

            i = 0; // On repart a la premiere Tile de la ligne
            j++; // On passe a la ligne suivante

        }
    }



    for(int j=0; j<nbLignes; j++){
            //printf("\n");
		for(int i=0; i<nbColonnes; i++){

		    (*Matrice)[i][j].spr.setTexture(*(g_core->getImageManager()->getImage(4)));
		    (*Matrice)[i][j].spr.setPosition(i*largeurTile, j*hauteurTile);

			if ((*Matrice)[i][j].num == 1){

			    //printf("1");

				(*Matrice)[i][j].spr.setTextureRect(sf::IntRect(0,0,100,100));
			}
			else if ((*Matrice)[i][j].num == 2){
                //printf("2");
				(*Matrice)[i][j].spr.setTextureRect(sf::IntRect(100,0,100,100));
			}
			else if ((*Matrice)[i][j].num == 3){
                //printf("3");
				(*Matrice)[i][j].spr.setTextureRect(sf::IntRect(200,0,100,100));
			}
		}
    }

}

World::~World(){

    printf("current drop number : %d\n", _drop.size());

    delete _team1.p;

    for (unsigned int i = 0; i < _team1.ai.size();){

        delete (_team1.ai[i]);
        _team1.ai[i] = NULL;
        _team1.ai.erase(_team1.ai.begin() + i);
    }

    for (unsigned int i = 0; i < _team2.ai.size();){

        delete (_team2.ai[i]);
        _team2.ai[i] = NULL;
        _team2.ai.erase(_team2.ai.begin() + i);
    }

    for(int i=0; i<3; i++)
        if(_r_spawner[i] != NULL) delete _r_spawner[i];


    for (unsigned int i = 0; i < _drop.size();){

        printf("drop deleted, pos : %d\n", i);
        delete (_drop[i]);
        _drop[i] = NULL;
        _drop.erase(_drop.begin() + i);
    }

    delete _team1.base;
    delete _team2.base;

}
