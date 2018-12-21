/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionTurkish;
    QAction *actionGerman;
    QAction *actionEnglish;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *topHorizontalLayout;
    QLabel *inputLabel;
    QLineEdit *inputLineEdit;
    QPushButton *inputPushButton;
    QGroupBox *filterTypeGroupBox;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *medianBlurRadioButton;
    QRadioButton *gaussianBlurRadioButton;
    QHBoxLayout *bottomHorizontalLayout;
    QLabel *outputLabel;
    QLineEdit *outputLineEdit;
    QPushButton *outputPushButton;
    QCheckBox *displayImageCheckBox;
    QMenuBar *menuBar;
    QMenu *menuLanguage;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(560, 296);
        MainWindow->setStyleSheet(QLatin1String("*{\n"
"font: 75 11pt;\n"
"background-color: rgb(199, 238, 206);\n"
"}\n"
"QPushButton, QLineEdit, QGroupBox\n"
"{\n"
"border: 2px solid rgb(0, 0, 0);\n"
"border-radius: 10px;\n"
"min-width: 80px;\n"
"min-height: 35px;\n"
"}\n"
"QPushButton\n"
"{\n"
"background-color: rgb(0, 255, 0);\n"
"}\n"
"QLineEdit\n"
"{\n"
"background-color: rgb(0, 170, 255);\n"
"}\n"
"QPushButton:hover, QRadioButton:hover, QCheckBox:hover\n"
"{\n"
"color: red;\n"
"}\n"
"QPushButton:!hover, QRadioButton:!hover, QCheckBox:!hover\n"
"{\n"
"color: black;\n"
"}"));
        actionTurkish = new QAction(MainWindow);
        actionTurkish->setObjectName(QStringLiteral("actionTurkish"));
        actionGerman = new QAction(MainWindow);
        actionGerman->setObjectName(QStringLiteral("actionGerman"));
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        topHorizontalLayout = new QHBoxLayout();
        topHorizontalLayout->setSpacing(6);
        topHorizontalLayout->setObjectName(QStringLiteral("topHorizontalLayout"));
        inputLabel = new QLabel(centralWidget);
        inputLabel->setObjectName(QStringLiteral("inputLabel"));

        topHorizontalLayout->addWidget(inputLabel);

        inputLineEdit = new QLineEdit(centralWidget);
        inputLineEdit->setObjectName(QStringLiteral("inputLineEdit"));

        topHorizontalLayout->addWidget(inputLineEdit);

        inputPushButton = new QPushButton(centralWidget);
        inputPushButton->setObjectName(QStringLiteral("inputPushButton"));

        topHorizontalLayout->addWidget(inputPushButton);


        verticalLayout->addLayout(topHorizontalLayout);

        filterTypeGroupBox = new QGroupBox(centralWidget);
        filterTypeGroupBox->setObjectName(QStringLiteral("filterTypeGroupBox"));
        horizontalLayout_2 = new QHBoxLayout(filterTypeGroupBox);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        medianBlurRadioButton = new QRadioButton(filterTypeGroupBox);
        medianBlurRadioButton->setObjectName(QStringLiteral("medianBlurRadioButton"));
        medianBlurRadioButton->setChecked(true);

        horizontalLayout_2->addWidget(medianBlurRadioButton);

        gaussianBlurRadioButton = new QRadioButton(filterTypeGroupBox);
        gaussianBlurRadioButton->setObjectName(QStringLiteral("gaussianBlurRadioButton"));

        horizontalLayout_2->addWidget(gaussianBlurRadioButton);


        verticalLayout->addWidget(filterTypeGroupBox);

        bottomHorizontalLayout = new QHBoxLayout();
        bottomHorizontalLayout->setSpacing(6);
        bottomHorizontalLayout->setObjectName(QStringLiteral("bottomHorizontalLayout"));
        outputLabel = new QLabel(centralWidget);
        outputLabel->setObjectName(QStringLiteral("outputLabel"));

        bottomHorizontalLayout->addWidget(outputLabel);

        outputLineEdit = new QLineEdit(centralWidget);
        outputLineEdit->setObjectName(QStringLiteral("outputLineEdit"));

        bottomHorizontalLayout->addWidget(outputLineEdit);

        outputPushButton = new QPushButton(centralWidget);
        outputPushButton->setObjectName(QStringLiteral("outputPushButton"));

        bottomHorizontalLayout->addWidget(outputPushButton);


        verticalLayout->addLayout(bottomHorizontalLayout);

        displayImageCheckBox = new QCheckBox(centralWidget);
        displayImageCheckBox->setObjectName(QStringLiteral("displayImageCheckBox"));

        verticalLayout->addWidget(displayImageCheckBox);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 560, 28));
        menuLanguage = new QMenu(menuBar);
        menuLanguage->setObjectName(QStringLiteral("menuLanguage"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuLanguage->menuAction());
        menuLanguage->addAction(actionEnglish);
        menuLanguage->addAction(actionGerman);
        menuLanguage->addAction(actionTurkish);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Hello_Qt_OpenCV", Q_NULLPTR));
        actionTurkish->setText(QApplication::translate("MainWindow", "Turkish", Q_NULLPTR));
        actionGerman->setText(QApplication::translate("MainWindow", "German", Q_NULLPTR));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", Q_NULLPTR));
        inputLabel->setText(QApplication::translate("MainWindow", "Input Image :", Q_NULLPTR));
        inputPushButton->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        filterTypeGroupBox->setTitle(QApplication::translate("MainWindow", "Filter type", Q_NULLPTR));
        medianBlurRadioButton->setText(QApplication::translate("MainWindow", "Median Blur", Q_NULLPTR));
        gaussianBlurRadioButton->setText(QApplication::translate("MainWindow", "Gaussian Blur", Q_NULLPTR));
        outputLabel->setText(QApplication::translate("MainWindow", "Output Image :", Q_NULLPTR));
        outputPushButton->setText(QApplication::translate("MainWindow", "Browse", Q_NULLPTR));
        displayImageCheckBox->setText(QApplication::translate("MainWindow", "Display Image After Saving", Q_NULLPTR));
        menuLanguage->setTitle(QApplication::translate("MainWindow", "Language", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
