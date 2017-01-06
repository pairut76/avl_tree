// AVLSet.hpp
//
// ICS 46 Spring 2016
// Project #3: Set the Controls for the Heart of the Sun
//
// An AVLSet is an implementation of a Set that is an AVL tree, which uses
// the algorithms we discussed in lecture to maintain balance every time a
// new element is added to the set.
//
// You are not permitted to use the containers in the C++ Standard Library
// (such as std::set, std::map, or std::vector).  Instead, you'll need
// to implement your AVL tree using your own dynamically-allocated nodes,
// with pointers connecting them, and with your own balancing algorithms
// used.

#ifndef AVLSET_HPP
#define AVLSET_HPP

#include "Set.hpp"



template <typename T>
class AVLSet : public Set<T>
{
public:
    struct avl_node
    {
        T key;
        int height;
        avl_node *left, *right;

        avl_node(const T& item)
        {
            key=item;
            left=NULL;
            right=NULL;
            height=1;
        }

    };
    // Initializes an AVLSet to be empty.
    AVLSet();

    // Cleans up the AVLSet so that it leaks no memory.
    virtual ~AVLSet();

    // Initializes a new AVLSet to be a copy of an existing one.
    AVLSet(const AVLSet& s);

    // Assigns an existing AVLSet into another.
    AVLSet& operator=(const AVLSet& s);
  

    // isImplemented() should be modified to return true if you've
    // decided to implement an AVLSet, false otherwise.
    virtual bool isImplemented() const;
    virtual void balance(avl_node *&_root);
    virtual int setHeight(avl_node *&_root);
    virtual void balanceRight(avl_node *&_root);
    virtual void balanceLeft(avl_node *&_root);
 



    // add() adds an element to the set.  If the element is already in the set,
    // this function has no effect.  This function always runs in O(log n) time
    // when there are n elements in the AVL tree.
    virtual void add(const T& element);
    virtual void addr(avl_node  *&_root, const T& element);
    virtual void delete_nodes(avl_node *&_root, const T& element);

    // contains() returns true if the given element is already in the set,
    // false otherwise.  This function always runs in O(log n) time when
    // there are n elements in the AVL tree.
    virtual bool contains(const T& element) const;


    // size() returns the number of elements in the set.
    virtual unsigned int size() const;


    


private:
    avl_node *root;
    int size_avl;

};


template <typename T>
AVLSet<T>::AVLSet()
{
    root=NULL;
    size_avl=0;
}


template <typename T>
AVLSet<T>::~AVLSet()
{
    //remove(root->item)

    while(root!=NULL)
    {
        delete_nodes(root, root->key);
    }
}


template <typename T>
AVLSet<T>::AVLSet(const AVLSet& s)
{
    
}


template <typename T>
AVLSet<T>& AVLSet<T>::operator=(const AVLSet& s)
{
    //root=copyNodes(s.root);
    return *this;
}



template <typename T>
bool AVLSet<T>::isImplemented() const
{
    return true;
}


template <typename T>
void AVLSet<T>::add(const T& element)
{
    //std::cout<<"being added: "<<element<<std::endl;

    if(root==NULL)
    {
        avl_node *temp=new avl_node(element);
        root=temp;
        size_avl++;
        return;
    }
    else
    {
        //std::cout<<"root value add: "<<root->key<<std::endl;
        addr(root,element);
    }
    
}

template <typename T>

