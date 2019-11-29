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

    int GetLength();
    char* GetTextCharArray();
    char* GetTextSendFormattet();
};

Message::Message(char* _text, int _length)
{
    length = _length;
    std::cout << "Message: Text: " << _text << " Length: " << _length << std::endl;
    //char temp[_length];
    strncpy(text, _text, _length); //TODO strcpy or strncpy
    std::cout << "Message: Saved msg: " << text << std::endl;
}

int Message::GetLength()
{
    return length;
}

char* Message::GetTextCharArray()
{
    std::cout << "MEssage: GetTextCharArray: " << text << " length: " << length << std::endl;
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