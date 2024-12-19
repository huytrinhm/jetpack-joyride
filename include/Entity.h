#ifndef ENTITY_H
#define ENTITY_H

class Entity {
 public:
  virtual ~Entity() {}
  virtual void onCreate() = 0;
  virtual void onUpdate(float deltaTime) = 0;
};

#endif
