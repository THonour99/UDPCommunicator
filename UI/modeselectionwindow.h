#ifndef MODESELECTIONWINDOW_H
#define MODESELECTIONWINDOW_H

#include <QWidget>
#include "AppManager.h"

namespace Ui {
class ModeSelectionWindow;
}

class ModeSelectionWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ModeSelectionWindow(QWidget *parent = nullptr);
    ~ModeSelectionWindow();

signals:
    void modeSelected(CommunicationMode mode);

private slots:
    void onLocalModeSelected();
    void onRemoteModeSelected();

private:
    Ui::ModeSelectionWindow *ui;
};

#endif // MODESELECTIONWINDOW_H
