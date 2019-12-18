#ifndef POD_CPP
#define POD_CPP

Pod::Pod():
    id(-1)
    {}

Pod::Pod(int _id):
    id(_id)
    {}

Pod::~Pod(){}

int Pod::getId(){
    return id;
}

#endif