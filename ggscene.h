#ifndef GGSCENE_H
#define GGSCENE_H

#include <QGraphicsView>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class GGScene: public QGraphicsView
{
    friend class MainWindow;
public:
    GGScene(int score);
private:
    QLabel* GGprompt;
    QLabel* finalScorePrompt;
    QLabel* scoreDisplay;
    QPushButton* restartButton;
};

#endif // GGSCENE_H
