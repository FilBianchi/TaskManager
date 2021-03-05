#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVector>
#include <QMap>

class TreeItem
{
public:

    explicit TreeItem();
    virtual ~TreeItem();

    TreeItem* parent() const;
    qsizetype idx() const;

    TreeItem* child(qsizetype idx) const;
    qsizetype childCount() const;
    void insertChild(qsizetype idx, TreeItem *child);
    void appendChild(TreeItem *child);
    void removeChild(qsizetype idx);
    void moveChild(qsizetype from, qsizetype to);

    virtual bool setData(QString property, const QVariant &value, int role = Qt::EditRole);
    virtual QVariant data(QString property, int role) const;

    virtual Qt::ItemFlags flags(QString property) const;

private:

    void setParent(TreeItem *parent);

    TreeItem* m_parent;
    QVector<TreeItem*> m_children;

    QMap<QString, QVariant> m_properties;
};

#endif // TREEITEM_H
