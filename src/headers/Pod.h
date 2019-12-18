#ifndef POD_H
#define POD_H

class Pod
{
private:
    const int id;

public:
    Pod();
    Pod(int);
    ~Pod();

    int getId();
    std::pair<int,int> location;
};

#endif
