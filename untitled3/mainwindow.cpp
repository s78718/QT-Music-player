#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMediaMetaData>
#include <QString>
#include <QMessageBox>
#include <QTextCodec>
#include <QProcess>
#include <QMenu>
#include <database.h>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{ 
    //連結資料庫
    database d;
    d.createConnection();
    d.createTable();
    d.insert();
    d.queryAll();


    ui->setupUi(this);
    //固定視窗大小
    this->setFixedSize(this->width(),this->height());
    //設定list為隱藏
    ui->listWidget->setVisible(false);
    ui->listWidget_2->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->label_21->setVisible(false);
    ui->label_22->setVisible(false);

    connect(ui->label_3, SIGNAL(mousepress()), this, SLOT(label_3_clicked()));
    connect(ui->label_4, SIGNAL(mousepress()), this, SLOT(label_4_clicked()));
    connect(ui->label_5, SIGNAL(mousepress()), this, SLOT(label_5_clicked()));
    connect(ui->label_6, SIGNAL(mousepress()), this, SLOT(label_6_clicked()));
    connect(ui->label_7, SIGNAL(mousepress()), this, SLOT(label_7_clicked()));
    connect(ui->label_10, SIGNAL(mousepress()), this, SLOT(label_10_clicked()));
    connect(ui->label_11, SIGNAL(mousepress()), this, SLOT(label_11_clicked()));
    connect(ui->label_12, SIGNAL(mousepress()), this, SLOT(label_12_clicked()));
    connect(ui->label_13, SIGNAL(mousepress()), this, SLOT(label_13_clicked()));
    connect(ui->label_14, SIGNAL(mousepress()), this, SLOT(label_14_clicked()));
    connect(ui->label_15, SIGNAL(mousepress()), this, SLOT(label_15_clicked()));
    connect(ui->label_18, SIGNAL(mousepress()), this, SLOT(label_18_clicked()));
    connect(ui->label_20, SIGNAL(mousepress()), this, SLOT(label_20_clicked()));
    connect(ui->label_22, SIGNAL(mousepress()), this, SLOT(label_22_clicked()));

    connect(ui->label,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ShowTextEditMenu(QPoint)));

    //connect(player ,SIGNAL(positionChanged(qint64 position)), this, SLOT(musicPositionChange(qint64 position)));
    connect(ui->dial,SIGNAL(sliderMoved(int position)),this,SLOT(on_dial_sliderMoved(int position)));
    connect(ui->listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem *item)),this,SLOT(on_listWidget_itemDoubleClicked(QListWidgetItem *item)));
    connect(ui->horizontalSlider,SIGNAL(sliderMoved(int position)),this,SLOT(on_horizontalSlider_sliderMoved(int position)));
    connect(ui->horizontalSlider,SIGNAL(sliderPressed()),this,SLOT(on_horizontalSlider_sliderPressed()));

    //音樂進度條
    progressTimer = new QTimer(this);
    connect(progressTimer,SIGNAL(timeout()),this,SLOT(on_playProgressUpdate()));
    progressTimer->start(1000);

    //掃描目前時間
    clocktimer = new QTimer(this);
    connect(clocktimer, SIGNAL(timeout()), this, SLOT(clock()));
    clocktimer->start(500);

    //初始化音樂設定
    playlist = new QMediaPlaylist();
    player = new QMediaPlayer;
    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));


    //設置音量 循環
    player->setVolume(80);
    playlist->setPlaybackMode(QMediaPlaylist::Sequential);

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_horizontalSlider_sliderPressed()
{

    //點擊移動進度條
    int value=ui->horizontalSlider->sliderPosition();
    qint64 duction=player->duration();
    int max=ui->horizontalSlider->maximum();
    player->setPosition(duction*value/max);


}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    //橫桿移動
    double percent = (position*1.0)/(ui->horizontalSlider->maximum());
    double value = (player->duration())*percent;
    player->setPosition(int(value));

}

