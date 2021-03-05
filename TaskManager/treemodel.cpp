#include "treemodel.h"
#include "treeitem.h"

TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent), m_invisibleRootItem(new TreeItem())
{
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant ret;

    if (orientation == Qt::Horizontal)
    {
        if (role == Qt::DisplayRole)
        {
            ret = m_headers.at(section);
        }
    }

    return ret;
}

bool TreeModel::setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role)
{
    if (orientation == Qt::Horizontal)
    {
        m_headers.replace(section, value.toString());

        emit headerDataChanged(Qt::Horizontal, section, section);
    }

    return true;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
    QModelIndex idx;

    if (hasIndex(row, column, parent))
    {
        TreeItem *parentItem;

        if (!parent.isValid())
        {
            parentItem = m_invisibleRootItem;
        }
        else
        {
            parentItem = static_cast<TreeItem*>(parent.internalPointer());
        }

        TreeItem *childItem = parentItem->child(row);
        if (childItem)
        {
            idx = createIndex(row, column, childItem);
        }
    }

    return idx;
}

QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    QModelIndex idx;

    if (index.isValid())
    {
        TreeItem *child = static_cast<TreeItem*>(index.internalPointer());
        TreeItem *parent = child->parent();

        if (parent != m_invisibleRootItem)
        {
            idx = createIndex(static_cast<int>(parent->idx()),
                              0, parent);
        }
    }

    return idx;
}

int TreeModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;

    if (!parent.isValid())
    {
        parentItem = m_invisibleRootItem;
    }
    else
    {
        parentItem = static_cast<TreeItem*>(parent.internalPointer());
    }

    return static_cast<int>(parentItem->childCount());
}

int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)

    return static_cast<int>(m_headers.count());
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
    QVariant ret;

    if (index.isValid())
    {
        TreeItem *item;
        item = static_cast<TreeItem*>(index.internalPointer());
        ret = item->data(m_headers.at(index.column()), role);
    }

    return ret;
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    bool ret = false;
    TreeItem *item;

    if (index.isValid())
    {
        QString property = m_headers.at(index.column());

        item = static_cast<TreeItem*>(index.internalPointer());

        if (item->data(property, role) != value)
        {
            item->setData(property, value, role);
            emit dataChanged(index, index, QVector<int>() << role);
            ret = true;
        }
    }

    return ret;
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::NoItemFlags;

    if (index.isValid())
    {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        QString property = m_headers.at(index.column());

        flags = item->flags(property);
    }

    return flags;
}

bool TreeModel::insertRows(int row, int count, const QModelIndex &parent)
{
    bool ret = true;
    TreeItem *item;

    beginInsertRows(parent, row, row + count - 1);

    if (parent.isValid())
    {
        item = static_cast<TreeItem*>(parent.internalPointer());
    }
    else
    {
        item = m_invisibleRootItem;
    }

    for (int i = 0; i < count; i++)
    {
        item->insertChild(row, new TreeItem());
    }

    endInsertRows();

    return ret;
}

bool TreeModel::removeRows(int row, int count, const QModelIndex &parent)
{
    bool ret = true;
    TreeItem *item;

    beginRemoveRows(parent, row, row + count - 1);

    if (parent.isValid())
    {
        item = static_cast<TreeItem*>(parent.internalPointer());
    }
    else
    {
        item = m_invisibleRootItem;
    }

    for (int i = 0; i < count; i++)
    {
        item->removeChild(row);
    }

    endRemoveRows();

    return ret;
}

bool TreeModel::insertColumns(int column, int count, const QModelIndex &parent)
{
    Q_UNUSED(parent)

    beginInsertColumns(QModelIndex(), column, column + count - 1);

    for (int i = 0; i < count; i++)
    {
        m_headers.insert(column + i, "test");
    }

    endInsertColumns();

    return true;
}

bool TreeModel::removeColumns(int column, int count, const QModelIndex &parent)
{
    beginRemoveColumns(parent, column, column + count - 1);

    for (int i = 0; i < count; i++)
    {
        m_headers.remove(column);
    }

    endRemoveColumns();

    return true;
}

bool TreeModel::moveRows(const QModelIndex &sourceParent, int sourceRow, int count, const QModelIndex &destinationParent, int destinationChild)
{
    return QAbstractItemModel::moveRows(sourceParent, sourceRow, count, destinationParent, destinationChild);
}

bool TreeModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
//    TreeItem *item;
    bool ret;

//    if (parent.isValid())
//    {
//        item = static_cast<TreeItem*>(parent.internalPointer());
//    }
//    else
//    {
//        item = m_invisibleRootItem;
//    }

    ret = QAbstractItemModel::dropMimeData(data, action, row, column, parent);

    qDebug() << data << action << row << column << parent;

    return ret;
}

QMimeData *	TreeModel::mimeData(const QModelIndexList &indexes) const
{
    QMimeData *ret;

    ret = QAbstractItemModel::mimeData(indexes);

    return ret;
}

QStringList	TreeModel::mimeTypes() const
{
    QStringList ret;

    ret = QAbstractItemModel::mimeTypes();

    return ret;
}

Qt::DropActions	TreeModel::supportedDropActions() const
{
    Qt::DropActions ret;

    ret = Qt::CopyAction | Qt::MoveAction | Qt::LinkAction;

    return ret;
}
