#include "app.h"

#include <QGuiApplication.h>
#include <QQmlApplicationEngine.h>

#include "core/cursor.h"
#include "core/board.h"
#include "core/nodevaluefinder.h"

#include "nodes/addnode.hpp"
#include "nodes/printnode.hpp"
#include "nodes/dividenode.hpp"
#include "nodes/modulonode.hpp"
#include "nodes/multiplynode.hpp"
#include "nodes/subtractnode.hpp"
#include "nodes/varnode.hpp"

namespace tsr
{
App::App(int argc, char* argv[])
{
#if defined(Q_OS_WIN)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    mpApp = new QGuiApplication(argc, argv);
    mpEngine = new QQmlApplicationEngine();

    qmlRegister();

    mpEngine->load(QUrl(QStringLiteral("qrc:/views/main.qml")));
    if (mpEngine->rootObjects().isEmpty())
    {
        throw std::runtime_error("failed to load qrc");
    }
}

void App::qmlRegister()
{
    qmlRegisterType<Cursor>("cursor", 1, 0, "Cursor");
    qmlRegisterType<Board>("board", 1, 0, "Board");
    qmlRegisterType<NodeValueFinder>("noderesults", 1, 0, "Result");

    qmlRegisterType<PrintNode>("printnode", 1, 0, "PrintNode");

    qmlRegisterType<VarNode>("varnode", 1, 0, "VarNode");

    qmlRegisterType<AddNode>("addnode", 1, 0, "AddNode");
    qmlRegisterType<SubtractNode>("subtractnode", 1, 0, "SubtractNode");
    qmlRegisterType<MultiplyNode>("multiplynode", 1, 0, "MultiplyNode");
    qmlRegisterType<DivideNode>("dividenode", 1, 0, "DivideNode");
    qmlRegisterType<ModuloNode>("modulonode", 1, 0, "ModuloNode");
}

void App::run()
{
    std::cout << "Welcome " PROJECT_NAME " version: " PROJECT_VERSION "\n";
    mpApp->exec();
}

App::~App()
{
    delete mpEngine;
    delete mpApp;
}
}