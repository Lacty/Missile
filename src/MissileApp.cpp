
#include "MyLib/window_size.h"
#include "MyLib/noncopyable.h"
#include "MyLib/ci_app.h"
#include "MyLib/mouse.h"
#include "MyLib/key.h"

#include "cinder/Camera.h"
#include "cinder/Matrix.h"
#include <list>

#include "Missile/missile.h"


class MissileApp : public AppNative,
                   public ly::noncopyable {
private:
  std::list<Missile> missiles;
  Vec3f pos;
  Vec3f rot;
  Vec3f vel;
  Vec3f tra;

  CameraPersp camera;

public:
  void setup();

  void mouseDown(MouseEvent event) final {
    Mouse::get().PushEvent(event);
  }
  void mouseUp(MouseEvent event) final {
    Mouse::get().PullEvent(event);
  }
  void mouseMove(MouseEvent event) final {
    Mouse::get().MoveEvent(event);
  }
  void mouseDrag(MouseEvent event) final {
    Mouse::get().MoveEvent(event);
  }
  void keyDown(KeyEvent event) final {
    Key::get().setKeyPush(event.getCode());
    Key::get().setKeyPress(event.getCode());
  }
  void keyUp(KeyEvent event) final {
    Key::get().popKeyPress(event.getCode());
    Key::get().setKeyPull(event.getCode());
  }

  void update();
  void draw();
};

void MissileApp::setup() {
  setWindowSize(int(WindowSize::Width),
                int(WindowSize::Height));
  Mouse::get();
  Key::get();

  camera = CameraPersp(getWindowWidth(), getWindowHeight(),
                       35.f, 0.5f, 1000.f);
  camera.lookAt(Vec3f(0, 0, 700),
                Vec3f(0, 0, 0));

  vel = Vec3f(0, 1, 0);
}

void MissileApp::update() {
  rot.y += 0.04f;
  rot.x += 0.03f;
  Matrix44f root_translate = Matrix44f::createTranslation(Vec3f(0, 0, 0));
  Matrix44f rotate = Matrix44f::createRotation(rot);
  Matrix44f translate = Matrix44f::createTranslation(Vec3f(0, 80, 140));
  pos = root_translate * rotate * translate * Vec3f(0, 0, 0);

  for (auto &obj : missiles) {
    obj.setTarget(pos);
    obj.update();
  }

  if (!Key::get().isPush(KeyEvent::KEY_SPACE)) return;
  missiles.emplace_back(Missile(camera));
}

void MissileApp::draw() {
  gl::clear(Color(0, 0, 0));
  gl::setMatrices(camera);

  for (auto& obj : missiles) {
    obj.draw();
  }

  gl::color(Color(1, 0, 0));
  gl::drawCube(pos, Vec3f(10, 10, 10));

  Mouse::get().flashInput();
  Key::get().flashInput();
}

CINDER_APP_NATIVE(MissileApp, RendererGl)
