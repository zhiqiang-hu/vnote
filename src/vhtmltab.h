#ifndef VHTMLTAB_H
#define VHTMLTAB_H

#include <QString>
#include <QPointer>
#include "vedittab.h"
#include "vconstants.h"

class VEdit;

class VHtmlTab : public VEditTab
{
    Q_OBJECT

public:
    VHtmlTab(VFile *p_file, VEditArea *p_editArea, OpenFileMode p_mode, QWidget *p_parent = 0);

    // Close current tab.
    // @p_forced: if true, discard the changes.
    bool closeFile(bool p_forced) Q_DECL_OVERRIDE;

    // Enter read mode.
    // Will prompt user to save the changes.
    void readFile() Q_DECL_OVERRIDE;

    // Save file.
    bool saveFile() Q_DECL_OVERRIDE;

    // Scroll to anchor @p_anchor.
    void scrollToAnchor(const VAnchor& p_anchor) Q_DECL_OVERRIDE;

    void insertImage() Q_DECL_OVERRIDE;

    // Search @p_text in current note.
    void findText(const QString &p_text, uint p_options, bool p_peek,
                  bool p_forward = true) Q_DECL_OVERRIDE;

    // Replace @p_text with @p_replaceText in current note.
    void replaceText(const QString &p_text, uint p_options,
                     const QString &p_replaceText, bool p_findNext) Q_DECL_OVERRIDE;

    void replaceTextAll(const QString &p_text, uint p_options,
                        const QString &p_replaceText) Q_DECL_OVERRIDE;

    QString getSelectedText() const Q_DECL_OVERRIDE;

    void clearSearchedWordHighlight() Q_DECL_OVERRIDE;

public slots:
    // Enter edit mode.
    void editFile() Q_DECL_OVERRIDE;

private slots:
    // Handle text changed in m_editor.
    void handleTextChanged();

    // Emit statusChanged() signal to notify that status of this tab has changed.
    void noticeStatusChanged();

    // m_editor requests to save changes and enter read mode.
    void saveAndRead();

    // m_editor requests to discard changes and enter read mode.
    void discardAndRead();

private:
    // Setup UI.
    void setupUI();

    // Show the file content in read mode.
    void showFileReadMode();

    // Show the file content in edit mode.
    void showFileEditMode();

    // Called to zoom in/out content.
    void zoom(bool p_zoomIn, qreal p_step = 0.25) Q_DECL_OVERRIDE;

    VEdit *m_editor;
};
#endif // VHTMLTAB_H