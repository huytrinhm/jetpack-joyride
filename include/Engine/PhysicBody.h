#ifndef PHYSICBODY_H
#define PHYSICBODY_H

#include "Component.h"
#include "box2d/box2d.h"

class PhysicBody : public Component {
 public:
  PhysicBody(b2BodyId bodyId);
  void FixedUpdate() override;
  void ApplyForce(b2Vec2 force);
  void SetVelocity(b2Vec2 velocity);
  void SetGravityScale(float scale);
  ~PhysicBody();

 private:
  b2BodyId bodyId;
  b2Vec2 totalForce;
};

#endif  // PHYSICBODY_H
