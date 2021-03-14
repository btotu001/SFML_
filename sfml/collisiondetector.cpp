#include "collisiondetector.h"
#include <iostream>
/*
bool Collisiondetector::testAABBOverlap(Ball* b1, Ball* b2) {
	float d1x = b2->min_x - b1->max_x;
	float d1y = b2->min_y - b1->max_y;
	float d2x = b1->min_x - b2->max_x;
	float d2y = b1->min_y - b2->max_y;

	if (d1x > 0.0f || d1y > 0.0f)
		return false;

	if (d2x > 0.0f || d2y > 0.0f)
		return false;

	return true;

}
*/

bool CollisionDetector::testAABBOverlap(GameObject* obj1, GameObject* obj2) {
	float d1x = obj2->min_x - obj1->max_x;
	float d1y = obj2->min_y - obj1->max_y;
	float d2x = obj1->min_x - obj2->max_x;
	float d2y = obj1->min_y - obj2->max_y;

	if (d1x > 0.0f || d1y > 0.0f)
		return false;

	if (d2x > 0.0f || d2y > 0.0f)
		return false;

	return true;
}

void CollisionDetector::resolvePenetration(Ball* ball, Box* box, Vector3 v, double dist) {

	/*
	Vector3 v = b2->m_particle->getPosition() - b1->m_particle->getPosition();

	//the distance is norm of vector v minus the sum of radii
	double dist = v.norm() - (b1->getRadius() + b2->getRadius());

	//If the distance is smaller than zero , there is penetration
	if (dist < 0.0) {
		Vector3 penetration - v * (dist/v.norm();
	}

	*/

	//compute the penetration vector between b1 and b2
	Vector3 penetration = v * (-dist / v.norm());
	//penetration.print();
	//how much we should move b1 and b2? According to their inverse masses.
	double invmass1 = ball->m_particle->getInverseMass();
	double invmass2 = box->m_particle->getInverseMass();
	double totalmass = invmass1 + invmass2;
	Vector3 move1;
	
	if (totalmass > 0.0) {
		move1 = penetration * (invmass1 / totalmass);
		
	}
	else {
		//both have infinite mass. so move both half way.??
		move1 = penetration * -0.5;
		
	}

	//move1.print()
	//move2.print()

	//set the new position
	ball->m_particle->setPosition(ball->m_particle->getPosition() + move1);
	


	double radius = ball->getRadius();
	double ball_x = ball->m_particle->getPosition().getX();
	double ball_y = ball->m_particle->getPosition().getY();

	//4 easy cases:
	//- ball center is within min_x and max_x of box 
	if (ball_x >= box->min_x && ball_x <= box->max_x) {
		//check above: y-coordinate collides and y-speed is negative
		if ((ball_y - radius) <= box->max_y && ball->m_particle->getVelocity().getY() < 0.0) {
			Vector3 vel = ball->m_particle->getVelocity();
			double y = vel.getY();
			vel = vel + Vector3(0.0, -2 * y, 0.0);
			//vel = vel * damping;
			ball->m_particle->setVelocity(vel);

			
		}
		/*
		else if ((ball_y - radius) <= box->max_y && ball->m_particle->getVelocity().getY() < 0.0) {
			Vector3 move = ball->m_particle->getPosition();
			double y = pos.getY();
			pos = pos + Vector3(0.0, -radius, 0.0);

			ball->m_particle->setPosition(pos);
			ball->m_particle->setPosition(ball->m_particle->getPosition() + move);
			return true;
		}
		*/


		//check below: y-cord and y-speed is positive
		if ((ball_y - radius) >= box->min_y && ball->m_particle->getVelocity().getY() > 0.0) {
			Vector3 vel = ball->m_particle->getVelocity();
			double y = vel.getY();
			vel = vel + Vector3(0.0, -2 * y, 0.0);
			//vel = vel * damping;
			ball->m_particle->setVelocity(vel);

			/*
			if ((ball_y + (2*radius) ) <= box->max_y) {
				Vector3 pos = ball->m_particle->getPosition();
				double y = pos.getY();
				pos = pos + Vector3(0.0, -radius, 0.0);

				ball->m_particle->setPosition(pos);

			}
			*/
			

		}

	}
	//- ball center is within min_y and max_y of box 
	if (ball_y >= box->min_y && ball_y <= box->max_y) {
		//check left: ball x.cord plus radius against min_x annd x-speed > 0
		if ((ball_x + radius) >= box->min_x && ball->m_particle->getVelocity().getX() > 0.0) {
			Vector3 vel = ball->m_particle->getVelocity();
			double x = vel.getX();
			vel = vel + Vector3(-2 * x, 0.0, 0.0);
			//vel = vel * damping;
			ball->m_particle->setVelocity(vel);
			
		}

		//check right: x-cord - radius < than max_x and x-speed <0
		if ((ball_x - radius) <= box->max_x && ball->m_particle->getVelocity().getX() < 0.0) {
			Vector3 vel = ball->m_particle->getVelocity();
			double x = vel.getX();
			vel = vel + Vector3(-2 * x, 0.0, 0.0);
			//vel = vel * damping;
			ball->m_particle->setVelocity(vel);
		
		}
	}

	//4 corners:
	//
	//1. Compute distance to all 4 corners 
	//2. Check if any these is smaller than the radius of the ball
	double dx, dy;

	//upper left corner
	dx = box->min_x - ball_x;
	dy = ball_y - box->max_y;
	if ((dx * dx + dy * dy) <= radius * radius) {
		Vector3 vel = ball->m_particle->getVelocity();
		vel = vel * (-1); //reverse the velocity vector
		ball->m_particle->setVelocity(vel);
		
	}


	//lover left corner (dy is same as before)
	dy = box->min_y - ball_y;
	if ((dx * dx + dy * dy) <= radius * radius) {
		Vector3 vel = ball->m_particle->getVelocity();
		vel = vel * (-1); //reverse the velocity vector
		ball->m_particle->setVelocity(vel);
		
	}

	//lover right corner (dy is same as before)
	dx = ball_x - box->max_x;
	if ((dx * dx + dy * dy) <= radius * radius) {
		Vector3 vel = ball->m_particle->getVelocity();
		vel = vel * (-1); //reverse the velocity vector
		ball->m_particle->setVelocity(vel);
		
	}


	//upper right corner (dx is same as before)
	dy = ball_y - box->max_y;
	if ((dx * dx + dy * dy) <= radius * radius) {
		Vector3 vel = ball->m_particle->getVelocity();
		vel = vel * (-1); //reverse the velocity vector
		ball->m_particle->setVelocity(vel);
		
	}

	


}


 bool CollisionDetector::detectAndResolveCollision(Ball* ball, Box* box) {

	 double radius = ball->getRadius();
	 double ball_x = ball->m_particle->getPosition().getX();
	 double ball_y = ball->m_particle->getPosition().getY();

	//4 easy cases:
	//- ball center is within min_x and max_x of box 
	if (ball_x >= box->min_x && ball_x <= box->max_x) {
		//check above: y-coordinate collides and y-speed is negative
		if ((ball_y - radius) <= box->max_y && ball->m_particle->getVelocity().getY() < 0.0) {
			Vector3 vel = ball->m_particle->getVelocity();
			double y = vel.getY();
			vel = vel + Vector3(0.0, -2 * y, 0.0);
			//vel = vel * damping;
			ball->m_particle->setVelocity(vel);

			return true;
		}
		


		//check below: y-cord and y-speed is positive
		if ((ball_y + radius) >= box->min_y && ball->m_particle->getVelocity().getY() > 0.0) {
			Vector3 vel = ball->m_particle->getVelocity();
			double y = vel.getY();
			vel = vel + Vector3(0.0, -2 * y, 0.0);
			//vel = vel * damping;
			ball->m_particle->setVelocity(vel);

			return true;

		}

	}
	//- ball center is within min_y and max_y of box 
	if (ball_y >= box->min_y && ball_y <= box->max_y) {
		//check left: ball x.cord plus radius against min_x annd x-speed > 0
		if ((ball_x + radius) >= box->min_x && ball->m_particle->getVelocity().getX() > 0.0) {
			Vector3 vel = ball->m_particle->getVelocity();
			double x = vel.getX();
			vel = vel + Vector3( -2 * x, 0.0, 0.0);
			//vel = vel * damping;
			ball->m_particle->setVelocity(vel);
			return true;
		}

		//check right: x-cord - radius < than max_x and x-speed <0
		if ((ball_x - radius) <= box->max_x && ball->m_particle->getVelocity().getX() < 0.0) {
			Vector3 vel = ball->m_particle->getVelocity();
			double x = vel.getX();
			vel = vel + Vector3(-2 * x, 0.0, 0.0);
			//vel = vel * damping;
			ball->m_particle->setVelocity(vel);
			return true;
		}
	}

	//4 corners:
	//
	//1. Compute distance to all 4 corners 
	//2. Check if any these is smaller than the radius of the ball
	double dx, dy;

	//upper left corner
	dx = box->min_x - ball_x;
	dy = ball_y - box->max_y; 
	if ((dx * dx + dy * dy) <= radius * radius) {
		Vector3 vel = ball->m_particle->getVelocity();
		vel = vel * (-1); //reverse the velocity vector
		ball->m_particle->setVelocity(vel);
		return true;
	}


	//lover left corner (dy is same as before)
	dy = box->min_y - ball_y;
	if ((dx * dx + dy * dy) <= radius * radius) {
		Vector3 vel = ball->m_particle->getVelocity();
		vel = vel * (-1); //reverse the velocity vector
		ball->m_particle->setVelocity(vel);
		return true;
	}

	//lover right corner (dy is same as before)
	dx = ball_x - box->max_x;
	if ((dx * dx + dy * dy) <= radius * radius) {
		Vector3 vel = ball->m_particle->getVelocity();
		vel = vel * (-1); //reverse the velocity vector
		ball->m_particle->setVelocity(vel);
		return true;
	}


	//upper right corner (dx is same as before)
	dy = ball_y - box->max_y;
	if ((dx * dx + dy * dy) <= radius * radius) {
		Vector3 vel = ball->m_particle->getVelocity();
		vel = vel * (-1); //reverse the velocity vector
		ball->m_particle->setVelocity(vel);
		return true;
	}

	return false;

}


