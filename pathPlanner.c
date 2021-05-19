//Include "obstacles.h"

#include "obstacles.h"
#include <stdlib.h>
#include <stdio.h>

//Function to create the vertices
int createVertices(Environment* env){
	//Allocate memory for Vertices array in Environment struct
	env->vertices = (Vertex *) malloc((env->numObstacles * 4) * (sizeof(Vertex)));
	//Iterate through the number of obstacles
	for(int i = 0; i < env->numObstacles; i++){
		//Iterate through each Obstacle in the obstacles array
		Obstacle* r = &env->obstacles[i];
		//Create and store the vertices inside of env->vertices
		//Top left corner
		env->vertices[env->numVertices].x = r->x;
		env->vertices[env->numVertices].y = r->y;
		//Set the vertex obstacle to be the current obstacle
		env->vertices[env->numVertices].obstacle = r;
		env->numVertices++;
		
		//Top right corner
		env->vertices[env->numVertices].x = r->x + r->w;
		env->vertices[env->numVertices].y = r->y;
		//Set the vertex obstacle to be the current obstacle
		env->vertices[env->numVertices].obstacle = r;
		env->numVertices++;
		
		//Bottom left corner
		env->vertices[env->numVertices].x = r->x;
		env->vertices[env->numVertices].y = r->y-r->h;
		//Set the vertex obstacle to be the current obstacle
		env->vertices[env->numVertices].obstacle = r;
		env->numVertices++;
		
		//Bottom right corner
		env->vertices[env->numVertices].x = r->x + r->w;
		env->vertices[env->numVertices].y = r->y - r->h;
		//Set the vertex obstacle to be the current obstacle
		env->vertices[env->numVertices].obstacle = r;
		env->numVertices++;
	}
	return env->numVertices;   //Return the number of vertices we created.
}

//Function to create edges that connect the vertices
int createEdges(Environment* env){
	//Keep track of the number of edges we create.
	int edgeCounter = 0;
	//Iterate through numVertices
	for(int i = 0; i < env->numVertices; i++){
		Vertex* currVertex = &env->vertices[i];
		currVertex->firstNeighbour = NULL;
		Neighbour* currNeighbour = NULL;
		//Iterate through numVertices again to connect the vertices
		for(int j = 0; j < env->numVertices; j++){
			//If the memory address is the same for both vertices, then do no thing
			if(i != j){
				//Allocate memory for a new neighbour and set it's vertex as the current vertex
				Neighbour* neighbour = (Neighbour *) malloc(sizeof(Neighbour));
				neighbour->vertex = &env->vertices[j];
				//Increment edge counter  by 1
				edgeCounter++;
				//If the current Neighbour is the head, set it's first neighbour as neighbour
				if(currNeighbour == NULL){
					currVertex->firstNeighbour = neighbour;
				//If not, set the next neighbour
				}else{
					currNeighbour->next = neighbour;
				}
				//Set the current neighbour as neighbour
				currNeighbour = neighbour;
				
			}
		}
		//Set the tail
		currVertex->lastNeighbour = currNeighbour;
	}
	//Return the number of edges we created
	return edgeCounter;
}

