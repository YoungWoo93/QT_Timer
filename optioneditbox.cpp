#include "optioneditbox.h"

#include <iostream>

optionEditBox::optionEditBox()
{
    editBox = new QWidget();
    editBox->resize(500,300);
    QGridLayout* layout = new QGridLayout();

    layout->addWidget(new QLabel("명칭"), 0, 0, 1, 1);
    layout->addWidget(new QLabel("시간"), 1, 0, 1, 1);
    layout->addWidget(new QLabel("시작멘트"), 2, 0, 1, 1);
    layout->addWidget(new QLabel("종료멘트"), 3, 0, 1, 1);

    nameEdit = new QTextEdit();
    timeEdit = new QTextEdit();
    annoEdit = new QTextEdit();
    memoEdit = new QTextEdit();

    startMentCheck = new QCheckBox("시작멘트 출력");
    endMentCheck = new QCheckBox("종료멘트 출력");
    timeMentCheck = new QCheckBox("시간멘트 출력");

    submit = new QPushButton("ok");

    layout->addWidget(nameEdit, 0, 1, 1, 3);
    layout->addWidget(timeEdit, 1, 1, 1, 3);
    layout->addWidget(annoEdit, 2, 1, 1, 3);
    layout->addWidget(memoEdit, 3, 1, 1, 3);

    layout->addWidget(startMentCheck, 4, 0, 1, 1);
    layout->addWidget(endMentCheck, 4, 1, 1, 1);
    layout->addWidget(timeMentCheck, 4, 2, 1, 1);
    layout->addWidget(submit, 4, 3, 1, 1);

    editBox->setLayout(layout);
}

void optionEditBox::inputButton(void)
{
    emit inputButtonSignal(nameEdit->toPlainText(),
                           timeEdit->toPlainText().toInt(),
                           annoEdit->toPlainText(),
                           memoEdit->toPlainText(),
                           startMentCheck->isChecked(),
                           endMentCheck->isChecked(),
                           timeMentCheck->isChecked());

    this->editBox->close();
}
