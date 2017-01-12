/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QWidget>
#include "applicationframe.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionOpen_Program;
    QAction *actionClose_Program;
    QAction *actionExit;
    QAction *actionShowCameraView;
    QAction *actionShowProgramView;
    QWidget *centralWidget;
    ApplicationFrame *applicationFrameWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuCamera;
    QMenu *menuProgram;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(301, 251);
        actionOpen_Program = new QAction(MainWindowClass);
        actionOpen_Program->setObjectName(QStringLiteral("actionOpen_Program"));
        actionClose_Program = new QAction(MainWindowClass);
        actionClose_Program->setObjectName(QStringLiteral("actionClose_Program"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionShowCameraView = new QAction(MainWindowClass);
        actionShowCameraView->setObjectName(QStringLiteral("actionShowCameraView"));
        actionShowProgramView = new QAction(MainWindowClass);
        actionShowProgramView->setObjectName(QStringLiteral("actionShowProgramView"));
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        applicationFrameWidget = new ApplicationFrame(centralWidget);
        applicationFrameWidget->setObjectName(QStringLiteral("applicationFrameWidget"));
        applicationFrameWidget->setGeometry(QRect(0, 0, 301, 251));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(applicationFrameWidget->sizePolicy().hasHeightForWidth());
        applicationFrameWidget->setSizePolicy(sizePolicy);
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 301, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuCamera = new QMenu(menuBar);
        menuCamera->setObjectName(QStringLiteral("menuCamera"));
        menuProgram = new QMenu(menuBar);
        menuProgram->setObjectName(QStringLiteral("menuProgram"));
        MainWindowClass->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuCamera->menuAction());
        menuBar->addAction(menuProgram->menuAction());
        menuFile->addAction(actionOpen_Program);
        menuFile->addAction(actionClose_Program);
        menuFile->addAction(actionExit);
        menuCamera->addAction(actionShowCameraView);
        menuProgram->addAction(actionShowProgramView);

        retranslateUi(MainWindowClass);
        QObject::connect(actionShowCameraView, SIGNAL(triggered()), MainWindowClass, SLOT(ShowCameraView()));
        QObject::connect(actionExit, SIGNAL(triggered()), MainWindowClass, SLOT(close()));
        QObject::connect(actionOpen_Program, SIGNAL(triggered()), MainWindowClass, SLOT(OpenProgram()));
        QObject::connect(actionClose_Program, SIGNAL(triggered()), MainWindowClass, SLOT(CloseCurrentProgram()));
        QObject::connect(actionShowProgramView, SIGNAL(triggered()), MainWindowClass, SLOT(ShowProgramView()));

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "GL Scratchpad", 0));
        actionOpen_Program->setText(QApplication::translate("MainWindowClass", "Open Program", 0));
        actionClose_Program->setText(QApplication::translate("MainWindowClass", "Close Program", 0));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0));
        actionShowCameraView->setText(QApplication::translate("MainWindowClass", "Show View", 0));
#ifndef QT_NO_TOOLTIP
        actionShowCameraView->setToolTip(QApplication::translate("MainWindowClass", "Show Camera View", 0));
#endif // QT_NO_TOOLTIP
        actionShowProgramView->setText(QApplication::translate("MainWindowClass", "Show View", 0));
#ifndef QT_NO_TOOLTIP
        actionShowProgramView->setToolTip(QApplication::translate("MainWindowClass", "Show Program View", 0));
#endif // QT_NO_TOOLTIP
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", 0));
        menuCamera->setTitle(QApplication::translate("MainWindowClass", "Camera", 0));
        menuProgram->setTitle(QApplication::translate("MainWindowClass", "Program", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
