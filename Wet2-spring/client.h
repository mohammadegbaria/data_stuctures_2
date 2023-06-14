
class client
{
private:
    int id;
    bool vip;
    int phone;
    int buying;
public:
    client(int id,bool vip,int phone):id(id),vip(vip),phone(phone),buying(0){}
    ~client();
    bool getvip();
   // the function is to add the new purchase to the expense of the vip clients
    void setnewpurchase(int ne);
   // using this function in getexpense 
    double getexp();
    int getphone();
    void newset();
};

client::~client()
{
}
