// QT include
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
// project include
#include "lib/socketclient.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    // create obj to connect to server via TCP socket protocol
    SocketClient *socket = new SocketClient();
    socket->connectToServer("192.168.1.100", 1234);

    engine.rootContext()->setContextProperty("backend", socket);
    engine.load(url);

    return app.exec();
}
