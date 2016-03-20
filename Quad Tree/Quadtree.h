#ifndef QUADTREE_H
#define QUADTREE_H

/***************************************
 * UW User ID:  s28chaud
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ***************************************/

#include "ece250.h"
#include "Quadtree_node.h"
#include "Exception.h"
#include <iostream>

template <typename T>
class Quadtree {
	private:
		Quadtree_node<T> *tree_root;
		int count;

	public:
		Quadtree();
		~Quadtree();

		// Accessors

		int size() const;
		bool empty() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		Quadtree_node<T> *root() const;
		bool member( T const &, T const & ) const;

		// Mutators

		void insert( T const &, T const & );
		void clear();

	
};

template <typename T>
Quadtree<T>::Quadtree():
tree_root( 0 ), 
count( 0 ) {
	// empty constructor
}

template <typename T>
Quadtree<T>::~Quadtree() {
    clear();
}

template <typename T>
int Quadtree<T>::size() const {
	return count;
}

template <typename T>
bool Quadtree<T>::empty() const {
    
    if (count == 0) {
        return true;
    } else {
        return false;
    }
}

template <typename T>
T Quadtree<T>::min_x() const {
    if(count == 0) {
        throw underflow();
    }
    return tree_root->min_x();
}

template <typename T>
T Quadtree<T>::min_y() const {
    if(count == 0) {
        throw underflow();
    }
    return tree_root->min_y();
}

template <typename T>
T Quadtree<T>::max_x() const {
    if(count == 0) {
        throw underflow();
    }
    return tree_root->max_x();
}

template <typename T>
T Quadtree<T>::max_y() const {
    if(count == 0) {
        throw underflow();
    }
    return tree_root->max_y();
}

template <typename T>
T Quadtree<T>::sum_x() const {
    return tree_root->sum_x();
}

template <typename T>
T Quadtree<T>::sum_y() const {
    return tree_root->sum_y();
}

template <typename T>
Quadtree_node<T> *Quadtree<T>::root() const {
    if (count == 0) {
        return 0;
    } else {
        return tree_root;
    }
}

template <typename T>
bool Quadtree<T>::member( T const &x, T const &y ) const {
    if (count == 0) {
        return false;
    }
    if (x == tree_root->retrieve_x() && y == tree_root->retrieve_y()) {
        return true;
    } else {
        return tree_root->member(x, y);
    }
}

template <typename T>
void Quadtree<T>::insert( T const &x, T const &y ) {
    if (tree_root == 0) {                           //new root
        tree_root = new Quadtree_node<T>(x, y);
        count++;
    } else{
        if(tree_root->insert(x, y))
        {
            count++;
        }
    }
}

template <typename T>
void Quadtree<T>::clear() {
    if(tree_root != 0 )
    {
        tree_root->clear();
        tree_root = 0;
    }
    count = 0;

}



// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
