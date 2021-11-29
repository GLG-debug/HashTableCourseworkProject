TEMPLATE = app

#QMAKE_CXXFLAGS += -O2 -mpreferred-stack-boundary=2 -finline-small-functions -momit-leaf-frame-pointer

CONFIG += \
    c++14 \
    debug

QT += \
    widgets \
    core \
    gui \
    charts \
    xml

RESOURCES += \
    SourceCode/resources.qrc

FORMS += \
    SourceCode/UserInterface/FilesUI/demonstrationWidget.ui \
    SourceCode/UserInterface/FilesUI/mainWindow.ui \
    SourceCode/UserInterface/FilesUI/testingWidget.ui \
    SourceCode/UserInterface/FilesUI/textBrowserWidget.ui

HEADERS += \
    SourceCode/BusinessLogic/Convert/convert.h \
    SourceCode/BusinessLogic/Hash/Algorithm/Family/doubleHashing.h \
    SourceCode/BusinessLogic/Hash/Algorithm/Family/family.h \
    SourceCode/BusinessLogic/Hash/Algorithm/Family/pseudorandomProbing.h \
    SourceCode/BusinessLogic/Hash/Algorithm/One/linearProbing.h \
    SourceCode/BusinessLogic/Hash/Algorithm/One/one.h \
    SourceCode/BusinessLogic/Hash/Algorithm/One/quadraticProbing.h \
    SourceCode/BusinessLogic/Hash/Algorithm/abstract.h \
    SourceCode/BusinessLogic/Hash/Factory/abstract.h \
    SourceCode/BusinessLogic/Hash/Factory/family.h \
    SourceCode/BusinessLogic/Hash/Factory/one.h \
    SourceCode/BusinessLogic/Hash/Function/Family/family.h \
    SourceCode/BusinessLogic/Hash/Function/Family/fnv1a.h \
    SourceCode/BusinessLogic/Hash/Function/One/equivalent.h \
    SourceCode/BusinessLogic/Hash/Function/One/one.h \
    SourceCode/BusinessLogic/Hash/Function/One/standart.h \
    SourceCode/BusinessLogic/Hash/Function/Pattern/familyToOne.h \
    SourceCode/BusinessLogic/Hash/Function/abstract.h \
    SourceCode/BusinessLogic/Hash/Table/Pattern/subscriber.h \
    SourceCode/BusinessLogic/Hash/Table/abstract.h \
    SourceCode/BusinessLogic/Hash/Table/chains.h \
    SourceCode/BusinessLogic/Hash/Table/openAddress.h \
    SourceCode/BusinessLogic/Pattern/singleton.h \
    SourceCode/BusinessLogic/Statistics/dispersion.h \
    SourceCode/BusinessLogic/businessLogic.h \
    SourceCode/BusinessLogic/hashHeaderFiles.h \
    SourceCode/UserInterface/ClassesUI/Validator/validator.h \
    SourceCode/UserInterface/ClassesUI/Widgets/Demonstration/demonstrationWidget.h \
    SourceCode/UserInterface/ClassesUI/Widgets/Testing/testingWidget.h \
    SourceCode/UserInterface/ClassesUI/Widgets/TextBrowser/textBrowserWidget.h \
    SourceCode/UserInterface/ClassesUI/Windows/MainWindow/mainWindow.h

SOURCES += \
    SourceCode/BusinessLogic/Convert/convert.cpp \
    SourceCode/UserInterface/ClassesUI/Widgets/Demonstration/demonstrationWidget.cpp \
    SourceCode/UserInterface/ClassesUI/Widgets/Testing/testingWidget.cpp \
    SourceCode/UserInterface/ClassesUI/Widgets/TextBrowser/textBrowserWidget.cpp \
    SourceCode/UserInterface/ClassesUI/Windows/MainWindow/mainWindow.cpp \
    SourceCode/BusinessLogic/debug.cpp
    #SourceCode/main.cpp