void AVLSet<T>::addr(avl_node *&_root, const T& element)
{
   //std::cout<<"enter addr"<<std::endl;
    //std::cout<<_root->key<<std::endl;
    if(_root==NULL)
    {
        //std::cout<<"value added"<<std::endl;
        _root=new avl_node(element);
        size_avl++;
    }
    else if(element >_root->key)
    {
        //std::cout<<"element>root"<<std::endl;
        //_root->right;
        std::cout<<_root->key<<std::endl;
        addr(_root->right, element);
    }
    else if(element<_root->key)
    {
        //std::cout<<"element<root"<<std::endl;
        //_root->left;
        std::cout<<_root->key<<std::endl;
        addr(_root->left,element);
    }
    
    if(element==root->key)
        return;
    //balance
    balance(_root);
    //balance(_root);
}
template <typename T>
void AVLSet<T>::delete_nodes(avl_node *&_root, const T& element)
{
    std::cout<<"deleting! "<<_root->key<<std::endl;

    if(_root==NULL)
    {
        std::cout<<"done"<<std::endl;
        return;
    }

    
    else if(element>_root->key&&_root->left!=NULL)
    {
        std::cout<<"element>root "<<element<<std::endl;
        delete_nodes(_root->right, element);
    }
        
    else if(element<_root->key&&_root->right!=NULL)
     {
        std::cout<<"element<root "<<element<<std::endl;
        std::cout<<_root->left<<std::endl;
        delete_nodes(_root->left, element);
    }

    else if(_root->right==NULL)
    {
        std::cout<<"delete left"<<std::endl;
        avl_node * temp=_root;
        _root=_root->left;
        delete temp;
        size_avl--;
    }
    else if(_root->left==NULL)
    {
        std::cout<<"delete right"<<std::endl;
        avl_node * temp=_root;
        _root=_root->right;
        delete temp;
        size_avl--;
    }

    
    else
    {
        std::cout<<"being deleted: "<<_root->key<<std::endl;
        //T l_key;

        //_root->key=findlowest(_root->right)->key;

        
        //_root->key=findMin(_root->right)->key;
        
        //avl_node *root_copy=_root;
        //root_copy=root_copy->right;
        //while(root_copy!=NULL)
        //    root_copy=root_copy->left;
        std::cout<<"key being replaced: "<<_root->key<<std::endl;
        //_root->key=root_copy->key;
        //std::cout<<"key found: "<<root_copy->key<<std::endl;
        
        //root->key=l_key;
        //_root->key=_root->key
        delete_nodes(_root->right, _root->key);
    }
    balance(_root);

}
/*
template <typename T>
AVLSet::avl_node * AVLSet<T>::findlowest(avl_node *_root)
{
    while(_root->left!=NULL)
        _root=_root->left;
    return _root;

}

*/
template <typename T>
void AVLSet<T>::balance(avl_node *&_root)
{

    std::cout<<"balancing tree"<<std::endl;
    if(_root->left==NULL||_root->right==NULL)
    {
        std::cout<<"getting out"<<std::endl;
        return;
    }

    std::cout<<"height: "<<_root->height<<std::endl;
    _root->height=setHeight(_root);
    if((_root->left->height - _root->right->height) >1)
    {
        std::cout<<"balance right"<<std::endl;
        balanceRight(_root);
    }
    if((_root->right->height-_root->left->height)>1)
    {
        std::cout<<"balance left"<<std::endl;

        balanceLeft(_root);
    }
    _root->height=setHeight(_root);
}


template <typename T>
int AVLSet<T>::setHeight(avl_node *& _root)
{
    if(_root==NULL)
        return 0;
    if(_root->right->height > _root->left->height)
        return (_root->right->height)+1;
    else
        return (_root->left->height)+1;
}
template <typename T>
void AVLSet<T>::balanceRight(avl_node *& _root)
{
    if(_root->left->right->height > _root->left->left->height)
        //rotate left
    {
        avl_node * _node=_root->right;
        _root->right=_node->left;
        _node->right=_root;
        _node->height=setHeight(_root);
        _root=_node;
    }
    //rotate right
    avl_node * _node=_root->left;
    _root->right=_node->left;
    _node->left=_root;
    _node->height=setHeight(_root);
    _root=_node;

}
template <typename T>
void AVLSet<T>::balanceLeft(avl_node *& _root)
{
    if(_root->right->left->height > _root->right->right->height)
    {
        avl_node *_node=_root->left;
        _root->right=_node->left;
        _node->left=_root;
        _node->height=setHeight(_root);
        _root=_node;
    }
    avl_node * _node=_root->right;
    _root->right=_node->left;
    _node->right=_root;
    _node->height=setHeight(_root);
    _root=_node;
        


}
template <typename T>
bool AVLSet<T>::contains(const T& element) const
{
    //std::cout<<"current root: "<<root->key<<std::endl;
    //for (avl_node * p=root; p; p=p->right)
    //{
     //   std::cout<<root->key<<std::endl;

    //}
    return false;
}


template <typename T>
unsigned int AVLSet<T>::size() const
{
    return size_avl;
}



#endif // AVLSET_HPP

