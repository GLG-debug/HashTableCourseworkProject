#include "../SourceCode/UserInterface/ClassesUI/Windows/MainWindow/mainWindow.h"

// 7820126495              7'820'126'495
// max value  18'446'744'073'709'551'615
//#include <QDebug>
//#include <cmath>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

//    qDebug() << static_cast<size_t>(std::pow(95, 5)
//                                    + std::pow(95, 4)
//                                    + std::pow(95, 3)
//                                    + std::pow(95, 2)
//                                    + std::pow(95, 1)
//                                    );
//    qDebug() << std::numeric_limits<size_t>::max();

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