//Create a function to check if two lines intersect
int intersect(Vertex* v1, Vertex* v2, Obstacle* o){
	//If they come from the same obstacle, return 1
	if(v1->obstacle == v2->obstacle){
		return 1;
	}
	Vertex v3, v4;
	double ua, ub;
	//Top
	v3.x = o->x;
	v3.y = o->y;
	v4.x = o->x + o->w;
	v4.y = o->y;
	//Calculate ua and ub
	ua = (double)(((v4.x - v3.x)*(v1->y-v3.y))-((v4.y-v3.y)*(v1->x-v3.x))) / (double)((((v4.y-v3.y)*(v2->x-v1->x)))-((v4.x-v3.x)*(v2->y-v1->y)));
	ub = (double)(((v2->x - v1->x)*(v1->y-v3.y))-((v2->y-v1->y)*(v1->x-v3.x))) / (double)(((v4.y-v3.y)*(v2->x-v1->x))-((v4.x-v3.x)*(v2->y-v1->y)));
	//Check if 0 < ua < 1 and 0 < ub < 1
	if(ua > 0 && ua < 1 && ub > 0 && ub < 1){
		return 1;
	}
	//Right
	v3.x = o->x + o->w;
	v3.y = o->y;
	v4.x = o->x + o->w;
	v4.y = o->y - o->h;
	//Calculate ua and ub
	ua = (double)(((v4.x - v3.x)*(v1->y-v3.y))-((v4.y-v3.y)*(v1->x-v3.x))) / (double)((((v4.y-v3.y)*(v2->x-v1->x)))-((v4.x-v3.x)*(v2->y-v1->y)));
	ub = (double)(((v2->x - v1->x)*(v1->y-v3.y))-((v2->y-v1->y)*(v1->x-v3.x))) / (double)(((v4.y-v3.y)*(v2->x-v1->x))-((v4.x-v3.x)*(v2->y-v1->y)));
	//Check if 0 < ua < 1 and 0 < ub < 1
	if(ua > 0 && ua < 1 && ub > 0 && ub < 1){
		return 1;
	}
	//bottom
	v3.x = o->x;
	v3.y = o->y - o->h;
	v4.x = o->x + o->w;
	v4.y = o->y - o->h;
	//Calculate ua and ub
	ua = (double)(((v4.x - v3.x)*(v1->y-v3.y))-((v4.y-v3.y)*(v1->x-v3.x))) / (double)((((v4.y-v3.y)*(v2->x-v1->x)))-((v4.x-v3.x)*(v2->y-v1->y)));
	ub = (double)(((v2->x - v1->x)*(v1->y-v3.y))-((v2->y-v1->y)*(v1->x-v3.x))) / (double)(((v4.y-v3.y)*(v2->x-v1->x))-((v4.x-v3.x)*(v2->y-v1->y)));
	//Check if 0 < ua < 1 and 0 < ub < 1
	if(ua > 0 && ua < 1 && ub > 0 && ub < 1){
		return 1;
	}
	
	//Left
	v3.x = o->x;
	v3.y = o->y;
	v4.x = o->x;
	v4.y = o->y - o->h;
	//Calculate ua and ub
	ua = (double)(((v4.x - v3.x)*(v1->y-v3.y))-((v4.y-v3.y)*(v1->x-v3.x))) / (double)((((v4.y-v3.y)*(v2->x-v1->x)))-((v4.x-v3.x)*(v2->y-v1->y)));
	ub = (double)(((v2->x - v1->x)*(v1->y-v3.y))-((v2->y-v1->y)*(v1->x-v3.x))) / (double)(((v4.y-v3.y)*(v2->x-v1->x))-((v4.x-v3.x)*(v2->y-v1->y)));
	//Check if 0 < ua < 1 and 0 < ub < 1
	if(ua > 0 && ua < 1 && ub > 0 && ub < 1){
		return 1;
	}
	//If ua and ub do not intersect, return 0;
	
	return 0;
}

int removeEdges(Environment* env){
	//Get the total edges we start off with
	int totalEdges = env->numVertices * (env->numVertices-1);
	//Iterate through numVertices
	for(int i = 0; i < env->numVertices; i++){
		//Create a current neighbour and a previous neighbour
		Neighbour* currN = env->vertices[i].firstNeighbour;
		Neighbour* prevN = NULL;
		while(currN != NULL){
			//Iterate through numObstacles
			for(int j = 0; j < env->numObstacles; j++){
				//Check if the lines intersect with object using our intersect() function
				if(intersect(&env->vertices[i], currN->vertex, &env->obstacles[j]) == 1){
					//Remove this neighbour
					//Check if the current neighbour is the head
					if(currN == env->vertices[i].firstNeighbour){
						env->vertices[i].firstNeighbour = currN->next;
					//Check if the current neighbour is the tail
					}else if(currN == env->vertices[i].lastNeighbour){
						env->vertices[i].lastNeighbour = prevN;
					}
					//Otherwise, it is in the middle of the linked list.
					else{
						prevN->next = currN->next;
					}
					//Subtract one from totalEdges
					totalEdges--;
					//We can now free the neighbour we removed.
					free(currN);
					//Set the neighbour we removed to null, so it breaks out the while loop.
					currN = NULL;
					break;
					
				}
			}
			//If the current neighbour is null, don't set the previous neighbour to be current neighbour
			if(currN != NULL){
				prevN = currN;
			}
			//If the current neighbour hasn't been removed, move onto the next neighbour;
			if(currN != NULL){
				currN = currN->next;
			}
		}
	}
	//Return the new total number of edges
	return totalEdges;
	
}

//Create a function to free all of our memory allocations
void cleanupEverything(Environment* env){
	//Iterate through the vertices
	for(int i = 0; i < env->numVertices; i++){
		//Get the firstNeighbour of env->vertices[i]
		Neighbour* currN = env->vertices[i].firstNeighbour;
		//Get the next neighbour
		Neighbour* nextN = currN->next;
		//Free every neighbour until you reach the lastNeighbour
		while(nextN != env->vertices[i].lastNeighbour){
			free(currN);
			currN = nextN;
			nextN = nextN->next;
		}
		//One last time, free the neighbour before lastNeighbour
		free(currN);
		//free lastNeighbour
		free(nextN);
	}
	//Free the vertices array
	free(env->vertices);
	//Free the obstacles array
	free(env->obstacles);
}
