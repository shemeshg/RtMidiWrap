#include "mainclass.h"

#include "./libs/websocket/websocketclientwrapper.h"
#include "./libs/websocket/websockettransport.h"

#include <QCoreApplication>
#include <QWebChannel>
#include <QWebSocketServer>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <QSettings>

#include "src/webchannel/wcmidiout.h"
#include "src/webchannel/wcmidiin.h"
#include "src/webchannel/wcuserdata.h"
#include "src/webchannel/virtualinout.h"

#include "uimain.h"

using namespace Webchannel;

MainClass::MainClass(QApplication &app):app{app}
{
    parseParams();
}

void MainClass::parseParams()
{

    QSettings settings("shemeshg", "MidiRouter");
    port = settings.value("server/port", 12345).toInt();
    cout<<"Server port is "<<port<< "\n";

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets server");
    parser.addHelpOption();

    QCommandLineOption portOption(QStringList() << "p" << "port",
                                  QCoreApplication::translate("main", "Port for midi server [default: 12345]."),
                                  QCoreApplication::translate("main", "port"), QLatin1String(""));
    parser.addOption(portOption);


    parser.process(app);

    if (!parser.value(portOption).toStdString().empty()){
        int serverPortToSet = parser.value(portOption).toInt();
        settings.setValue("server/port", serverPortToSet);
        cout<<"Server port is set to " << serverPortToSet<< " in configuration file\n";
        port = serverPortToSet;
    }

}


int MainClass::connectAndExec(){
    bool serverIsRunning = false;
    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"),
                            QWebSocketServer::NonSecureMode);
    if (!server.listen(QHostAddress::Any, port)) {
        //qFatal("Failed to open web socket server.");
        serverIsRunning = false;
    } else {
        serverIsRunning = true;
    }

    if (!serverIsRunning){
        UiMain uimain(serverIsRunning, port);
        uimain.show();
        return app.exec();
    }

    // wrap WebSocket clients in QWebChannelAbstractTransport objects
    WebSocketClientWrapper clientWrapper(&server);

    // setup the channel
    QWebChannel channel;
    QObject::connect(&clientWrapper, &WebSocketClientWrapper::clientConnected,
                     &channel, &QWebChannel::connectTo);

    // setup the dialog and publish it to the QWebChannel
    WcMidiOut* wcmidiout = new WcMidiOut(&app);
    channel.registerObject(QStringLiteral("wcmidiout"), wcmidiout);
    WcMidiIn* wcmidiin = new WcMidiIn(&app);
    channel.registerObject(QStringLiteral("wcmidiin"), wcmidiin);
    WcUserData* wcuserdata = new WcUserData(&app);
    channel.registerObject(QStringLiteral("wcuserdata"), wcuserdata);
    QObject::connect(wcuserdata, SIGNAL(applicationQuitSignal()), &app, SLOT(quit()));


    UiMain uimain(serverIsRunning, port);
    uimain.showMinimized();
    return app.exec();
}
