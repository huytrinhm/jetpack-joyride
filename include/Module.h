#ifndef MODULE_H
#define MODULE_H

class Module {
 public:
  virtual ~Module() {}
  virtual void update(float deltaTime) = 0;
};

#endif
