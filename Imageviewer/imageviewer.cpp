#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QTranslator>
#include <QIcon>
#include "networkImageModel.h"
#include "directoryTraverse.h"

#include <QKeyEvent>

class KeyBackQuit: public QObject
{
public:
    KeyBackQuit(QObject *qmlRoot, QObject *parent = 0)
        : QObject(parent), m_qmlRoot(qmlRoot)
    {}

    bool eventFilter(QObject *watched, QEvent * e)
    {
        switch(e->type())
        {
        case QEvent::KeyPress:
            if( ((QKeyEvent*)e)->key() == Qt::Key_Back )
            {
                e->accept();
                return true;
            }
            break;
        case QEvent::KeyRelease:
            if( ((QKeyEvent*)e)->key() == Qt::Key_Back )
            {
                e->accept();
                //qApp->quit();
                QMetaObject::invokeMethod(m_qmlRoot, "backKeyProcess");
                return true;
            }
            break;
        default:
            break;
        }
        return QObject::eventFilter(watched, e);
    }

    QObject *m_qmlRoot;
};

void imageViewer()
{
    qmlRegisterType<ImageModel>("hk.ImageModel", 1, 0, "ImageModel");
    qmlRegisterType<DirectoryTraverse>("hk.DirectoryTraverse", 1, 0, "DirTraverse");
}

/*
int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon("icons/ic_find.png"));

    QQmlApplicationEngine engine;
    ImageModel * model = new ImageModel();
    DirectoryTraverse *traverse = new DirectoryTraverse();
    engine.rootContext()->setContextProperty("imageModel", model);
    engine.rootContext()->setContextProperty("dirTraverse", traverse);
    engine.load(QUrl(u"qrc:/imageview/imageviewer.qml"_qs));

    QList<QObject*> rootObjects = engine.rootObjects();
    int count = rootObjects.size();
    for(int i = 0; i < count; i++)
    {
        if(rootObjects.at(i)->objectName() == "qmlWin")
        {
            qDebug() << "find qmlWin";
            app.installEventFilter(new KeyBackQuit(rootObjects.at(i)));
            break;
        }
    }

    return app.exec();
}
*/
