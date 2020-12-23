#ifndef DEEPPTR_H
#define DEEPPTR_H

namespace Katalog {
    template <class T>
    class DeepPtr
    {
    private:
        T* obj;
    public:
        /**
         * @brief DeepPtr Crea il puntatore smart ad un oggetto
         * @param o Oggetto a cui punta. Default nullptr
         */
        DeepPtr(T* o = nullptr);
        /**
         * @brief DeepPtr Costruttore di copia
         * @param ptr DeepPtr da copiare
         */
        DeepPtr(const DeepPtr &ptr);
        /**
         * @brief operator = Assegnazione del puntatore
         * @param ptr DeepPtr da cui prendere il valore da assegnare
         * @return Riferimento al chiamante
         */
        DeepPtr& operator=(const DeepPtr &ptr);
        ~DeepPtr();
        /**
         * @brief operator * Dereferenizia il puntatore
         * @return Riferimento all'oggetto puntato
         */
        T& operator*() const;
        /**
         * @brief operator -> Puntatore all'oggetto
         * @return Puntatore all'oggetto
         */
        T* operator->() const;
    };
};

#endif // DEEPPTR_H
