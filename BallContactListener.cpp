#include "BallContactListener.h"

void BallContactListener::BeginContact(b2Contact* contact){
	printf("touch\n");
	const b2Body* bodyA = contact->GetFixtureA()->GetBody();
    const b2Body* bodyB = contact->GetFixtureB()->GetBody();
	b2Vec2 posA = bodyA->GetPosition();
	b2Vec2 posB = bodyB->GetPosition();

	printf("PosA x:%f y:%f\n",posA.x,posA.y);
	printf("PosB x:%f y:%f\n",posB.x,posB.y);
}

/// Called when two fixtures cease to touch.
void BallContactListener::EndContact(b2Contact* contact){
	printf("...and go\n");
}

void BallContactListener::PreSolve(b2Contact* contact, const b2Manifold* oldManifold)
{
}

void BallContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}