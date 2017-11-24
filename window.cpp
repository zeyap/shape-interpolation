#include "renderarea.h"
#include "window.h"

#include <QtWidgets>
#include <QGridLayout>

const int IdRole = Qt::UserRole;
static QLabel* statusLabel;

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
    speedLabel= new QLabel(tr("FPS"));
    speedLabel->setBuddy(speedSlider);

    //drawLine button
    drawShapeButton = new QPushButton(tr("Draw Shape"));

    //mode combobox
    modeComboBox = new QComboBox();
    modeComboBox->addItem(tr("linear"));
    modeComboBox->addItem(tr("vector"));
    modeComboBox->addItem(tr("clockwise"));
    modeComboBox->addItem(tr("counterClock"));

    clearButton = new QPushButton(tr("Clear"));
    saveButton = new QPushButton(tr("Save"));

    //play button
    playButton = new QPushButton(tr("Play"));

    statusLabel=new QLabel(tr(" "));


    connect(numberSpinBox, SIGNAL(valueChanged(int)),
            this, SLOT(numberChanged(int)));
    connect(speedSlider, SIGNAL(valueChanged(int)),
            this, SLOT(frequencyChanged(int)));

    connect(drawShapeButton, SIGNAL(clicked()),
            this, SLOT(drawShape()));
    connect(clearButton, SIGNAL(clicked()),
            this, SLOT(clear()));
    connect(saveButton, SIGNAL(clicked()),
            this, SLOT(save()));
    connect(modeComboBox,SIGNAL(currentIndexChanged(int)),
            this,SLOT(changeMode(int)));
    connect(playButton, SIGNAL(clicked()),
            this, SLOT(play()));

    QGridLayout *mainLayout = new QGridLayout;

    mainLayout->setRowStretch(0,renderArea->height);
    //Columns with a higher stretch factor take more of the available space.
    //default is 0

    mainLayout->setColumnStretch(1, 1);
    mainLayout->setColumnStretch(2, 1);
    mainLayout->setColumnStretch(3, 1);
    mainLayout->setColumnStretch(4, 1);
    resize(800,600);
    mainLayout->addWidget(renderArea, 0, 0, renderArea->height, renderArea->width);

    mainLayout->addWidget(speedLabel, 2, 0, Qt::AlignRight);
    mainLayout->addWidget(speedSlider, 2, 1);

    mainLayout->addWidget(numberLabel, 3, 0, Qt::AlignRight);
    mainLayout->addWidget(numberSpinBox, 3, 1);

    mainLayout->addWidget(drawShapeButton, 2, 2);
    mainLayout->addWidget(saveButton, 2, 4);
    mainLayout->addWidget(clearButton, 3, 4);

    mainLayout->addWidget(modeComboBox, 2, 3);
    mainLayout->addWidget(playButton, 3, 3);

    mainLayout->addWidget(statusLabel,1,0);

    setLayout(mainLayout);

    setWindowTitle(tr("E2"));
    setStatus("");


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
    setStatus("");
}
void Window::changeMode(int mode){
    renderArea->changeMode(mode);
}
void Window::play(){
    renderArea->play();
}

void Window::save(){
    renderArea->save();
}

void Window::setStatus(QString str){
    statusLabel->setText(str);
}
