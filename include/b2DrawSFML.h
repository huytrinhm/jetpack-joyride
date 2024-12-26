#include "Config.h"
#include "Engine/GameManager.h"
#include "SFML/Graphics.hpp"
#include "Utilities.h"
#include "box2d/box2d.h"

#include <iostream>

namespace DebugDraw {

sf::Color from_b2HexColor(b2HexColor color) {
  return sf::Color((color & 0xff0000) >> 16, (color & 0x00ff00) >> 8,
                   color & 0x0000ff, DEBUG_DRAW_OPACITY);
}

void DrawSolidCapsule(b2Vec2 p1,
                      b2Vec2 p2,
                      float radius,
                      b2HexColor color,
                      void* context) {
  // Draw the two circles
  sf::CircleShape circle1 = sf::CircleShape(meterToPixel(radius));
  circle1.setFillColor(from_b2HexColor(color));
  circle1.setOrigin(meterToPixel(radius), meterToPixel(radius));
  circle1.setPosition(meterToPixel(p1));
  static_cast<sf::RenderTarget*>(context)->draw(circle1);

  sf::CircleShape circle2 = sf::CircleShape(meterToPixel(radius));
  circle2.setFillColor(from_b2HexColor(color));
  circle2.setOrigin(meterToPixel(radius), meterToPixel(radius));
  circle2.setPosition(meterToPixel(p2));
  static_cast<sf::RenderTarget*>(context)->draw(circle2);
}

void DrawString(b2Vec2 p, const char* string, void* context) {
  sf::Text text(string, AssetManager::Instance().GetFont("Jetpackia"), 10);
  text.setFillColor(sf::Color::White);
  text.setOrigin(text.getLocalBounds().width / 2,
                 text.getLocalBounds().height / 2);
  text.setPosition(meterToPixel(p));
  static_cast<sf::RenderTarget*>(context)->draw(text);
}

void DrawPolygon(const b2Vec2* vertices,
                 int vertexCount,
                 b2HexColor color,
                 void* context) {
  std::vector<sf::Vertex> v;
  for (int i = 0; i < vertexCount; i++) {
    sf::Vertex point(meterToPixel(vertices[i]));
    point.color = from_b2HexColor(color);
    v.push_back(point);
  }
  sf::Vertex pointS(meterToPixel(vertices[0]));
  pointS.color = from_b2HexColor(color);
  v.push_back(pointS);
  static_cast<sf::RenderTarget*>(context)->draw(&v[0], v.size(),
                                                sf::LinesStrip);
}

void DrawSolidPolygon(b2Transform transform,
                      const b2Vec2* vertices,
                      int vertexCount,
                      float radius,
                      const b2HexColor color,
                      void* context) {
  sf::ConvexShape convex = sf::ConvexShape();
  convex.setPointCount(vertexCount);
  for (int i = 0; i < vertexCount; i++) {
    convex.setPoint(i, meterToPixel({vertices[i].x + transform.p.x,
                                     vertices[i].y + transform.p.y}));
  }
  convex.setFillColor(from_b2HexColor(color));
  static_cast<sf::RenderTarget*>(context)->draw(convex);
}

void DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context) {
  // std::vector<sf::Vertex> v;
  // const float drawRadius = radius;
  // int count = drawRadius * 10;
  // float unitR = 2 * B2_PI / count;
  // for (int i = 0; i < count; i++) {
  //   sf::Vertex point(
  //       sf::Vector2f{center.x, center.y} +
  //       sf::Vector2f(cos(unitR * i) * drawRadius, sin(unitR * i) *
  //       drawRadius));
  //   point.color =
  //       sf::Color(color & 0xff0000, color & 0x00ff00, color & 0x0000ff);
  //   v.push_back(point);
  // }
  // sf::Vertex point(sf::Vector2f{center.x, center.y} +
  //                  sf::Vector2f(cos(0) * drawRadius, sin(0) * drawRadius));
  // point.color = sf::Color(color & 0xff0000, color & 0x00ff00, color &
  // 0x0000ff); v.push_back(point);
  // static_cast<sf::RenderTarget*>(context)->draw(&v[0], v.size(),
  //                                               sf::LinesStrip);
  // std::cerr << "DrawCircle" << std::endl;
  throw std::runtime_error("DrawCircle not implemented");
}

void DrawSolidCircle(b2Transform transform,
                     float radius,
                     b2HexColor color,
                     void* context) {
  // b2Vec2 center = transform.p;
  // sf::CircleShape circle = sf::CircleShape(radius);
  // circle.setFillColor(
  //     sf::Color(color & 0xff0000, color & 0x00ff00, color & 0x0000ff));
  // sf::Vector2f pos = sf::Vector2f{center.x, center.y};
  // circle.setPosition(pos - sf::Vector2f(radius, radius));
  // static_cast<sf::RenderTarget*>(context)->draw(circle);
  // std::cerr << "DrawSolidCircle" << std::endl;
  throw std::runtime_error("DrawSolidCircle not implemented");
}

void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context) {
  sf::Vertex line[] = {
      sf::Vertex(meterToPixel(p1)),
      sf::Vertex(meterToPixel(p2)),
  };
  line[0].color = from_b2HexColor(color);
  line[1].color = from_b2HexColor(color);
  static_cast<sf::RenderTarget*>(context)->draw(line, 2, sf::Lines);
}

void DrawPoint(b2Vec2 p, float size, b2HexColor color, void* context) {
  size /= 3;
  sf::CircleShape circle = sf::CircleShape(size);
  circle.setFillColor(from_b2HexColor(color));
  circle.setOrigin(size, size);
  circle.setPosition(meterToPixel(p));
  static_cast<sf::RenderTarget*>(context)->draw(circle);
}

void DrawTransform(b2Transform xf, void* context) {
  DrawPoint(xf.p, 10, b2HexColor(0xff0000), context);
}

b2DebugDraw debugDraw = {DrawPolygon,
                         DrawSolidPolygon,
                         DrawCircle,
                         DrawSolidCircle,
                         DrawSolidCapsule,
                         DrawSegment,
                         DrawTransform,
                         DrawPoint,
                         DrawString,
                         b2AABB{0},
                         false,  // drawUsingBounds
                         true,   // shapes
                         true,   // joints
                         true,   // joint extras
                         true,   // aabbs
                         false,  // mass
                         true,   // contacts
                         true,   // colors
                         true,   // normals
                         true,   // impulse
                         false,  // friction
                         nullptr};
};  // namespace DebugDraw
