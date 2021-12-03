#include "../SourceCode/UserInterface/ClassesUI/Windows/MainWindow/mainWindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
