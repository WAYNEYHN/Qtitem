#ifndef AUDIO_H
#define AUDIO_H

#include <QWidget>
#include <QAudioFormat>
#include <QAudioDeviceInfo>
#include <QMessageBox>
#include <QAudioInput>
#include <QFile>
#include <QTimer>
#include <QDebug>
#include <QEventLoop>
class Audio : public QWidget
{
    Q_OBJECT
public:
    explicit Audio(QWidget *parent = 0);

    //参数0：不会自动结束录音
    //参数1：3秒自动结束录音
    void startAudio(QString fileName, int flag = 0);


signals:


public slots:
    void stopAudio();
private:
    QAudioInput *m_Audio;
    QFile *m_file;
};

#endif // AUDIO_H
