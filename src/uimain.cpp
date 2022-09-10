#include "uimain.h"
#include "config.h"
#include <QGridLayout>
#include <QSettings>
#include <QMenuBar>
#include <QApplication>
#include <QMessageBox>

UiMain::UiMain(bool isServerRunning, int portNumber, QWidget *parent) : QWidget(parent)
{

    QLabel *labelVersion = new QLabel(tr("Version %1").arg(PROJECT_VER));

    labelServerStatus = new QLabel(tr("Status: Running")); //NOLINT
    if (!isServerRunning){
        labelServerStatus->setText(tr("Status: Not running"));
    }

    QLabel *labelPortNumber = new QLabel(tr("Port number:"));
    namePortNumber = new QLineEdit; //NOLINT
    namePortNumber->setText(QString::number(portNumber));

    saveAndQuitButton = new QPushButton(tr("Save and quit")); //NOLINT
    saveAndQuitButton->show();

    connect(saveAndQuitButton, &QPushButton::clicked,
            this, &UiMain::saveAndQuit);

    //! [constructor and input fields]

    //! [layout]
    QGridLayout *mainLayout = new QGridLayout; //NOLINT
    mainLayout->addWidget(labelServerStatus, 0, 0, 1, 2);
    mainLayout->addWidget(labelPortNumber, 1, 0, Qt::AlignTop);
    mainLayout->addWidget(namePortNumber, 1, 1);    
    mainLayout->addWidget(labelVersion, 2, 0);
    mainLayout->addWidget(saveAndQuitButton, 2, 1);
    //! [layout]

    //![setting the layout]
    setLayout(mainLayout);
    setWindowTitle(tr("Midi Router Server"));


    QMenuBar* menuBar = new QMenuBar(); //NOLINT
    QMenu *fileMenu = new QMenu("File");
    QAction *aboutAct = new QAction(tr("About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, &QAction::triggered, this, &UiMain::about);

    QAction *aboutQtAct = new QAction(tr("About Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, &QAction::triggered, this, &QApplication::aboutQt);

    QAction *quitQtAct = new QAction(tr("Quit"), this);
    quitQtAct->setStatusTip(tr("Quit"));
    connect(quitQtAct, &QAction::triggered, this, &QApplication::quit);

    fileMenu->addAction(aboutAct);
    fileMenu->addAction(aboutQtAct);
    fileMenu->addAction(quitQtAct);
    menuBar->addMenu(fileMenu);

    mainLayout->setMenuBar(menuBar);
}

void UiMain::saveAndQuit()
{
    QSettings settings("shemeshg", "MidiRouter");
    int serverPortToSet = namePortNumber->text().toInt();
    settings.setValue("server/port", serverPortToSet);
    close();
}

void UiMain::about()
{
    QMessageBox::about(this, tr("About Menu"),
            tr("Version %1").arg(PROJECT_VER) );
}
