/*
This implementation adds a StructureCapacity member variable to the UnionFind class,
which keeps track of the current capacity of the upSideDownTree array.
The Insert function increases the size of the array by a factor of 2 when
the key to be inserted is greater than or equal to the current size of the array.
The Remove function replaces the node to be removed with the last node in the array,
decrements the size variable, and then checks if the size is less than or equal to half the StructureCapacity.
If it is, then it decreases the capacity of the upSideDownTree array by a factor of 2.
*/

// --------------------------DO NOT FORGET TO MODIFY THE CODE THAT THEY WON'T KNOW!-------------------------//

#ifndef _UFC_
#define _UFC_

#include <iostream>
#include <ostream>
#include "HashTable.h"

/*
    member extra is an object of kind Extra.
    Extra class should have default constructor!
    Extra() - the empty contructor should set the new object to a neutral value => like 0 for - and +
    Kind Extra sholud have operator+ and operato-!
    the operator action doesn't have to suit his name!
    Extra should have a function called extraCalc(Extra &)!
*/
template <class Key, class Data, class Extra>
class NodeExtra
{
public:
  Key key;
  Data data;
  NodeExtra *parent;
  int rank;
  Extra extra;

  NodeExtra(Key key, Data data, Extra extra) : key(key), data(data), parent(nullptr), rank(0), extra(extra) {}
};

template <class Key, class Data, class Extra>
class UnionFindExtra
{
public:
  UnionFindExtra() = default;
  ~UnionFindExtra()
  {
    NodeExtra<Key, Data, Extra> *** GG = forest.get_data();
    for (int i = 0; i < forest.size(); i++)
    {
      delete *GG[i];
    }

    delete [] GG;
    
  }
  // Obj_1 comes first
  void Union(Key keyForObj_1, Key keyForObj_2)
  {

    if(std::is_same<int, Key>::value && keyForObj_2 == 92891)
    {
      std::cout << "";
    }

    NodeExtra<Key, Data, Extra> **Obj_1Rootp = forest.get(keyForObj_1);
    NodeExtra<Key, Data, Extra> **Obj_2Rootp = forest.get(keyForObj_2);


    // at least one key does not exist
    if (!Obj_1Rootp || !Obj_2Rootp)
    {
      return;
    }

    NodeExtra<Key, Data, Extra> *Obj_1Root = FindWithOutKyvoots(*Obj_1Rootp);
    NodeExtra<Key, Data, Extra> *Obj_2Root = FindWithOutKyvoots(*Obj_2Rootp);

    // united
    if (Obj_1Root == Obj_2Root)
      return;

    if (Obj_1Root->rank < Obj_2Root->rank)
    { // case 1

      Obj_1Root->parent = Obj_2Root;
      // extra_b_new = extra_a_old + extra_b_old
      Obj_2Root->extra = Obj_2Root->extra;
      // extra_a_new = extra_a_old - extra_b_new
      //Obj_1Root->extra = Obj_1Root->extra - Obj_2Root->extra;

      //additional calculations
      Obj_1Root->extra.extraCalc(Obj_2Root->extra);
    }
    else if (Obj_1Root->rank > Obj_2Root->rank)
    { // case 2

      Obj_2Root->parent = Obj_1Root;
      // extra_b_new = extra_b_old
      // Obj_2Root->extra = Obj_2Root->extra;
      // extra_a_new = extra_a_old
      // Obj_1Root->extra = Obj_1Root->extra

      //additional calculations
      Obj_2Root->extra.extraCalc(Obj_1Root->extra);
    }
    else
    { // case 3

      Obj_2Root->parent = Obj_1Root;
      //additional calculations
      Obj_2Root->extra.extraCalc(Obj_1Root->extra);

      Obj_1Root->rank++;
    }
  }

  NodeExtra<Key, Data, Extra> **getNode(Key key)
  {
    return (forest.get(key));
  }

  NodeExtra<Key, Data, Extra> *Find(Key key)
  {
		
    if(std::is_same<int, Key>::value && key == 42833)
    {
      std::cout << "";
    }

    // get pointer to the wanted node
    NodeExtra<Key, Data, Extra> **ptrToTargetNode = forest.get(key);

    // Key not found
    if (ptrToTargetNode == nullptr)
    {
      return nullptr;
    }
    NodeExtra<Key, Data, Extra> *TargetNode = *ptrToTargetNode;

    // update extra before reshaping the tree
    updateExtrasFromNode_x_ToRoot(TargetNode);

    // reshape
    return Find(TargetNode);
  }

