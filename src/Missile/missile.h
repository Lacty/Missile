
#pragma once
#include "../MyLib/ci_app.h"
#include "cinder/Matrix.h"
#include "cinder/Camera.h"


class Missile {
private:
  Vec3f pos;
  Vec3f size;
  Vec3f rot_speed;

  Color color;

  Vec3f velocity;
  Vec3f rotate;

  Vec3f target;

  CameraPersp& cam;

  void horming();

public:
  Missile(CameraPersp& cam);

  void setTarget(Vec3f target) {
    this->target = target;
  }

  void update();
  void draw();
};