CC=g++
SRC = Navmesh.cpp Entity.cpp NPC.cpp NPCSoldier.cpp  Map.cpp Shader.cpp Input.cpp Texture.cpp Camera.cpp Util.cpp Model.cpp objloader.cpp
OBJ = $(SRC:.cpp=.o)

INC = -I/usr/local/include/
LIB = -L/usr/local/lib -lSOIL -lGLEW -lassimp -lm -lGL -lglfw


all:	$(OBJ)
	$(CC) $(OBJ) main.cpp global.cpp Core.cpp $(INC) $(LIB) -o exe


Entity.o:	Entity.h Entity.cpp
		$(CC) -c Entity.cpp -o Entity.o

Navmesh.o:	Navmesh.h Navmesh.cpp
		$(CC) -c Navmesh.cpp -o Navmesh.o

NPC.o:		NPC.h NPC.cpp
		$(CC) -c NPC.cpp -o NPC.o

NPCSoldier.o:	NPCSoldier.h NPCSoldier.cpp
		$(CC) -c NPCSoldier.cpp -o NPCSoldier.o

Map.o:		Map.h Map.cpp Core.cpp
		$(CC) -c Map.cpp -o Map.o



Shader.o:	Shader.h Shader.cpp
		$(CC) -c Shader.cpp -o Shader.o

Input.o:	Input.h Input.cpp
		$(CC) -c Input.cpp -o Input.o

Texture.o:	Texture.h Texture.cpp
		$(CC) -c Texture.cpp -I/usr/local/include/ -o Texture.o

Camera.o:	Camera.h Camera.cpp
		$(CC) -c Camera.cpp -o Camera.o


Util.o:		Util.h Util.cpp
		$(CC) -c Util.cpp -o Util.o


objloader.o:	objloader.h objloader.cpp
		$(CC) -c objloader.cpp -o objloader.o

Model.o:	Model.h Model.cpp
		$(CC) -c Model.cpp -o Model.o



clean:	
	rm -v *.o *~
