#include <QApplication>
#include <QQmlApplicationEngine>

#include "include/overlayfactory.h"
#include "include/videomodel.h"
#include "include/videothread.h"

int main(int argc, char* argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  srand(time(NULL));

  QApplication app(argc, argv);

  QQmlApplicationEngine engine;
  const QUrl url(QStringLiteral("qrc:/main.qml"));
  QObject::connect(&engine, &QQmlApplicationEngine::objectCreated, &app,
                   [url](QObject* obj, const QUrl& objUrl) {
                     if (!obj && url == objUrl)
                       QCoreApplication::exit(-1);
                   },
                   Qt::QueuedConnection);

  qmlRegisterType<VideoModel>("VideoModel", 1, 0, "VideoModel");
  qmlRegisterType<VideoThread>("VideoThread", 1, 0, "VideoThread");
  qmlRegisterUncreatableMetaObject(OverlayEffects::staticMetaObject, "OverlayEffects", 1, 0, "OverlayEffects",
                                   "Error: only enums");

  engine.load(url);

  return app.exec();
}
