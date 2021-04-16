#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "include/videomodel.h"
#include "include/videothread.h"

int main(int argc, char* argv[])
{
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

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

  engine.load(url);

  return app.exec();
}
