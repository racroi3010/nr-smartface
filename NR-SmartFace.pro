#-------------------------------------------------
#
# Project created by QtCreator 2015-11-23T21:22:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += xml
TARGET = NR-SmartFace
TEMPLATE = app
CONFIG += link_pkgconfig
PKGCONFIG += opencv

SOURCES += main.cpp\
        mainwindow.cpp \
    SharedImageBuffer.cpp \
    neofacealg.cpp \
    preferencehandler.cpp \
    CameraThread.cpp \
    ProcessingThread.cpp \
    MatToQImageUtil.cpp \
    imagelabel.cpp \
    videoprocessing.cpp \
    UserUtils.cpp \
    dialoguserregister_new.cpp \
    dialoguseranalysis_new.cpp \
    dialoguserlist_new.cpp \
    userlabel.cpp \
    dialogsetting.cpp \
    userlabelhist.cpp \
    dialoguserlisthist.cpp \
    dialogmatching.cpp \
    BaseDialog.cpp \
    digitalclock.cpp \
    neuroalg.cpp \
    faceenginebuilder.cpp \
    checklicensethread.cpp \
    neuroengineparams.cpp

HEADERS  += mainwindow.h \
    Buffer.h \
    SharedImageBuffer.h \
    neofacealg.h \
    feature.h \
    NeoFaceM.h \
    preferencehandler.h \
    CameraThread.h \
    ProcessingThread.h \
    MatToQImageUtil.h \
    Constants.h \
    imagelabel.h \
    videoprocessing.h \
    BaseDialog.h \
    FixedQThread.h \
    UserUtil.h \
    user.h \
    dialoguserregister_new.h \
    dialoguseranalysis_new.h \
    dialoguserlist_new.h \
    userlabel.h \
    dialogsetting.h \
    userlabelhist.h \
    dialoguserlisthist.h \
    dialogmatching.h \
    digitalclock.h \
    neuroalg.h \
    facealginterface.h \
    TutorialUtils.h \
    faceenginebuilder.h \
    checklicensethread.h \
    engineparams.h \
    neuroengineparams.h

FORMS    += mainwindow.ui \
    dialoguserregister_new.ui \
    dialoguseranalysis_new.ui \
    dialoguserlist_new.ui \
    dialogsetting.ui \
    dialoguserlisthist.ui \
    dialogmatching.ui
#LIBS += "libs/libneofacem400.so"

RESOURCES += \
    images.qrc



#unix:!macx: LIBS += -L$$PWD/libs/ -lneofacem400

#INCLUDEPATH += $$PWD/libs
#DEPENDPATH += $$PWD/libs


#LIBS += -L $$PWD/libs
LIBS += -lNBiometricClient -lNBiometrics -lNCluster -lNClusterJni -lNCore -lNDevices -lNLicensing -lNMedia -lNMediaProc -lopenblas


INCLUDEPATH += $$PWD/include
