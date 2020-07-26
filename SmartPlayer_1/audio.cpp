#include "audio.h"

Audio::Audio(QWidget *parent) : QWidget(parent)
{

}

/**
 * @brief Audio::startAudio
 * @param fileName
 * @param flag   默认为0，如果传入参数1则会录音3秒并保存
 */
void Audio::startAudio(QString fileName, int flag)
{
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultInputDevice();
    if(device.isNull())  //录音设备不存在
    {
        QMessageBox::warning(NULL, "QAudioDeviceInfo", "录音设备不存在");
    }
    else
    {
        //音频编码要求
        QAudioFormat m_format;
        m_format.setSampleRate(16000); //设置采样频率
        m_format.setChannelCount(1); //设置声道
        m_format.setSampleSize(16); //设置位深
        m_format.setCodec("audio/pcm");


        //判断设备是否支持该格式
        if(!device.isFormatSupported(m_format))
        {
            m_format = device.nearestFormat(m_format);
        }
        //打开文件
        m_file = new QFile();
        m_file->setFileName(fileName);
        m_file->open(QIODevice::WriteOnly);

        //录音对象
        m_Audio = new QAudioInput(m_format, this);
        m_Audio->start(m_file);
        qDebug() << "开始录音";
        if(flag == 1)
        {
              QEventLoop l;
              QTimer::singleShot(3000, this, SLOT(stopAudio()));
              QTimer::singleShot(3000, &l, &QEventLoop::quit);
              l.exec();
        }

    }


}

void Audio::stopAudio()
{
    //停止录音
    m_Audio->stop();
    //关闭文件
    m_file->close();
    //删除文件对象
    delete m_file;

    m_file = NULL;
}

