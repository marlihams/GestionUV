#include "mainutprofiler.h"
#include <QApplication>
#include"UTProfiler.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainUTProfiler &w=MainUTProfiler::getUTProfiler();

    w.show();
    return a.exec();
}
