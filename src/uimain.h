#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>

class UiMain : public QWidget
{
    Q_OBJECT
public:
    explicit UiMain(bool isServerRunning, int portNumber, QWidget *parent = nullptr);
private:
    QLineEdit *namePortNumber;
    QLabel *labelServerStatus;
    QPushButton *saveAndQuitButton;
signals:
public slots:
    void saveAndQuit();

};


