#ifndef ABSTRACTTREEITEMFACTORY_H
#define ABSTRACTTREEITEMFACTORY_H

#include "treeitem.h"

class AbstractTreeItemFactory
{
public:
    AbstractTreeItemFactory();

    TreeItem* getTreeItem(QString type);

private:

    QStringList m_types;
};

#endif // ABSTRACTTREEITEMFACTORY_H
