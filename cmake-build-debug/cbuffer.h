//
// Created by Fabio on 26/08/2020.
//

#ifndef CBUFFER_CBUFFER_H
#define CBUFFER_CBUFFER_H

#include <algorithm>
#include <assert.h>
#include "exeptionBuffer.h"

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
        } else return nullptr;
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
        } else return nullptr;
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
        if(currentIndex < sizeBuffer) {
            arrayptr[currentIndex] = obj;
            numElement++;
            currentIndex++;
        }
        else {
            for(type_dimension i = 1; i < sizeBuffer; i++){
                arrayptr[i] = arrayptr[i-1];
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
                                        "vecchio: la coda e' vuota.");
        } else {
            T temp = arrayptr[0];
            for (type_dimension i = 1; i < sizeBuffer; i++) {
                arrayptr[i] = arrayptr[i - 1];
            }
            numElement--;
            currentIndex--;
        }
    }

    //supporto iteratori lettura scrittura
};

#endif //CBUFFER_CBUFFER_H
