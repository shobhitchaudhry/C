#ifndef DEQUE_AS_ARRAY_H
#define DEQUE_AS_ARRAY_H

/******************************************
 * UW User ID:  s28chaud
 * Submitted for ECE 250
 * Semester of Submission:  (Winter) 2016
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 ******************************************/

#include "Exception.h"
#include <iostream>
using namespace std;

class Deque_as_array {
	private:
		int array_size;
		int*array;
		int ihead;
		int itail;
		int count;

	public:
		Deque_as_array( int = 10 );
		~Deque_as_array();

		int head() const;
		int tail() const;
		int size() const;
		bool empty() const;
		int capacity() const;

		void enqueue_head( int const & );
		void enqueue_tail( int const & );
		int dequeue_head();
		int dequeue_tail();
		void clear();
        void print();
};

 
Deque_as_array::Deque_as_array( int n ):
array_size( max( 1, n ) ),
array( new int[array_size] ), 
count( 0 ) {
    ihead=itail=0;  //initailising ihead and itail to 0
}


Deque_as_array::~Deque_as_array() {
    delete [] array;    //destruct the array
    array=0;            //clear the array
    count=0;            //reset the count
}

 
int Deque_as_array::size() const {
	return count;
}


int Deque_as_array::capacity() const {
	return array_size;
}

 
bool Deque_as_array::empty() const {
    bool isEmpty=false;
    if(size()==0){
        isEmpty=true;
    }
	return isEmpty;
}

 
int Deque_as_array::head() const {
    if (size() <= 0) {
        throw underflow();      //no head exists since deque is empty
    } else {
        return array[ihead];
    }
}

 
int Deque_as_array::tail() const {
    if (size() <= 0) {
        throw underflow();      //no tail exists since deque is empty
    } else {
        return array[itail];
    }
}


void Deque_as_array::enqueue_head( int const &obj ) {
    if(count == array_size) {
        throw overflow();                       //deque is full
    } else if (count == 0) {
        array[ihead] = array[itail] = obj;      //first object
        count++;
    } else {
        ihead--;
        if (ihead < 0) {            //go to the end of the deque if reached the end of the array and deque is not full
            ihead += array_size;
        }
        array[ihead] = obj;
        count++;
    }}


void Deque_as_array::enqueue_tail( int const &obj ) {
    if(count == array_size) {
        throw overflow();                       //deque is full
    } else if (count == 0) {
        array[itail] = array[ihead] = obj;      //first object
        count++;
    } else {
        itail++;
        if (itail > (array_size-1)) {       //go to the front of the deque if reached the end of the array and deque is not full
            itail -= array_size;
        }
        array[itail] = obj;
        count++;
    }
}

 
int Deque_as_array::dequeue_head() {
    if(count==0){
        throw underflow();      //no head to remove exists since deque is empty
    }else{
        int toRemove = array[ihead];
        array[ihead] = 0;
        if (ihead != itail) {
            if (ihead == array_size-1) {
                ihead -= array_size;    //go to the front of the deque if reached the end of the array after deleting
            }
            ihead++;
        }
        count--;
        return toRemove;     // This returns a default object
    }
}

int Deque_as_array::dequeue_tail() {
    if (count == 0) {
        throw underflow();      //no tail to remove exists since deque is empty
    }else{
        int toRemove = array[itail];       //return value
        array[itail] = 0;
        if(ihead != itail) {
            if (itail == 0) {
                itail += array_size;    //go to the end of the deque if reached the front of the array after deleting
            }
            itail--;            //make itail point to the prev value
        }
        count--;              //decrement count
        return toRemove;     // This returns a default object
    }
}
 
void Deque_as_array::clear() {
    array = new int[array_size];    //make a new deque
    count = 0 ;                     //change the old variables to the right values
    ihead=itail=0;
}

void Deque_as_array::print() {
    if(count<=0){
        throw underflow();
    }else{
        int i = ihead;
        for (int elements = 1; elements < count; elements++, i++) {
            cout << array[(i)%array_size] << ";";
        }
        cout << tail() << endl;    //To add a line break at the end of print loop
    }
}


#endif
