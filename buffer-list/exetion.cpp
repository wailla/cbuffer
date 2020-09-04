//
// Created by Fabio on 03/09/2020.
//

#include "exeptionBuffer.h"
/**
	@file queue_exceptions.cpp
	@brief Definizione delle classi di eccezioni custom relative alla classe
           queue
    @description
    File sorgente con la definizione delle classi di eccezioni custom
    empty_queue_exception e queue_iterator_out_of_bounds_exception.
*/

// Direttive per il pre-compilatore

#include "exeptionBuffer.h"
// queue_iterator_out_of_bounds_exception

// Definizione della classe eccezione custom empty_queue_exception
empty_buffer_exception::empty_buffer_exception(const std::string &message) :
        _message(message) {} // initialization list

// Definizione del metodo what()
std::string empty_buffer_exception::what() const {
    return _message;
}

/*
	Definizione della classe eccezione custom
    queue_iterator_out_of_bounds_exception
*/

// Definizione del costruttore
buffer_iterator_out_of_bounds_exception::
buffer_iterator_out_of_bounds_exception(const std::string &message) :
        _message(message) {} // initialization list

// Definizione del metodo what()
std::string buffer_iterator_out_of_bounds_exception::what() const {
    return _message;
}