#ifndef THEORY_WIDGET_H
#define THEORY_WIDGET_H

#include "ui_textBrowserWidget.h"

#include <QWidget>
#include <QFile>
#include <QtXml>

class TextBrowserWidget : public QWidget
                        , protected Ui::TextBrowserWidget
{
private:
    /*
     *  HTML
    */
    QStringList m_htmlPages;
    int m_currentIndexPage;

public:
    TextBrowserWidget(const QString &xmlFile = {}
                      , QWidget *pWidget = nullptr);

public:
    bool unpack(const QString &xmlFile);
    void setFontPointSize(int size) {
        QFont font = m_textBrowser->font();
        font.setPointSize(size);
        m_textBrowser->setFont(font);
    }

private:
    /*
     *  Business logic
    */
    bool setSourceMainPage() {
        if(not m_htmlPages.isEmpty()) {
            m_textBrowser->setSource( QUrl( m_htmlPages.front() ) );
            return true;
        }
        return false;
    }

private slots:
    void slotPageChanged(const QUrl &url);
    void slotClickedMain();
    void slotClickedPrev();
    void slotClickedNext();
};
#endif // THEORY_WIDGET_H
