#include "application.h"

#include "QGuiApplication.h"
#include "QQmlApplicationEngine.h"

namespace tsr
{
Application::Application(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    app = new QGuiApplication(argc, argv);

    engine = new QQmlApplicationEngine();
    engine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine->rootObjects().isEmpty())
        std::runtime_error("");
}

void Application::run()
{
    std::cout << "Welcome " PROJECT_NAME " version: " PROJECT_VERSION "\n";
    app->exec();
}

Application::~Application()
{
}
}