void MainWindow::on_playProgressUpdate()
{

    //秒數 進度條
    qint64 pos = player->position();
    qint64 duration = player->duration();
    double value = (1.0*pos/duration)*100;
    ui->horizontalSlider->setValue(int(value));

    //秒數
    int sec=player->position()/1000%60;
    ui->lcdNumber_3->display(sec);
    int min=player->position()/1000/60%60;
    ui->lcdNumber_4->display(min);

    int all_sec=player->duration()/1000%60;
    ui->lcdNumber_5->display(all_sec);
    int all_min=player->duration()/1000/60%60;
    ui->lcdNumber_6->display(all_min);

    //偵測下一首
    double next=player->position()*1.0/player->duration()*1.0;

    if((next >= 0.00 && next<=0.10 )|| (next >= 0.85 && next <=0.95))
    {
        ui->label_17->setText("Next~~~~\r\n" + playlist->media(playlist->nextIndex()).canonicalUrl().fileName());
    }
    else
    {
        ui->label_17->setText("");
    }


}


void MainWindow::on_dial_sliderMoved(int position)
{
    //音量
    player->setVolume(position);
}


void MainWindow::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    //QListWidgetItem *item

    player->playlist()->setCurrentIndex(ui->listWidget->currentRow());
    ui->label_2->setText(player->currentMedia().canonicalUrl().fileName());

}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus)
{

    if (player->LoadedMedia)
    {
        //抓目前撥放歌第幾首
        ui->label_16->setText(QString::number(playlist->currentIndex()+1)+" / " +QString::number(playlist->mediaCount()));

        //抓檔案名
        ui->label_2->setText(player->currentMedia().canonicalUrl().fileName());

        //抓取播放位置
        ui->listWidget->row(ui->listWidget->findItems(playlist->currentMedia().canonicalUrl().fileName(),Qt::MatchContains)[0]);

        //追蹤list曲目位置
        ui->listWidget->setCurrentRow(playlist->currentIndex());

        //歌曲圖片
        QImage cover=player->metaData("ThumbnailImage").value<QImage>();
        QPixmap pix=QPixmap::fromImage(cover);
        ui->label_7->setPixmap(pix);

        //歌曲演唱者
        QString actor=player->metaData("Author").toString();
        ui->label_8->setText(actor);

        //歌曲專輯
        QString album=player->metaData("Title").toString();
        ui->label_9->setText(album);

        //歌曲資訊
        ui->textEdit->clear();
        for(int i=0;i<player->availableMetaData().size();i++)
        {
            ui->textEdit->append(player->availableMetaData().at(i)+" : "+player->metaData(player->availableMetaData().at(i)).toString());
        }
        ui->textEdit->setReadOnly(true);
        ui->textEdit->setLineWrapColumnOrWidth(100);

        //讀取歌詞(須放在同音樂目錄內且同名)
        ui->listWidget_2->clear();

        QFile lrc_file(playlist->currentMedia().canonicalUrl().path().replace(".mp3",".txt").mid(1).toUtf8());//前面多一斜線濾除

        if (lrc_file.open(QIODevice::ReadOnly))
        {

            QTextStream lrc_read(&lrc_file);

            lrc_read.setCodec("UTF-8");
            while(!lrc_read.atEnd())
            {
                QString word=lrc_read.readLine();
                ui->listWidget_2->addItem(word.mid(word.lastIndexOf("]")+1));

            }
        }

        lrc_file.close();
    }

}


void MainWindow::clock()
{
    //時間
    QDateTime curDateTime=QDateTime::currentDateTime();
    int hour = curDateTime.time().hour();//?前的小?
    ui->lcdNumber->display(hour);

    int minute = curDateTime.time().minute();//?前的分
    ui->lcdNumber_2->display(minute);

}


void MainWindow::label_3_clicked()
{
    //play &pause
    if(!playlist->isEmpty())
    {
        if(player->state()==player->PlayingState)
        {

            ui->label_3->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-play-button-50"));
            player->pause();
        }
        else
        {

            ui->label_3->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-pause-squared-50"));
            player->play();
        }
    }

}

void MainWindow::label_5_clicked()
{
    //PREVIOUS
    if(!playlist->isEmpty())
    {

        playlist->next();
        ui->label_2->setText(player->currentMedia().canonicalUrl().fileName());

    }
}


void MainWindow::previous_error()
{


}


void MainWindow::label_4_clicked()
{
    //NEXT
    if(!playlist->isEmpty())
    {

        playlist->previous();

        ui->label_2->setText(player->currentMedia().canonicalUrl().fileName());

    }
}

