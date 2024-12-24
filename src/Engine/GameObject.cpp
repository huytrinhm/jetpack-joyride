#include "Engine/GameObject.h"
#include "Engine/Animator.h"
#include "Engine/PhysicBody.h"

GameObject::GameObject(const std::string& name) : name(name) {
  transform.gameObject = this;
}

void GameObject::Start() {}
void GameObject::Update() {}
void GameObject::FixedUpdate() {}
void GameObject::Render(GameRenderer& renderer) {}

void GameObject::DoStart() {
  for (const auto& component : components) {
    component->Start();
  }

  Start();
}

void GameObject::DoUpdate() {
  Update();

  for (const auto& component : components) {
    component->Update();
  }
}

void GameObject::DoFixedUpdate() {
  FixedUpdate();

  for (const auto& component : components) {
    component->FixedUpdate();
  }
}

template <typename T, typename... Args>
T* GameObject::AddComponent(Args&&... args) {
  static_assert(std::is_base_of<Component, T>::value,
                "T must inherit from Component");
  auto component = std::make_unique<T>(std::forward<Args>(args)...);
  component->gameObject = this;
  T* componentPtr = component.get();
  components.push_back(std::move(component));
  return componentPtr;
}

template <typename T>
T* GameObject::GetComponent() {
  for (const auto& component : components) {
    if (auto casted = dynamic_cast<T*>(component.get())) {
      return casted;
    }
  }
  return nullptr;
}

template <typename T>
void GameObject::RemoveComponent() {
  for (auto it = components.begin(); it != components.end(); ++it) {
    if (dynamic_cast<T*>((*it).get())) {
      components.erase(it);
      return;
    }
  }
}

// Explicit template instantiations
template Transform* GameObject::AddComponent<Transform>();
template Transform* GameObject::GetComponent<Transform>();
template void GameObject::RemoveComponent<Transform>();

template Animator* GameObject::AddComponent<Animator, sf::Texture&>(
    sf::Texture&);
template Animator* GameObject::GetComponent<Animator>();
template void GameObject::RemoveComponent<Animator>();

template PhysicBody* GameObject::AddComponent<PhysicBody, b2BodyId>(b2BodyId&&);
template PhysicBody* GameObject::GetComponent<PhysicBody>();
template void GameObject::RemoveComponent<PhysicBody>();
