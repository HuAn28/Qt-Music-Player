#include "mymusic.h"
#include "ui_mymusic.h"
#include <QDebug>

myMusic::myMusic(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::myMusic)
{
    ui->setupUi(this);
    initUI();
    readFile();
}

myMusic::~myMusic()
{
    delete ui;
}

// 读取文件
void myMusic::readFile()
{
    // 设置要遍历的目录
    str_pathmusic = "D:/快速访问/音乐";
    QDir dir(str_pathmusic);
    // 设置文件过滤器
    QStringList nameFileters;
    nameFileters << "*.mp3";
    // 将过滤后的文件名称存入到list中
    QStringList files = dir.entryList(nameFileters, QDir::Files | QDir:: Readable, QDir::Name);
    // 添加到listwidget的item中
    ui->listWidget->addItems(files);
    // 把item加入到listwidget中
    ui->listWidget->sortItems();

    p_item = ui->listWidget->item(0);
    p_item->setSelected(true);

    connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(slot_musicListRowNum(int)));
}

void myMusic::slot_musicListRowNum(int n_number)
{
    qDebug() << n_number << endl;
    qDebug() << ui->listWidget->item(n_number)->text() << endl;
    str_music = ui->listWidget->item(n_number)->text();
    p_player = new QMediaPlayer();
    p_player->setMedia(QUrl::fromLocalFile(str_pathmusic + '/' + str_music));
    p_player->setVolume(100);
    n_music_number = n_number;
}

// 初始化界面
void myMusic::initUI()
{
    this->setWindowIcon(QIcon(":/Image/Music_Tubiao.png"));
    connect(ui->upBtn, SIGNAL(clicked()), this, SLOT(slot_upbtn_clicked()));
    connect(ui->downBtn, SIGNAL(clicked()), this, SLOT(slot_downbtn_clicked()));
    connect(ui->playBtn, SIGNAL(clicked()), this, SLOT(slot_playbtn_clicked()));

    //connect(p_player, SIGNAL(stateChanged(QMediaPlayer::StoppedState)), this, SLOT(on_Time_label));
}

void myMusic::slot_upbtn_clicked()   // 上一曲
{
    p_player->stop();
    if (n_music_number == 0) {
        int nMax = ui->listWidget->count();
        str_music =  ui->listWidget->item(nMax - 1)->text();
        p_item = ui->listWidget->item(nMax - 1);
        p_item->setSelected(true);
        QString str = str_pathmusic + '/' + str_music;

        p_player->setMedia(QUrl::fromLocalFile(str));
        p_player->setVolume(100);
        p_player->play();
        n_music_number = nMax - 1;
    }
    else {
        n_music_number = n_music_number - 1;
        str_music =  ui->listWidget->item(n_music_number)->text();
        p_item = ui->listWidget->item(n_music_number);
        p_item->setSelected(true);
        QString str = str_pathmusic + '/' + str_music;

        p_player->setMedia(QUrl::fromLocalFile(str));
        p_player->setVolume(100);
        p_player->play();
    }
    b_play_music = true;
    ui->musicLabel->setText(str_music);
    ui->playBtn->setText("暂停");
}

void myMusic::slot_downbtn_clicked() // 下一曲
{
    p_player->stop();
    int nMax = ui->listWidget->count();
    if (n_music_number == nMax - 1) {
        str_music =  ui->listWidget->item(0)->text();
        p_item = ui->listWidget->item(0);
        p_item->setSelected(true);
        QString str = str_pathmusic + '/' + str_music;

        p_player->setMedia(QUrl::fromLocalFile(str));
        p_player->setVolume(100);
        p_player->play();
        n_music_number = 0;
    }
    else {
        n_music_number = n_music_number + 1;
        str_music =  ui->listWidget->item(n_music_number)->text();
        p_item = ui->listWidget->item(n_music_number);
        p_item->setSelected(true);
        QString str = str_pathmusic + '/' + str_music;

        p_player->setMedia(QUrl::fromLocalFile(str));
        p_player->setVolume(100);
        p_player->play();
    }
    b_play_music = true;
    ui->musicLabel->setText(str_music);
    ui->playBtn->setText("暂停");
}

void myMusic::slot_playbtn_clicked() // 播放
{
    if(b_play_music)
    {
        ui->playBtn->setText("播放");
        b_play_music = false;
        p_player->pause();
        ui->musicLabel->setText(" ");
    }
    else
    {
        ui->playBtn->setText("暂停");
        b_play_music = true;
        p_player->play();
        ui->musicLabel->setText(str_music);
    }
}

