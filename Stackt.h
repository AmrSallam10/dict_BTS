// File: Stackt.h
// Stack template class definition. 
// Dynamic array implementation 

#ifndef STACKT_H           
#define STACKT_H           

template <class Type>

class Stackt
{
   public:
      
      Stackt(int nelements = 128);		// Constructor
	  Stackt (const Stackt<Type> &);	// Copy Constructor
	  ~Stackt();						// Destructor

	  // Member Functions	      
      void push(Type );				// Push
      void pop(Type &);				// Pop
	  void stackTop(Type &) const;	// retrieve top
      bool stackIsEmpty() const;	// Test for Empty stack
      bool stackIsFull() const;		// Test for Full stack

   private:
      Type *stack;					// pointer to dynamic array
	  int top, MaxSize;				

}; 

#endif // STACKT_H
#include "Stackt.cpp"

