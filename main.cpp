#include "src/mainclass.h"
#include <QIcon>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icon.png"));
    MainClass mc(app);
    return mc.connectAndExec();
}

