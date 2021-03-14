#pragma once
#include "gameobject.h"
#include "ball.h"
#include "box.h"
class CollisionDetector {

public:

	//Test if there might be a collision between two balls
	//static bool testAAABBOverlap(Balll* b1, Ball*b2);

	//test if there might be a collision between two  gameobjects
	static bool testAABBOverlap(GameObject* obj1, GameObject* obj2);

	//Detects and resolves the collision between two balls
	static bool detectAndResolveCollision(Ball* b1, Ball* b2);

	//Detects and resolves the collision between a ball and a box
	static bool detectAndResolveCollision(Ball* ball, Box* box);


private:

	//Resolves the collision i.e. computes velocities of balls b1 and b2
	//the collision. MODIFIES THE VELOCITIES!!!
	static void resolveCollision(Ball* b1, Ball* b2);

	//Removes any penetration between balls b1 and b2 i.e.
	// moves the objects according to their weight. MODIFIES THE POS
	static void resolvePenetration(Ball* b1, Ball* b2, Vector3 v, double dist);

	//Removes any penetration between ball and a box 
	static void resolvePenetration(Ball* ball, Box* box, Vector3 v, double dist);

	//resolve the collision between a ball and a box
	static void resolveCollision(Ball* b1, Box* box);
};