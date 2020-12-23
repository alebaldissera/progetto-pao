#include "DeepPtr.h"

using namespace Katalog;


template<class T>
DeepPtr<T>::DeepPtr(T *o): obj(o) {}

template<class T>
DeepPtr<T>::DeepPtr(const DeepPtr &ptr): obj(new T(*(ptr.obj))) {}

template<class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr &ptr)
{
    if(this != &ptr){
        delete obj;
        obj = new T(*(ptr.obj));
    }
    return *this;
}

template<class T>
DeepPtr<T>::~DeepPtr()
{
    delete obj;
}

template<class T>
T &DeepPtr<T>::operator*() const
{
    return *obj;
}

template<class T>
T *DeepPtr<T>::operator->() const
{
    return obj;
}
