#ifndef POD_H
#define POD_H

class Pod
{
private:
    int m_id;

public:
    Pod();
    Pod(int);
    ~Pod();

    int getId();
};
Pod::Pod(){};

Pod::Pod(int id)
{
    Pod::m_id = id;
}

Pod::~Pod(){};

int Pod::getId(){
    return Pod::m_id;
}


#endif