  void Insert(Key key, Data data, Extra extra)
  {

    forest.put(key, new NodeExtra<Key, Data, Extra>(key, data, extra));
  }

  // do not forget to free the returned array
  NodeExtra<Key, Data, Extra> ***get_all_data()
  {
    return forest.get_data();
  }

  template <class D, class E>
  friend std::ostream &operator<<(std::ostream &os, UnionFindExtra<int, D, E> &obj);

  int used_size()
  {
    return forest.size();
  }

  int unused_size()
  {
    return forest.Table_size();
  }

  // returns the sum from node with key = key to the root.
  Extra get_validExtra(Key key)
  {

    NodeExtra<Key, Data, Extra> **data = forest.get(key);
    if (!data)
    {
      return Extra{};
    }
    return FindSumOfExtrasFromNode_x_ToRoot(*data);
  }

  Extra *get_extra(Key key)
  {
    NodeExtra<Key, Data, Extra> **ptrToTargetNode = forest.get(key);
    if (!ptrToTargetNode)
    {
      return nullptr;
    }
    return (*ptrToTargetNode)->extra;
  }

private:
  HashTable<Key, NodeExtra<Key, Data, Extra> *> forest;

  Extra FindSumOfExtrasFromNode_x_ToRoot(NodeExtra<Key, Data, Extra> *x)
  {
    Extra sum;
    sum.Initialize(x->extra.player_);
    NodeExtra<Key, Data, Extra> *temp = x; // no need for temp, but looks nicer with it
    while (temp)
    {
      sum = sum + temp->extra;
      temp = temp->parent;
    }
    return sum;
  }
  void updateExtrasFromNode_x_ToRoot(NodeExtra<Key, Data, Extra> *x)
  {

    Extra sumOfExtras = FindSumOfExtrasFromNode_x_ToRoot(x);

    //decrease the root
    NodeExtra<Key, Data, Extra>* rootOfX = FindWithOutKyvoots(x);
    sumOfExtras = sumOfExtras % rootOfX->extra;

    Extra PrevExtra; // Extra() - the empty contructor should set the new object to a neutral value => like 0 for - and +
    NodeExtra<Key, Data, Extra> *temp = x;

    // it does not affect the root nor the first son in the series
    while (temp->parent && temp->parent->parent)
    {
      sumOfExtras -= PrevExtra;
      PrevExtra = temp->extra;
      temp->extra = sumOfExtras;
      temp = temp->parent;
    }
  }

  NodeExtra<Key, Data, Extra> *Find(NodeExtra<Key, Data, Extra> *x)
  {

    if (x->parent == nullptr)
    {
      return x;
    }

    // recursive operation that traverse the upSideDownTree! it also updates the extra for each x
    x->parent = Find(x->parent);

    return x->parent;
  }

  void Remove(Key key)
  {

    // just deletes a node in one of the opposite trees
    // this can cause a tree to be corrupted

    forest.remove(key);
  }

  NodeExtra<Key, Data, Extra>* FindWithOutKyvoots(NodeExtra<Key, Data, Extra>* tor)
  {
    if(!tor){return nullptr;}
    while (tor->parent)
    {
      tor = tor->parent;
    }
    return tor;
  }
  // Errors
};

template <class D, class E>
std::ostream &operator<<(std::ostream &os, UnionFindExtra<int, D, E> &obj)
{
  // obj.forest.Table_Diagram();
  // obj.forest.Table_Diagram();
  HashTable<int, int> parents;

  try
  {
    // works when the keys are from 0 to size()!
    for (int i = 0; i < obj.forest.size(); i++)
    {
      // get the parent of node with key i
      NodeExtra<int, D, E> *parent = obj.Find(i);

      // get the number of how many childrens do parent have (parent included)
      int *parentDataInParents = parents.get(parent->key);

      if (!parentDataInParents)
      {
        parents.put(parent->key, 1);
        continue;
      }

      // increase children count
      (*parentDataInParents)++;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }

  for (int i = 0; i < obj.forest.size(); i++)
  {
    int *pp = parents.get(i);
    if (!pp)
    {
      continue;
    }
    std::cout << std::endl;
    std::cout << "[" << i << ", " << *pp << "] ";
  }
  parents.Table_Diagram();
  std::cout << std::endl;
  return os;
}

#endif