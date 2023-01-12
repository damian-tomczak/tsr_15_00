#include "resultparser.h"

#pragma warning( disable : 4996 )

QString ResultParser::orderResult(QString string)
{
    QString path{ QString("%1/tsr_output.py").arg(
        QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)) };

    QFile file{ path };

    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream stream(&file);

        QString import1{ "import math\n" };
        QString addFunc{ "def add(a,b):\n return a+b\n" };
        QString subFunc{ "def subtract(a,b):\n return a-b\n" };
        QString mulFunc{ "def multiply(a,b):\n return a*b\n" };
        QString divFunc{ "def divide(a,b):\n return a/b\n" };
        QString moduFunc{ "def modulo(a,b):\n return a%b\n" };

        if (string.indexOf("math") >= 0)
        {
            stream << import1 << "\n";
        }
        if (string.indexOf("add") >= 0)
        {
            stream << addFunc << "\n";
        }
        if (string.indexOf("subtract") >= 0)
        {
            stream << subFunc << "\n";
        }
        if (string.indexOf("multiply") >= 0)
        {
            stream << mulFunc << "\n";
        }
        if (string.indexOf("divide") >= 0)
        {
            stream << divFunc << "\n";
        }
        if (string.indexOf("modulo") >= 0)
        {
            stream << moduFunc << "\n";
        }

        stream << "\n" << string << "\n";
    }

    file.close();

    QProcess q;
    q.start("python " + path);
    q.waitForFinished();
    QString output{ q.readAllStandardOutput() };

    if (output.size() <= 0)
    {
        output = "ERR";
        output += q.readAllStandardError();
    }

    return output;

}


