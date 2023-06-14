#ifndef _OUR_TREE
#define _OUR_TREE


/*
first version of an AVL tree
supports basic functions
key should have:
  operators:
    - <
    - >
    - ==
*/

#include <iostream>
#include <stdlib.h>
#include <math.h>

template <typename Key, typename Data>
class Node {
 public:
  Key key;
  Data data;
  int height;
  Node<Key, Data> *left;
  Node<Key, Data> *right;
  Node<Key, Data> *parent;
  int size;
  int extra;

  explicit Node(const Key &key, const Data &data)
      : key(key), data(data), height(1), left(nullptr), right(nullptr), parent(nullptr), size(1) {}

  ~Node() = default;

};

template <typename Key, typename Data>
class RankedAVLTree {
 public:
 RankedAVLTree() : root(nullptr) {}

  ~RankedAVLTree() {
    DeleteTree(root);
  }
    Node<Key, Data>* getroot()
  {
    return this->root;
  }
  bool Insert(const Key &key, const Data &data) {
    if(!FindNode(root, key)){
      root = InsertNode(root, key, data);
      return true;
    }
    return false;
  }

  bool Remove(const Key &key) {
    if(FindNode(root, key)){
      root = Remove(root, key);
      return true;
    }
    return false;
  }


  void InsertNode(Node<Key, Data>* node){
    if(!FindNode(root, node->key))
      root = InsertNode(root, node->key, node->data, node);
  }

//update has bugs
  void update(Key& prevKey, Key& newkey, Data& newData)
  {
    Node<Key, Data>* temp = FindNode(root, prevKey);

    if(!temp) {return;} 

    if(!(temp->key == prevKey)) {return;}
    
    Node<Key, Data>* removed;
    root = Remove(root, prevKey, 0, &removed);
    if(removed){
    (removed)->key = newkey;
    (removed)->data = newData;
    }

    this->InsertNode(removed);
  }
  
  Data* Find(const Key &key) {
    return Find(root, key);
  }

int GetRank(const Key &key) {
  return GetRank(root, key);
}

Data* Max() const{
  Node<Key, Data>* maxNode = getMaxNode();
  if(!maxNode){
    return nullptr;
  }

  return &(maxNode->data);
}
Node<Key, Data>* FindByRank(int k) {
  return FindByRank(root, k);
}

  void printInOrder()
  {
    std::cout << std::endl;
    printInOrder_aux(this->root);
    std::cout << std::endl;
  }

  Node<Key, Data>** TreeNodesToArray()
  {
    if(!this->root)
      return nullptr;
    Node<Key, Data>** array = new Node<Key, Data>*[this->root->size];
    int place = 0;
    TreeNodesToNodesArray(this->root, array, place);
    return array;
  }

  Data* TreeNodesToDataArray(int &N)
  {
    if(!this->root)
      return nullptr;
    Data* array = new Data[this->root->size];
    int place = 0;
    N = this->root->size;
    TreeNodesToDataArray(this->root, array, place);
    return array;
  }

  int get_size() const{
    return root->size;
  }

  Key& getIdByReference(const Key& key)
  {
    return FindNode(root, key)->key;
  }

  Node<Key, Data>* FindNode(const Key &key){
    return FindNode(root, key);
  }

 private:
  Node<Key, Data> *root;

