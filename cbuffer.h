//
// Created by Fabio on 26/08/2020.
//

#ifndef CBUFFER_CBUFFER_H
#define CBUFFER_CBUFFER_H

#include <algorithm>
#include "exeptionBuffer.h"
#include <iterator> // std::random_iterator_tag
#include <cstddef>  // std::ptrdiff_t

//_dbuffer = arrayptr
//_size = sizeBuffer
template<typename T>
class cbuffer {

private:
    T *arrayptr; ///<puntaore alla testa della lista
    unsigned int sizeBuffer;///<grandezza del buffer
    unsigned int numElement;///<quantità di elementi nel buffer
    typedef unsigned int type_dimension; ///< Definzione del tipo corrispondente a size
    unsigned int currentIndex;///<dove punta il mio buffer

public:

    /**
    @brief Costruttore di default (METODO FONDAMENTALE)

    Costruttore di default per istanziare un cbuffer vuoto. E' l'unico costruttore
    che puo' essere usato per create un arrayptr di cbuffer!
**/
    cbuffer() : sizeBuffer(0), arrayptr(nullptr), currentIndex(0) {
    }

    /**
        @brief Costruttore secondario

        Costruttore secondario. Permette di istanziare un cbuffer con una data dimensione.
        @param size Dimensione del cbuffer da istanziare
    **/
    explicit cbuffer(type_dimension size) : sizeBuffer(0), arrayptr(nullptr), currentIndex(0) {
        arrayptr = new T[size];
        sizeBuffer = size;
    }

    /**
        @brief Costruttore secondario

        Costruttore secondario. Permette di istanziare un cbuffer con una data dimensione
        e di inizializzare le celle dell'arrayptr con il valore dato
        @param size Dimensione del cbuffer da istanziare
        @param value Valore da usare per inizizalizzare le celle dell'arrayptr
    **/
    cbuffer(type_dimension size, const T &value) : sizeBuffer(0), arrayptr(nullptr), currentIndex(0) {
        arrayptr = new T[size];
        sizeBuffer = size;
        for (type_dimension i = 0; i < sizeBuffer; ++i) {
            arrayptr[i] = value;
            numElement++;
            currentIndex++;
        }
    }

    /**
        @brief Costruttore secondario

        Costruttore secondario. Permette di istanziare un cbuffer su tipi T da un altro
        cbuffer che contiene tipi Q. La creazione è possibile solo se è possibile castare
        un tipo Q in un tipo T (il controllo lo fà il compilatore).

        @param pther cbuffer sorgente
    **/
    template<typename Q>
    cbuffer(const cbuffer<Q> &other) : arrayptr(nullptr), sizeBuffer(0), currentIndex(0) {
        arrayptr = new T[other.sizeBuffer()];

        try {
            for (unsigned int i = 0; i < other.sizeBuffer(); ++i)
                arrayptr[i] = static_cast<T>(other[i]);
            numElement++;
            currentIndex++;
        }
        catch (...) {
            delete[] arrayptr;
            arrayptr = nullptr;
            sizeBuffer = 0;
            currentIndex = 0;
            throw;
        }
        sizeBuffer = other.sizeBuffer();
    }

    /**
        @brief Copy constructor (METODO FONDAMENTALE)

        Costruttore di copia. Permette di istanziare un cbuffer con i valori
        presi da un altro cbuffer.
        @param other cbuffer da usare per creare quello corrente
    **/
    cbuffer(const cbuffer &other) : sizeBuffer(0), arrayptr(nullptr), currentIndex(0) {
        arrayptr = new T[other.sizeBuffer];

        for (unsigned int i = 0; i < other.sizeBuffer; ++i) {
            arrayptr[i] = other.arrayptr[i];
            numElement++;
            currentIndex++;
        }
        sizeBuffer = other.sizeBuffer;
    }

