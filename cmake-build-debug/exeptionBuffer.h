//
// Created by Fabio on 26/08/2020.
//

#ifndef CBUFFER_EXEPTIONBUFFER_H
#define CBUFFER_EXEPTIONBUFFER_H
// Direttive per il pre-compilatore

#include <string> // std::string

// Dichiarazione della classe eccezione custom empty_queue_exception

/**
	@brief Eccezione di coda vuota
    @description
	Classe eccezione custom di coda vuota.
	Viene lanciata quando si prova ad accedere (in lettura e/o scrittura)
    agli elementi di una coda vuota, oppure quando si prova a rimuovere
    l'elemento più vecchio di una coda vuota.
*/
class empty_buffer_exception {

    std::string _message; ///< @brief Messaggio di errore

public:
    /**
		@brief Costruttore
	    @description
		Costruttore che istanzia un'eccezione di array vuoto, inizializzando
	    con il messaggio di errore.
	    @param message messaggio di errore
	*/
    empty_buffer_exception(const std::string &message);

    /**
		@brief Messaggio di errore
		@description
		Metodo che restituisce il messaggio di errore dell'eccezione di coda
	    vuota.

		@return messaggio di errore
	*/
    std::string what() const;
};

/*
	Dichiarazione della classe eccezione custom
    queue_iterator_out_of_bounds_exception
*/

/**
	@brief Eccezione di iteratore della coda fuori dai limiti
    @description
	Classe eccezione custom di iteratore della coda fuori dai limiti.
	Viene lanciata quando un iteratore della coda prova ad accedere a una
	locazione di memoria esterna alla coda.
*/
class buffer_iterator_out_of_bounds_exception {

    std::string _message; ///< @brief Messaggio di errore

public:

    /**
        @brief Costruttore

        Costruttore che istanzia un'eccezione di iteratore della coda
        fuori dai limiti, inizializzandola con il messaggio di errore.
        @param message messaggio di errore
    */
    buffer_iterator_out_of_bounds_exception(const std::string &message);

    /**
        @brief Messaggio di errore

        Metodo che restituisce il messaggio di errore dell'eccezione
        di iteratore della coda fuori dai limiti.

        @return messaggio di errore
    */
    std::string what() const;
};

#endif //CBUFFER_EXEPTIONBUFFER_H
