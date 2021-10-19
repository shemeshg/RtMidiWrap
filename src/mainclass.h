#pragma once
#include <QApplication>

class MainClass
{
public:    
    MainClass(QApplication &app);
    void connectAndExec();
    int getPort(){
        return port;
    }
    bool getServerIsRunning(){
        return serverIsRunning;
    }
private:
    int port = 12345;
    bool serverIsRunning = false;
    QApplication &app;
    void parseParams();

};