    /**
        @brief Operatore di assegnamento (METODO FONDAMENTALE)

        Operatore di assegnamento. Permette la copia tra cbuffer.
        @param other cbuffer sorgente
        @return Riferimento a this
    **/
    cbuffer &operator=(const cbuffer &rhs) {
        if (this != &rhs) {

            cbuffer tmp(rhs);

            std::swap(this->arrayptr, tmp.arrayptr);
            std::swap(this->sizeBuffer, tmp.sizeBuffer);
        }

        return *this;
    }


    /**
        @brief Distruttore (METODO FONDAMENTALE)

        Distruttore. Rimuove la memoria allocata da cbuffer.
    **/
    ~cbuffer() {
        delete[] arrayptr;
        arrayptr = nullptr;
        sizeBuffer = 0;
    }
    //fine dei metodi fondamentiali

    /**
     *
     * @return
     */
    unsigned int size() {
        return sizeBuffer;
    }

    /**
        @return
        Ritorna il numero di elementi nel buffer
     */
    unsigned int elementIn() {
        return numElement;
    }

    /**
        @brief Accesso ai dati in scrittura/lettura

        Metodo per leggere/scrivere il valore index-esimo dell'array.

        @pre E' necessario che address < sizeBuffer
        @param index Indice della cella dell'array da leggere/scrivere
        @return il contenuto della cella index-esima
    **/
    T &operator[](type_dimension address) {
        if (address < sizeBuffer) {
            return arrayptr[address];
        } else throw buffer_iterator_out_of_bounds_exception("l'index selezionato è maggiore "
                                                             "della grandezza del buffer");
    }

    /**
        @brief Accesso ai dati in lettura

        Metodo per leggere/scrivere il valore arrayptr-esimo dell'arrayptr.

        @pre E' necessario che address < sizeBuffer
        @param index Indice della cella dell'arrayptr da leggere/scrivere
        @return il contenuto della cella arrayptr-esima
    **/
    const T &operator[](type_dimension address) const {
        if (address < sizeBuffer) {
            return arrayptr[address];
        } else
            throw buffer_iterator_out_of_bounds_exception("l'index selezionato è maggiore "
                                                          "della grandezza del buffer");
    }

    /**
     * @brief Accesso dati in scrittura
     *
     * Metodo per aggingere un qualsiasi oggetto all'interno di un buffer. Se il buffer
     * è pieno sovrascrive il dato più vecchio
     *
     * @pre obj deve avere supportare un operatore di assegnamento
     * @param un oggetto qualsiasi in aggiunta
     */
    void add(const T &obj) {
        if (currentIndex < sizeBuffer) {
            arrayptr[currentIndex] = obj;
            numElement++;
            currentIndex++;
        } else {
            for (type_dimension i = 1; i < sizeBuffer; i++) {
                arrayptr[i] = arrayptr[i - 1];
            }
            arrayptr[currentIndex] = obj;
        }
    }

    /**
     * @brief Accesso dati in scrittura
     *
     * Metodo per rimuvovere oggetto più vecchio dal buffer
     *
     * @pre il buffer deve essere popolato
     */
    T remuoveold() {
        if (sizeBuffer == 0) {
            throw empty_buffer_exception("Impossibile rimuovere l'elemento piu' "
                                         "vecchio: il buffer e' vuota.");
        } else {
            T temp = arrayptr[0];
            for (type_dimension i = 1; i < sizeBuffer; i++) {
                arrayptr[i] = arrayptr[i - 1];
            }
            numElement--;
            currentIndex--;
            return temp;
        }
    }

    //supporto iteratori lettura scrittura

    class const_iterator; // forward declaration

    class iterator {

        T *_ptr;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;


        iterator() : _ptr(nullptr) {}

        iterator(const iterator &other) : _ptr(other._ptr) {}

        iterator &operator=(const iterator &other) {
            _ptr = other._ptr;
            return *this;
        }

        ~iterator() {}

        // Ritorna il dato riferito dall'iteratore (dereferenziamento)
        reference operator*() const {
            return *_ptr;
        }

        // Ritorna il puntatore al dato riferito dall'iteratore
        pointer operator->() const {
            return _ptr;
        }

