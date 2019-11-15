#ifndef POD_H
#define POD_H

class Pod
{
private:
    const int m_id;

public:
    Pod();
    Pod(int);
    ~Pod();

    int getId();
};

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
