#include "application.h"

#include "QGuiApplication.h"
#include "QQmlApplicationEngine.h"

#include "nodes/cursor.h"
#include "nodes/blackboard.h"
#include "nodes/nodevaluefinder.h"

namespace tsr
{
Application::Application(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    app = new QGuiApplication(argc, argv);
    engine = new QQmlApplicationEngine();

    qmlRegister();

    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine->rootObjects().isEmpty())
    {
        throw std::runtime_error("failed to load qrc");
    }
}

void Application::qmlRegister()
{
    qmlRegisterType<Cursor>("cursor", 1, 0, "Cursor");
    qmlRegisterType<BlackBoard>("blackBoard", 1, 0, "Board");
    qmlRegisterType<NodeValueFinder>("noderesults", 1, 0, "Result");
}

void Application::run()
{
    std::cout << "Welcome " PROJECT_NAME " version: " PROJECT_VERSION "\n";
    app->exec();
}

Application::~Application()
{
    delete engine;
    delete app;
}
}