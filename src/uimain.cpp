#include "uimain.h"
#include <QGridLayout>
#include <QSettings>

UiMain::UiMain(bool isServerRunning, int portNumber, QWidget *parent) : QWidget(parent)
{

    QLabel *labelVersion = new QLabel(tr("v1.2.0"));

    labelServerStatus = new QLabel(tr("Status: Running"));
    if (!isServerRunning){
        labelServerStatus->setText(tr("Status: Not running"));
    }

    QLabel *labelPortNumber = new QLabel(tr("Port number:"));
    namePortNumber = new QLineEdit;
    namePortNumber->setText(QString::number(portNumber));

    saveAndQuitButton = new QPushButton(tr("Save and quit"));
    saveAndQuitButton->show();

    connect(saveAndQuitButton, &QPushButton::clicked,
            this, &UiMain::saveAndQuit);

    //! [constructor and input fields]

    //! [layout]
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(labelServerStatus, 0, 0, 1, 2);
    mainLayout->addWidget(labelPortNumber, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(namePortNumber, 1, 1);    
    mainLayout->addWidget(labelVersion, 2, 0);
    mainLayout->addWidget(saveAndQuitButton, 2, 1);
    //! [layout]

    //![setting the layout]
    setLayout(mainLayout);
    setWindowTitle(tr("Midi Router Server"));
}

void UiMain::saveAndQuit()
{
    QSettings settings("shemeshg", "MidiRouter");
    int serverPortToSet = namePortNumber->text().toInt();
    settings.setValue("server/port", serverPortToSet);
    close();
}
