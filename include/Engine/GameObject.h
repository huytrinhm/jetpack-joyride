#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>
#include "Component.h"
#include "Engine/GameRenderer.h"
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

  template <typename T>
  void RemoveComponent();

  void DoStart();
  void DoUpdate();
  void DoFixedUpdate();

  virtual void Start();
  virtual void Update();
  virtual void FixedUpdate();
  virtual void Render(GameRenderer& renderer);
};

#endif  // GAMEOBJECT_H
