#ifndef VECTOR_H
#define VECTOR_H

namespace Katalog {

typedef unsigned int u_int;

template <class T>
class vector
{
public:
    vector();
    ~vector();
    vector(const vector &v);
    vector& operator=(const vector &v);

    //iteratori
    /**
     * @brief Classe iterator per scorrere il vettore
     */
    class iterator{
    friend class vector;
    private:
        u_int offset;
        T* start;

    public:
        iterator(u_int i = 0);
        bool operator==(const iterator& i) const;
        bool operator!=(const iterator& i) const;
        iterator& operator++();
        iterator operator++(int);
        iterator operator+(const u_int i) const;
        iterator &operator+=(const u_int i);
        iterator &operator--();
        iterator operator--(int);
        iterator operator-(const u_int i) const;
        iterator &operator-=(const u_int i);

        T& operator*() const;
        T* operator->() const;
    };
    /**
     * @brief Classe const_iterator per scorrere un vettore costante
     */
    class const_iterator{
        friend class vector;
    private:
        u_int offset;
        T* start;

    public:
        const_iterator(u_int i = 0);
        bool operator==(const const_iterator& i) const;
        bool operator!=(const const_iterator& i) const;
        const_iterator &operator++();
        const_iterator operator++(int);
        const_iterator operator+(const u_int i) const;
        const_iterator &operator+=(const u_int i);
        const_iterator &operator--();
        const_iterator operator--(int);
        const_iterator operator-(const u_int i) const;
        const_iterator &operator-=(const u_int i);

        const T &operator*() const;
        const T *operator->() const;
    };
    /**
     * @brief begin: Restituisce un iteratore al primo elemento del vector
     * @retrun vector<T>::iterator
     */
    iterator begin();
    /**
     * @brief begin const: Restituisce un iteratore costante al primo elemento del vector
     * @return vector<T>::const_iterator
     */
    const_iterator begin() const;
    /**
     * @brief end: Restituisce un iteratore all'ultimo elemento del vettore
     * @return vector<T>::iterator
     */
    iterator end();
    /**
     * @brief end const: Restituisce un iteratore costante all'ultimo elemento del vettore
     * @return vector<T>::const_iterator
     */
    const_iterator end() const;

    //funzioni sul vettore
    /**
     * @brief front: Restituisce un riferimento al primo elemento dell'array
     * @return T&
     */
    T& front() const;
    /**
     * @brief back: Restituisce un riferimento all'ultimo elemento dell'array
     * @return T&
     */
    T& back() const;
    /**
     * @brief push_back: Aggiunge in coda al vettore un elemento. Può provocare un riallocamento
     * @param o: Oggetto da inserire
     */
    void push_back(const T& o);
    /**
     * @brief pop_back: Rimuove l'ultimo elemento del vettore
     */
    void pop_back();
    /**
     * @brief empty: Indica se il vettore è vuoto
     * @return true sse il vettore è privo di elementi
     */
    bool empty() const;
    /**
     * @brief size: Indica il numero di elementi attualmente nel vettore
     * @return numero di elementi nel vettore
     */
    u_int size() const;
    /**
     * @brief capacity: Indica il numero massimo di elementi che si possono inserire nel vettore prima di dover riallocare la memoria
     * @return numero di elementi inseribili prima di riallocare la memoria
     */
    u_int capacity() const;
    /**
     * @brief insert: Inserisce un elemento in una posizione specifica. Può provocare un riallocamento
     * @param o oggetto da inserire
     * @param pos iteratore che punta alla posizione in cui inserire l'oggetto
     */
    void insert(const T& o, iterator pos);
    /**
     * @brief erase: Rimuove degli elementi dal vettore
     * @param start Iteratore che indica il primo elemento da rimuovere
     * @param end Iteratore che indica la posizione successiva all'ultimo elemento da rimuovere
     */
    void erase(iterator start, iterator end);
    /**
     * @brief shrink_to_fit Prova a rimpicciolire la dimensione del vettore. Può provocare un riallocamento
     */
    void shrink_to_fit();
    /**
     * @brief append Aggiunge in coda gli elementi del vettore indicato. Può provocare un riallocamento
     * @param v Vettore sorgente da cui copiare gli elementi
     */
    void append(const vector& v);
    /**
     * @brief operator []: Ottiene un riferimento all'elemento alla posizione indicata
     * @param i: Iteratore alla posizione dell'elemento da prelevare
     * @return Oggetto all'indice i
     */
    T& operator[](const iterator i);
    /**
     * @brief operator [] const: Ottiene un riferimento costante all'elemento alla posizione indicata
     * @param i Iteratore alla posizione dell'elemento da prelevare
     * @return Oggetto costante all'indice i
     */
    const T &operator[](const const_iterator i) const;

private:
    T* list;
    u_int lsize;
    u_int lcapacity;
    /**
     * @brief realloc: Rialloca l'array estendendolo e mantenendo gli oggetti precedentemente inseriti
     */
    void realloc();
};

template <class T>
vector<T>::vector(): list(new T[1]), lsize(0), lcapacity(1)
{

}

template<class T>
vector<T>::~vector()
{
    delete[] list;
}

template<class T>
vector<T>::vector(const vector &v): list(new T[v.lcapacity]), lsize(v.lsize), lcapacity(v.lcapacity)
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
void vector<T>::erase(vector::iterator first, vector::iterator last)
{
    if(last == end()){
        lsize = first.offset;
        return;
    }
    for(; last != end(); ++last, ++first){
        list[first.offset] = list[last.offset];
    }
    lsize = first.offset;
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
    for(const_iterator j = v.begin(); j != v.end(); ++j)
        push_back(*j);
}

template<class T>
T &vector<T>::operator[](const vector::iterator i)
{
    return *(list + i.offset);
}

template<class T>
const T &vector<T>::operator[](const vector::const_iterator i) const
{
    return *(list + i.offset);
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
    return start == i.start && offset == i.offset;
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
    iterator aux(((static_cast<int>(offset) - static_cast<int>(i) < 0) ? 0 : offset - i));
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

}

#endif // VECTOR_H
