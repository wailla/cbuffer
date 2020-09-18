//
// Created by Fabio on 03/09/2020.
//

#include "exeptionBuffer.h"
// queue_iterator_out_of_bounds_exception

// Definizione della classe eccezione custom empty_buffer_exception
empty_buffer_exception::empty_buffer_exception(const std::string &message) :
        _message(message) {} // initialization list

// Definizione del metodo what()
std::string empty_buffer_exception::what() const {
    return _message;
}

/*
	Definizione della classe eccezione custom
    buffer_iterator_out_of_bounds_exception
*/

// Definizione del costruttore
buffer_iterator_out_of_bounds_exception::
buffer_iterator_out_of_bounds_exception(const std::string &message) :
        _message(message) {} // initialization list

// Definizione del metodo what()
std::string buffer_iterator_out_of_bounds_exception::what() const {
    return _message;
}