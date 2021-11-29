#include "textBrowserWidget.h"

TextBrowserWidget::TextBrowserWidget(const QString &xmlFile, QWidget *pWidget)
    : QWidget(pWidget)
{
    setupUi(dynamic_cast<QWidget *>(this));

    connect( m_main, &QPushButton::clicked, this, &TextBrowserWidget::slotClickedMain );
    connect( m_next, &QPushButton::clicked, this, &TextBrowserWidget::slotClickedNext );
    connect( m_previous, &QPushButton::clicked, this, &TextBrowserWidget::slotClickedPrev );
    connect( m_textBrowser, &QTextBrowser::sourceChanged, this, &TextBrowserWidget::slotPageChanged );

    m_textBrowser->setOpenExternalLinks(true);

    unpack(xmlFile);
}

/*
 *  HTML theory
*/

inline void TextBrowserWidget::slotPageChanged(const QUrl &url) {
    QString value = url.toString().section('/', -1);
    auto iterator = std::find_if(m_htmlPages.cbegin(), m_htmlPages.cend()
                              , [value](const QString &other)->bool {
        return ( other.section('/', -1) == value );
    });
    if(iterator == m_htmlPages.cend()) {
        m_textBrowser->clear();
        return;
    }

    m_currentIndexPage = iterator - m_htmlPages.cbegin();
    bool isMainPage = (m_currentIndexPage == 0);
    m_main->setDisabled(isMainPage);
    m_previous->setEnabled( isMainPage ? false : m_currentIndexPage not_eq 1 );
    m_next->setEnabled( isMainPage ? false : m_currentIndexPage not_eq (m_htmlPages.size() - 1) );
}

inline void TextBrowserWidget::configureTheButtons() {
    m_main->setEnabled(m_currentIndexPage not_eq 0);
    m_previous->setEnabled(m_currentIndexPage not_eq 1);
    m_next->setEnabled(m_currentIndexPage not_eq (m_htmlPages.size() - 1));
}

inline bool TextBrowserWidget::unpack(const QString &xmlFileName) {
    QDomDocument xmlDocument;

    QFile xmlFile(xmlFileName);
    if(not xmlFile.open(QIODevice::ReadOnly)) {
        return false;
    }

    bool isSet = xmlDocument.setContent(&xmlFile);
    xmlFile.close();

    if(not isSet) {
        return false;
    }

    QDomElement infoNode = xmlDocument.firstChild().nextSiblingElement("info");

    QDomElement currentDirectoryElement = infoNode.firstChildElement("directory");
    QStringList searchPaths;
    while (not currentDirectoryElement.isNull()) {
        searchPaths.append(currentDirectoryElement.text());
        currentDirectoryElement = currentDirectoryElement.nextSiblingElement("directory");
    }

    QDomElement currentPage = infoNode.firstChildElement("order").firstChildElement("page");
    if(currentPage.isNull()) {
        return false;
    }

    QStringList result;
    QString currentTagName;
    bool isExists;
    while(not currentPage.isNull()) {
        currentTagName = currentPage.text();
        isExists = false;

        for(const QString &name : searchPaths) {
            if(QDir(name).exists(currentTagName)) {
                isExists = true;
                break;
            }
        }

        if(not isExists) {
            return false;
        }
        result.push_back(currentTagName);
        currentPage = currentPage.nextSiblingElement("page");
    }

    m_textBrowser->setSearchPaths(searchPaths);
    m_htmlPages = result;

    return setSourceMainPage();
}

inline void TextBrowserWidget::slotClickedMain() {
    configureTheButtons();
    if(m_currentIndexPage not_eq 0) {
        m_textBrowser->setSource(m_htmlPages.front());
    }
}

inline void TextBrowserWidget::slotClickedPrev() {
    configureTheButtons();
    if(m_currentIndexPage not_eq 1) {
        m_textBrowser->setSource(m_htmlPages[--m_currentIndexPage]);
    }
}

inline void TextBrowserWidget::slotClickedNext() {
    configureTheButtons();
    if(m_currentIndexPage not_eq (m_htmlPages.size() - 1)) {
        m_textBrowser->setSource(m_htmlPages[++m_currentIndexPage]);
    }
}
