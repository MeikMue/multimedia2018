#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTranslator>
#include "myglitem.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QTranslator t;
    t.load(":/translations/testmm2017_de.qm");
    app.installTranslator(&t);

    qmlRegisterType<MyGlItem>("GlComponents", 1,0, "MyGlItem");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
