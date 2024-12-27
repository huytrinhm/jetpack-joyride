#include "Rocket.h"
#include "AssetManager.h"
#include "Config.h"
#include "Engine/PhysicBody.h"
#include "GameManager.h"
#include "Utilities.h"

Rocket::Rocket(float delayDuration, float aimDuration, float lockDuration)
    : state(State::Delay),
      speed(3 * GameManager::Instance().scrollSpeed),
      stateTime(0.0f),
      delayDuration(delayDuration),
      aimDuration(aimDuration),
      lockDuration(lockDuration) {
  animator = this->AddComponent<Animator>(
      AssetManager::Instance().GetTexture("rocket"));
  auto aimAnimation = animator->AddAnimation("aim", true, 9);
  for (int i = 0; i < 4; i++)
    aimAnimation->frames.emplace_back(sf::IntRect{(i % 4) * 64, 64, 64, 64},
                                      0.2f, sf::Vector2f(-62, 0));

  auto lockAnimation = animator->AddAnimation("lock", true, 9);
  for (int i = 0; i < 4; i++)
    lockAnimation->frames.emplace_back(sf::IntRect{(i % 4) * 64, 128, 64, 64},
                                       0.2f, sf::Vector2f(-62, 0));

  auto launchAnimation = animator->AddAnimation("launch", true, 5);
  for (int i = 0; i < 4; i++)
    launchAnimation->frames.emplace_back(sf::IntRect{(i % 4) * 90, 0, 90, 64},
                                         0.1f, sf::Vector2f(10, 0));

  animator->PlayAnimation("aim");
}

void Rocket::Update() {
  stateTime += GameManager::Instance().deltaTime;
  switch (state) {
    case State::Delay:
      if (stateTime >= delayDuration) {
        transform.position = {WORLD_WIDTH + 30,
                              GameManager::Instance().player->GetPosition().y};
        state = State::Aim;
        stateTime = 0.0f;
      }
      break;
    case State::Aim:
      Aim();

      if (stateTime >= aimDuration) {
        state = State::Lock;
        stateTime = 0.0f;
        animator->PlayAnimation("lock");
      }
      break;
    case State::Lock:
      if (stateTime >= lockDuration) {
        state = State::Launch;
        stateTime = 0.0f;
        Launch();
      }
      break;
    default:
      break;
  }
}

void Rocket::Aim() {
  // Move the aim position towards the player's y position
  float targetY = GameManager::Instance().player->GetPosition().y;
  float currentY = transform.position.y;
  float newY = currentY + aimSpeed * GameManager::Instance().deltaTime *
                              ((targetY > currentY) ? 1 : -1);
  if (std::abs(newY - targetY) < aimSpeed * GameManager::Instance().deltaTime) {
    newY = targetY;
  }
  transform.position.y = newY;
}

void Rocket::Launch() {
  animator->PlayAnimation("launch");

  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_kinematicBody;
  bodyDef.position = pixelToMeter(transform.position);

  b2BodyId bodyId = b2CreateBody(GameManager::Instance().worldId, &bodyDef);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.isSensor = true;
  shapeDef.userData = static_cast<CollidableGameObject*>(this);

  b2Capsule capsule = makeHorizontalCapsule(pixelToMeter(60), pixelToMeter(18));
  b2CreateCapsuleShape(bodyId, &shapeDef, &capsule);

  auto physicBody = this->AddComponent<PhysicBody>(bodyId);
  physicBody->SetVelocity({-pixelToMeter(speed), 0});
}

void Rocket::Render(GameRenderer& renderer) {
  animator->Render(renderer);
}
