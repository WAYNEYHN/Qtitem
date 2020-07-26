#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>


#include "audio.h"
#include "speech2text.h"
#include "text2speech.h"
#include "robot.h"
#include <QSound>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_pressed();

    void on_pushButton_released();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    QString getJson(QByteArray str);
    void on_pushButton_4_clicked();
    void stopRecord();

private:
    Ui::Widget *ui;
    Audio *audio; //在自动聊天中
    QMediaPlayer *Player;
    Audio *audio_1 ;

};

#endif // WIDGET_H
