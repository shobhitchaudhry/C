#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/****************************************
 * UW User ID:  s28chaud
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"
using namespace std;
enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;
		int power;
		int array_size;
		T *array;
		state *array_state;

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		array_state[i] = EMPTY;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
    delete[] array;
    delete[] array_state;
    // do i make these 0?
}

template<typename T >
int DoubleHashTable<T >::size() const {
    return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    return array_size;
}



template<typename T >
bool DoubleHashTable<T >::empty() const {
    if (size() == 0) {
        return true;
    } else {
        return false;
    }
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
    int value = static_cast<int> (obj);
    int location = value % array_size;      //value mod array size or (k mod m )
    if(location < 0) {
        location += array_size;             //getting a positive value in the array_size range if negative
    }
    return location;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
    
    int value = (static_cast<int> (obj))/ array_size; // i/M
    int location;
    
    location = value % array_size;    // (i / M) % M
    
    if(location < 0) {
        location += array_size; //getting a positive value in the array_size range if negative
    }
    if((location%2) == 0) {     //if location is even , make odd
        location += 1;
    }
    
    return location;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {

    if(count == 0) {
        return false;
    }else{
        int location;
    
        for (int i = 0; i < array_size; i++) {
        
            location = (h1(obj) + i*h2(obj)) % array_size ;     // h(k,i) = (h1 (k ) + i.h2 (k )) mod M from lecture notes
            
            if (array_state[location] == EMPTY) {       // check if the location is empty
                return false;                           // if empty then false
            }
            else if ( (array_state[location] == OCCUPIED) && (array[location] == obj) ) {
                return true;        // if it is occupied and with the right object, return true
            }
        }
        return false;
    }
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
        return array[n];
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
    
    if(count == array_size) {   // table is full
        throw overflow();
    }else{
        int location = 0;
        int i = 0;
        do {
            location = (h1(obj) + i*h2(obj)) % array_size;
            i++;
        } while (array_state[location] == OCCUPIED);
        
        array[location] = obj;
        array_state[location] = OCCUPIED;
        count++;
    }
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
    if(count == 0) {
        return false;
    }else{
        int location;
        for (int i = 0; i < array_size; i++) {
            
            location = (h1(obj) + i*h2(obj)) % array_size;
            if (array_state[location] == EMPTY) {
                return false;
            }else if ((array_state[location] = OCCUPIED) && (array[location] == obj) ) {
                array_state[location] = DELETED;
                count--;
                return true;
            }
        }
        return false;
    }
}

template<typename T >
void DoubleHashTable<T >::clear() {
    for (int i = 0; i < array_size; i++) {
        array_state[i] = EMPTY;
        array[i] = 0;
    }
    count = 0;
    return ;
}

template<typename T >
void DoubleHashTable<T >::print() const {
    cout << "location - value - state \n";
    for (int i = 0; i < array_size; i++) {
        cout << i << " - " << array[i] << " - " << array_state[i] << endl;
    }
    return;
}

#endif
