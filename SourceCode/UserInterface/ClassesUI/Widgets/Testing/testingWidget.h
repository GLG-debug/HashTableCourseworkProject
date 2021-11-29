#ifndef TESTING_WIDGET_H
#define TESTING_WIDGET_H

#include "ui_testingWidget.h"

#include <random>

#include <QWidget>
#include <QtXml>
#include <QMessageBox>

class TestingWidget : public QWidget
                    , protected Ui::TestingWidget
{
    Q_OBJECT

private:
    QDomDocument m_document;
    QDomElement  m_currentQuestion;
    QString      m_currentComplexityName;
    QString      m_currentTopicName;
    QString      m_currentTypeName;

    QFile        m_file;
    QVector<std::pair<QString, bool>> m_answers;

private:
    enum class Topic : short {
        Everything, DiscreteMathematics, HashFunction, HashTable, Algorithm, Undefined
    };
    enum class Complexity : short {
        Everything, Easy, Medium, Hard, Undefined
    };
    enum class TagXML : short {
        Question, Caption, Text, Answer, Undefined
    };

public:
    TestingWidget(QWidget *pWidget = nullptr);
    ~TestingWidget() {
        if(m_file.isOpen()) {
            m_file.close();
        }
    }

private:
    void hideCheckBoxes();
    void showCheckBoxes();
    QString getHTMLQuestion(QDomElement domNode);
    void configureInput(const QString &);
    bool showNextQuestion();
    void setEnabledGUIStartTesting(bool flag);
    TagXML getTagsEnumFromQString(const QString&);
    bool checkAnswer(const QString&);

private slots:
    void slotSwitchedTopics();
    void slotSwitchedComplexity();
    void slotClickedConfirm();
    void slotClickedStart();
    void resetInput();
    void slotResetTesting();
    void slotClickedStop();

signals:
    void signalFileOpened(bool /*isOpen*/);
    void signalContentIsSet(bool /*isSet*/);
    void signalReplyGiven(bool /*isCorrect*/);
    void signalStartOfTesting();
    void signalEndOfTesting();
};
#endif // TESTING_WIDGET_H
