#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtWidgets>
#include<QList>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    createActions();
    createMenus();
    createToolBar();

    enterTextLabel=new QLabel(tr("Enter your text:"));
    text=new QLineEdit;
    bfCodeLabel=new QLabel(tr("This is code of BrainFuck:"));
    bfCode=new QTextEdit;

    bfCodeLengthLabel=new QLabel(tr("Length of code: "));
    bfCodeLength=new QLineEdit(tr("0"));
    bfCodeLength->setAlignment(Qt::AlignRight);

    bfCodeLength->setMaximumWidth(100);

    text->setMinimumWidth(200);

    bfCode->setMinimumWidth(500);
    bfCode->setMaximumHeight(500);
    compresCodeLabel=new QLabel("Compressed code:");
    compresCode=new QTextEdit;
    compresCode->setMinimumWidth(500);
    compresCode->setMaximumHeight(500);
    compresCodeLengthLabel=new QLabel("Compressed code\nlength:");
    compresCodeLength=new QLineEdit("0");
    compresCodeLength->setMaximumWidth(100);
    compresCodeLength->setAlignment(Qt::AlignRight);
    translateButton=new QPushButton(tr("Translate"));
    connect(translateButton, SIGNAL(clicked()),this,SLOT(translateButClick()));

    QGridLayout*layout1=new QGridLayout;
    layout1->addWidget(enterTextLabel,0,0);
    layout1->addWidget(text,1,0,1,3);
    layout1->addWidget(translateButton,1,3);

    QGridLayout*layout2=new QGridLayout;
    layout2->addWidget(bfCodeLabel,0,0);
    layout2->addWidget(bfCode,1,0,1,4);
    layout2->addWidget(bfCodeLengthLabel,2,0);
    layout2->addWidget(bfCodeLength,2,1);

    QGridLayout*layout3=new QGridLayout;
    layout3->addWidget(compresCodeLabel,0,0);
    layout3->addWidget(compresCode,1,0,1,4);
    layout3->addWidget(compresCodeLengthLabel,2,0);
    layout3->addWidget(compresCodeLength,2,1);

    QFrame*frame1=new QFrame(this);
    frame1->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    frame1->setLayout(layout1);

    QFrame*frame2=new QFrame(this);
    frame2->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    frame2->setLayout(layout2);

    QFrame*frame3=new QFrame(this);
    frame3->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    frame3->setLayout(layout3);

    QVBoxLayout*mainLayout=new QVBoxLayout;
    mainLayout->addWidget(frame1);
    mainLayout->addWidget(frame2);
    mainLayout->addWidget(frame3);
    QWidget*widget=new  QWidget;

    widget->setLayout(mainLayout);
    setCentralWidget(widget);
    setMinimumHeight(600);
    setMinimumWidth(600);
    setWindowTitle(tr("Kolmogorov's complexity"));
    setWindowIcon(QIcon(":/images/k.jpg"));



}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::translateStringToBF(QString s)
{
    char arr[30000];
    int arr_i = 0;
    int arr_n = 1;
    int k=0;
    for (int i=0;i<s.size();i++){
        k+=s[i].toLatin1();
    }
    k/=s.size();
    for (int i = 0; i < 30000; i++)
        arr[i] =(char)k;
    QList<QChar> res;
    for (int i = 0; s[i] != '\0'; i++){
        int min_d = 0;
        for (int j = 0;j < arr_n; j++){
            if (abs(arr[min_d] - (s[i]).toLatin1())>abs(arr[j] - (s[i]).toLatin1()))
                min_d = j;
        }
        if (min_d < arr_i){
            for (int j = 0; j < arr_i - min_d; j++){
                res.push_back('<');
            }
        }
        else{
            for (int j = 0; j < min_d - arr_i; j++){
                res.push_back('>');
            }
        }
        arr_i = min_d;
        if (s[i] >arr[arr_i]){
            for (int j = 0; j < (s[i]).toLatin1() - arr[arr_i]; j++){
                res.push_back('+');
            }
        }
        else{
            for (int j = 0; j < arr[arr_i] - (s[i]).toLatin1(); j++){
                res.push_back('-');
            }
        }
        arr[arr_i] = (s[i]).toLatin1();
        res.push_back('.');
        if (min_d == arr_n - 1)
            arr_n++;
    }
    QString res_text;
    foreach(QChar c, res)
        res_text.append(c);
    return res_text;
}
void MainWindow::translateButClick()
{
    QString bfCodeText=translateStringToBF(text->text());
    bfCode->setText(bfCodeText);
    bfCodeLength->setText(QString::number(bfCodeText.size()));
    QString compressText=compressCode(bfCodeText);
    compresCode->setText(compressText);
    compresCodeLength->setText(QString::number(compressText.size()));

}
QString MainWindow::compressCode(QString s)
{
    QList<QChar>res;
    int i=0,
        n=s.size();
    while(i<n){
        QChar c=s[i];
        int k=0;
        while(i<n  && s[i]==c){
            i++;
            k++;
        }
        if(k==1)
            res.append(c);
        else{
            foreach(QChar kChar,QString::number(k))
                res.append(kChar);
            res.append(c);
        }
    }
    QString res_text;
    foreach(QChar c, res)
        res_text.append(c);
    return res_text;
}

