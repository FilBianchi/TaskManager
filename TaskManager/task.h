#ifndef TASK_H
#define TASK_H

#include "treeitem.h"

class Task : public TreeItem
{
public:
    Task();

    virtual bool setData(QString property, const QVariant &value, int role = Qt::EditRole);
    virtual QVariant data(QString property, int role) const;

private:

    QString m_name;
};

#endif // TASK_H
