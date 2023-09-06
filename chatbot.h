#ifndef CHATBOT_H
#define CHATBOT_H

#include <QObject>
#include <QTimer>
#include <QSqlQuery>
#include <QSqlQueryModel>


class ChatBot : public QObject
{
    Q_OBJECT

public:
    explicit ChatBot(QObject *parent = nullptr);

public slots:
    void receiveMessage(const QString& message);

signals:
    void sendMessage(const QString& message);

private:
    QString processMessage(const QString& message);
};

#endif // CHATBOT_H
