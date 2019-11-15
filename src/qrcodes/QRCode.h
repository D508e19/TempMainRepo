#ifndef QRCODES_H
#define QRCODES_H

#include <argos3/core/utility/math/vector2.h>

class QRCode
{
private:

    argos::CVector2 position;
    
public:

    argos::CVector2 GetPosition();
    void SetPosition(argos::CVector2 newPosition);
    
    QRCode();
    ~QRCode();
};

QRCode::QRCode(){}

QRCode::~QRCode(){}

argos::CVector2 QRCode::GetPosition(){
    return position;
}

void QRCode::SetPosition(argos::CVector2 newPosition){
    position = newPosition;
}

#endif
