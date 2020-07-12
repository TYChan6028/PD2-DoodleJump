#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(815, 900);
    launchGame();
    launchSideMenu();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::launchGame()
{
    game = new Game();
    setCentralWidget(game);
    game->setFocus();
    connect(game, &Game::gameOver, this, &MainWindow::genGameOverScene);
}

void MainWindow::launchSideMenu()
{
    delete sideMenu;
    sideMenu = new SideMenu();
    addDockWidget(Qt::RightDockWidgetArea, sideMenu);
    connect(game->player, &Player::currentScore, sideMenu, &SideMenu::changeScore);
    connect(sideMenu->pauseButton, &QPushButton::clicked, game->player, &Player::pausePlayer);
    connect(game->player, &Player::resumeGame, this, &MainWindow::onSMPauseClicked);
    connect(sideMenu->quitButton, &QPushButton::clicked, this, &MainWindow::close);
    game->setFocus();
}

void MainWindow::onSMPauseClicked()
{
    // return focus to game
    centralWidget()->setFocus();
}

void MainWindow::genGameOverScene(int score)
{
    delete game;
    game = nullptr;
    // load game over scene
    finishMenu = new GGScene(score);
    setCentralWidget(finishMenu);
    connect(finishMenu->restartButton, &QPushButton::clicked, this, &MainWindow::launchGame);
    connect(finishMenu->restartButton, &QPushButton::clicked, this, &MainWindow::launchSideMenu);
}
