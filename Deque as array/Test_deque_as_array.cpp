#include "Deque_as_array.h"
#include <iostream>

using namespace std;
int main() {
    
    cout << "Starting Test Run" << endl << endl;
    cout << "Creating a new deque of capacity 5" << endl;
    
    Deque_as_array *deck = new Deque_as_array(5);       //new deque called deck creation
    
    cout << "New deque created successfully" << endl << endl;
    
    cout << "Capacity: " << deck->capacity() << endl;
    cout << "Size:" << deck->size() << endl;
    cout<< "Empty?: " << deck->empty() << endl;
    
    if(deck->capacity()==5 && deck->size()==0 && deck->empty()==1)
    {
        cout<< "No errors detected" << endl;
    }else{
        cout<< "Error detected" << endl;
    }
    cout<< "____________________" << endl << endl;
    
    
    
    cout<< "Adding an element(6) to deque" << endl;
    
    deck->enqueue_tail(6);
    cout << "ihead and itail test after enqueue" << endl;
    if(deck->head()==6 && deck->tail()==6){
        cout << "ihead = itail = " << deck->head() << endl;
        cout<< "No errors detected" << endl;
    }else
    {
        cout<< "Error detected: Could not enqueue" << endl;
    }
    
    cout<< "____________________" << endl << endl;


    
    cout<< "Enqueuing and dequeuing test" << endl;
    deck->enqueue_tail(7);
    deck->enqueue_head(8);
    deck->enqueue_tail(9);
    // this looks like (8,6,7,9)
    deck->dequeue_head();
    // this looks like (6,7,9)
    
    cout << "Capacity: " << deck->capacity() << endl;
    cout << "Size:" << deck->size() << endl;
    cout<< "Empty?: " << deck->empty() << endl;
    
    cout<< "The deque we have now is: " ;
    deck->print();
    
    if(deck->capacity()==5 && deck->size()==3 && deck->empty()==0 && deck->head()==6 && deck->tail()==9)
    {
        cout << "ihead = " << deck->head() << endl;
        cout << "itail = " << deck->tail() << endl;
        cout<< "No errors detected" << endl;
    }else{
        cout<< "Error detected" << endl;
    }
    cout<< "____________________" << endl << endl;

    
    
    //clearing the deque
    
    cout << "Deque clearing test" << endl;
    deck->clear();
    cout << "Deque cleared" << endl;
    cout << "Deque should now be in original state" << endl;
    
    cout << "Capacity: " << deck->capacity() << endl;
    cout << "Size:" << deck->size() << endl;
    cout<< "Empty?: " << deck->empty() << endl;
    
    if(deck->capacity()==5 && deck->size()==0 && deck->empty()==1)
    {
        cout<< "No errors detected" << endl;
    }else{
        cout<< "Error detected" << endl;
    }
    cout<< "____________________" << endl << endl;

	
    cout << "Underflow test on the cleared array" << endl;
    try {
        cout << "trying head() function on empty deque" << endl;
        deck->head();
        cout << "head() function failed to error but gave value '" << deck->head() << "' instead" << endl;
    } catch( underflow ) {
        cout << "Underflow error caught from head()" << endl;
    } catch (...) {
        cout << "head() errored out but did not throw underflow exception." << endl;
    }
    
    cout << endl;
    
    try {
        cout << "trying tail() function on empty deque" << endl;
        deck->tail();
        cout << "tail() function failed to error but gave value '" << deck->tail() << "' instead" << endl;
    } catch( underflow ) {
        cout << "Underflow error caught from tail()" << endl;
    } catch (...) {
        cout << "tail() errored out but did not throw underflow exception." << endl;
    }
    cout << endl;
    
    try {
        cout << "trying print() function on empty deque" << endl;
        deck->print();
        cout << "print() function failed to error but gave value ': ";
        deck->print();
        cout << "' instead" << endl;
    } catch( underflow ) {
        cout << "Underflow error caught from print()" << endl;
    } catch (...) {
        cout << "print() errored out but did not throw underflow exception." << endl;
    }
    cout << endl;
    
    try {
        cout << "trying dequeue_head() on empty deque" << endl;
        int removedInt = deck->dequeue_head();
        cout << "dequeue_head() function failed to error but gave value '" << removedInt<< "' instead" << endl;
    } catch( underflow ) {
        cout << "Underflow error caught from dequeue_head()" << endl;
    } catch (...) {
        cout << "dequeue_head() errored out but did not throw underflow exception." << endl;
    }
    
    cout<< "____________________" << endl << endl;
    
    cout << "Overflow test" << endl;
    
    cout << "Filling up deque to check overflow" << endl;
        deck->enqueue_tail(6);
        deck->enqueue_tail(7);
        deck->enqueue_tail(8);
        deck->enqueue_tail(9);
        deck->enqueue_tail(10);
    

    cout<< "The deque we have now is: " ;
    deck->print();
    cout << endl;
    cout << "Checking overflow" << endl;
    try {
        cout << "trying enqueue_head() on full deque" << endl;
        deck->enqueue_head( 11 );
        cout << "dequeue_head() function failed to error and ran successfully" << endl;
    } catch( overflow ) {
        cout << "overflow error caught from dequeue_head()" << endl;
    } catch(...) {
        cout << "Failure in enqueue_head(): expecting an underflow exception but caught a different exception" << endl;
    }
    cout << endl;
    
    try {
        cout << "trying enqueue_tail() on full deque" << endl;
        deck->enqueue_tail( 12 );
        cout << "dequeue_head() function failed to error and ran successfully" << endl;
    } catch( overflow ) {
        cout << "overflow error caught from enqueue_tail()" << endl;
    } catch(...) {
        cout << "enqueue_tail() errored out but did not throw underflow exception." << endl;
    }
    cout<< "____________________" << endl << endl;
    
	cout << "Finishing Test Run" << endl;

	return 0;
}