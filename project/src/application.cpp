#include "application.h"

#include <QGuiApplication.h>
#include <QQmlApplicationEngine.h>

#include "core/cursor.h"
#include "core/blackboard.h"
#include "core/nodevaluefinder.h"

#include "nodes/addnode.h"
#include "nodes/printnode.h"
#include "nodes/dividenode.h"
#include "nodes/modulonode.h"
#include "nodes/multiplynode.h"
#include "nodes/subtractnode.h"
#include "nodes/var1dnode.h"

namespace tsr
{
Application::Application(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    mpApp = new QGuiApplication(argc, argv);
    mpEngine = new QQmlApplicationEngine();

    qmlRegister();

    mpEngine->load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (mpEngine->rootObjects().isEmpty())
    {
        throw std::runtime_error("failed to load qrc");
    }
}

void Application::qmlRegister()
{
    qmlRegisterType<Cursor>("cursor", 1, 0, "Cursor");
    qmlRegisterType<BlackBoard>("blackBoard", 1, 0, "Board");
    qmlRegisterType<NodeValueFinder>("noderesults", 1, 0, "Result");

    qmlRegisterType<PrintNode>("printnode", 1, 0, "PrintNode");

    qmlRegisterType<Var1DNode>("var1dnode", 1, 0, "Var1DNode");

    qmlRegisterType<AddNode>("addnode", 1, 0, "AddNode");
    qmlRegisterType<SubtractNode>("subtractnode", 1, 0, "SubtractNode");
    qmlRegisterType<MultiplyNode>("multiplynode", 1, 0, "MultiplyNode");
    qmlRegisterType<DivideNode>("dividenode", 1, 0, "DivideNode");
    qmlRegisterType<ModuloNode>("modulonode", 1, 0, "ModuloNode");
}

void Application::run()
{
    std::cout << "Welcome " PROJECT_NAME " version: " PROJECT_VERSION "\n";
    mpApp->exec();
}

Application::~Application()
{
    delete mpEngine;
    delete mpApp;
}
}