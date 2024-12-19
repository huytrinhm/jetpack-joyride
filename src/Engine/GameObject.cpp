#include "Engine/GameObject.h"
#include "Engine/Animator.h"

GameObject::GameObject(const std::string& name) : name(name) {
  transform.gameObject = this;
}

void GameObject::Start() {
  for (const auto& component : components) {
    component->Start();
  }
}

void GameObject::Update() {
  for (const auto& component : components) {
    component->Update();
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

// Explicit template instantiations
template Transform* GameObject::AddComponent();
template Transform* GameObject::GetComponent();

template Animator* GameObject::AddComponent(sf::Texture&);
template Animator* GameObject::GetComponent();