void MainWindow::label_6_clicked()
{

    ui->listWidget_2->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->label_22->setVisible(false);

    if(ui->listWidget->isVisible()==true)
    {
        ui->label_21->setVisible(false);
        ui->listWidget->setVisible(false);
    }
    else
    {
        ui->label_21->setText(QString::fromLocal8Bit("目前播放"));
        ui->label_21->setVisible(true);
        ui->listWidget->setVisible(true);
    }

}

void MainWindow::label_7_clicked()
{
    ui->listWidget_2->setVisible(false);
    ui->listWidget->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->label_22->setVisible(false);

    if(ui->textEdit->isVisible()==false)
    {
        ui->label_21->setText(QString::fromLocal8Bit("歌曲資訊"));
        ui->label_21->setVisible(true);
        ui->textEdit->setVisible(true);
    }
    else
    {
        ui->label_21->setVisible(false);
        ui->textEdit->setVisible(false);
    }


}


void MainWindow::label_10_clicked()
{
    ui->textEdit->setVisible(false);
    ui->listWidget->setVisible(false);
    ui->textEdit_2->setVisible(false);
    ui->label_22->setVisible(false);

    if(ui->listWidget_2->isVisible()==false)
    {
        ui->label_21->setText(QString::fromLocal8Bit("歌詞"));
        ui->label_21->setVisible(true);
        ui->listWidget_2->setVisible(true);
    }
    else
    {
        ui->label_21->setVisible(false);
        ui->listWidget_2->setVisible(false);
    }


}

void MainWindow::label_11_clicked()
{
    //不刪除舊list 採加入法
    ui->listWidget->setVisible(false);
    ui->textEdit->setVisible(false);

    QMessageBox msgBox;
    msgBox.setWindowTitle(QString::fromLocal8Bit("加入音樂"));
    msgBox.setText(QString::fromLocal8Bit("保留播放清單,並加入新歌曲"));
    msgBox.setInformativeText(QString::fromLocal8Bit("選擇檔案夾或是檔案"));
    msgBox.addButton(QString::fromLocal8Bit("資料夾"),QMessageBox::AcceptRole);
    msgBox.addButton(QString::fromLocal8Bit("檔案"),QMessageBox::ActionRole);
    msgBox.addButton(QString::fromLocal8Bit("取消"),QMessageBox::RejectRole);
    int ret = msgBox.exec();

    switch (ret) {
    case 0:
    {
        //開啟資料夾格式
        QString path_dir=file->getExistingDirectory(nullptr,tr("Finding Dir Music"));

        if(!path_dir.isEmpty())
        {
            //內含資料夾
            //(遞迴)
            dir_find_files(path_dir);
            ui->label_3->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-pause-squared-50"));
            player->play();
        }

        break;
    }

    case 1:
    {
        //開啟檔案格式

        QStringList path=file->getOpenFileNames(nullptr,tr("Finding Music"),".", tr("Files (*.mp3 *.wav)"));

        if(!path.isEmpty())
        {

            foreach(QString pa,path)
            {
                playlist->addMedia(QUrl::fromLocalFile(pa));
                QStringList last=pa.split("/");
                ui->listWidget->addItem(last.last());

            }

            ui->label_3->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-pause-squared-50"));
            player->play();
        }

        break;
    }

    case 2:
    {
        msgBox.close();
        break;

    }

    }


}



void MainWindow::dir_find_files(QString path_dir)
{
    //遞迴找裡面資料夾 label12 label11

    QDir dir(path_dir);
    dir.setFilter(QDir::Dirs|QDir::Files);
    foreach (QFileInfo d,dir.entryInfoList())
    {
        if(d.isDir())
        {
            //避開上層資料夾
            if(d.fileName()=="."||d.fileName()=="..")
            {
                continue;
            }
            else
            {
                //找深一層資料夾(遞迴)
                dir_find_files(d.filePath());
            }
        }

        else
        {
            //檔案輸出list playist
            if(d.filePath().contains(".mp3")||d.filePath().contains(".wav"))
            {
                playlist->addMedia(QUrl::fromLocalFile(d.filePath()));
                QStringList last=d.filePath().split("/");
                ui->listWidget->addItem(last.last());
            }
        }

    }

}


