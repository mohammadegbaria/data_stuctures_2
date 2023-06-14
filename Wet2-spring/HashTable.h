/*
Hash table

supports size changing!

*/

#ifndef _HASH_TABLE_
#define _HASH_TABLE_

#include "prime.h"

template <typename Key, typename Data>
class HashTable {
 public:
  HashTable(int size = 17) : size_(size), table_(new Node*[size]()){}

  ~HashTable() {
    for (int i = 0; i < size_; i++) {
      Node *node = table_[i];
      while (node) 
      {
        Node *temp = node;
        node = node->next;
        delete temp;
      }
    }
    delete[] table_;
  }

  void put(Key key, Data data) 
  {
    unsigned int index = hash(key, size_);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             
   // Node *node = table_[index];
   RankedAVLTree<key,data>* helper= tree[index];
   
    while (node) {
      if (node->key == key) 
      {
        //node->data = data;
        return;
      }
      node = node->next;
    }
    node = new Node{key, data};
    node->next = table_[index];
    table_[index] = node;
    if (++count_ > size_) 
    {
      int new_size = closer_prime(size_ * 2);
      resize(new_size);
    }
  }

  Data* get(Key key) 
  {
    unsigned int index = hash(key, size_);
    Node *node = table_[index];
    while (node) {
      if (node->key == key) 
      {
        return &(node->data);
      }
      node = node->next;
    }
    return nullptr;
  }

  void remove(Key key) 
  {
    unsigned int index = hash(key, size_);
    Node *node = table_[index];
    if (node && node->key == key) {
      table_[index] = node->next;
      delete node;
      if (--count_ < size_ / 4) 
      {
        int new_size = size_ / 2;
        if(!is_prime(new_size))
          new_size = closer_prime(new_size);
        resize(new_size);
      }
      return;
    }
    while (node) {
      if (node->next && node->next->key == key) 
      {
        Node *temp = node->next;
        node->next = temp->next;
        delete temp;
        if (--count_ < size_ / 4) 
        {
          int new_size = closer_prime(size_ / 2);
          resize(new_size);
        }
        return;
      }
      node = node->next;
    }
  }

  bool contains(Key key) 
  {
    unsigned int index = hash(key, size_);
    Node *node = table_[index];
    while (node) {
      if (node->key == key) 
      {
        return true;
      }
      node = node->next;
    }
    return false;
  }

  int size() 
  {
    return count_;
  }

  int Table_size()
  {
    return size_;
  }


  void Table_Diagram() const
  {
    for (int i = 0; i < size_; i++)
    {
      std::cout << std::endl << i << " <+> ";
      int c = 0;
      Node* node = table_[i];
      while (node != nullptr)
      {
        c++;
        node = node->next;
      }
      
      std::cout << c << std::endl;

    }
    
  }

  //do not forget to free the returned array
  Data** get_data()
  {
    Data** valid = new Data*[this->count_];
    int j = 0;

    for (int i = 0; i < this->size_; i++)
    {
      Node* node = table_[i];
      while (node && j < this->count_)
      {
        valid[j] = &(node->data);
        j++;
        node = node->next;
      }
      
    }
    
    return valid;
  }

 private:
  /*struct Node {
    Key key;
    Data data;
    Node *next;
  };*/
  RankedAVLTree<Key,Data>** trees
  int size_;
  //Node **table_;
  int count_ = 0;


  void resize(int new_size) 
  {
    Node **new_table = new Node*[new_size]();
    for (int i = 0; i < size_; i++) {
      Node *node = table_[i];
      while (node) {
        Node *temp = node;
        node = node->next;
        unsigned int index = hash(temp->key, new_size) % new_size;
        temp->next = new_table[index];
        new_table[index] = temp;
      }
    }
    delete[] table_;
    table_ = new_table;
    size_ = new_size;
  }

  std::size_t Nhash(const Key& key, std::size_t table_size) {
    std::size_t multiplier = 2654435761;
    std::size_t shift = 32;
    std::size_t index = static_cast<std::size_t>(static_cast<std::size_t>(multiplier * key) >> shift) % table_size;;
    //return static_cast<std::size_t>(static_cast<std::size_t>(multiplier * key)) % table_size;
    return index;
  }

//FNV hash (better than the previous one)
unsigned int hash(const Key& key, std::size_t table_size) {
  unsigned int hash = 2166136261u; // Initialize the hash to a prime value
  const unsigned char *p = reinterpret_cast<const unsigned char*>(&key);
  size_t size = sizeof(Key);
  for (size_t i = 0; i < size; ++i) {
    hash = (hash ^ p[i]) * 16777619u; // Multiply by a prime value
  }
  return hash % table_size; // Return the index in the range [0, table_size-1]
}

};

#endif