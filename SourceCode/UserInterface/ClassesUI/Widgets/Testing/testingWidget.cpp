#include "testingWidget.h"

TestingWidget::TestingWidget(QWidget *pWidget)
    : QWidget(pWidget)
    , m_currentComplexityName("everything")
    , m_currentTopicName("everything")
    , m_file("./QuestionsXML/questions.xml")
{
    setupUi(dynamic_cast<QWidget *>(this));

    connect( m_pbConfirm, &QPushButton::clicked, this, &TestingWidget::slotClickedConfirm );

    connect( m_pbStart, &QPushButton::clicked, this, &TestingWidget::slotClickedStart );
    connect( m_pbStop, &QPushButton::clicked,  this, &TestingWidget::slotClickedStop );

    connect( m_rbAllDifficulties, &QRadioButton::clicked, this, &TestingWidget::slotSwitchedComplexity );
    connect( m_rbEasy, &QRadioButton::clicked,   this, &TestingWidget::slotSwitchedComplexity );
    connect( m_rbMedium, &QRadioButton::clicked, this, &TestingWidget::slotSwitchedComplexity );
    connect( m_rbHard, &QRadioButton::clicked,   this, &TestingWidget::slotSwitchedComplexity );

    connect( m_rbAllTopics, &QRadioButton::clicked, this, &TestingWidget::slotSwitchedTopics );
    connect( m_rbDiscreteMathematics, &QRadioButton::clicked, this, &TestingWidget::slotSwitchedTopics );
    connect( m_rbHashFunction, &QRadioButton::clicked, this, &TestingWidget::slotSwitchedTopics );
    connect( m_rbHashTable, &QRadioButton::clicked,    this, &TestingWidget::slotSwitchedTopics );
    connect( m_rbAlgorithm, &QRadioButton::clicked,    this, &TestingWidget::slotSwitchedTopics );

    connect(this, &TestingWidget::signalEndOfTesting, this, &TestingWidget::slotResetTesting);

    m_frmConfirm->hide();
}

inline void TestingWidget::hideCheckBoxes() {
    QCheckBox *currentCheckBox;
    for(unsigned i = 0; i < 9; ++i) {
        currentCheckBox = findChild<QCheckBox *>(QString("m_cbIndex%1").arg(i));
            currentCheckBox->hide();
    }
}

inline void TestingWidget::showCheckBoxes() {
    QCheckBox *currentCheckBox;
    for(unsigned i = 0, size = m_answers.size(); i < size; ++i) {
        currentCheckBox = findChild<QCheckBox *>(QString("m_cbIndex%1").arg(i));
        currentCheckBox->show();
        currentCheckBox->setText(m_answers[i].first);
    }
}

inline QString TestingWidget::getHTMLQuestion(QDomElement element) {
    QString currentQuestion;

    element = element.firstChildElement();
    do {
        switch (getTagsEnumFromQString(element.tagName())) {
            case TagXML::Caption: {
                currentQuestion.append(
                    QString("<h3>%1</h3>").arg(element.text())
                );
            } break;
            case TagXML::Text: {
            currentQuestion.append(
                QString(R"(
                    <p align="justify">
                        <var>
                            <font face="Times New Roman, Times, serif">
                                %2
                            </font>
                        </var>
                    </p>
                )").arg(element.text())
            );
            } break;
            case TagXML::Answer: {
                m_answers.append(std::make_pair(
                    element.text(),
                    element.hasAttribute("type") ? (element.attribute("type") == "correct")
                                                 : false
                ));
            } break;
            case TagXML::Question: {
                throw std::invalid_argument("the question cannot be nested within the question");
            } break;
            case TagXML::Undefined: {
                throw std::invalid_argument("tag undefined");
            } break;
        }
        element = element.nextSiblingElement();
    } while(not element.isNull());

    return currentQuestion;
}

inline void TestingWidget::configureInput(const QString &value) {
    hideCheckBoxes();
    resetInput();

    if(value == "choice") {
        m_swInputData->setCurrentIndex(0);
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(m_answers.begin(), m_answers.end(), std::default_random_engine(seed));
        showCheckBoxes();
    }
    else if(value == "integer") {
        m_swInputData->setCurrentIndex(1);

    }
    else if(value == "floatingPoint") {
        m_swInputData->setCurrentIndex(2);
    }
    else {
        throw std::invalid_argument("input not defined");
    }
}

inline bool TestingWidget::showNextQuestion() {
    m_currentTypeName = m_currentQuestion.attribute("type");

    bool continueFlag = true;
    while(not m_currentQuestion.isNull() && continueFlag) {
        if(   ( m_currentTopicName == "everything"
                || m_currentTopicName == m_currentQuestion.attribute("category") )
           && ( m_currentComplexityName == "everything"
               || m_currentComplexityName == m_currentQuestion.attribute("complexity") )
        ) {
            m_answers.clear();
            m_testingTextBrowser->setHtml(
                getHTMLQuestion(m_currentQuestion)
            );
            configureInput(m_currentTypeName);
            continueFlag = false;
        }
        m_currentQuestion = m_currentQuestion.nextSiblingElement("question");
    }
    return (not continueFlag);
}