void MainWindow::label_12_clicked()
{
    //刪除舊list 加入新list
    ui->listWidget->setVisible(false);
    ui->textEdit->setVisible(false);

    QMessageBox msgBox;
    msgBox.setWindowTitle(QString::fromLocal8Bit("加入音樂"));
    msgBox.setText(QString::fromLocal8Bit("清空播放清單,並加入新歌曲"));
    msgBox.setInformativeText(QString::fromLocal8Bit("選擇檔案夾或是檔案"));
    msgBox.addButton(QString::fromLocal8Bit("資料夾"),QMessageBox::AcceptRole);
    msgBox.addButton(QString::fromLocal8Bit("檔案"),QMessageBox::ActionRole);
    msgBox.addButton(QString::fromLocal8Bit("取消"),QMessageBox::RejectRole);
    int ret = msgBox.exec();

    switch (ret) {
    case 0:
    {
        //開啟資料夾格式
        path_dir=file->getExistingDirectory(nullptr,tr("Finding Dir Music"));

        if(!path_dir.isEmpty())
        {
            //內含資料夾
            player->unbind(playlist);
            playlist->clear();
            ui->listWidget->clear();
            //(遞迴)
            dir_find_files(path_dir);

            player->setPlaylist(playlist);
            ui->label_3->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-pause-squared-50"));
            player->play();
        }

        break;
    }

    case 1:
    {
        //開啟檔案格式

        QStringList path=file->getOpenFileNames(nullptr,tr("Finding Music"),".", tr("Files (*.mp3 *.wav )"));

        if(!path.isEmpty())
        {

            player->unbind(playlist);
            playlist->clear();
            ui->listWidget->clear();
            foreach(QString pa,path)
            {
                playlist->addMedia(QUrl::fromLocalFile(pa));
                QStringList last=pa.split("/");
                ui->listWidget->addItem(last.last());

            }

            player->setPlaylist(playlist);
            ui->label_3->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-pause-squared-50"));
            player->play();
        }

        break;
    }

    case 2:
    {
        msgBox.close();
        break;

    }

    }

}


void MainWindow::label_13_clicked()
{

    //歌曲循環模式
    if(player_PlaybackMode==0)
    {
        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        ui->label_13->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-1st-50.png"));
        player_PlaybackMode=1;
    }
    else if(player_PlaybackMode==1)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Random);
        ui->label_13->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-shuffle-50.png"));
        player_PlaybackMode=2;
    }
    else if (player_PlaybackMode==2)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        ui->label_13->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-replay-50.png"));
        player_PlaybackMode=3;
    }

    else if(player_PlaybackMode==3)
    {
        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
        ui->label_13->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-n-50.png"));
        player_PlaybackMode=0;
    }


}

void MainWindow::label_14_clicked()
{

    //隱藏控制鈕
    if(control_button==0)
    {
        ui->label_6->setVisible(false);
        ui->label_10->setVisible(false);
        ui->label_11->setVisible(false);
        ui->label_3->setVisible(false);
        ui->label_4->setVisible(false);
        ui->label_5->setVisible(false);
        ui->label_12->setVisible(false);
        ui->label_13->setVisible(false);
        ui->label_18->setVisible(false);
        ui->label_21->setVisible(false);
        ui->listWidget->setVisible(false);
        ui->listWidget_2->setVisible(false);
        ui->textEdit->setVisible(false);
        ui->horizontalSlider->setVisible(false);
        control_button=1;
    }
    else
    {
        ui->label_6->setVisible(true);
        ui->label_10->setVisible(true);
        ui->label_11->setVisible(true);
        ui->label_3->setVisible(true);
        ui->label_4->setVisible(true);
        ui->label_5->setVisible(true);
        ui->label_12->setVisible(true);
        ui->label_13->setVisible(true);
        ui->label_18->setVisible(true);
        ui->horizontalSlider->setVisible(true);
        control_button=0;
    }
}

