#include"client.h"

bool client::getvip()
{
    return this->vip;
}

void client::setnewpurchase(int ne)
{
    this->buying+=ne;
}

double client::getexp()
{
    return this->buying;
}

int client::getphone()
{
    return this->phone;
}

void client::newset()
{
    this->buying=0;
}