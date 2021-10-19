#include "src/mainclass.h"
#include "src/uimain.h"
#include <QIcon>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/icon.png"));
    MainClass mc(app);
    mc.connectAndExec();



    UiMain uimain(mc.getServerIsRunning(), mc.getPort());
    if (mc.getServerIsRunning()){
        uimain.showMinimized();
    } else{
        uimain.show();
    }
    return app.exec();
}

