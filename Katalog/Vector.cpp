#include "Vector.h"

using namespace Katalog;

template <class T>
vector<T>::vector(): list(new T[1]), lcapacity(1), lsize(0)
{

}

template<class T>
vector<T>::~vector()
{
    delete[] list;
}

template<class T>
vector<T>::vector(const vector &v): list(new T[v.capacity]), lsize(v.size), lcapacity(v.lcapacity)
{
    for(u_int i = 0; i < lsize; i++){
        list[i] = v.list[i];
    }
}

template<class T>
vector<T> &vector<T>::operator=(const vector &v)
{
    if(this != &v){
        delete[] list;
        lcapacity = v.lcapacity;
        lsize = v.lsize;
        list = new T[lcapacity];
        for(u_int i = 0; i < lsize; i++){
            list[i] = v.list[i];
        }
    }
    return *this;
}

template<class T>
typename vector<T>::iterator vector<T>::begin()
{
    iterator aux;
    aux.start = list;
    return aux;
}

template<class T>
typename vector<T>::const_iterator vector<T>::begin() const
{
    const_iterator aux;
    aux.start = list;
    return aux;
}

template<class T>
typename vector<T>::iterator vector<T>::end()
{
    iterator aux(lsize);
    aux.start = list;
    return aux;
}

template<class T>
typename vector<T>::const_iterator vector<T>::end() const
{
    const_iterator aux(lsize);
    aux.start = list;
    return aux;
}

template<class T>
T &vector<T>::front() const
{
    return list[0];
}

template<class T>
T &vector<T>::back() const
{
    return list[lsize - 1];
}

template<class T>
void vector<T>::push_back(const T &o)
{
    if(lsize == lcapacity){
        realloc();
    }

    list[lsize] = T(o);
    ++lsize;
}

template<class T>
void vector<T>::pop_back()
{
    --lsize;
}

template<class T>
bool vector<T>::empty() const
{
    return (size) ? true : false;
}

template<class T>
u_int vector<T>::size() const
{
    return lsize;
}

template<class T>
u_int vector<T>::capacity() const
{
    return lcapacity;
}

template<class T>
void vector<T>::insert(const T &o, vector::iterator pos)
{
    if(lsize + 1 < lcapacity)
        realloc();
    for(u_int i = lsize - 1; i >= pos.offset; --i){
        list[i + 1] = list[i];
    }
    list[pos.offset] = T(o);
}

template<class T>
void vector<T>::erase(const vector::iterator &start, const vector::iterator &end)
{
    if(end == end()){
        lsize = start.offset + 1;
        return;
    }
    for(; end != end(); ++end, ++start){
        *start = *end;
    }
    lsize = start.offset + 1;
}

template<class T>
void vector<T>::shrink_to_fit()
{
    if(lsize < lcapacity / 2 && lcapacity != 1){
        T* temp = new T[lcapacity / 2];
        for(u_int i = 0; i < lsize; i++){
            temp[i] = list[i];
        }
        delete[] list;
        list = temp;
    }
}

template<class T>
void vector<T>::append(const vector &v)
{
    while(lsize + v.lsize >= lcapacity) //estendo la capacità del mio vettore per permettere di inserire tutti gli elementi del secondo
        realloc();
    for(iterator i = begin(), j = v.begin(); j != v.end(); ++i, ++j)
        *i = *j;
}

template<class T>
T &vector<T>::operator[](const vector::iterator &i) const
{
    return *i;
}

template<class T>
const T &vector<T>::operator[](const vector::const_iterator &i) const
{
    return *i;
}

template<class T>
void vector<T>::realloc()
{
    lcapacity *= 2;
    T* temp = new T[lcapacity];
    for(u_int i = 0; i < lsize; ++i){
        temp[i] = list[i];
    }
    delete[] list;
    list = temp;
}

template<class T>
vector<T>::iterator::iterator(u_int i): offset(i), start(nullptr) {}

template<class T>
bool vector<T>::iterator::operator==(const vector::iterator &i) const
{
    return start == i.start & offset == i.offset;
}

template<class T>
bool vector<T>::iterator::operator!=(const vector::iterator &i) const
{
    return !operator==(i);
}

template<class T>
typename vector<T>::iterator &vector<T>::iterator::operator++()
{
    offset++;
    return *this;
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator++(int)
{
    iterator r(*this);
    offset++;
    return r;
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator+(const u_int i) const
{
    iterator aux(offset + i);
    aux.start = start;
    return aux;
}

template<class T>
typename vector<T>::iterator &vector<T>::iterator::operator+=(const u_int i)
{
    offset += i;
    return *this;
}

template<class T>
typename vector<T>::iterator &vector<T>::iterator::operator--()
{
    offset--;
    return *this;
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator--(int)
{
    iterator r(*this);
    offset++;
    return r;
}

template<class T>
typename vector<T>::iterator vector<T>::iterator::operator-(const u_int i) const
{
    iterator aux((offset - i < 0) ? 0 : offset - i);
    aux.start = start;
    return aux;
}

template<class T>
typename vector<T>::iterator &vector<T>::iterator::operator-=(const u_int i)
{
    if((offset -= i) < 0) offset = 0;
    return *this;
}

template<class T>
T &vector<T>::iterator::operator*() const
{
    return *(start+offset);
}

template<class T>
T *vector<T>::iterator::operator->() const
{
    return start + offset;
}

template<class T>
vector<T>::const_iterator::const_iterator(u_int i): offset(i), start(nullptr) {}

template<class T>
bool vector<T>::const_iterator::operator==(const vector::const_iterator &i) const
{
    return (offset == i.offset) && (start == i.start);
}

template<class T>
bool vector<T>::const_iterator::operator!=(const vector::const_iterator &i) const
{
    return !operator==(i);
}

template<class T>
typename vector<T>::const_iterator &vector<T>::const_iterator::operator++()
{
    offset++;
    return *this;
}

template<class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator++(int)
{
    const_iterator aux(*this);
    offset++;
    return aux;
}

template<class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator+(const u_int i) const
{
    const_iterator aux(offset + i);
    aux.start = start;
    return aux;
}

template<class T>
typename vector<T>::const_iterator &vector<T>::const_iterator::operator+=(const u_int i)
{
    offset+=i;
    return *this;
}

template<class T>
typename vector<T>::const_iterator &vector<T>::const_iterator::operator--()
{
    offset++;
    return *this;
}

template<class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator--(int)
{
    const_iterator aux(*this);
    offset--;
    return aux;
}

template<class T>
typename vector<T>::const_iterator vector<T>::const_iterator::operator-(const u_int i) const
{
    const_iterator aux(*this);
    aux.offset -= i;
    return aux;
}

template<class T>
typename vector<T>::const_iterator &vector<T>::const_iterator::operator-=(const u_int i)
{
    offset -= i;
    return *this;
}

template<class T>
const T &vector<T>::const_iterator::operator*() const
{
    return *(start + offset);
}

template<class T>
const T *vector<T>::const_iterator::operator->() const
{
    return start + offset;
}