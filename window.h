#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <stdio.h>

class QLabel;
class QPushButton;
class QSpinBox;
class QSlider;

class RenderArea;

class Window : public QWidget
{
    Q_OBJECT

public:
    Window();

private slots:

    void frequencyChanged(int value);
    void numberChanged(int value);

    void drawShape();
    void clear();
    void play();

private:
    RenderArea *renderArea;

    QLabel *numberLabel;
    QSpinBox *numberSpinBox;

    QLabel *speedLabel;
    QSlider *speedSlider;

    QPushButton *drawShapeButton;

    QPushButton *clearButton;

    QPushButton *playButton;

};

#endif // WINDOW_H
