
#include "missile.h"
#include "../MyLib/key.h"


Missile::Missile(CameraPersp& cam) :
pos(0, -100, 0),
size(10, 20, 10),
rotate(0, 0, 0),
rot_speed(0, 0, 10),
velocity(0, 10, 0),
color(1, 1, 1),
cam(cam) {}


void Missile::horming() {
  gl::pushModelView();

  gl::translate(pos);
  gl::rotate(rotate);
  gl::translate(velocity);
  auto current_matrix = gl::getModelView() * cam.getInverseModelViewMatrix();

  gl::popModelView();

  Vec3f Velocity = Vec3f(current_matrix.m03,
                         current_matrix.m13,
                         current_matrix.m23);
  Vec3f Forward = Velocity - pos;
  Vec3f Aim = target - pos;

  // 進行方向に対してターゲットが右にいるか左にいるかを判定
  if ((Forward.x * Aim.y - Forward.y * Aim.x) > 0) {
    rotate += rot_speed;
  } else { rotate -= rot_speed; }
}

void Missile::update() {
  horming();
}

void Missile::draw() {
  gl::color(color);

  gl::pushModelView();

  gl::translate(pos);
  gl::rotate(rotate);
  gl::translate(velocity);
  gl::drawCube(Vec3f::zero(), size);

  // ビュー行列にカメラの逆行列を掛けてワールド行列を取り出す
  auto current_matrix = gl::getModelView() * cam.getInverseModelViewMatrix();

  // m03 == x, m13 == y, m23 == z
  pos = Vec3f(current_matrix.m03,
              current_matrix.m13,
              current_matrix.m23);

  gl::popModelView();
}