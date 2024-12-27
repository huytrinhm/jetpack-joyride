#include "Engine/PhysicBody.h"
#include <iostream>
#include "Engine/GameObject.h"
#include "GameManager.h"
#include "Utilities.h"

PhysicBody::PhysicBody(b2BodyId bodyId) : bodyId(bodyId), totalForce({0, 0}) {}

void PhysicBody::FixedUpdate() {
  b2Vec2 position = b2Body_GetPosition(bodyId);
  b2Rot rotation = b2Body_GetRotation(bodyId);
  gameObject->transform.position = meterToPixel(position);
  gameObject->transform.rotation = b2Rot_GetAngle(rotation);

  b2Body_ApplyForceToCenter(bodyId, totalForce, true);
  totalForce = {0, 0};

  // std::cerr << "Position: " << position.x << ", " << position.y << std::endl;
}

void PhysicBody::ApplyForce(b2Vec2 force) {
  totalForce += force;
}

void PhysicBody::SetVelocity(b2Vec2 velocity) {
  b2Body_SetLinearVelocity(bodyId, velocity);
}

PhysicBody::~PhysicBody() {
  if (b2Body_IsValid(bodyId))
    b2DestroyBody(bodyId);
}