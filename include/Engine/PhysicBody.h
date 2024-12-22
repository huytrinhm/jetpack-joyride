#ifndef PHYSICBODY_H
#define PHYSICBODY_H

#include "Component.h"
#include "box2d/box2d.h"

class PhysicBody : public Component {
 public:
  PhysicBody(b2Vec2 position, b2Vec2 scale);
  void FixedUpdate() override;

 private:
  b2BodyId bodyId;
};

#endif  // PHYSICBODY_H
