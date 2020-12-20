#include "optioneditbox.h"

#include <iostream>

optionEditBox::optionEditBox()
{
    editBox = new QWidget();
    editBox->resize(500,300);
    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel("name"), 0, 0, 1, 1);
    layout->addWidget(new QLabel("time"), 1, 0, 1, 1);
    layout->addWidget(new QLabel("announc"), 2, 0, 1, 1);
    layout->addWidget(new QLabel("memo"), 3, 0, 1, 1);

    nameEdit = new QTextEdit();
    timeEdit = new QTextEdit();
    annoEdit = new QTextEdit();
    memoEdit = new QTextEdit();

    submit = new QPushButton("ok");

    layout->addWidget(nameEdit, 0, 1, 1, 1);
    layout->addWidget(timeEdit, 1, 1, 1, 1);
    layout->addWidget(annoEdit, 2, 1, 1, 1);
    layout->addWidget(memoEdit, 3, 1, 1, 1);
    layout->addWidget(submit, 4, 0, 1, 1);

    editBox->setLayout(layout);
}

void optionEditBox::inputButton(void)
{
    emit inputButtonSignal(nameEdit->toPlainText(), timeEdit->toPlainText().toInt(), annoEdit->toPlainText(), memoEdit->toPlainText());
    this->editBox->close();
}
