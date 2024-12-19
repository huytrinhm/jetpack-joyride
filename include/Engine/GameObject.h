#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <string>
#include <vector>
#include "Component.h"
#include "Transform.h"

class GameObject {
 private:
  std::vector<std::unique_ptr<Component>> components;

 public:
  std::string name;
  Transform transform;

  GameObject(const std::string& name);

  template <typename T, typename... Args>
  T* AddComponent(Args&&... args);

  template <typename T>
  T* GetComponent();

  void DoStart();
  void DoUpdate();

  virtual void Start();
  virtual void Update();
};

#endif  // GAMEOBJECT_H
