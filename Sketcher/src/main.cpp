#include "stdafx.h"
#include "Sketcher.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Sketcher window;
    window.show();
    return app.exec();
}
