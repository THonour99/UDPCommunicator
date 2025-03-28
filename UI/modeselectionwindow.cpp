#include "ModeSelectionWindow.h"
#include "ui_modeselectionwindow.h"

ModeSelectionWindow::ModeSelectionWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ModeSelectionWindow)
{
    ui->setupUi(this);
    setWindowTitle("选择通信模式");

    connect(ui->localButton, &QPushButton::clicked, this, &ModeSelectionWindow::onLocalModeSelected);
    connect(ui->remoteButton, &QPushButton::clicked, this, &ModeSelectionWindow::onRemoteModeSelected);
}

ModeSelectionWindow::~ModeSelectionWindow()
{
    delete ui;
}

void ModeSelectionWindow::onLocalModeSelected()
{
    emit modeSelected(LocalMode);
}

void ModeSelectionWindow::onRemoteModeSelected()
{
    emit modeSelected(RemoteMode);
}
