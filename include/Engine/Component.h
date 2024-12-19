#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component {
 public:
  GameObject* gameObject = nullptr;

  virtual ~Component();
  virtual void Update();
  virtual void Start();
};

#endif  // COMPONENT_H
