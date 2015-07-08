
#include "missile.h"
#include "../MyLib/key.h"
#include <cmath> // sqrt


Missile::Missile(CameraPersp& cam) :
cam(cam),
velocity(0, 0, 0) {}


void Missile::horming() {

}

void Missile::update() {
  horming();
}

void Missile::draw() {
  gl::pushModelView();

  static float angle = 0.f;

  if (Key::get().isPush(KeyEvent::KEY_d)) angle += 0.1f;
  if (Key::get().isPush(KeyEvent::KEY_a)) angle -= 0.1f;
  if (Key::get().isPress(KeyEvent::KEY_w)) velocity.y += 2;
  if (Key::get().isPress(KeyEvent::KEY_s)) velocity.y -= 2;

  Vec3f axis(1, 0, 0);
  Matrix44f rotate = Matrix44f::createRotation(axis, angle);
  rotate.setTranslate(Vec3f::zero());
  gl::translate(last_pos);
  gl::rotate(rotate);
  gl::translate(velocity);
  gl::drawStrokedCube(Vec3f::zero(), Vec3f(10, 10, 10));

  auto matrix = gl::getModelView() * cam.getInverseModelViewMatrix();
  //last_pos = Vec3f(matrix.m03, matrix.m13, matrix.m23);

  console() << "[x = " << matrix.m03 << "][y = " << matrix.m13 << "][z = " << matrix.m23 << "]" << std::endl;

  gl::popModelView();
}
