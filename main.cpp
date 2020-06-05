#include "src/mainclass.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainClass mc(app);
    return mc.connectAndExec();
}

