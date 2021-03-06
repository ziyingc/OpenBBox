#include <QtWidgets>

#include "subjectdialog.h"

SubjectDialog::SubjectDialog(QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);


    int frameStyle = QFrame::Sunken | QFrame::Panel;

    integerLabel = new QLabel;
    integerLabel->setFrameStyle(frameStyle);
    QPushButton *integerButton = new QPushButton(tr("integer"));

    doubleLabel = new QLabel;
    doubleLabel->setFrameStyle(frameStyle);
    QPushButton *doubleButton = new QPushButton(tr("double"));

    itemLabel = new QLabel;
    itemLabel->setFrameStyle(frameStyle);
    QPushButton *itemButton = new QPushButton(tr("item"));

    textLabel = new QLabel;
    textLabel->setFrameStyle(frameStyle);
    QPushButton *textButton = new QPushButton(tr("Tag"));

    QPushButton *okButton = new QPushButton(tr("OK"));


    connect(integerButton, SIGNAL(clicked()), this, SLOT(setInteger()));
    connect(doubleButton, SIGNAL(clicked()), this, SLOT(setDouble()));
    connect(itemButton, SIGNAL(clicked()), this, SLOT(setItem()));
    connect(textButton, SIGNAL(clicked()), this, SLOT(setText()));
    connect(okButton, SIGNAL(clicked()), this, SLOT(sendSignal()));


    QWidget *page = new QWidget;
    QGridLayout *layout = new QGridLayout(page);
    layout->setColumnStretch(0, 1);
    layout->setColumnMinimumWidth(0, 250);
    layout->addWidget(integerButton, 3, 1);
    layout->addWidget(integerLabel, 3, 0);
    layout->addWidget(doubleButton, 1, 1);
    layout->addWidget(doubleLabel, 1, 0);
    layout->addWidget(itemButton, 2, 1);
    layout->addWidget(itemLabel, 2, 0);
    layout->addWidget(textButton, 0, 1);
    layout->addWidget(textLabel, 0, 0);

    layout->addWidget(okButton, 4, 1);
    //layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Ignored, QSizePolicy::MinimumExpanding), 4, 0);

    mainLayout->addWidget(page);

    setWindowTitle(tr("Subject Info."));
}

void SubjectDialog::setInteger()
{
//! [0]
    bool ok;
    int i = QInputDialog::getInt(this, tr("QInputSubjectDialog::getInteger()"),
                                 tr("Percentage:"), 25, 0, 100, 1, &ok);
    if (ok)
        integerLabel->setText(tr("%1%").arg(i));
//! [0]
}

void SubjectDialog::setDouble()
{
//! [1]
    bool ok;
    double d = QInputDialog::getDouble(this, tr("QInputSubjectDialog::getDouble()"),
                                       tr("Amount:"), 37.56, -10000, 10000, 2, &ok);
    if (ok)
        doubleLabel->setText(QString("$%1").arg(d));
//! [1]
}

void SubjectDialog::setItem()
{
//! [2]
    QStringList items;
    items << tr("Spring") << tr("Summer") << tr("Fall") << tr("Winter");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("QInputSubjectDialog::getItem()"),
                                         tr("Season:"), items, 0, false, &ok);
    if (ok && !item.isEmpty())
        itemLabel->setText(item);
//! [2]
}

void SubjectDialog::setText()
{
//! [3]
    bool ok;
    QString text = QInputDialog::getText(this, tr("QInputSubjectDialog::getText()"),
                                         tr("Tag:"), QLineEdit::Normal,
                                         "", &ok);

    if (ok && !text.isEmpty())
    {
        textLabel->setText(text);
        subject.name = text;
    }else {
        subject.name = "";
    }

//! [3]
}

void SubjectDialog::sendSignal(){
    if(!subject.name.isEmpty()){
        subject.status = true;
        emit processPassSubinfo(subject);
        close();
    }
}




