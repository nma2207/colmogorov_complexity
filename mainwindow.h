#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QGraphicsView>
QT_BEGIN_NAMESPACE
class QGraphicsView;
class QLineEdit;
class QPushButton;
class QTextEdit;
class QLabel;
class QAction;
QT_END_NAMESPACE



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QLabel *enterTextLabel;
    QLineEdit* text;
    QLabel *bfCodeLabel;
    QTextEdit *bfCode;
    QLabel *bfCodeLengthLabel;
    QLineEdit *bfCodeLength;
    QLabel *compresCodeLabel;
    QTextEdit *compresCode;
    QLabel *compresCodeLengthLabel;
    QLineEdit *compresCodeLength;
    QPushButton *translateButton;
    QAction *clearAllAction;
    QAction *exitAction;
    QAction *saveAction;
    QAction *saveToTxtAction;
    QAction *openAction;
    QAction *runAction;
    QAction *aboutAction;
    QMenu *fileMenu;
    QMenu *aboutMenu;
    QMenu *runMenu;
    QToolBar *toolBar;
    void createActions();
    void createMenus();
    void createToolBar();
    QString translateStringToBF(QString);
    QString compressCode(QString );
private slots:
    void translateButClick();
    void clear();
    void save();
    void open();
    void about();
    void saveToTxt();
};

#endif // MAINWINDOW_H
