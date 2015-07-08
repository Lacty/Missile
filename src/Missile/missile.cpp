#include "missile.h"
#include "../MyLib/key.h"
#include <cmath> // sqrt


Missile::Missile(CameraPersp& cam) :
pos(0, -100, 0),
size(10, 20, 10),
rotate(0, 0, 0),
rot_speed(0, 0, 6),
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

  // �i�s�����ɑ΂��ă^�[�Q�b�g���E�ɂ��邩���ɂ��邩�𔻒�
  /*if ((Forward.x * Aim.y - Forward.y * Aim.x) > 0) {
  rotate += rot_speed;
  } else { rotate -= rot_speed; }*/

  // �^�[�Q�b�g�ɑ΂��Ēǔ������ۂ̉��]���x�𒲐����鏈��
  // �^�[�Q�b�g���i�s����||�����ɂ����Ɖ��]���x����
  float lengthAim = std::sqrt(Aim.x * Aim.x + Aim.y * Aim.y);
  Aim.x /= lengthAim; Aim.y /= lengthAim;
  float Cross = Forward.x * Aim.y - Forward.y * Aim.x;
  rotate.z += rot_speed.z * Cross / velocity.y; // �ړ����x�Ŋ����Ă������Ƃ������~�ɂȂ�
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

  // �r���[�s���ɃJ�����̋t�s�����|���ă��[���h�s���������o��
  auto current_matrix = gl::getModelView() * cam.getInverseModelViewMatrix();

  // m03 == x, m13 == y, m23 == z
  pos = Vec3f(current_matrix.m03,
              current_matrix.m13,
              current_matrix.m23);

  gl::popModelView();
}
