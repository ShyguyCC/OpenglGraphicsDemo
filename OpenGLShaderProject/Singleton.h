//taken stright from karstens game engine.

#ifndef SINGLETON_H
#define SINGLETON_H

// simple singleton code, 

template <class T>
class Singleton
{

public:

	static T* Instance();	

private:

	Singleton() {}
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);

};

//------------------------------------------------------------------------------------------------------
//template function that will create an instance of any type and return its address
//------------------------------------------------------------------------------------------------------
template <class T> T* Singleton<T>::Instance()
{

	//declare a pointer to the object and assign it NULL value
	//this will happen only once, ie - the first iteration of this function
	static T* s_singletonObject = 0;

	//check if pointer is NULL, and if it is, instantiate the object
	if (!s_singletonObject)
	{
		s_singletonObject = new T();
	}

	//alternatively just return the address
	return s_singletonObject;

}

#endif