

class Records
{
private:
    int parent;
    int id;
    int copies;
public:
    Records()=default;
    ~Records();
    Records(int id,int copies):parent(-1),id(id),copies(copies){}
};