inline void TestingWidget::setEnabledGUIStartTesting(bool flag) {
    m_gbTopics->setEnabled(flag);
    m_gbDifficulty->setEnabled(flag);
    m_pbStart->setEnabled(flag);
    m_pbStop->setDisabled(flag);
    m_frmConfirm->setVisible(not flag);
}

inline TestingWidget::TagXML TestingWidget::getTagsEnumFromQString(const QString &value) {
    TagXML result = {
        value == "question"  ? TagXML::Question
        : value == "caption" ? TagXML::Caption
        : value == "text"    ? TagXML::Text
        : value == "answer"  ? TagXML::Answer
        : TagXML::Undefined
    };
    return result;
}

/*
 *  Slots
*/

inline void TestingWidget::slotSwitchedTopics() { 
    QString result = {
        m_rbAllTopics->isChecked()             ? QString("everything"         )
        : m_rbDiscreteMathematics->isChecked() ? QString("discreteMathematics")
        : m_rbHashFunction->isChecked()        ? QString("hashFunction"       )
        : m_rbHashTable->isChecked()           ? QString("hashTable"          )
        : m_rbAlgorithm->isChecked()           ? QString("algorithm"          )
                                               : QString()
    };
    if(result.isNull()) {
        throw std::invalid_argument("topic undefined");
    }
    m_currentTopicName = result;
}

inline void TestingWidget::slotSwitchedComplexity() {
    QString result = {
        m_rbAllDifficulties->isChecked() ? QString("everything")
        : m_rbEasy->isChecked()          ? QString("easy"      )
        : m_rbMedium->isChecked()        ? QString("medium"    )
        : m_rbHard->isChecked()          ? QString("hard"      )
                                         : QString()
    };
    if(result.isNull()) {
        throw std::invalid_argument("complexity undefined");
    }
    m_currentComplexityName = result;
}

inline bool TestingWidget::checkAnswer(const QString &value) {
    if(m_answers.size() <= 0) {
        return false;
    }

    bool result = true;
    if(value == "choice") {
        QCheckBox *currentCheckBox;
        for(unsigned i = 0, size = m_answers.size(); i < size; ++i) {
            currentCheckBox = findChild<QCheckBox *>(QString("m_cbIndex%1").arg(i));
            if(m_answers[i].second) {
                result &= currentCheckBox->isChecked();
            }
            else {
                result &= not currentCheckBox->isChecked();
            }
        }
    }
    else if(value == "integer" || value == "floatingPoint") {
        QString answer = {
            value == "integer" ? m_sbInteger->text()
                               : m_sbDouble->text()
        };
        auto iter = std::find_if(m_answers.begin(), m_answers.end()
                     , [answer](const std::pair<QString, bool> &value)->bool {
            return (value.second == true && value.first == answer);
        });
        return (iter not_eq m_answers.end());
    }
    else {
        throw std::invalid_argument("input not defined");
    }
    return result;
}

inline void TestingWidget::slotClickedConfirm(){
    bool result = checkAnswer(m_currentTypeName);
    emit signalReplyGiven(result);

    if(not showNextQuestion()) {
        setEnabledGUIStartTesting(true);
        emit signalEndOfTesting();
    }
}

inline void TestingWidget::slotClickedStart(){
    bool isOpened = m_file.open(QIODevice::ReadOnly);
    emit signalFileOpened(isOpened);

    if(isOpened) {
        bool isSet = m_document.setContent(&m_file);
        m_file.close();
        emit signalContentIsSet(isSet);

        if(isSet) {
            QDomNode questions = m_document.firstChild().nextSiblingElement("questions");
            if(questions.isNull()) {
                return;
            }

            QDomNode firstQuestion = questions.firstChild().nextSiblingElement("question");
            if(firstQuestion.isNull()) {
                return;
            }
            m_currentQuestion = firstQuestion.toElement();
            if( showNextQuestion() ) {
                setEnabledGUIStartTesting(false);
                emit signalStartOfTesting();
            }
        }
    }
    return;
}

inline void TestingWidget::resetInput() {
    QCheckBox *currentCheckBox;
    for(unsigned i = 0; i < 9; ++i) {
        currentCheckBox = findChild<QCheckBox *>(QString("m_cbIndex%1").arg(i));
            currentCheckBox->setChecked(false);
    }
    m_sbInteger->clear();
    m_sbDouble->clear();
}

inline void TestingWidget::slotResetTesting() {
    m_testingTextBrowser->clear();
    setEnabledGUIStartTesting(true);
    resetInput();
}

inline void TestingWidget::slotClickedStop() {
    emit signalEndOfTesting();
}
