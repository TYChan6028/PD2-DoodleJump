#include "ggscene.h"

GGScene::GGScene(int score)
{
    setFixedSize(600, 900);
    // game over prompt
    GGprompt = new QLabel("GAME OVER", this);
    QFont font1("Arial", 35, QFont::Black);
    GGprompt->setFont(font1);
    GGprompt->setAlignment(Qt::AlignCenter);
    GGprompt->setGeometry(100, 200, 400, 200);
    // your final score prompt
    finalScorePrompt = new QLabel("YOUR FINAL SCORE IS", this);
    QFont font2("Arial", 15, QFont::Black);
    finalScorePrompt->setFont(font2);
    finalScorePrompt->setAlignment(Qt::AlignCenter);
    finalScorePrompt->setGeometry(100, 300, 400, 200);
    // display final score
    scoreDisplay = new QLabel(this);
    scoreDisplay->setGeometry(0, 400, 600, 300);
    scoreDisplay->setNum(score);
    QFont font("Arial", 50, QFont::Normal);
    scoreDisplay->setFont(font);
    scoreDisplay->setAlignment(Qt::AlignCenter);
    // add restart button
    restartButton = new QPushButton("RESTART", this);
    restartButton->setGeometry(200, 730, 200, 50);
}
