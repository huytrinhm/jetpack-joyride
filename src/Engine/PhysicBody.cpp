#include "Engine/PhysicBody.h"
#include <iostream>
#include "Engine/GameManager.h"
#include "Engine/GameObject.h"

PhysicBody::PhysicBody(b2Vec2 position, b2Vec2 scale) {
  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_dynamicBody;
  bodyDef.position = position;
  bodyId = b2CreateBody(GameManager::Instance().worldId, &bodyDef);
  b2Polygon dynamicBox = b2MakeBox(scale.x / 2, scale.y / 2);
  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.density = 0.08f;  // kg/px^2
  shapeDef.friction = 0.0f;
  b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

void PhysicBody::FixedUpdate() {
  b2Vec2 position = b2Body_GetPosition(bodyId);
  b2Rot rotation = b2Body_GetRotation(bodyId);
  gameObject->transform.position = sf::Vector2f(position.x, position.y);
  gameObject->transform.rotation = b2Rot_GetAngle(rotation);
  //   std::cerr << "Position: " << position.x << ", " << position.y <<
  //   std::endl;
}
