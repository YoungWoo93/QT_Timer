#include "prograsslist.h"

prograssList::prograssList(mainWidget * p)
{
    list = new QListWidget();
    addButton = new QPushButton("추가");
    addButton->setMinimumHeight(100);
    nodeCounter = 0;
    nodeFocuse = -1;
    parent = p;
    editBox = new optionEditBox();

    submenu = new QMenu();

    QAction *startAction = new QAction(tr("선택"), this);
    connect(startAction, SIGNAL(triggered()), SLOT(itemStart()));
    submenu->addAction(startAction);

    QAction *fixAction = new QAction(tr("수정"), this);
    connect(fixAction, SIGNAL(triggered()), SLOT(itemFix()));
    submenu->addAction(fixAction);

    QAction *deleteAction = new QAction(tr("삭제"), this);
    connect(deleteAction, SIGNAL(triggered()), SLOT(itemDelete()));
    submenu->addAction(deleteAction);




    list->setFlow(QListWidget::LeftToRight);
    list->setAutoScroll(true);

    QHBoxLayout * hBoxLayout = new QHBoxLayout(this);
    hBoxLayout->addWidget(list);
    hBoxLayout->addWidget(addButton);

    connect(addButton, SIGNAL(clicked()), SLOT(addNode()));
    connect(editBox, SIGNAL(inputButtonSignal(QString, int, QString, QString)), this, SLOT(setNodeValue(QString, int, QString, QString)));
//    connect(editBox->submit, SIGNAL(clicked()), editBox, SLOT(inputButton()));
    connect(editBox->submit,&QPushButton::clicked,editBox,&optionEditBox::inputButton);
    connect(list, SIGNAL(itemClicked(QListWidgetItem *)), SLOT(itemSelect(QListWidgetItem *)));
}

void prograssList::addNode()
{
    prograssNode* node = new prograssNode(nodeCounter++);
    node->setContextMenuPolicy(Qt::CustomContextMenu);
    QListWidgetItem* item = new QListWidgetItem();
    item->setSizeHint(QSize(105,105));

    list->addItem(item);
    list->setItemWidget(item, node);

    connect(node, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(ShowContextMenu(const QPoint&)));


}

void prograssList::itemSelect(QListWidgetItem * item)
{
    if(nodeFocuse != -1)
    {
        prograssNode* temp = (prograssNode*)list->itemWidget(list->item(nodeFocuse));
        temp->click();
    }


    nodeFocuse = list->row(item);
    prograssNode* node = (prograssNode*)list->itemWidget(item);


    node->click();
    int time = node->getTime();
    QString ment = node->getAnnouncement();

    emit mentSettingSignal(ment);
    emit timeLimitSignal(time);
}

void prograssList::itemStart()
{
    emit itemSelect(list->selectedItems()[0]);
}

void prograssList::itemFix()
{
    prograssNode* node = (prograssNode*)list->itemWidget(list->item(nodeFocuse));

    editBox->nameEdit->setText(node->getName());
    editBox->timeEdit->setText(QString::number(node->getTime()));
    editBox->annoEdit->setText(node->getAnnouncement());
    editBox->memoEdit->setText(node->getMemo());



    editBox->editBox->show();

}

void prograssList::itemDelete()
{
    int target = list->row(list->selectedItems()[0]);
    list->takeItem(target);

    if(target == nodeFocuse)
        nodeFocuse = -1;
    else
        nodeFocuse--;
}



void prograssList::ShowContextMenu(const QPoint& pos)
{
    QPoint globalPos = list->mapToGlobal(pos);	// Map the global position to the userlist

    int target = list->row(list->selectedItems()[0]);
    list->item(target)->setSelected(true);

    globalPos.setX(globalPos.x()+105*target);
    submenu->exec(globalPos);
}

void prograssList::setNodeValue(QString name, int time, QString annunce, QString memo)
{
    prograssNode* node = (prograssNode*)list->itemWidget(list->selectedItems()[0]);

    node->setName(name);
    node->setTime(time);
    node->setAnnouncement(annunce);
    node->setMemo(memo);
}

