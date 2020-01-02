#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <label_click.h>
#include <QListWidgetItem>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



private slots:

    void clock();

    void label_3_clicked();
    void label_4_clicked();
    void label_5_clicked();
    void label_6_clicked();
    void label_7_clicked();
    void label_10_clicked();
    void label_11_clicked();
    void label_12_clicked();
    void label_13_clicked();
    void label_14_clicked();
    void label_15_clicked();
    void label_18_clicked();
    void label_20_clicked();
    void label_22_clicked();

    void ShowTextEditMenu(QPoint);

    void onMediaStatusChanged(QMediaPlayer::MediaStatus);
    void dir_find_files(QString dir);
    void previous_error();
    void on_playProgressUpdate();

    void on_dial_sliderMoved(int position);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_horizontalSlider_sliderMoved(int position);
    void on_horizontalSlider_sliderPressed();//偵測物件slider事件press

private:

    Ui::MainWindow *ui;
    QTimer *clocktimer;
    QTimer *pictimer;
    QMediaPlayer *player;
    QMediaPlaylist * playlist;
    QTimer *progressTimer;
    QFileDialog *file;


    int favor=0;
    int player_PlaybackMode=0;
    int bg_picture=0;
    int control_button=0;
    QString path_dir;

};
#endif // MAINWINDOW_H
