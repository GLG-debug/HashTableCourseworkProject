#include "mainWindow.h"

inline void MainWindow::appendStatusbarText(const QString &value) {
    m_timer->stop();
    QString newData;
    if(m_lblStatusbarText->text().size() + value.size() < 150) {
        newData.append(m_lblStatusbarText->text());
    }
    newData.append(value + "; ");
    m_lblStatusbarText->setText(newData);
    m_timer->start();
}

inline void MainWindow::saveResult() {
    QDate currentTime = QDate::currentDate();
    short day        = currentTime.day();
    short month      = currentTime.month();
    short year       = currentTime.year() % 1000;

    constexpr short sizeDay     = 5;
    constexpr short sizeMonth   = 4;
    constexpr short sizeYear    = 10;
    constexpr short sizeCorrect = 8;
    constexpr short sizeTotal   = 8;
    //constexpr short sizeSubject    = 3;
    //constexpr short sizeComplexity = 2;
    constexpr short size = {
        sizeDay + sizeMonth + sizeYear
        + sizeCorrect + sizeTotal
     // + sizeSubject + sizeComplexity
    };

    std::bitset<size> newData;
    for(const auto &value : std::initializer_list<std::pair<short, short>>{
            {day, sizeDay}, {month, sizeMonth}, {year, sizeYear}
            , {m_numerOfCorrect, sizeCorrect}, {m_numberOfAll, sizeTotal}
    }) {
        newData <<= value.second;
        newData |= value.first;
    }

    QByteArray byteArray;

    while(newData.any()) {
        byteArray.push_front( static_cast<char>( newData.to_ullong()) );
        newData >>= CHAR_BIT;
    }

    QFile file("save.dat");
    file.open(QIODevice::Append);
    file.write(byteArray);
    file.close();
}

MainWindow::MainWindow(QWidget *pWidget)
    : QMainWindow ( pWidget )
    , m_timer( new QTimer(this) )
    , m_lblStatusbarText(new QLabel)
{
    setupUi(dynamic_cast<QMainWindow *>(this));

    /*
     *  Size
    */

    QSize screen = QApplication::desktop()->screenGeometry().size();
    move(screen.width() / 30, screen.height() / 20);

    /*
     *  Signals and slots
    */

    connect( m_tabWidget, &QTabWidget::tabBarClicked, m_demonstrationTab, &DemonstrationWidget::slotTabSwitched);

    connect( m_actionTheory, &QAction::triggered, this, [this]() {
        m_stackedWidget->setCurrentIndex(0);
    });
    connect( m_actionPractice, &QAction::triggered, this, [this]() {
        m_stackedWidget->setCurrentIndex(1);
    });

    connect( m_actionAbout, &QAction::triggered, this, [](){
        QMessageBox::aboutQt(nullptr);
    });

    /*
     *  Theory
    */

    m_theoryTab->unpack("./TheoryHTML/info.xml");

    /*
     * Testing page
    */

    m_lblStatusbarText->setParent(m_statusbar);
    QFont font = m_lblStatusbarText->font();
    font.setPointSize(12);
    m_lblStatusbarText->setFont(font);

    m_statusbar->addWidget(m_lblStatusbarText);
    m_timer->setParent(this);
    m_timer->setInterval(1000 * 5);
    m_timer->callOnTimeout(m_lblStatusbarText, &QLabel::clear);


    connect( m_secondPage, &TestingWidget::signalStartOfTesting, this, [this]() {
        m_numerOfCorrect = 0;
        m_numberOfAll = 0;
        appendStatusbarText("Testing has begun");
    });
    connect( m_secondPage, &TestingWidget::signalEndOfTesting, this, [this]() {
        saveResult();
        appendStatusbarText("Test ended, results saved");
    });
    connect( m_secondPage, &TestingWidget::signalReplyGiven, this, [this](bool result) {
        ++m_numberOfAll;
        if(result) {
            ++m_numerOfCorrect;
            appendStatusbarText("Correct answer");
        }
        else {
            appendStatusbarText("False answer");
        }
    });
    connect( m_secondPage, &TestingWidget::signalFileOpened, this, [this](bool flag) {
        appendStatusbarText(flag ? "File successfully opened" : "File cannot be opened");
    });
    connect( m_secondPage, &TestingWidget::signalContentIsSet, this, [this](bool flag) {
        appendStatusbarText(flag ? "Content of file successfully set" : "Failure to set content of file");
    });

    /*
     *  Manual window
    */
    connect( m_actionManual, &QAction::triggered, this, [this]() {
        auto *manualWindow = new QDialog(this, Qt::Dialog);
        manualWindow->setModal(true);

        auto *centralLayout = new QVBoxLayout;
        auto *textBrowser = new TextBrowserWidget(":/ManualHTML/info.xml");
        textBrowser->setFontPointSize(12);
        centralLayout->addWidget(textBrowser);
        auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
        connect(buttonBox, &QDialogButtonBox::clicked, manualWindow, &QDialog::close);
        centralLayout->addWidget(buttonBox);

        manualWindow->setLayout(centralLayout);
        manualWindow->setMinimumSize({ 800, 600 });
        manualWindow->setWindowFlags(manualWindow->windowFlags() & ~Qt::WindowContextHelpButtonHint);
        manualWindow->setWindowTitle("Manual");
        manualWindow->show();
    });
}