void MainWindow::label_15_clicked()
{
    //更換桌布
    if (bg_picture==0)
    {
        ui->label->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/43678226495_8fa7997ed0_o-1400x933.jpg"));
        bg_picture=1;
    }
    else if (bg_picture==1)
    {
        ui->label->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/46808914365_c7e3ab9153_o-1400x1049.jpg"));
        bg_picture=2;
    }
    else if(bg_picture==2)
    {
        ui->label->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/binoculars-fog-foggy-1136815-1400x863.jpg"));
        bg_picture=3;
    }
    else if(bg_picture==3)
    {
        ui->label->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/16920916207_9dccf15ef1_o-1400x930.jpg"));
        bg_picture=4;
    }
    else if(bg_picture==4)
    {
        ui->label->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/DSC07827mm.jpg"));
        bg_picture=5;
    }
    else if(bg_picture==5)
    {
        ui->label->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/woman-wanderer_4460x4460-1400x933.jpg"));
        bg_picture=6;
    }
    else if(bg_picture==6)
    {
        ui->label->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/maxime-staudenmann-122479.jpg"));
        bg_picture=7;
    }
    else if(bg_picture==7)
    {
        ui->label->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/hiking-icelands-fields_4460x4460-1400x933.jpg"));
        bg_picture=8;
    }
    else if(bg_picture==8)
    {

        ui->label->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/StockSnap_2OFIOYTTWR-1400x904.jpg"));
        bg_picture=0;
    }

}

void MainWindow::label_18_clicked()
{
    //寫入歌詞
    ui->listWidget->setVisible(false);
    ui->listWidget_2->setVisible(false);
    ui->textEdit->setVisible(false);
    ui->label_21->setVisible(false);

    if(ui->textEdit_2->isVisible()==false)
    {
        ui->textEdit_2->clear();
        QMessageBox msgBox;
        msgBox.setWindowTitle(QString::fromLocal8Bit("加入歌詞"));
        msgBox.setText(QString::fromLocal8Bit("是否要加入目前播放歌曲歌詞"));
        msgBox.setInformativeText(QString::fromLocal8Bit("(接受動態歌詞與普通歌詞)"));
        msgBox.addButton(QString::fromLocal8Bit("確定"),QMessageBox::AcceptRole);
        msgBox.addButton(QString::fromLocal8Bit("取消"),QMessageBox::RejectRole);
        int ret = msgBox.exec();

        switch (ret) {
        case 0:
        {
            ui->textEdit_2->setVisible(true);
            ui->label_21->setVisible(true);
            ui->label_21->setText(QString::fromLocal8Bit("編輯歌詞"));
            ui->label_22->setVisible(true);

            break;
        }

        case 1:

            break;

        }

    }
    else
    {

        ui->textEdit_2->setVisible(false);
        ui->label_21->setVisible(false);
        ui->label_22->setVisible(false);
        //QDir dir(playlist->currentMedia().canonicalUrl().path().toUtf8());
        //dir.cdUp();
        //QString path= file->getOpenFileName(nullptr,tr("Opening Dir of CurrentMusic"),dir.path(),tr("Files (*.txt)"));

    }

}


void MainWindow::label_22_clicked()
{
    ui->textEdit_2->setVisible(false);
    ui->label_21->setVisible(false);
    ui->label_22->setVisible(false);
    QMessageBox msgBox;
    msgBox.setWindowTitle(QString::fromLocal8Bit("儲存"));
    msgBox.setText(QString::fromLocal8Bit("確定歌詞正確?"));
    msgBox.setInformativeText(QString::fromLocal8Bit("將歌詞存到與歌同資料夾內,並儲存成同歌曲名稱.txt"));
    msgBox.addButton(QString::fromLocal8Bit("確定"),QMessageBox::AcceptRole);
    msgBox.addButton(QString::fromLocal8Bit("取消"),QMessageBox::RejectRole);
    int ret = msgBox.exec();

    switch (ret) {
    case 0:

    {
        QFile lrc_file(player->currentMedia().canonicalUrl().path().mid(1).replace(".mp3",".txt").replace(".wav",".txt").toUtf8()); //路徑由mp3 wav改為txt

        if (lrc_file.open(QIODevice::WriteOnly| QIODevice::Text))
        {

            QTextStream lrc_write(&lrc_file);
            lrc_write.setCodec("UTF-8");
            lrc_write << ui->textEdit_2->toPlainText();

        }

        lrc_file.close();

        break;
    }

    case 1:
    {

        break;
    }
    }
}

