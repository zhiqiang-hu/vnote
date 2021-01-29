#ifndef NODE_H
#define NODE_H

#include <QDateTime>
#include <QVector>
#include <QSharedPointer>
#include <QDir>

#include <global.h>

namespace vnotex
{
    class Notebook;
    class INotebookConfigMgr;
    class INotebookBackend;
    class File;

    // Used when add/new a node.
    struct NodeParameters
    {
        QDateTime m_createdTimeUtc = QDateTime::currentDateTimeUtc();
        QDateTime m_modifiedTimeUtc = QDateTime::currentDateTimeUtc();
        QString m_attachmentFolder;
        QStringList m_tags;
    };

    // Node of notebook.
    class Node
    {
    public:
        enum Flag {
            None = 0,
            // A node with content.
            Content = 0x1,
            // A node with children.
            Container = 0x2,
            ReadOnly = 0x4
        };
        Q_DECLARE_FLAGS(Flags, Flag)

        enum Use {
            Normal,
            RecycleBin,
            Root
        };

        enum { InvalidId = 0 };

        // Constructor with all information loaded.
        Node(Flags p_flags,
             ID p_id,
             const QString &p_name,
             const QDateTime &p_createdTimeUtc,
             const QDateTime &p_modifiedTimeUtc,
             const QStringList &p_tags,
             const QString &p_attachmentFolder,
             Notebook *p_notebook,
             Node *p_parent);

        // Constructor not loaded.
        Node(Flags p_flags,
             const QString &p_name,
             Notebook *p_notebook,
             Node *p_parent);

        virtual ~Node();

        bool isLoaded() const;

        bool isRoot() const;

        const QString &getName() const;
        void setName(const QString &p_name);

        void updateName(const QString &p_name);

        // Fetch path of this node within notebook.
        // This may not be the same as the actual file path. It depends on the config mgr.
        virtual QString fetchPath() const;

        // Fetch absolute file path if available.
        virtual QString fetchAbsolutePath() const = 0;

        bool isContainer() const;

        bool hasContent() const;

        Node::Use getUse() const;
        void setUse(Node::Use p_use);

        ID getId() const;

        const QDateTime &getCreatedTimeUtc() const;

        const QDateTime &getModifiedTimeUtc() const;
        void setModifiedTimeUtc();

        const QVector<QSharedPointer<Node>> &getChildren() const;
        int getChildrenCount() const;

        QSharedPointer<Node> findChild(const QString &p_name, bool p_caseSensitive = true) const;

        bool containsChild(const QString &p_name, bool p_caseSensitive = true) const;

        bool containsChild(const QSharedPointer<Node> &p_node) const;

        void addChild(const QSharedPointer<Node> &p_node);

        void insertChild(int p_idx, const QSharedPointer<Node> &p_node);

        void removeChild(const QSharedPointer<Node> &p_node);

        void setParent(Node *p_parent);
        Node *getParent() const;

        Notebook *getNotebook() const;

        void load();
        void save();

        const QStringList &getTags() const;

        const QString &getAttachmentFolder() const;
        void setAttachmentFolder(const QString &p_attachmentFolder);

        QString fetchAttachmentFolderPath();

        QDir toDir() const;

        bool isReadOnly() const;
        void setReadOnly(bool p_readOnly);

        // Get File if this node has content.
        virtual QSharedPointer<File> getContentFile() const = 0;

        void loadCompleteInfo(ID p_id,
                              const QDateTime &p_createdTimeUtc,
                              const QDateTime &p_modifiedTimeUtc,
                              const QStringList &p_tags,
                              const QVector<QSharedPointer<Node>> &p_children);

        static bool isAncestor(const Node *p_ancestor, const Node *p_child);

    protected:
        Notebook *m_notebook = nullptr;

    private:
        INotebookConfigMgr *getConfigMgr() const;

        bool m_loaded = false;

        Flags m_flags = Flag::None;

        Use m_use = Use::Normal;

        ID m_id = InvalidId;

        QString m_name;

        QDateTime m_createdTimeUtc;

        QDateTime m_modifiedTimeUtc;

        QStringList m_tags;

        QString m_attachmentFolder;

        Node *m_parent = nullptr;

        QVector<QSharedPointer<Node>> m_children;
    };

    Q_DECLARE_OPERATORS_FOR_FLAGS(Node::Flags)
} // ns vnotex

#endif // NODE_H
