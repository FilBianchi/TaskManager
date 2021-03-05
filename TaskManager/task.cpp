#include "task.h"

#include <QVariant>

Task::Task()
{

}

bool Task::setData(QString property, const QVariant &value, int role)
{
    if (role == Qt::EditRole)
    {
        if (property == "Name")
        {
            m_name = value.toString();
        }
    }

    return true;
}

QVariant Task::data(QString property, int role) const
{
    QVariant ret;

    if (role == Qt::DisplayRole)
    {
        if (property == "Name")
        {
            ret = m_name;
        }
    }

    return ret;
}
