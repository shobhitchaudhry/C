#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

/****************************************
 * UW User ID:  s28chaud
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "ece250.h"
#include <algorithm>

template <typename T>
class Quadtree;

template <typename T>
class Quadtree_node {
	private:
		T       x_value;
		T       y_value;

		Quadtree_node *north_west;
		Quadtree_node *north_east;
		Quadtree_node *south_west;
		Quadtree_node *south_east;

	public:
		Quadtree_node( T const & = T(), T const & = T() );

		T retrieve_x() const;
		T retrieve_y() const;

		Quadtree_node *nw() const;
		Quadtree_node *ne() const;
		Quadtree_node *sw() const;
		Quadtree_node *se() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		bool member( T const &, T const & ) const;

		bool insert( T const &, T const & );
		void clear();

	friend class Quadtree<T>;
};

template <typename T>
Quadtree_node<T>::Quadtree_node( T const &x, T const &y ):
x_value( x ), 
y_value( y ), 
north_west( 0 ),
north_east( 0 ),
south_west( 0 ),
south_east( 0 ) {
	// empty constructor
}

template <typename T>
T Quadtree_node<T>::retrieve_x() const {
	return x_value;
}

template <typename T>
T Quadtree_node<T>::retrieve_y() const {
	return y_value;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::nw() const {
	return north_west;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::ne() const {
	return north_east;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::sw() const {
	return south_west;
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::se() const {
	return south_east;
}

template <typename T>
T Quadtree_node<T>::min_x() const {
    if(north_west != 0 && south_west != 0) {
        T min = std::min(north_west->min_x() , south_west->min_x());
        min = std::min(x_value, min);
        return min;
    } else if (north_west != 0 && south_west == 0) {
        T min = std::min(north_west->min_x(), x_value);
        return min;
    } else if (north_west == 0 && south_west != 0) {
        T min = std::min(south_west->min_x(), x_value);
        return min;
    } else {
        return x_value;
    }
}

template <typename T>
T Quadtree_node<T>::min_y() const {
    if(south_west != 0 && south_east != 0) {
        T min = std::min(south_west->min_y() , south_east->min_y());
        min = std::min(y_value, min);
        return min;
    } else if (south_west != 0 && south_east == 0) {
        T min = std::min(south_west->min_y(), y_value);
        return min;
    } else if (south_west == 0 && south_east != 0) {
        T min = std::min(south_east->min_y(), y_value);
        return min;
    } else {
        return y_value;
    }
}

template <typename T>
T Quadtree_node<T>::max_x() const {
    if(north_east != 0 && south_east != 0) {
        T max = std::max(north_east->max_x() , south_east->max_x());
        max = std::max(x_value, max);
        return max;
    } else if (north_east != 0 && south_east == 0) {
        T max = std::max(north_east->max_x(), x_value);
        return max;
    } else if (north_east == 0 && south_east != 0) {
        T max = std::max(south_east->max_x(), x_value);
        return max;
    } else {
        return x_value;
    }
}

template <typename T>
T Quadtree_node<T>::max_y() const {
    if(north_west != 0 && north_east != 0) {
        T max = std::max(north_west->max_y() , north_east->max_y());
        max = std::max(x_value, max);
        return max;
    } else if (north_west != 0 && north_east == 0) {
        T max = std::max(north_west->max_y(), x_value);
        return max;
    } else if (north_west == 0 && north_east != 0) {
        T max = std::max(north_east->max_y(), x_value);
        return max;
    } else {
        return y_value;
    }
}

template <typename T>
T Quadtree_node<T>::sum_x() const {
    if ( this == 0 ) {
        // hint...
        return 0;
    } else {
        T sum = north_west->sum_x() + north_east->sum_x() + south_west->sum_x() + south_east->sum_x() + x_value;
        return sum;
    }
}

template <typename T>
T Quadtree_node<T>::sum_y() const {
    if ( this == 0 ) {
        // hint...
        return 0;
    } else {
        T sum = north_west->sum_y() + north_east->sum_y() + south_west->sum_y() + south_east->sum_y() + y_value;
        return sum;
    }
}

template <typename T>
bool Quadtree_node<T>::member( T const &x, T const &y ) const {
    
    if( x == x_value && y == y_value) {
        return true;
    }
    
    
    if (x >= x_value) {
        if (y >= y_value) {
            if(north_east != 0) {
                return north_east->member(x, y);            //NE
            }
        }
        else{
            if(south_east != 0) {                           //SE
                return south_east->member(x, y);
            }
        }
    }
    else {
        if (y >= y_value) {                                 //NW
            if(north_west != 0) {
                return north_west->member(x, y);
            }
        }else {                                             //SW
            if(south_west != 0) {
                return south_west->member(x, y);
            }
        }
    }
    return false;
    
}

template <typename T>
bool Quadtree_node<T>::insert( T const &x, T const &y ) {
    
    if (this!= 0 && x == x_value && y ==  y_value){
        return false;                                       //already exists?
    }
    
    if (x >= x_value) {
        if (y >= y_value) {
            if(north_east != 0) {                           //a node already exists in north east quadrant
                return north_east->insert(x, y);            //then call insert on the NE quad
            } else {                                        //a node DNE already in the SE quad
                north_east = new Quadtree_node<T>(x, y);    //create a new node
                return true;
            }
        }
        else{
            if(south_east != 0) {
                return south_east->insert(x, y);            //same for SE
            } else {
                south_east = new Quadtree_node<T>(x, y);
                return true;
            }
        }
    }
    else {
        if (y >= y_value) {                                 //NW
            if(north_west != 0) {
                return north_west->insert(x, y);
            } else {
                north_west = new Quadtree_node<T>(x, y);
                return true;
            }
        }else {                                             //SW
            if(south_west != 0) {
                return south_west->insert(x, y);
            } else {
                south_west = new Quadtree_node<T>(x, y);
                return true;
            }
        }
    }
    return false;
}

template <typename T>
void Quadtree_node<T>::clear() {
    if(north_west != 0) {
        north_west->clear();
        north_west=0;
    }
    if(north_east != 0) {
        north_east->clear();
        north_east=0;
    }
    if(south_west != 0) {
        south_west->clear();
        south_west=0;
    }
    if(south_east != 0) {
        south_east->clear();
        south_east=0;
    }
    delete this;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
