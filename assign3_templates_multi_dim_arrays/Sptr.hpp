/*
 * Sptr.hpp
 *
 *  Created on: May 7, 2012
 *      Author: devon mcbride
 */
//#include <mutex>
#include <boost/thread/thread.hpp> // doesn't work with my eclipse right now
#ifndef SPTR_HPP_
#define SPTR_HPP_

namespace cs540 {

class Counter{
	//private: commented out for ease of testing
	public:
		int count;
	    	mutable boost::mutex m_mutex;
	public:
		Counter() : count(1) {}

		Counter * get(){
			return this;
		}

		int getCurrentCount(){
			return count;
		}

		void inc(){
			boost::mutex::scoped_lock lock(m_mutex);
			this->count++;
		}

		void dec(){
			boost::mutex::scoped_lock lock(m_mutex);
			this->count--;
		}
};


#if 0

/*-------------
   Constructs a smart pointer that points to the null pointer.
   ------------*/
Sptr(); // why is this outside the template????

/*-------------
   Constructs a smart pointer that points to the given object.
   The reference count is initialized to one.
   -------------*/
template <typename U>
Sptr(U *);


/*-------------
   The reference count is incremented. If U * is not implicitly convertible to T
   *, this will result in a syntax error. Note that both the normal copy
   constructur and a member template copy constructor must be provided for proper
   operation.
   --------------*/
Sptr(const Sptr &);
template <typename U> Sptr(const Sptr<U> &);


/*-------------
   The reference count is incremented. If U * is not implicitly convertible to T
   *, this will result in a syntax error. Note that both the normal assignment
   operator and a member template assignment operator must be provided for proper
   operation.
   -------------*/
Sptr &operator=(const Sptr &);
template <typename U> Sptr<T> &operator=(const Sptr<U> &);

/*-------------
   The smart pointer is set to point to the null pointer. The reference count for
   the currently pointed to object, if any, is decremented.
   -------------*/
void reset();


/*-------------
   A reference to the pointed-to object is returned. Note that this will be a
   const-reference if T is a const-qualified type.
   -------------*/
T &operator*() const;

/*-------------
   The pointer is returned. Note that this will be a pointer-to-const if T is a
   const-qualified type.
   -------------*/
T *operator->() const;

/*-------------
   The pointer is returned. Note that this will be a pointer-to-const if T is a
   const-qualified type.
   -------------*/
T *get() const;

/*-------------
   This is to implement the ability to test the pointer for null in a bool
   context. Use Google to find articles on the safe-bool idiom to understand how
   to use this.
   -------------*/
//operator unspecified_bool_type() const;
#endif /* #if 0 comment */


template<typename T>
class Sptr {

	public://private: removed for ease of testing
		T * pointer;
		Counter * counter;
	public:

		// explicit default constructor
		Sptr() : pointer(0), counter(0) {}

		// value parameter constructor
		template<typename U>
		Sptr(U * u) : pointer(u) {
			counter = new Counter;
		}

		// copy constructor
		Sptr(const Sptr & sptr) : pointer(sptr.get()),
								  counter(sptr.getCounter()) {
			sptr.counter->inc();
		}

		//ap2(bp2); // Automatic conversion to base class pointer.
		//error: no match for call to ‘(Sptr<A>) (Sptr<B>&)’

		// member template copy constructor
		template<typename U>
		Sptr(const Sptr<U> & theOther) : pointer(theOther.get()),
										 counter(theOther.getCounter()){
			theOther.counter->inc();
		}

		T * get() const{
			return pointer;
		}

		int getCount(){
			return counter->getCurrentCount();
		}

		Counter * getCounter() const{
			return counter;
		}


		// for assignment of same types
		Sptr & operator=(const Sptr & righthandside){
			if (this->get() != righthandside.get()){
				/* no match for ‘operator!=’ in ‘this != righthandside’ */
				pointer = righthandside.get();
				counter = righthandside.counter;
				counter->dec();
			}
			return *this;
		}

		/*===========================================================
		 * WARNING TO SELF: the following is a real mish-mash
		 * in my head.  I've been given the prototype, and the body
		 * itself is straight-forward, but, the signature is
		 * not really sinking into my understanding well.
		 * ==========================================================*/

		/*===========================================
		 * For assignment of types within hierarchy.
		 * If U* isn't implicitly convertible to T*,
		 * this will result in a syntax error.
		 * ==========================================*/
		//                   (Sptr<A>)                (Sptr<B>&)
		template <typename U> Sptr<T> &operator=(const Sptr<U> & righthandside){

		//Sptr & operator=(const Sptr & righthandside){
			if (this->get() != righthandside.get()){

				// this syntax is a real shot in the dark!
				//pointer = Sptr<T*>::static_pointer_cast(righthandside.get());
				pointer = righthandside.get();

				counter = righthandside.counter;
				counter->dec();
			}
			return *this;
		}

		T &operator*() const {
			return *pointer;
		}

		T* operator->() const {
			return pointer;
		}

		void reset(){
			counter->dec();
			pointer = 0;
		}

		/*
		bool &operator bool() const{
			return true;
		}
		 */

		// I don't know how this works.
		 operator bool() const
		 {
			 return (pointer ? true: false);
		 }
};

template <typename T1, typename T2>
bool operator==(const Sptr<T1> & t1, const Sptr<T2> &t2){
	return (t1.pointer == t2.pointer) ? true : false;
}

template <typename T1, typename T2>
bool operator!=(const Sptr<T1> & t1, const Sptr<T2> &t2){
	return (t1.pointer != t2.pointer) ? true : false;
}



template <typename T1>
bool operator!(const Sptr<T1> & t1){
	return  true;
}

template <typename T, typename U>
Sptr<T> static_pointer_cast(const Sptr<U> & sp){
	return static_pointer_cast<T>(Sptr<U>(sp));
}


template <typename T, typename U>
Sptr<T> dynamic_pointer_cast(const Sptr<U> & sp){
	return dynamic_pointer_cast<T>(Sptr<U>(sp));
}

}// end namespace cs540

#endif /* SPTR_HPP_ */


