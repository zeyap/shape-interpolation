#include "renderarea.h"
#include "window.h"

#include <QtWidgets>
#include <QGridLayout>

const int IdRole = Qt::UserRole;

Window::Window()
{
    renderArea = new RenderArea;

    //spinbox
    numberSpinBox = new QSpinBox;
    numberSpinBox->setRange(10, 50);
    numberLabel = new QLabel(tr("Interpolation number:"));
    numberLabel->setBuddy(numberSpinBox);

    //speed slider
    speedSlider=new QSlider(Qt::Horizontal);
    speedSlider->setMinimum(1);
    speedSlider->setMaximum(5);
    speedLabel= new QLabel(tr("Speed"));
    speedLabel->setBuddy(speedSlider);

    //drawLine button
    drawShapeButton = new QPushButton(tr("Draw Shape"));

    //mode combobox
    modeComboBox = new QComboBox();
    modeComboBox->addItem(tr("linear"));
    modeComboBox->addItem(tr("vector"));
    modeComboBox->addItem(tr("clockwise"));
    modeComboBox->addItem(tr("counterClock"));

    //play button
    clearButton = new QPushButton(tr("Clear"));

    //play button
    playButton = new QPushButton(tr("Play"));


    connect(numberSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(numberChanged(int)));
    connect(speedSlider, SIGNAL(valueChanged(int)),
            this, SLOT(frequencyChanged(int)));

    connect(drawShapeButton, SIGNAL(clicked()),
            this, SLOT(drawShape()));
    connect(clearButton, SIGNAL(clicked()),
            this, SLOT(clear()));
    connect(modeComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(changeMode(int)));
    connect(playButton, SIGNAL(clicked()),
            this, SLOT(play()));

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setRowStretch(0,renderArea->height);
    mainLayout->setColumnStretch(0, 1);
    //Columns with a higher stretch factor take more of the available space.
    //default is 0
    mainLayout->setColumnStretch(3, 1);
    resize(500,500);
    mainLayout->addWidget(renderArea, 0, 0, renderArea->height, renderArea->width);

    mainLayout->addWidget(numberLabel, 2, 0, Qt::AlignRight);
    mainLayout->addWidget(numberSpinBox, 2, 1);

    mainLayout->addWidget(drawShapeButton, 2, 3);
    mainLayout->addWidget(clearButton, 3, 3);

    mainLayout->addWidget(speedLabel, 1, 0, Qt::AlignRight);
    mainLayout->addWidget(speedSlider, 1, 1);

    mainLayout->addWidget(modeComboBox, 2, 4);
    mainLayout->addWidget(playButton, 3, 4);
    setLayout(mainLayout);

    setWindowTitle(tr("E2"));
}

void Window::numberChanged(int value){
    renderArea->setNumber(value);
}

void Window::frequencyChanged(int value){
    renderArea->setSpeed((float)value);
}

void Window::drawShape(){
    renderArea->drawShape();
}
void Window::clear(){
    renderArea->clear();
}
void Window::changeMode(int mode){
    renderArea->changeMode(mode);
}
void Window::play(){
    renderArea->play();
}