    Node<Key, Data>* InsertNode(Node<Key, Data> *no, const Key &key, const Data &data, Node<Key, Data> *nodeToInsert = nullptr) {
        if (!no) {
            if(!nodeToInsert)
              return new Node<Key, Data>(key, data);
            else {/*
              nodeToInsert->parent = nullptr;
              nodeToInsert->left = nullptr;
              nodeToInsert->right = nullptr;*/
              return nodeToInsert;
            }
        }
        if (key < no->key) 
        {
          no->left = InsertNode(no->left, key, data, nodeToInsert);
          (no->left)->parent = no;
        } else if (key > no->key) 
        {
            no->right = InsertNode(no->right, key, data, nodeToInsert);
            (no->right)->parent = no;
        } else 
        {
            return nullptr;
        }
        no->size = 1 + GetSize(no->left) + GetSize(no->right);
        no->height = 1 + std::max(GetHeight(no->left), GetHeight(no->right));
        return Balance(no);
        }

void swapSonParent(Node<Key, Data> *son, Node<Key, Data> *father, Node<Key, Data> sonMirror, Node<Key, Data> fatherMirror){

  int sonIsLeft = 0, sonIsRight = 0;
  if((son->parent && son->parent->key == father->key)){
    if(father->left && father->left->key == son->key){
      sonIsLeft = 1;
    } else {
      sonIsRight = 1;
    }
  }

  if(father->parent){
    if(father->parent->left && father->parent->left->key == father->key)
      father->parent->left = son;
    else
      father->parent->right = son;
  }

    if(sonIsLeft){
      son->right = father->right;
      son->left = father;
      father->right = sonMirror.right;
      father->left = sonMirror.left;
    }
    if(sonIsRight){
      son->left = father->left;
      son->right = father;
      father->left = sonMirror.left;
      father->right = sonMirror.right;
    }
      son->parent = father->parent;
      father->parent = son;

      if(root->key == father->key)
        root = son;
}

  void copyNodePointers(Node<Key, Data>* source, Node<Key, Data>* dst){
    if(!dst || !source){return;}
    dst->left = source->left;
    dst->right = source->right;
    if(dst->right)
      dst->right->parent = dst;
    if(dst->left)
      dst->left->parent = dst;
    dst->parent = source->parent;
    source->parent = dst->parent;
  }

