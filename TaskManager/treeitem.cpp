#include "treeitem.h"

#include <QVariant>

TreeItem::TreeItem()
{

}

TreeItem::~TreeItem()
{

}

TreeItem* TreeItem::parent() const
{
   return m_parent;
}

qsizetype TreeItem::idx() const
{
    return m_parent->m_children.indexOf(this);
}

TreeItem* TreeItem::child(qsizetype idx) const
{
    return m_children.at(idx);
}

qsizetype TreeItem::childCount() const
{
    return m_children.count();
}

void TreeItem::insertChild(qsizetype idx, TreeItem *child)
{
    m_children.insert(idx, child);
    child->setParent(this);
}

void TreeItem::appendChild(TreeItem *child)
{
    m_children.append(child);
}

void TreeItem::removeChild(qsizetype idx)
{
    TreeItem *item = m_children.takeAt(idx);
    delete item;
}

void TreeItem::moveChild(qsizetype from, qsizetype to)
{
    m_children.move(from, to);
}

bool TreeItem::setData(QString property, const QVariant &value, int role)
{
    bool ret = false;

    if (role == Qt::EditRole)
    {
        m_properties.insert(property, value);
        ret = true;
    }

    return ret;
}

QVariant TreeItem::data(QString property, int role) const
{
    QVariant ret;

    if ((role == Qt::DisplayRole) || (role == Qt::EditRole))
    {
        ret = m_properties.value(property);
    }

    return ret;
}

Qt::ItemFlags TreeItem::flags(QString property) const
{
    Q_UNUSED(property)

    return Qt::ItemIsEditable |
            Qt::ItemIsEnabled |
            Qt::ItemIsSelectable |
            Qt::ItemIsDragEnabled |
            Qt::ItemIsDropEnabled;
}

void TreeItem::setParent(TreeItem *parent)
{
    m_parent = parent;
}