void MainWindow::ShowTextEditMenu(QPoint)
{

    //右鍵選單
    QMenu *texteditmenu = new QMenu(ui->label);

    QAction *add_song_clearaction = new QAction(QString::fromLocal8Bit("加入歌曲/清除清單"),ui->label);
    connect(add_song_clearaction,SIGNAL(triggered()),this,SLOT(label_12_clicked()));

    QAction *add_songaction = new QAction(QString::fromLocal8Bit("加入歌曲/保留清單"),ui->label);
    connect(add_songaction,SIGNAL(triggered()),this,SLOT(label_11_clicked()));

    QAction *uiaction = new QAction(QString::fromLocal8Bit("開啟/隱藏介面"),ui->label);
    connect(uiaction,SIGNAL(triggered()),this,SLOT(label_14_clicked()));

    QAction *desktopaction = new QAction(QString::fromLocal8Bit("更換桌布"),ui->label);
    connect(desktopaction,SIGNAL(triggered()),this,SLOT(label_15_clicked()));

    QAction *previousaction = new QAction(QString::fromLocal8Bit("上一首"),ui->label);
    connect(previousaction,SIGNAL(triggered()),this,SLOT(label_4_clicked()));

    QAction *nextaction = new QAction(QString::fromLocal8Bit("下一首"),ui->label);
    connect(nextaction,SIGNAL(triggered()),this,SLOT(label_5_clicked()));


    QAction *playaction ;
    playaction = new QAction(QString::fromLocal8Bit("播放/暫停"),ui->label);
    connect(playaction,SIGNAL(triggered()),this,SLOT(label_3_clicked()));


    QAction *lrcaction = new QAction(QString::fromLocal8Bit("歌詞"),ui->label);
    connect(lrcaction,SIGNAL(triggered()),this,SLOT(label_10_clicked()));

    QAction *addlrcaction = new QAction(QString::fromLocal8Bit("加入歌詞"),ui->label);
    connect(addlrcaction,SIGNAL(triggered()),this,SLOT(label_18_clicked()));

    QAction *listaction = new QAction(QString::fromLocal8Bit("目前正在播放清單"),ui->label);
    connect(listaction,SIGNAL(triggered()),this,SLOT(label_6_clicked()));

    QAction *songaction = new QAction(QString::fromLocal8Bit("歌曲資訊"),ui->label);
    connect(songaction,SIGNAL(triggered()),this,SLOT(label_7_clicked()));


    QAction *playbackaction;
    if(player_PlaybackMode==0)
    {
        playbackaction = new QAction(QString::fromLocal8Bit("播放模式-正常"),ui->label);
    }
    if(player_PlaybackMode==1)
    {
        playbackaction = new QAction(QString::fromLocal8Bit("播放模式-單曲"),ui->label);
    }
    if (player_PlaybackMode==2)
    {
        playbackaction = new QAction(QString::fromLocal8Bit("播放模式-隨機"),ui->label);
    }
    if (player_PlaybackMode==3)
    {
        playbackaction = new QAction(QString::fromLocal8Bit("播放模式-全部循環"),ui->label);
    }
    connect(playbackaction,SIGNAL(triggered()),this,SLOT(label_13_clicked()));

    texteditmenu->addAction(listaction);
    texteditmenu->addSection("-------------");
    texteditmenu->addAction(add_song_clearaction);
    texteditmenu->addAction(add_songaction);
    texteditmenu->addSection("-------------");
    texteditmenu->addAction(playbackaction);
    texteditmenu->addSection("-------------");
    texteditmenu->addAction(playaction);
    texteditmenu->addAction(previousaction);
    texteditmenu->addAction(nextaction);
    texteditmenu->addSection("-------------");
    texteditmenu->addAction(songaction);
    texteditmenu->addAction(lrcaction);
    texteditmenu->addAction(addlrcaction);
    texteditmenu->addSection("-------------");
    texteditmenu->addAction(uiaction);
    texteditmenu->addAction(desktopaction);

    texteditmenu->move(cursor().pos());
    texteditmenu->show();
}


void MainWindow::label_20_clicked()
{
    //是否為最愛
    if(favor==0)
    {

        ui->label_20->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-heart-outline-48.png"));
        favor=1;

    }
    else
    {
        ui->label_20->setPixmap(QPixmap("C:/Users/s7871/Pictures/Saved Pictures/icon/icons8-love-24.png"));
        favor=0;
    }

}

