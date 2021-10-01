#pragma once
#include <QApplication>

class MainClass
{
public:    
    MainClass(QApplication &app);
    int connectAndExec();
private:
    int port = 12345;
    QApplication &app;
    void parseParams();

};


