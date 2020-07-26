#include "text2speech.h"
#include "widget.h"
#include "speech2text.h"
text2Speech::text2Speech(QWidget *parent) : QWidget(parent)
{

}


//调用两次postSync
/**
 * @brief text2Speech::playeText
 * @param text  需要发给服务器进行语音合成的QString
 * @return      服务器返回的token和text组装的url
 */
QByteArray text2Speech::playeText(QString text)
{

   QString accessToken;

   //获取token
   QString tokenUrl = QString(baiduToken).arg(client_id).arg(client_secret);
   Speech m_speech;   //创建Speech对象方便进行Json解析

   QMap<QString, QString> header;
   header.insert(QString("Content-Type"), QString("audio/pcm;rate=16000"));
   QByteArray requestData;
   QByteArray replyData;  //服务器返回的数据

   GetToken m_GetToken;
   bool result = m_GetToken.postSync(tokenUrl, header, requestData, replyData);
   if(result)
   {
       QString key = "access_token";
       accessToken = m_speech.getJsonValue(replyData, key);
       qDebug() << accessToken;
   }
   else
   {
        this->close();
   }

    //组成url
    QByteArray url="http://tsn.baidu.com/text2audio?";
    url.append("&tex=");//lan固定为zh,中英文混合识别，per朗读人，aue返回语音格式
    url.append(QUrl::toPercentEncoding(text));
    url.append(QString("&lan=zh&cuid=hqyj&ctp=1&tok="+accessToken+"&pit=8&per=3"));//语音合成参数
    qDebug()<<"百度语音合成Url检测："<<url;
    return url;
}