bool CollisionDetector::detectAndResolveCollision(Ball* b1, Ball* b2) {
	
	
	//vector between b1 and b2
	Vector3 v = b2->m_particle->getPosition() - b1->m_particle->getPosition();

	//the distance is norm of vector v minus the sum of radii
	double dist = v.norm() - (b1->getRadius() + b2->getRadius());

	//If the distance is smaller than zero 
	if (dist < 0.0) {
		//resolve the penetration first
		resolvePenetration(b1, b2, v, dist);
		//Then resolve the collision and modify velocities
		resolveCollision(b1, b2);
		return true;
	}
	return false;

}

void CollisionDetector::resolveCollision(Ball* b1, Ball* b2) {

	//compute the velocities
	Vector3 v12 = b1->m_particle->getVelocity() - b2->m_particle->getVelocity();
	Vector3 v21 = b2->m_particle->getVelocity() - b1->m_particle->getVelocity();

	Vector3 x12 = b1->m_particle->getPosition() - b2->m_particle->getPosition();
	Vector3 x21 = b2->m_particle->getPosition() - b1->m_particle->getPosition();

	double mass1 = b1->m_particle->getMass();
	double mass2 = b2->m_particle->getMass();
	double totalmass = mass1 + mass2;

	//Vector3 v1_new = b1->m_particle->getVelocity() - x12 * (2 * mass2 * (v12 * x12) / (totalmass * x12))

	//b1->m_particle->setVelocity(v1_new);
	//b2->m_particle->setVelocity(v2_new);

}

