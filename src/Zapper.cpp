#include "Zapper.h"
#include <iostream>
#include "AssetManager.h"
#include "Config.h"
#include "Engine/Animator.h"
#include "Engine/PhysicBody.h"
#include "GameManager.h"
#include "Utilities.h"
#include "box2d/box2d.h"

Zapper::Zapper(ZapperType zapperType,
               const sf::Vector2f& position,
               int length,
               bool isActive)
    : length(length), isActive(isActive), currentFrame(0) {
  transform.position = position;

  zapperRenderTexture.create(length * 16 + 2 * 32, 32);
  zapperSprite.setTexture(zapperRenderTexture.getTexture());
  zapperSprite.setOrigin(zapperSprite.getLocalBounds().width / 2,
                         zapperSprite.getLocalBounds().height / 2);
  zapperEffectSprite.setTexture(
      AssetManager::Instance().GetTexture("zapperEffect"));
  zapperHeadSprite.setTexture(
      AssetManager::Instance().GetTexture("zapperHead"));
  zapperHeadSprite.setOrigin(16, 16);

  float pixelLength = length * 16 + 32;
  float pixelWidth = 22;
  const b2Vec2 scale = pixelToMeter({pixelWidth, pixelLength});

  b2BodyDef bodyDef = b2DefaultBodyDef();
  bodyDef.type = b2_kinematicBody;
  bodyDef.linearVelocity = {-pixelToMeter(GameManager::Instance().scrollSpeed),
                            0};
  bodyDef.position = pixelToMeter(position);

  if (zapperType == ZAPPER_HORIZONTAL) {
    bodyDef.rotation = b2MakeRot(0);
    zapperSprite.setRotation(0);
  } else if (zapperType == ZAPPER_MAIN_DIAGONAL) {
    bodyDef.rotation = b2MakeRot(B2_PI / 4);
    zapperSprite.setRotation(45);
  } else if (zapperType == ZAPPER_SUB_DIAGONAL) {
    bodyDef.rotation = b2MakeRot(-B2_PI / 4);
    zapperSprite.setRotation(-45);
  } else {
    bodyDef.rotation = b2MakeRot(B2_PI / 2);
    zapperSprite.setRotation(90);
  }

  b2BodyId bodyId = b2CreateBody(GameManager::Instance().worldId, &bodyDef);

  b2ShapeDef shapeDef = b2DefaultShapeDef();
  shapeDef.isSensor = true;
  shapeDef.userData = static_cast<CollidableGameObject*>(this);

  b2Capsule capsule = makeHorizontalCapsule(scale.y, scale.x);
  b2CreateCapsuleShape(bodyId, &shapeDef, &capsule);

  this->AddComponent<PhysicBody>(bodyId);
}

sf::IntRect getZapperEffectFrame(int frame) {
  return {frame * 16, 0, 16, 29};
}

sf::IntRect getZapperHeadFrame(int frame) {
  return {(frame % 4) * 32, (frame / 4) * 32, 32, 32};
}

void Zapper::Render(GameRenderer& renderer) {
  zapperRenderTexture.clear(sf::Color::Transparent);

  for (int i = 0; i < length; i++) {
    zapperEffectSprite.setPosition({32 + 16.f * i, 1});
    zapperEffectSprite.setTextureRect(getZapperEffectFrame(i));
    zapperRenderTexture.draw(zapperEffectSprite);
  }

  // Render head
  zapperHeadSprite.setPosition({16 + 8, 16});
  zapperHeadSprite.setTextureRect(getZapperHeadFrame(0));
  zapperHeadSprite.setRotation(90);
  zapperRenderTexture.draw(zapperHeadSprite);

  zapperHeadSprite.setPosition({length * 16.f + 32 + 16 - 8, 16});
  zapperHeadSprite.setTextureRect(getZapperHeadFrame(0));
  zapperHeadSprite.setRotation(-90);
  zapperRenderTexture.draw(zapperHeadSprite);

  zapperRenderTexture.display();

  renderer.AddDrawable(4, &zapperSprite);
}

void Zapper::Update() {
  zapperSprite.setPosition(transform.position);
}
