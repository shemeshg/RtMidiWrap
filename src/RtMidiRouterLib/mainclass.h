#pragma once
#include <QApplication>

namespace {
    constexpr int defaultPort = 12345;
}

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
    int port = defaultPort;
    bool serverIsRunning = false;
    QApplication &app;
    void parseParams();

};


