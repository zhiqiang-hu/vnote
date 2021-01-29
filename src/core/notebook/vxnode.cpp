#include "vxnode.h"

#include <QDir>

#include <utils/pathutils.h>
#include "notebook.h"

using namespace vnotex;

VXNode::VXNode(ID p_id,
               const QString &p_name,
               const QDateTime &p_createdTimeUtc,
               const QDateTime &p_modifiedTimeUtc,
               const QStringList &p_tags,
               const QString &p_attachmentFolder,
               Notebook *p_notebook,
               Node *p_parent)
    : Node(Node::Flag::Content,
           p_id,
           p_name,
           p_createdTimeUtc,
           p_modifiedTimeUtc,
           p_tags,
           p_attachmentFolder,
           p_notebook,
           p_parent)
{
}

VXNode::VXNode(const QString &p_name,
               Notebook *p_notebook,
               Node *p_parent)
    : Node(Node::Flag::Container,
           p_name,
           p_notebook,
           p_parent)
{
}

QString VXNode::fetchAbsolutePath() const
{
    return PathUtils::concatenateFilePath(m_notebook->getRootFolderAbsolutePath(),
                                          fetchPath());
}

QSharedPointer<File> VXNode::getContentFile() const
{
    return nullptr;
}
