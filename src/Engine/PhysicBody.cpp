#include "Engine/PhysicBody.h"
#include <iostream>
#include "Engine/GameManager.h"
#include "Engine/GameObject.h"
#include "Utilities.h"

PhysicBody::PhysicBody(b2BodyId bodyId) : bodyId(bodyId) {}

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

PhysicBody::~PhysicBody() {
  if (b2Body_IsValid(bodyId))
    b2DestroyBody(bodyId);
}