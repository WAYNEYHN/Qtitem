#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("第六组实训：智能语音");
    Player = new QMediaPlayer(this);
    QVideoWidget *m_videoW = new QVideoWidget(this);
    Player->setVideoOutput(m_videoW);

    this->ui->textEdit->setText("按住说话");
}

Widget::~Widget()
{
    delete ui;
}
//按下开始录音
void Widget::on_pushButton_pressed()
{
    ui->pushButton->setText("松开识别");
    audio = new Audio();
    audio->startAudio("D:\\1.pcm");

}

//松开按钮开始识别
void Widget::on_pushButton_released()
{
    //停止录音
    audio->stopAudio();
    //修改按钮文字
    ui->pushButton->setText("开始识别");

    Speech m_speech;
    QString text = m_speech.getText("D:\\1.pcm");


    ui->textEdit->setText(text);
    ui->pushButton->setText("按住说话");
    on_pushButton_3_clicked();



}

//文本转语音
void Widget::on_pushButton_2_clicked()
{

    //接收文本
    text2Speech tts;
    QString temp = ui->textEdit->toPlainText();
    //语音播放：直接通过返回的url播放
    QByteArray url = tts.playeText(temp);
    Player->setMedia(QUrl::fromLocalFile(url));
    Player->play();

}

//机器人聊天模块：智能将当前textedit中的文本发送且对话只进行一次
void Widget::on_pushButton_3_clicked()
{
    QString text = ui->textEdit->toPlainText();
    robot smartR;
    QByteArray str = smartR.Robot(text);
    QString result = getJson(str);
    ui->textEdit->setText(result);
    on_pushButton_2_clicked();
}

//解析图灵机器人发回的Json
QString Widget::getJson(QByteArray str)
{
    QJsonObject json1 = QJsonDocument::fromJson(str).object();
    QJsonArray json2 = json1.value("results").toArray();
    QJsonObject json3 = json2[0].toObject();                 //直接通过下标获取
    QJsonObject json4 = json3.value("values").toObject();
    QString text = json4.value("text").toString();
    return text;
}

//自动语音聊天实现
void Widget::on_pushButton_4_clicked()
{
    QString fileName ="E:\\2.pcm"; //存放监测文件
    QString fileName_1 = "E:\\1.pcm";//存放录音文件

    QString text ;
    QSound *sound1;//播放.wav格式
    audio_1 = new Audio();
    audio = new Audio();
    int recording = 0; //标记是否在进行通话录音

    while(1)
    {
        if(recording == 0)
        {
            //开始录音
            //参数 1 表示录音会自动结束
            audio->startAudio(fileName, 1);  //会自动停止录音的audio

            Speech m_speech;
            text = m_speech.getText(fileName);
            qDebug() << text;
        }

        if(text.contains("小"))
        {

            //表示可以开始对话录音
            recording = 1;

            sound1 = new QSound(":/ding.wav");//加载声音文件
            sound1->play();
            qDebug() << "开始录音";
            audio_1->startAudio(fileName_1, 0);
            text = "";


        }
        if(text.contains("再见"))
        {
              ui->textEdit->setText("拜拜");
              on_pushButton_2_clicked();
              break;

        }
        if(recording == 1)//正在录音
        {
            //对即将进行的对话进行录音，设置QTimer计时器，5秒后发送
             QEventLoop l;
             QTimer::singleShot(5000, this, SLOT(stopRecord()));
             QTimer::singleShot(5000, &l, &QEventLoop::quit);
             l.exec();
             //创建Speech对象，进行语音识别
             Speech m_speech;
             QString text = m_speech.getText(fileName_1);
             ui->textEdit->setText(text);

             //向图灵机器人发送textEdit的文本并输出返回的语音
             on_pushButton_3_clicked();

             //设置计时器，防止监测的audio对象录入不必要的语音
             QEventLoop l_1;
             QTimer::singleShot(2500, &l_1, &QEventLoop::quit);
             l_1.exec();

             sound1 = new QSound(":/dong.wav");//加载声音文件
             sound1->play();

             recording = 0;

        }
    }

}

void Widget::stopRecord()
{
    audio_1->stopAudio();
}
