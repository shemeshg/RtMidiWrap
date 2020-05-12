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


using namespace Webchannel;



int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    QSettings settings("shemeshg", "MidiRouter");
    int port = settings.value("server/port", 12345).toInt();
    cout<<"Server port is "<<port<< "\n";

    QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets server");
    parser.addHelpOption();

    QCommandLineOption portOption(QStringList() << "p" << "port",
            QCoreApplication::translate("main", "Port for midi server [default: 12345]."),
            QCoreApplication::translate("main", "port"), QLatin1String(""));
    parser.addOption(portOption);

    QCommandLineOption virtualportOption(QStringList() << "v" << "virtualport",
            QCoreApplication::translate("main", "run virtual port (will not run server)"),
            QCoreApplication::translate("main", "virtualport"), QLatin1String(""));
    parser.addOption(virtualportOption);

    parser.process(app);

    string virtualPortname = parser.value(virtualportOption).toStdString();
    if (! virtualPortname.empty()){
        addVirtualInOutPort(virtualPortname);
        char input;
        std::cin.get(input);
        return 0;
    }

    if (!parser.value(portOption).toStdString().empty()){
        int serverPortToSet = parser.value(portOption).toInt();
        settings.setValue("server/port", serverPortToSet);
        cout<<"Server port is set to " << serverPortToSet<< " in configuration file, start server again\n";
        return 0;
    }




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

