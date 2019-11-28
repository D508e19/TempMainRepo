#ifndef _MESSAGE_H
#define _NESSAGE_H

#include <cstring>

class Message
{
private:
    char text[0];
    int length;

public:
    Message(char _text[], int _lenght);

    char* GetTextCharArray();
    char* GetTextSendFormattet();
};

Message::Message(char* _text, int _length)
{
    //char temp[_length];
    strncpy(text, _text, _length); //TODO strcpy or strncpy
}

char* Message::GetTextCharArray()
{
    return text;
}

char* Message::GetTextSendFormattet()
{
    //char temp[length + 1];
    //strcpy(temp, text);
    //temp[length + 1] = '\n';

    //return temp;
    return text;
    //return "Test";
}

#endif