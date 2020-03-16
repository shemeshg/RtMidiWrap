#include "./libs/websocket/websocketclientwrapper.h"
#include "./libs/websocket/websockettransport.h"

#include <QCoreApplication>
#include <QWebChannel>
#include <QWebSocketServer>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>

#include "src/webchannel/wcmidiout.h"
#include "src/webchannel/wcmidiin.h"
#include "src/webchannel/wcuserdata.h"



using namespace Webchannel;

RtMidiOut *midiout;
void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
{
    UNUSED(deltatime);
    UNUSED(userData);
  midiout->sendMessage(message);
}


void openVirtualPort(string portname){
    RtMidiIn *midiin = new RtMidiIn();
    midiin->openVirtualPort(portname);
    midiout = new RtMidiOut();
    midiout->openVirtualPort(portname);
    midiin->setCallback( &mycallback );

    char input;
    std::cin.get(input);
}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets server");
    parser.addHelpOption();

    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for midi server [default: 12345]."),
            QCoreApplication::translate("main", "port"), QLatin1String("12345"));
    parser.addOption(portOption);

    QCommandLineOption virtualportOption(QStringList() << "v" << "virtualport",
            QCoreApplication::translate("main", "run virtual port (will not run server)"),
            QCoreApplication::translate("main", "virtualport"), QLatin1String(""));
    parser.addOption(virtualportOption);

    parser.process(app);

    string virtualPortname = parser.value(virtualportOption).toStdString();
    if (! virtualPortname.empty()){
        openVirtualPort(virtualPortname);
        return 0;
    }

    int port = parser.value(portOption).toInt();



    QWebSocketServer server(QStringLiteral("QWebChannel Standalone Example Server"),
                            QWebSocketServer::NonSecureMode);
    if (!server.listen(QHostAddress::Any, port)) {
        qFatal("Failed to open web socket server.");
        return 1;
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
    return app.exec();



}

