#ifndef PROGRASSLIST_H
#define PROGRASSLIST_H
#include "prograssnode.h"
#include "stopwatch.h"
#include "optioneditbox.h"

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
#include <QString>

class mainWidget;

class prograssList : public QWidget
{
    Q_OBJECT
public:
    prograssList(mainWidget * p = 0);
    void removeNode(int no);

signals:
    void timeLimitSignal(int);
    void mentSettingSignal(QString, QString, bool);

public slots:
    void addNode();
    void itemSelect(QListWidgetItem *item);

    void itemStart();
    void itemFix();
    void itemDelete();
    void setNodeValue(QString name, int time, QString annunce, QString memo, bool sMent, bool eMent, bool tMent);

    void ShowContextMenu(const QPoint&);
private:

    int nodeCounter;
    int nodeFocuse;

    QListWidget* list;
    optionEditBox* editBox;
    QPushButton* addButton;
    QMenu* submenu;
    mainWidget* parent;
};

#endif // PROGRASSLIST_H
