#ifndef OPTIONEDITBOX_H
#define OPTIONEDITBOX_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

#include <QPainter>
#include <QColor>
#include <QPen>
#include <QBrush>

#include <QMouseEvent>

#include <QPushButton>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMenu>
#include <QTextEdit>
#include <QCheckBox>
class optionEditBox : public QWidget
{
    Q_OBJECT
public:
    optionEditBox();
    QWidget* editBox;
    QTextEdit* nameEdit;
    QTextEdit* timeEdit;
    QTextEdit* annoEdit;
    QTextEdit* memoEdit;
    QPushButton* submit;
    QCheckBox* startMentCheck;
    QCheckBox* endMentCheck;
    QCheckBox* timeMentCheck;
public slots:
    void inputButton(void);

signals:
    void inputButtonSignal(QString, int, QString, QString, bool, bool, bool);



};

#endif // OPTIONEDITBOX_H