void CollisionDetector::resolvePenetration(Ball* b1, Ball* b2, Vector3 v, double dist) {
	/*
	Vector3 v = b2->m_particle->getPosition() - b1->m_particle->getPosition();

	//the distance is norm of vector v minus the sum of radii
	double dist = v.norm() - (b1->getRadius() + b2->getRadius());

	//If the distance is smaller than zero , there is penetration
	if (dist < 0.0) {
		Vector3 penetration - v * (dist/v.norm();
	}
	
	*/

	//compute the penetration vector between b1 and b2
	Vector3 penetration = v * (-dist / v.norm());
	//penetration.print();
	//how much we should move b1 and b2? According to their inverse masses.
	double invmass1 = b1->m_particle->getInverseMass();
	double invmass2 = b2->m_particle->getInverseMass();
	double totalmass = invmass1 + invmass2;
	Vector3 move1;
	Vector3 move2;
	if (totalmass > 0.0) {
		move1 = penetration * (-invmass1 / totalmass);
		move2 = penetration * (invmass2 / totalmass);
	}
	else {
		//both have infinite mass. so move both half way.??
		move1 = penetration * -0.5;
		move2 = penetration * 0.5;
	}

	//move1.print()
	//move2.print()

	//set the new position
	b1->m_particle->setPosition(b1->m_particle->getPosition() + move1);
	b2->m_particle->setPosition(b2->m_particle->getPosition() + move2);
}