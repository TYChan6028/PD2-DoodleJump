#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "game.h"
#include "sidemenu.h"
#include "ggscene.h"
#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void launchGame();
    void launchSideMenu();
    void onSMPauseClicked();
    void genGameOverScene(int score);
private:
    Ui::MainWindow *ui;
    Game* game = nullptr;
    GGScene* finishMenu = nullptr;
    SideMenu* sideMenu = nullptr;
    QLabel* title = nullptr;

};

#endif // MAINWINDOW_H
