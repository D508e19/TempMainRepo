#ifndef POD_CPP
#define POD_CPP

Pod::Pod():
    m_id(-1)
    {}         //todo cleanup/delete pods with index -1

Pod::Pod(int id):
    m_id(id)
    {}

Pod::~Pod(){}

int Pod::getId(){
    return m_id;
}

#endif