//Create the necessary typedef struct

//Refer to displayEnvironment() in display.c to see what to name the variables.

//Create Obstacle struct
typedef struct{
	int x;
	int y;
	int w;
	int h;
}Obstacle;

//Define Vertex struct here because it is needed for Neighbour struct
struct Vertex;

//Create Neighbour struct
typedef struct Neighbour{
	struct Vertex* vertex;  //Neighbouring vertex
	struct Neighbour* next;
}Neighbour;

//Create Vertex struct
typedef struct Vertex{
	int x;
	int y;
	Neighbour* firstNeighbour;   //head
	Neighbour* lastNeighbour;    //tail
	Obstacle* obstacle;
}Vertex;

//Create Environment struct
typedef struct{
	Obstacle* obstacles;
	int numObstacles;
	Vertex* vertices;
	int numVertices;
}Environment;

//Name the functions we will be using in pathPlanner.c
int createVertices(Environment* environment);
int createEdges(Environment* environment);
int removeEdges(Environment* environment);
void cleanupEverything(Environment* environment);