void MainWindow::createActions()
{
    clearAllAction=new QAction(QIcon(":/images/clear.jpg"),tr("Clear"),this);
    clearAllAction->setStatusTip(tr("Clear all text and line edits"));
    connect(clearAllAction,SIGNAL(triggered()),this, SLOT(clear()));

    exitAction=new QAction(QIcon(":images/exit.jpg"),tr("Exit"),this);
    exitAction->setShortcut(tr("Esc"));
    exitAction->setStatusTip(tr("Exit from program"));
    connect(exitAction,SIGNAL(triggered()),this,SLOT(close()));

    saveAction=new QAction(QIcon(":/images/save.jpg"),tr("Save"),this);
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save this text and this BrainFuck code"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));

    saveToTxtAction=new QAction(QIcon(":/images/savetxt.jpg"),tr("Save to txt"),this);
    saveToTxtAction->setShortcut(tr("Ctrl+D"));
    saveToTxtAction->setStatusTip(tr("Save this text and this BrainFuck code in txt file"));
    connect(saveToTxtAction,SIGNAL(triggered()),this,SLOT(saveToTxt()));

    openAction=new QAction(QIcon(":/images/open.jpg"),tr("Open"),this);
    openAction->setShortcut(tr("Ctrl+P"));
    openAction->setStatusTip(tr("Open saved text and Brainfuck code"));
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

    runAction=new QAction(QIcon(":/images/run.jpg"),tr("Run"),this);
    runAction->setShortcut(tr("Ctrl+F5"));
    runAction->setStatusTip(tr("Translate text to BrainFuck code"));
    connect(runAction,SIGNAL(triggered()),this,SLOT(translateButClick()));

    aboutAction=new QAction(QIcon(":/images/help.jpg"),tr("About"),this);
    aboutAction->setShortcut(tr("F1"));
    aboutAction->setStatusTip(tr("About this program"));
    connect(aboutAction, SIGNAL(triggered()),this,SLOT(about()));

}
void MainWindow::createMenus()
{
    fileMenu=menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(clearAllAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveToTxtAction);
    fileMenu->addAction(exitAction);

    runMenu=menuBar()->addMenu(tr("&Run"));
    runMenu->addAction(runAction);

    aboutMenu=menuBar()->addMenu(tr("&About"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolBar()
{
     toolBar=new QToolBar("tool bar");


     toolBar->addAction(openAction);
     toolBar->addSeparator();
     toolBar->addAction(saveAction);
     toolBar->addSeparator();
     toolBar->addAction(saveToTxtAction);
     toolBar->addSeparator();
     toolBar->addAction(runAction);
     toolBar->addSeparator();
     toolBar->addAction(clearAllAction);
     toolBar->setMinimumHeight(50);

     addToolBar(toolBar);
}
void MainWindow::clear()
{
    text->clear();
    bfCode->clear();
    bfCodeLength->setText("0");
    compresCode->clear();
    compresCodeLength->setText("0");
}
void MainWindow::save()
{
    QString filename=QFileDialog::getSaveFileName(this,
                                                  tr("Save Code"),"",
                                                  tr("Kolmogoro's complexity (*.klmgrvc);;All Files(*)"));
    if(filename.isEmpty())
        return;
    else
    {
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this,tr("Unaple open file"),file.errorString());
            return;
        }
        QDataStream out(&file);
        out.setVersion(QDataStream::Qt_5_6);
        out<<text->text();

    }

}
void MainWindow::open()
{
    QString filename=QFileDialog::getOpenFileName(this,
                                                  tr("Open Code"),"",
                                                  tr("Kolmogoro's complexity (*.klmgrvc);;All Files(*)"));
    if(filename.isEmpty())
        return;
    else
    {
        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this,tr("Unaple open file"),file.errorString());
            return;
        }
        QDataStream in(&file);
        in.setVersion(QDataStream::Qt_5_6);
        text->clear();
        QString s;
        in>>s;
        text->setText(s);
        translateButClick();


    }
}
void MainWindow::about()
{
    QMessageBox::about(this,tr("About this program"),tr("This program translate your text to code of BrainFuck Language"));
}
void MainWindow::saveToTxt()
{
    if(bfCode->toPlainText().isEmpty())
    {
        if(text->text().isEmpty())
        {
            QMessageBox::warning(this,tr("Warning"),tr("You don't enter text"));
            return;

        }
        else
           translateButClick();

    }
    QString filename=QFileDialog::getSaveFileName(this,
                                                  tr("Save Code"),"",
                                                  tr("Kolmogoro's complexity (*.txt);;All Files(*)"));
    if(filename.isEmpty())
        return;
    QFile file(filename);
    QTextStream stream(&file);
    if(file.open(QIODevice::WriteOnly))
    {
        stream<<text->text()<<"\n"<<bfCode->toPlainText()<<"\n"<<compresCode->toPlainText();
        file.close();
        if (stream.status() != QTextStream::Ok)
        {
            qDebug() << "Error of file write";
        }
    }
    //file.write(bfCode->toPlainText().toUtf8());
}
