/********************************************************************************
** Form generated from reading UI file 'cameraview.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERAVIEW_H
#define UI_CAMERAVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDial>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_CameraView
{
public:
    QDial *dial;
    QDial *dial_2;

    void setupUi(QDialog *CameraView)
    {
        if (CameraView->objectName().isEmpty())
            CameraView->setObjectName(QStringLiteral("CameraView"));
        CameraView->resize(227, 136);
        CameraView->setModal(false);
        dial = new QDial(CameraView);
        dial->setObjectName(QStringLiteral("dial"));
        dial->setGeometry(QRect(10, 10, 21, 21));
        dial->setSliderPosition(96);
        dial->setOrientation(Qt::Horizontal);
        dial->setInvertedAppearance(false);
        dial->setWrapping(true);
        dial->setNotchTarget(5.7);
        dial->setNotchesVisible(false);
        dial_2 = new QDial(CameraView);
        dial_2->setObjectName(QStringLiteral("dial_2"));
        dial_2->setGeometry(QRect(60, 10, 50, 64));

        retranslateUi(CameraView);

        QMetaObject::connectSlotsByName(CameraView);
    } // setupUi

    void retranslateUi(QDialog *CameraView)
    {
        CameraView->setWindowTitle(QApplication::translate("CameraView", "Camera View", 0));
    } // retranslateUi

};

namespace Ui {
    class CameraView: public Ui_CameraView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERAVIEW_H
