/********************************************************************************
** Form generated from reading UI file 'picture.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PICTURE_H
#define UI_PICTURE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_picture
{
public:
    QAction *action;
    QAction *action_3;
    QAction *action_5;
    QAction *action_6;
    QAction *action_2;
    QAction *action_4;
    QAction *action_7;
    QAction *action_8;
    QAction *actionF11;
    QAction *actionCTRL;
    QAction *action_9;
    QAction *action_10;
    QAction *actionNoahsai_github_io;
    QAction *actionNoahsai_github_io_2;
    QAction *actionGithub_com_noahsai;
    QAction *action_11;
    QWidget *centralWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *docklayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;
    QMenu *menuMade_by_noahsai;
    QMenu *menu_5;

    void setupUi(QMainWindow *picture)
    {
        if (picture->objectName().isEmpty())
            picture->setObjectName(QStringLiteral("picture"));
        picture->resize(556, 439);
        picture->setAcceptDrops(true);
        action = new QAction(picture);
        action->setObjectName(QStringLiteral("action"));
        action_3 = new QAction(picture);
        action_3->setObjectName(QStringLiteral("action_3"));
        action_5 = new QAction(picture);
        action_5->setObjectName(QStringLiteral("action_5"));
        action_6 = new QAction(picture);
        action_6->setObjectName(QStringLiteral("action_6"));
        action_2 = new QAction(picture);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_4 = new QAction(picture);
        action_4->setObjectName(QStringLiteral("action_4"));
        action_4->setCheckable(true);
        action_4->setChecked(true);
        action_7 = new QAction(picture);
        action_7->setObjectName(QStringLiteral("action_7"));
        action_7->setMenuRole(QAction::TextHeuristicRole);
        action_7->setIconVisibleInMenu(false);
        action_7->setPriority(QAction::NormalPriority);
        action_8 = new QAction(picture);
        action_8->setObjectName(QStringLiteral("action_8"));
        actionF11 = new QAction(picture);
        actionF11->setObjectName(QStringLiteral("actionF11"));
        actionCTRL = new QAction(picture);
        actionCTRL->setObjectName(QStringLiteral("actionCTRL"));
        action_9 = new QAction(picture);
        action_9->setObjectName(QStringLiteral("action_9"));
        action_9->setVisible(true);
        action_10 = new QAction(picture);
        action_10->setObjectName(QStringLiteral("action_10"));
        action_10->setVisible(true);
        actionNoahsai_github_io = new QAction(picture);
        actionNoahsai_github_io->setObjectName(QStringLiteral("actionNoahsai_github_io"));
        actionNoahsai_github_io_2 = new QAction(picture);
        actionNoahsai_github_io_2->setObjectName(QStringLiteral("actionNoahsai_github_io_2"));
        actionGithub_com_noahsai = new QAction(picture);
        actionGithub_com_noahsai->setObjectName(QStringLiteral("actionGithub_com_noahsai"));
        action_11 = new QAction(picture);
        action_11->setObjectName(QStringLiteral("action_11"));
        centralWidget = new QWidget(picture);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAcceptDrops(false);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(20, 10, 86, 41));
        scrollArea->setAcceptDrops(false);
        scrollArea->setStyleSheet(QStringLiteral(""));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 86, 41));
        scrollAreaWidgetContents->setAcceptDrops(false);
        scrollAreaWidgetContents->setStyleSheet(QLatin1String("#scrollAreaWidgetContents\n"
"{\n"
"background-color:qlineargradient(spread:pad, x1:0.567568, y1:1, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(94, 94, 94, 255))\n"
"}"));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setFrameShape(QFrame::NoFrame);
        label->setScaledContents(false);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        scrollArea->setWidget(scrollAreaWidgetContents);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(100, 120, 321, 231));
        docklayout = new QVBoxLayout(verticalLayoutWidget);
        docklayout->setSpacing(6);
        docklayout->setContentsMargins(11, 11, 11, 11);
        docklayout->setObjectName(QStringLiteral("docklayout"));
        docklayout->setContentsMargins(0, 0, 0, 0);
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        docklayout->addItem(verticalSpacer);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(40, 40));
        pushButton->setFocusPolicy(Qt::TabFocus);
        pushButton->setStyleSheet(QLatin1String("QPushButton\n"
"{	\n"
"background-color:  rgba(135, 175, 255, 50);\n"
"border-radius:20px;\n"
"padding:2px;\n"
"color:rgba(255,255,255,150);\n"
"font:bold;\n"
"}\n"
"QPushButton:hover\n"
"{	\n"
"background-color: rgba(135, 175, 255,200);\n"
"color:white;\n"
"}\n"
"QPushButton:checked\n"
"{	\n"
"	background-color: rgba(135, 175, 255,200);\n"
"}"));
        pushButton->setFlat(false);

        horizontalLayout_4->addWidget(pushButton);

        pushButton_2 = new QPushButton(verticalLayoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setMinimumSize(QSize(40, 40));
        pushButton_2->setFocusPolicy(Qt::TabFocus);
        pushButton_2->setStyleSheet(QLatin1String("QPushButton\n"
"{	\n"
"background-color:  rgba(135, 175, 255, 50);\n"
"border-radius:20px;\n"
"padding:2px;\n"
"color:rgba(255,255,255,150);\n"
"font:bold;\n"
"}\n"
"QPushButton:hover\n"
"{	\n"
"background-color: rgba(135, 175, 255,200);\n"
"color:white;\n"
"}\n"
"QPushButton:checked\n"
"{	\n"
"	background-color: rgba(135, 175, 255,200);\n"
"}"));

        horizontalLayout_4->addWidget(pushButton_2);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        docklayout->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 4, QSizePolicy::Minimum, QSizePolicy::Fixed);

        docklayout->addItem(verticalSpacer_2);

        picture->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(picture);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 556, 24));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QStringLiteral("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QStringLiteral("menu_4"));
        menuMade_by_noahsai = new QMenu(menu_4);
        menuMade_by_noahsai->setObjectName(QStringLiteral("menuMade_by_noahsai"));
        menu_5 = new QMenu(menuBar);
        menu_5->setObjectName(QStringLiteral("menu_5"));
        picture->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_5->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(action);
        menu_2->addAction(action_3);
        menu_2->addAction(action_5);
        menu_2->addAction(action_6);
        menu_2->addAction(action_2);
        menu_3->addAction(action_4);
        menu_4->addAction(action_7);
        menu_4->addAction(action_8);
        menu_4->addAction(actionF11);
        menu_4->addAction(actionCTRL);
        menu_4->addAction(action_11);
        menu_4->addSeparator();
        menu_4->addAction(menuMade_by_noahsai->menuAction());
        menuMade_by_noahsai->addAction(actionNoahsai_github_io_2);
        menuMade_by_noahsai->addAction(actionGithub_com_noahsai);
        menu_5->addAction(action_9);
        menu_5->addAction(action_10);

        retranslateUi(picture);

        QMetaObject::connectSlotsByName(picture);
    } // setupUi

    void retranslateUi(QMainWindow *picture)
    {
        picture->setWindowTitle(QApplication::translate("picture", "picture", Q_NULLPTR));
        action->setText(QApplication::translate("picture", "\346\211\223\345\274\200", Q_NULLPTR));
        action_3->setText(QApplication::translate("picture", "\347\225\214\351\235\242\347\255\211\345\256\275", Q_NULLPTR));
        action_5->setText(QApplication::translate("picture", "\347\225\214\351\235\242\347\255\211\351\253\230", Q_NULLPTR));
        action_6->setText(QApplication::translate("picture", "\345\256\236\351\231\205\345\244\247\345\260\217", Q_NULLPTR));
        action_2->setText(QApplication::translate("picture", "\345\205\250\345\261\217\345\210\207\346\215\242", Q_NULLPTR));
        action_4->setText(QApplication::translate("picture", "\345\210\260\345\272\225\351\203\250\350\207\252\345\212\250\345\210\207\346\215\242", Q_NULLPTR));
        action_7->setText(QApplication::translate("picture", "\342\206\220 - \344\270\212\344\270\200\345\274\240", Q_NULLPTR));
        action_8->setText(QApplication::translate("picture", "\342\206\222 - \344\270\213\344\270\200\345\274\240", Q_NULLPTR));
        actionF11->setText(QApplication::translate("picture", "F11/\345\217\214\345\207\273 - \345\205\250\345\261\217\345\210\207\346\215\242", Q_NULLPTR));
        actionCTRL->setText(QApplication::translate("picture", "CTRL+\346\273\232\350\275\256 - \347\274\251\346\224\276", Q_NULLPTR));
        action_9->setText(QApplication::translate("picture", "\351\241\272\346\227\266\351\222\210", Q_NULLPTR));
        action_10->setText(QApplication::translate("picture", "\351\200\206\346\227\266\351\222\210", Q_NULLPTR));
        actionNoahsai_github_io->setText(QApplication::translate("picture", "noahsai.github.io", Q_NULLPTR));
        actionNoahsai_github_io_2->setText(QApplication::translate("picture", "noahsai.github.io", Q_NULLPTR));
        actionGithub_com_noahsai->setText(QApplication::translate("picture", "github.com/noahsai", Q_NULLPTR));
        action_11->setText(QApplication::translate("picture", "\350\207\252\345\212\250\345\210\207\346\215\242\351\234\200\351\242\235\345\244\226\346\273\232\345\212\2504\346\254\241", Q_NULLPTR));
        label->setText(QString());
        pushButton->setText(QApplication::translate("picture", "<", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("picture", ">", Q_NULLPTR));
        menu->setTitle(QApplication::translate("picture", "\346\226\207\344\273\266", Q_NULLPTR));
        menu_2->setTitle(QApplication::translate("picture", "\346\230\276\347\244\272", Q_NULLPTR));
        menu_3->setTitle(QApplication::translate("picture", "\345\210\207\346\215\242\345\233\276\347\211\207", Q_NULLPTR));
        menu_4->setTitle(QApplication::translate("picture", "\345\270\256\345\212\251", Q_NULLPTR));
        menuMade_by_noahsai->setTitle(QApplication::translate("picture", "Made by noahsai", Q_NULLPTR));
        menu_5->setTitle(QApplication::translate("picture", "\346\227\213\350\275\254", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class picture: public Ui_picture {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PICTURE_H
