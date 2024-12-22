#include "SFML/Graphics.hpp"
#include "box2d/box2d.h"

#include <iostream>

namespace DebugDraw {

void DrawSolidCapsule(b2Vec2 p1,
                      b2Vec2 p2,
                      float radius,
                      b2HexColor color,
                      void* context) {}

void DrawString(b2Vec2 p, const char* string, void* context) {}

void DrawPolygon(const b2Vec2* vertices,
                 int vertexCount,
                 b2HexColor color,
                 void* context) {
  std::vector<sf::Vertex> v;
  for (int i = 0; i < vertexCount; i++) {
    sf::Vertex point(sf::Vector2f{vertices[i].x, vertices[i].y});
    point.color =
        sf::Color(color & 0xff0000, color & 0x00ff00, color & 0x0000ff);
    v.push_back(point);
  }
  sf::Vertex pointS(sf::Vector2f{vertices[0].x, vertices[0].y});
  pointS.color =
      sf::Color(color & 0xff0000, color & 0x00ff00, color & 0x0000ff);
  v.push_back(pointS);
  static_cast<sf::RenderTarget*>(context)->draw(&v[0], v.size(),
                                                sf::LinesStrip);
  std::cerr << "DrawPolygon" << std::endl;
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
    convex.setPoint(i, sf::Vector2f{vertices[i].x + transform.p.x,
                                    vertices[i].y + transform.p.y});
  }
  convex.setFillColor(
      sf::Color(color & 0xff0000, color & 0x00ff00, color & 0x0000ff, 50));
  static_cast<sf::RenderTarget*>(context)->draw(convex);
}

void DrawCircle(b2Vec2 center, float radius, b2HexColor color, void* context) {
  std::vector<sf::Vertex> v;
  const float drawRadius = radius;
  int count = drawRadius * 10;
  float unitR = 2 * B2_PI / count;
  for (int i = 0; i < count; i++) {
    sf::Vertex point(
        sf::Vector2f{center.x, center.y} +
        sf::Vector2f(cos(unitR * i) * drawRadius, sin(unitR * i) * drawRadius));
    point.color =
        sf::Color(color & 0xff0000, color & 0x00ff00, color & 0x0000ff);
    v.push_back(point);
  }
  sf::Vertex point(sf::Vector2f{center.x, center.y} +
                   sf::Vector2f(cos(0) * drawRadius, sin(0) * drawRadius));
  point.color = sf::Color(color & 0xff0000, color & 0x00ff00, color & 0x0000ff);
  v.push_back(point);
  static_cast<sf::RenderTarget*>(context)->draw(&v[0], v.size(),
                                                sf::LinesStrip);
  std::cerr << "DrawCircle" << std::endl;
}

void DrawSolidCircle(b2Transform transform,
                     float radius,
                     b2HexColor color,
                     void* context) {
  b2Vec2 center = transform.p;
  sf::CircleShape circle = sf::CircleShape(radius);
  circle.setFillColor(
      sf::Color(color & 0xff0000, color & 0x00ff00, color & 0x0000ff));
  sf::Vector2f pos = sf::Vector2f{center.x, center.y};
  circle.setPosition(pos - sf::Vector2f(radius, radius));
  static_cast<sf::RenderTarget*>(context)->draw(circle);
  std::cerr << "DrawSolidCircle" << std::endl;
}

void DrawSegment(b2Vec2 p1, b2Vec2 p2, b2HexColor color, void* context) {}

void DrawTransform(b2Transform xf, void* context) {
  std::cerr << "DrawTransform" << std::endl;
}

void DrawPoint(b2Vec2 p, float size, b2HexColor color, void* context) {
  sf::CircleShape circle = sf::CircleShape(size);
  circle.setOrigin(sf::Vector2f(size, size));
  circle.setFillColor(
      sf::Color(color & 0xff0000, color & 0x00ff00, color & 0x0000ff));
  circle.setPosition(sf::Vector2f{p.x, p.y});
  static_cast<sf::RenderTarget*>(context)->draw(circle);
  std::cerr << "DrawPoint" << std::endl;
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
                         b2AABB{b2Vec2{0, 0}, b2Vec2{0, 0}},
                         false,  // drawUsingBounds
                         true,   // shapes
                         true,   // joints
                         false,  // joint extras
                         false,  // aabbs
                         false,  // mass
                         false,  // contacts
                         false,  // colors
                         false,  // normals
                         false,  // impulse
                         false,  // friction
                         nullptr};
};  // namespace DebugDraw
