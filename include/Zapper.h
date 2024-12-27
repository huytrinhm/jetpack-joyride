#ifndef ZAPPER_H
#define ZAPPER_H

#include "Engine/Animator.h"
#include "Engine/GameObject.h"
#include "Harmful.h"
#include "ScrollerSpawner.h"

enum ZapperType {
  ZAPPER_HORIZONTAL,
  ZAPPER_VERTICAL,
  ZAPPER_MAIN_DIAGONAL,
  ZAPPER_SUB_DIAGONAL
};

class Zapper : public HarmfulGameObject {
 public:
  Zapper(ZapperType zapperType,
         const sf::Vector2f& position,
         int length,
         bool isActive = true);
  //   void Start() override;
  void Update() override;
  //   void FixedUpdate() override;
  void Render(GameRenderer& renderer) override;

 private:
  sf::RenderTexture zapperRenderTexture;
  sf::Sprite zapperSprite;
  sf::Sprite zapperEffectSprite;
  sf::Sprite zapperHeadSprite;
  int length;
  bool isActive;
  int currentFrame;
};

#endif  // ZAPPER_H