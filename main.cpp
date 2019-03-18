#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>

#include "httprequest.h"
#include "logincontroller.h"
#include "stackviewcontroller.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQuickStyle::setStyle("Material");

  qmlRegisterType<LoginController>("QGuov.Controller.Login", 1, 0, "LoginController");
  qmlRegisterType<StackViewController>("QGuov.Controller.StackView", 1, 0, "StackViewController");

  QQmlApplicationEngine engine;

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  new HttpRequest();

  return app.exec();
}
