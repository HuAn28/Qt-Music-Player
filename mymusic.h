#ifndef MYMUSIC_H
#define MYMUSIC_H

#include <QWidget>
#include <QDir>
#include <QListWidgetItem>
#include <QMediaPlayer>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class myMusic; }
QT_END_NAMESPACE

class myMusic : public QWidget
{
    Q_OBJECT

public:
    myMusic(QWidget *parent = nullptr);
    ~myMusic();

private:
    Ui::myMusic *ui;
    QString str_pathmusic;     // 音乐文件夹位置
    QListWidgetItem* p_item;   // 音乐列表
    bool b_play_music = false; // 是否播放音乐
    QMediaPlayer* p_player;
    QString str_music;         // 播放名称
    int n_music_number;

private:
    // 读取文件
    void readFile();
    // 初始化界面
    void initUI();

private slots:
    void slot_upbtn_clicked();   // 上一曲
    void slot_downbtn_clicked(); // 下一曲
    void slot_playbtn_clicked(); // 播放
    void slot_musicListRowNum(int);
};
#endif // MYMUSIC_H
