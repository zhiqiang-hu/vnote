#ifndef VXNODE_H
#define VXNODE_H

#include "node.h"

namespace vnotex
{
    // Node of VXNotebookConfigMgr.
    class VXNode : public Node
    {
    public:
        // For content node.
        VXNode(ID p_id,
               const QString &p_name,
               const QDateTime &p_createdTimeUtc,
               const QDateTime &p_modifiedTimeUtc,
               const QStringList &p_tags,
               const QString &p_attachmentFolder,
               Notebook *p_notebook,
               Node *p_parent);

        // For container node.
        VXNode(const QString &p_name,
               Notebook *p_notebook,
               Node *p_parent);

        QString fetchAbsolutePath() const Q_DECL_OVERRIDE;

        QSharedPointer<File> getContentFile() const Q_DECL_OVERRIDE;

    private:
    };
}

#endif // VXNODE_H