        // Operatore di iterazione post-incremento
        iterator operator++(int) {
            iterator tmp(*this);
            ++_ptr;
            return tmp;
        }

        // Operatore di iterazione pre-incremento
        iterator &operator++() {
            ++_ptr;
            return *this;
        }

        // Uguaglianza
        bool operator==(const iterator &other) const {
            return _ptr == other._ptr;
        }

        // Diversita'
        bool operator!=(const iterator &other) const {
            return !(*this == other);
        }

        friend class const_iterator;

        // Uguaglianza
        bool operator==(const const_iterator &other) const {
            return _ptr == other._ptr;
        }

        // Diversita'
        bool operator!=(const const_iterator &other) const {
            return _ptr != other._ptr;
        }

    private:

        // La classe container deve essere messa friend dell'iteratore per poter
        // usare il costruttore di inizializzazione.
        friend class dbuffer; // !!! Da cambiare il nome!

        // Costruttore privato di inizializzazione usato dalla classe container
        // tipicamente nei metodi begin e end
        explicit iterator(T *p) : _ptr(p) {}

    }; // classe iterator

    // Ritorna l'iteratore all'inizio della sequenza dati
    iterator begin() {
        return iterator(arrayptr);
    }

    // Ritorna l'iteratore alla fine della sequenza dati
    iterator end() {
        return iterator(arrayptr + sizeBuffer);
    }


    class const_iterator {
        const T *_ptr;
    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T value_type;
        typedef ptrdiff_t difference_type;
        typedef const T *pointer;
        typedef const T &reference;


        const_iterator() : _ptr(nullptr) {}

        const_iterator(const const_iterator &other) : _ptr(other._ptr) {}

        const_iterator &operator=(const const_iterator &other) {
            _ptr = other._ptr;
            return *this;
        }

        ~const_iterator() {}

        // Ritorna il dato riferito dall'iteratore (dereferenziamento)
        reference operator*() const {
            return *_ptr;
        }

        // Ritorna il puntatore al dato riferito dall'iteratore
        pointer operator->() const {
            return _ptr;
        }

        // Operatore di iterazione post-incremento
        const_iterator operator++(int) {
            const_iterator tmp(*this);
            ++_ptr;
            return tmp;
        }

        // Operatore di iterazione pre-incremento
        const_iterator &operator++() {
            ++_ptr;
            return *this;
        }

        // Uguaglianza
        bool operator==(const const_iterator &other) const {
            return _ptr == other._ptr;
        }

        // Diversita'
        bool operator!=(const const_iterator &other) const {
            return _ptr != other._ptr;
        }

        friend class iterator;

        // Uguaglianza
        bool operator==(const iterator &other) const {
            return _ptr == other._ptr;
        }

        // Diversita'
        bool operator!=(const iterator &other) const {
            return _ptr != other._ptr;
        }

        // Costruttore di conversione iterator -> const_iterator
        const_iterator(const iterator &other) : _ptr(other._ptr) {
        }

        // Assegnamento di un iterator ad un const_iterator
        const_iterator &operator=(const iterator &other) {
            _ptr = other._ptr;
            return *this;
        }

    private:

        // La classe container deve essere messa friend dell'iteratore per poter
        // usare il costruttore di inizializzazione.
        friend class dbuffer; // !!! Da cambiare il nome!

        // Costruttore privato di inizializzazione usato dalla classe container
        // tipicamente nei metodi begin e end
        const_iterator(const T *p) : _ptr(p) {}

        // !!! Eventuali altri metodi privati

    }; // classe const_iterator

    // Ritorna l'iteratore all'inizio della sequenza dati
    const_iterator begin() const {
        return const_iterator(arrayptr);
    }

    // Ritorna l'iteratore alla fine della sequenza dati
    const_iterator end() const {
        return const_iterator(arrayptr + sizeBuffer);
    }

}; // classe dbuffer

#endif //CBUFFER_CBUFFER_H
