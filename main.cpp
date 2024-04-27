#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "log4qt/log4qt.h"
#include "log4qt/basicconfigurator.h"
#include "log4qt/logger.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    // log4qt配置文件路径
    Log4Qt::BasicConfigurator::configure();

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject * obj, const QUrl & objUrl)
    {
        if (!obj && url == objUrl)
        {
            QCoreApplication::exit(-1);
        }
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
