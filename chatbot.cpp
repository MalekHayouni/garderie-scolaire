#include "chatbot.h"

ChatBot::ChatBot(QObject *parent) : QObject(parent)
{
}

void ChatBot::receiveMessage(const QString& message)
{
    // Use a timer to add a 2 second delay before sending the response
    QTimer::singleShot(400, [this, message]() {
        QString response = processMessage(message);
        emit sendMessage(response);
    });
}

QString ChatBot::processMessage(const QString& message)
{
    QString response;

    //get info from database
    QSqlQuery query;
    int ActivityCount = 0;
    query.prepare("SELECT COUNT(*) FROM activite");
    query.exec();
    if (query.next()) ActivityCount = query.value(0).toInt();


    // Define some default responses
    QString greetingResponse = "Hello there!";
    QString nameResponse = "Nice to meet you, ";
    QString timeResponse = "We work from 08:00 am to 05:00 pm !";
    QString activitycountResponse = "We currently have "+ QString::number(ActivityCount) + " activities";
    QString unknownResponse = "I'm sorry, I don't understand. Can you please rephrase?";

    // Split the message into individual words
    QStringList words = message.split(" ", QString::SkipEmptyParts);

    // Check for keywords in the message
    if (words.contains("hi") || words.contains("hello")) {response = greetingResponse;} 

    else if (words.contains("my") && words.contains("name")) {
        int index = words.indexOf("name");
        if (index + 1 < words.size()) {
            QString name = words.at(index + 2);
            response = nameResponse + name + "!";}
    }

    else if ((words.contains("working") && words.contains("hours")) || (words.contains("open") && words.contains("time"))) {
        response = timeResponse;
    }

    else if ((words.contains("number") || (words.contains("how") && words.contains("many"))) && words.contains("activities") ) {
        response = activitycountResponse;
    }

    else {
        response = unknownResponse;
    }

    return response;
}
