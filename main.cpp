#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>

#include "Imageviewer/imageViewer.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QTranslator translator;
    if (translator.load(":/imageviewer_zh_CN.qm"))
        app.installTranslator(&translator);

    QQmlApplicationEngine engine;
    imageViewer();
    const QUrl url(u"qrc:/Manager/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}
