#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include "httprequest.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QQuickStyle::setStyle("Material");

  QQmlApplicationEngine engine;

  engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  new HttpRequest();

  return app.exec();
}
