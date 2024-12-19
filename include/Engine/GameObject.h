#pragma once

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

  virtual void Start();
  virtual void Update();
};
