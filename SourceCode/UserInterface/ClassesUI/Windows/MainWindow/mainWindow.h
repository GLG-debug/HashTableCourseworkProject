#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "ui_mainWindow.h"
/*
#include "SourceCode/UserInterface/ClassesUI/Widgets/Demonstration/demonstrationWidget.h"
#include "SourceCode/UserInterface/ClassesUI/Widgets/Testing/testingWidget.h"
#include "SourceCode/UserInterface/ClassesUI/Widgets/TextBrowser/textBrowserWidget.h"
*/

#include <bitset>
#include <QDateTime>
#include <QFile>
#include <QArrayData>

class MainWindow : public QMainWindow
                 , protected Ui::MainWindow
{
private:
    QTimer *m_timer;
    QLabel *m_lblStatusbarText;

    size_t m_numerOfCorrect;
    size_t m_numberOfAll;

private:
    void appendStatusbarText(const QString &value);
    void saveResult();

public:
    MainWindow(QWidget *pWidget = nullptr);
};

#endif // MAIN_WINDOW_H
