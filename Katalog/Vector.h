#ifndef VECTOR_H
#define VECTOR_H

namespace Katalog {

typedef unsigned int u_int;

template <class T>
class vector
{
public:
    //costruttori, distruttori, assegnatori
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
    void erase(const iterator& start, const iterator& end);
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
    T& operator[](const iterator& i) const;
    /**
     * @brief operator [] const: Ottiene un riferimento costante all'elemento alla posizione indicata
     * @param i Iteratore alla posizione dell'elemento da prelevare
     * @return Oggetto costante all'indice i
     */
    const T &operator[](const const_iterator& i) const;

    //T& operator[](const u_int i) const;

private:
    T* list;
    u_int lsize;
    u_int lcapacity;
    /**
     * @brief realloc: Rialloca l'array estendendolo e mantenendo gli oggetti precedentemente inseriti
     */
    void realloc();
};

}

#endif // VECTOR_H
