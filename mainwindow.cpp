#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(WINDOW_WIDTH, WINDOW_HEIGHT));
    this->setWindowFlags(Qt::Window|Qt::FramelessWindowHint);
    QPalette pal;
    pal.setBrush(QPalette::Window, QPixmap(":/new/images/images/bg_main.png"));
    this->setPalette(pal);

    // create folder
    QString filePath = QDir::currentPath() + "/feature/";
    QDir dir1(filePath);
    if(!dir1.exists())
    {
        dir1.mkpath(".");
    }

    QString filePath_image= QDir::currentPath() + "/temp/";
    QDir dir(filePath_image);
    if(!dir.exists())
    {
        dir.mkpath(".");
    }

    QString filePath_hist= QDir::currentPath() + "/history/";
    QDir dir2(filePath_hist);
    if(!dir2.exists())
    {
        dir2.mkpath(".");
    }
    else
    {
        // remove history
        foreach (QString file, dir2.entryList()) {
            dir2.remove(file);
        }
    }

    PreferenceHandler::getInstance()->readXMLDom();

    // display time
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    // remove history


    // check license

    CheckLicenseThread *thread = new CheckLicenseThread();
    connect(thread, SIGNAL(startValidateLicense()), this, SLOT(startLicenseChecking()));
    connect(thread, SIGNAL(validateLicense(bool)), this, SLOT(checkLicense(bool)));


    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnExit_clicked()
{

    FaceEngineBuilder::getEngine(FaceEngineBuilder::ENGINE_NEURO)->close();
    this->close();
}

void MainWindow::on_btnRegister_clicked()
{
    dialog = new DialogUserAnalysis_New(this);
    dialog->setModal(true);
    dialog->show();
}

void MainWindow::on_btnAnalysis_clicked()
{
    dialog = new DialogUserAnalysis_New(this);
    dialog->setModal(true);
    dialog->show();

}

void MainWindow::on_btnUserList_clicked()
{
    DialogUserList_New *userList = new DialogUserList_New(this);
    userList->setModal(true);
    userList->show();
}

void MainWindow::on_btnSetting_clicked()
{
    DialogSetting *setting = new DialogSetting(this);
    setting->setModal(true);
    setting->show();
}
void MainWindow::showTime()
{
    QDateTime dateTime = QDateTime::currentDateTime();
    //ui->labelTime->setText(dateTime.toString("yyyyMMddhhmmss"));
    ui->labelTime->setText("<span style=\"color:#ffffff;\">" + dateTime.toString("yyyy.MM.dd hh:mm:ss") +"</span>");

}
void MainWindow::startLicenseChecking(){
    msgBox = new QMessageBox(this);
    msgBox->setText("<span style=\"color:#000000;\">Checking License...</span>");
    msgBox->setModal(true);
    msgBox->setWindowFlags(Qt::Dialog| Qt::CustomizeWindowHint|Qt::WindowTitleHint);
    msgBox->exec();
}

void MainWindow::checkLicense(bool result){
    if(msgBox){
        if(result){
            msgBox->setText("<span style=\"color:#000000;\">License OK</span>");

        } else {
            msgBox->setText("<span style=\"color:#000000;\">License Error</span>");
        }
        //msgBox->show();
    }


}
