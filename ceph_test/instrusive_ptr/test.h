#ifndef TEST_H_
#define TEST_H_

#include "atomic.h"
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <iostream>

using namespace std;
using namespace boost;

class RefObject
{
private:
	AtomicInt32 ref_;
public:
	RefObject() { }

	RefObject* get()
	{
		ref_.Inc();
		cout << "after get, ref: " << ref_.Get() << endl;
		return this;
	}

	void put()
	{
		int32_t ret = ref_.Dec();
		cout << "after put, ref: " << ref_.Get() << endl;
		if (ret == 0)
			delete this;
		return;
	}
};

class Test : public RefObject
{
private:
	string name_;
public:
	Test(string name) : name_(name)
	{
		cout << "construct test, name " << name_ << endl;
	}

	Test(Test &other)
	{
		name_ = other.name_;
		cout << "copy construct test, other name " << other.name_ << endl;
	}

	~Test()
	{
		cout << "descontruct test, name " << name_ <<endl;
	}
};

static inline void intrusive_ptr_add_ref(Test *s)
{
	s->get();
}

static inline void intrusive_ptr_release(Test *s)
{
	s->put();
}

typedef intrusive_ptr<Test> TestRef;
#endif


