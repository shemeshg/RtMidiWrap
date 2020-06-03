#ifndef MAINCLASS_H
#define MAINCLASS_H
#include <QApplication>

class MainClass
{
public:    
    MainClass(int argc, char* argv[]);
    int connectAndExec();
private:
    int port = 12345;
    QApplication app;
    void parseParams();

};

#endif // MAINCLASS_H
