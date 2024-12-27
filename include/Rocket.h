#pragma once
#include <SFML/Graphics.hpp>
#include "Engine/Animator.h"
#include "Engine/GameRenderer.h"
#include "Harmful.h"
#include "Player.h"

class Rocket : public HarmfulGameObject {
 public:
  Rocket(float delayDuration = 0.0f,
         float aimDuration = 3.0f,
         float lockDuration = 0.5f);
  void Update() override;
  void Render(GameRenderer& renderer) override;

 private:
  void Aim();
  void Launch();
  enum class State { Delay, Aim, Lock, Launch };
  State state;
  float speed;
  float stateTime;
  float delayDuration = 0.0f;
  float aimDuration = 3.0f;
  float lockDuration = 0.5f;
  const float aimSpeed = 50.0f;
  Animator* animator;
};
