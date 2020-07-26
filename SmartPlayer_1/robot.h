#ifndef ROBOT_H
#define ROBOT_H

#include <QWidget>
#include <QNetworkRequest>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QUrl>
class robot : public QWidget
{
    Q_OBJECT
public:
    explicit robot(QWidget *parent = 0);
    QByteArray Robot(QString text);
    QJsonObject JsonData(QString date);
signals:

public slots:
private:
    QByteArray result;
};

#endif // ROBOT_H
