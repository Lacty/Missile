
#pragma once
#include "../MyLib/ci_app.h"
#include "cinder/Matrix.h"
#include "cinder/Camera.h"


class Missile {
private:
  //Matrix44f matrix;
  Vec3f target;
  Vec3f last_pos;

  Vec3f velocity;

  CameraPersp& cam;

  void horming();

public:
  Missile(CameraPersp& cam);

  inline void setTarget(Vec3f target) {
    this->target = target;
  }

  void update();
  void draw();
};