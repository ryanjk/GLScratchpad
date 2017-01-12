/********************************************************************************
** Form generated from reading UI file 'programview.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRAMVIEW_H
#define UI_PROGRAMVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_ProgramView
{
public:
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *ProgramView)
    {
        if (ProgramView->objectName().isEmpty())
            ProgramView->setObjectName(QStringLiteral("ProgramView"));
        ProgramView->resize(189, 269);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ProgramView->sizePolicy().hasHeightForWidth());
        ProgramView->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(ProgramView);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        retranslateUi(ProgramView);

        QMetaObject::connectSlotsByName(ProgramView);
    } // setupUi

    void retranslateUi(QDialog *ProgramView)
    {
        ProgramView->setWindowTitle(QApplication::translate("ProgramView", "ProgramView", 0));
    } // retranslateUi

};

namespace Ui {
    class ProgramView: public Ui_ProgramView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRAMVIEW_H
