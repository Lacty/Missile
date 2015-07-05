
#include "missile.h"
#include "../MyLib/key.h"
#include <cmath> // sqrt


Missile::Missile(CameraPersp& cam) :
pos(0, -100, 0),
size(10, 20, 10),
rotate(0, 0, 0),
rot_speed(0, 0, 6),
velocity(0, 1, 0),
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

  console() << "Forward = " << Forward.normalized() << std::endl;
  console() << "Aim = " << Aim.normalized() << std::endl;

  float dot = Forward.normalized().dot(Aim.normalized());
  console() << "dot = " << dot << std::endl;

  if (dot < 1.0f) dot = 1.0f;

  float angle = std::acosf(dot); // 微動だにせず0
  console() << "angle" << angle << std::endl;


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