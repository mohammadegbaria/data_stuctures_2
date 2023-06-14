
#include "recordsCompany.h"


RecordsCompany::RecordsCompany()=default;


void settozero(Node<int,client*>* currentnode)
{
    if(currentnode==nullptr)
    {
        return;
    }
    
    currentnode->data->newset();
    settozero(currentnode->left);
    settozero(currentnode->right);
    return;
}
StatusType RecordsCompany:: newMonth(int *records_stocks, int number_of_records)
{
    if(number_of_records<0)
    {
        return StatusType::INVALID_INPUT;
    }
     try
     {
        int *helperarray =new int[number_of_records];
        for (int i = 0; i < number_of_records; i++)
        {
            helperarray[i]=0;
            Records* r1=new Records(i,records_stocks[i]);
            r_array[i]=r1;
        }
        Node<int,client*>* currentnode= vipclient.getroot();

        settozero(currentnode);
        
     }
     catch(const std::bad_alloc& w)
     {
        return StatusType::ALLOCATION_ERROR;
     }
     catch(const std::exception& e)
     {
        std::cerr << e.what() << '\n';
     }
        
}




StatusType RecordsCompany::addCostumer(int c_id,int phone)
{
    
    if(c_id<0||phone<0)
    {
        return StatusType::INVALID_INPUT;
    }
    
       try
       {

              if(clients.contains(c_id))
                {
                   return StatusType::ALREADY_EXISTS;
                }

            client* c1=new client(c_id,false,phone);
            clients.put(c_id,c1);
        
    }
        catch(const std::bad_alloc& e)
        {
           return StatusType::ALLOCATION_ERROR;
        }
        catch(const std::exception& e)
        {
          std::cerr << e.what() << '\n';
        }

    return StatusType:: SUCCESS;
    
}

Output_t<int> RecordsCompany:: getPhone(int c_id)
{
    if(c_id<0)
    {
       Output_t<int> x(StatusType::INVALID_INPUT);
	   return x;
    }

    if(!clients.contains(c_id))
    {
      Output_t<int> x(StatusType::DOESNT_EXISTS);
	  return x;
    }

    client** c1=clients.get(c_id);
    Output_t<int>x((*c1)->getphone());
    return x;

}




StatusType RecordsCompany::makeMember(int c_id)
{
    if(c_id<0)
    {
          return StatusType::INVALID_INPUT;
    }

    try
    {
       if(!clients.contains(c_id))
       {
        return StatusType::DOESNT_EXISTS;
       }

       if(vipclient.Find(c_id))
       {
        return StatusType::ALREADY_EXISTS;
       }

       client** c1= clients.get(c_id);
       vipclient.Insert(c_id,(*c1));

    }
    catch(const std::bad_alloc& e)
        {
           return StatusType::ALLOCATION_ERROR;
        }
    catch(const std::exception& e)
        {
          std::cerr << e.what() << '\n';
        }
    return StatusType::SUCCESS;
}

Output_t<bool> RecordsCompany:: isMember(int c_id)
{

    if(c_id<0)
    {
        Output_t<bool>x(StatusType::INVALID_INPUT);
        return x;
    }
    try
    {
        if(!clients.contains(c_id))
        {
            Output_t<bool>x(StatusType::DOESNT_EXISTS);
            return x;
        }
        client** c1= clients.get(c_id);
        Output_t<bool> x((*c1)->getvip());
        return x;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}


StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    if(c_id<0||r_id<0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
    if(lengthofarray<r_id||!(clients.contains(c_id)))
    {
        return StatusType::DOESNT_EXISTS;
    }
    int numpurchase=records[r_id];
    records[r_id]++;
    client** c1=clients.get(c_id);
    if((*c1)->getvip())
    {
        (*c1)->setnewpurchase(numpurchase+100);

    }

    }
    catch(const std::bad_alloc& e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
  return StatusType::SUCCESS;  

}


StatusType RecordsCompany:: addPrize(int c_id1, int c_id2, double  amount)
{
    if(c_id1<0||c_id2<c_id1||amount<=0)
    {
        return StatusType::INVALID_INPUT;
    }
    
    try
    {
    addlessthanx(c_id1-1,(-amount));
    addlessthanx(c_id2-1,amount);
     
     return  StatusType::SUCCESS;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    return  StatusType::SUCCESS;

}




 Output_t<double> RecordsCompany::getExpenses(int c_id)
 {
    if(c_id<0)
    {
      Output_t<double> x(StatusType::INVALID_INPUT);
	  return x;
    }
    try
    {
    if(!vipclient.Find(c_id))
    {
       Output_t<double> x(StatusType::DOESNT_EXISTS);
	   return x;
    }
    
    client** c1=vipclient.Find(c_id);
    double y=(*c1)->getexp();
    //sub of path
    
    Output_t<double> x(y);
    return x;

        
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
 }