  void replaceParents(Node<Key, Data>* Water, Node<Key, Data>* Fire){
    if(!Fire || !Water){return;}

    //water parent to be Fire parent
    if(Water->parent){
      if(Water->parent->left && Water->parent->left->key == Water->key){
      //water is left son
        Water->parent->left = Fire;
      } else {
        //water is right son
        Water->parent->right = Fire; 
      }
    }

    //Fire parent to be Water parent
    if(Fire->parent){
      if(Fire->parent->left && Fire->parent->left->key == Fire->key){
      //Fire is left son
        Fire->parent->left = Water;
      } else {
        //Fire is right son
        Fire->parent->right = Water; 
      }
    }
  }

//swaps the nodes themselves
void swapNodes(Node<Key, Data> *Fire, Node<Key, Data> *Water){

  Node<Key, Data> WaterMirror(Water->key, Water->data);
  WaterMirror.left = Water->left;
  WaterMirror.right = Water->right;
  WaterMirror.parent = Water->parent;

  Node<Key, Data> FireMirror(Water->key, Water->data);
  FireMirror.left = Fire->left;
  FireMirror.right = Fire->right;
  FireMirror.parent = Fire->parent;

  //if the are related parent - son
  if((Water->parent && Water->parent->key == Fire->key)){
    swapSonParent(Water, Fire, WaterMirror, FireMirror);
    return;
    }
  if((Fire->parent && Fire->parent->key == Water->key)){
    swapSonParent(Fire, Water, FireMirror, WaterMirror);
    return;
    }

  //their parents
  replaceParents(Water, Fire);

  //Water to be Fire
  copyNodePointers(Fire, Water);

  //Fire to be Water
  copyNodePointers(&WaterMirror, Fire);

  if(root->key == Fire->key)
    root = Water;
  if(root->key == Water->key)
    root = Fire;
}

void ModifyParentOfDeleted(Node<Key, Data> *no){
  if(no && no->parent){
    if(no->parent->left && no->parent->left->key == no->key){
      no->parent->left = nullptr;
    } else {
      no->parent->right = nullptr;
    }
  }
}
//has bugs
Node<Key, Data>* RemoveKeepingPointers(Node<Key, Data> *no, const Key &key, bool IsToDelete = 1, Node<Key, Data>** removed = nullptr) {
  if (!no) {
    return nullptr;
  }
  if (key > no->key) 
  {
    no->right = Remove(no->right, key, IsToDelete, removed);
  } else if (key < no->key) 
  {
    no->left = Remove(no->left, key, IsToDelete, removed);
  } else 
  {
    if (!no->left || !no->right) 
    {
      Node<Key, Data> *temp = no->left ? no->left : no->right;
      if (!temp) 
      {
        //is there a need that parent points now to null in the deleted child ptr?
        if(IsToDelete){
          //ModifyParentOfDeleted(no);
        if(no->parent){
          if(no->parent->left && no->parent->left->key == no->key){
            no->parent->left = nullptr;
          } else {
            no->parent->right = nullptr;
          }
        }
          delete no;
        }
        else
          (*removed) = no;
        return nullptr;
      }
      swapNodes(temp, no);
      Node<Key, Data> *toDelete = no;
      no = temp;
      temp->left = nullptr;
      temp->right = nullptr;

      if(IsToDelete){
          //ModifyParentOfDeleted(toDelete);
          delete toDelete;
      }
      else
        (*removed) = toDelete;

    } else 
    {
      Node<Key, Data> *temp = FindMin(no->right);
      swapNodes(temp, no);
      temp->right = Remove(temp->right, no->key, IsToDelete, removed);
      no = temp;
    }
  }
  no->size = 1 + GetSize(no->left) + GetSize(no->right);
  no->height = 1 + std::max(GetHeight(no->left), GetHeight(no->right));
  return Balance(no);
}

Node<Key, Data>* Remove(Node<Key, Data> *no, const Key &key, bool IsToDelete = 1, Node<Key, Data>** removed = nullptr) {
  if (!no) {
    return nullptr;
  }
  if (key > no->key) 
  {
    no->right = Remove(no->right, key);
  } else if (key < no->key) 
  {
    no->left = Remove(no->left, key);
  } else 
  {
    if (!no->left || !no->right) 
    {
      Node<Key, Data> *temp = no->left ? no->left : no->right;
      if (!temp) 
      {
        delete no;
        return nullptr;
      }
      *no = *temp;
      delete temp;
    } else 
    {
      Node<Key, Data> *temp = FindMin(no->right);
      no->key = temp->key;
      no->data = temp->data;
      no->right = Remove(no->right, temp->key);
    }
  }
  no->size = 1 + GetSize(no->left) + GetSize(no->right);
  no->height = 1 + std::max(GetHeight(no->left), GetHeight(no->right));
  return Balance(no);
}


Data* Find(Node<Key, Data> *node, const Key &key) {
  if (!node) {
    return nullptr;
  }
  if (key == node->key) 
  {
    return &node->data;
  } else if (key < node->key) 
  {
    return Find(node->left, key);

  } else 
  {

    return Find(node->right, key);
  }
}

Node<Key, Data>* FindNode(Node<Key, Data> *no, const Key &key) {
  if (!no) {
    return nullptr;
  }
  if (key == no->key){
    return no;
  } else if (key < no->key){
    return FindNode(no->left, key);
  } else {
    return FindNode(no->right, key);
  }
  return nullptr;
}
Node<Key, Data>* FindByRank(Node<Key, Data> *no, int k) {
  if (!no) {
    return nullptr;
  }
  int leftSize = GetSize(no->left);
  if (k < leftSize) {
    return FindByRank(no->left, k);
  } else if (k > leftSize) {
    return FindByRank(no->right, k - leftSize - 1);
  } else {
    return no;
  }
}

int GetSize(Node<Key, Data> *node) {
  return node ? node->size : 0;
}

int GetRank(Node<Key, Data> *no, const Key &key) {
  if (!no) {
    return 0;
  }
  if (key < no->key) {
    return GetRank(no->left, key);
  } else if (key > no->key) {
    return 1 + GetSize(no->left) + GetRank(no->right, key);
  } else {
    return GetSize(no->left);
  }
}

Node<Key, Data>* FindMin(Node<Key, Data> *node) {
  if(!node){
    return nullptr;
  }
  if (!node->left) {
    return node;
  }
  return FindMin(node->left);
}

int GetHeight(Node<Key, Data> *node) {
  return node ? node->height : 0;
}

int GetBalanceFactor(Node<Key, Data> *node) {
  return GetHeight(node->right) - GetHeight(node->left);
}

Node<Key, Data>* Balance(Node<Key, Data> *node) {
  node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
  node->size = 1 + GetSize(node->left) + GetSize(node->right);

  int balance_factor = GetBalanceFactor(node);
  if (balance_factor < -1 && GetBalanceFactor(node->left) <= 0) {
    return RotateRight(node);
  }
  if (balance_factor > 1 && GetBalanceFactor(node->right) >= 0) {
    return RotateLeft(node);
  }
  if (balance_factor < -1 && GetBalanceFactor(node->left) > 0) {
    node->left = RotateLeft(node->left);
    return RotateRight(node);
  }
  if (balance_factor > 1 && GetBalanceFactor(node->right) < 0) {
    node->right = RotateRight(node->right);
    return RotateLeft(node);
  }
  return node;
}

Node<Key, Data> *RotateLeft(Node<Key, Data> *node) {
  Node<Key, Data> *temp = node->right;
  node->right = temp->left;
  if(temp->left)
    temp->left->parent = node;
  temp->left = node;
  Node<Key, Data> *nodeParent = node->parent;
  node->parent = temp;
  temp->parent = nodeParent;
  node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
  temp->height = 1 + std::max(GetHeight(temp->left), GetHeight(temp->right));
  node->size = 1 + GetSize(node->left) + GetSize(node->right);
  temp->size = 1 + GetSize(temp->left) + GetSize(temp->right);

  return temp;
}

Node<Key, Data>* RotateRight(Node<Key, Data> *node) {
  Node<Key, Data> *temp = node->left;
  node->left = temp->right;
  if(temp->right)
    temp->right->parent = node;
  temp->right = node;
  Node<Key, Data> *nodeParent = node->parent;
  node->parent = temp;
  temp->parent = nodeParent;
  node->height = 1 + std::max(GetHeight(node->left), GetHeight(node->right));
  temp->height = 1 + std::max(GetHeight(temp->left), GetHeight(temp->right));
  node->size = 1 + GetSize(node->left) + GetSize(node->right);
  temp->size = 1 + GetSize(temp->left) + GetSize(temp->right);

  return temp;
}

void DeleteTree(Node<Key, Data> *node) {
  if (node == nullptr) {
    return;
  }
  DeleteTree(node->left);
  DeleteTree(node->right);
  delete node;
}


void printInOrder_aux(Node<Key, Data>* router)
{
  if(router == nullptr)
  {
    return;
  }
  
  printInOrder_aux(router->left);
  std::cout << "[ " << router->key << ", " << router->data << "] ";
  printInOrder_aux(router->right);

}

  void TreeNodesToNodesArray(Node<Key, Data>* node, Node<Key, Data>** arr, int &i)
  {
    if(!node)
    {
      return;
    }

    TreeNodesToNodesArray(node->left, arr, i);
    arr[i] = node;
    i++;
    TreeNodesToNodesArray(node->right, arr, i);
  }

  void TreeNodesToDataArray(Node<Key, Data>* node, Data* arr, int &i)
  {
    if(!node)
    {
      return;
    }

    TreeNodesToDataArray(node->left, arr, i);
    arr[i] = node->data;
    i++;
    TreeNodesToDataArray(node->right, arr, i);
  }

  Node<Key, Data>* getMaxNode() const{
    Node<Key, Data>* max = root;
    while (max && max->right) 
    {
      max = max->right;
    }
    return max;
  }


};


#endif