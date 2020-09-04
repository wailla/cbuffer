//
// Created by Fabio on 27/08/2020.
//

#ifndef CBUFFERLIST_CBUFFERLIST_H
#define CBUFFERLIST_CBUFFERLIST_H

#include <ostream> // std::ostream
#include <iterator> // std::forward_iterator_tag
#include <cstddef>  // std::ptrdiff_t
#include "exeptionBuffer.h"

/**
    @brief Coda FIFO
    description
    Classe template che implementa una coda FIFO di elementi generici T.
    @param T tipo del valore degli elementi della coda
 */
template<typename T, typename Q>
class cbufferlist {

    // Tipo di supporto privato della coda
    typedef T value_type; ///< @brief Tipo di supporto privato per rappresentare
    ///< il tipo generico del valore degli elementi del buffer
    struct element {
        value_type value; ///< @brief Valore dell'elemento
        element *next; ///< @brief Puntatore all'elemento successivo della coda

        /**
         * @brief costruttore di default (METODO FONDAMENTALE)
         * Unico cosrtuttore pre crazione di oggetto
         */
        element() : next(nullptr) {} // initialization list

        /**
         * @brief costruttore secondario
         *@description
		    Costruttore secondario che permette di istanziare un elemento,
			specificandone il valore.
         * @param v
         */
        explicit element(const value_type &v) : value(v), next(nullptr) {}

        /**
         * @brief construttore secondario
         * @description Costruttore secondario che permette di istanziare un elemento,
			specificandone il valore e il puntatore all'elemento successivo
		    della coda.
         * @param v valore elemento
         * @param n puntaotre all'elemnto succeivo
         */
        element(const value_type &v, element *n) : value(v), next(n) {} // initialization list
        /**
        @brief Distruttore (METODO FONDAMENTALE)

        @description
          Distruttore per deallocare la memoria allocata da un elemento.
        Viene chiamato automaticamente il distruttore del valore
        dell'elemento, corrispondente al distruttore del tipo T.
        */
        ~element() {
            next = nullptr;
        }
        /*
            Gli altri metodi fondamentali (Copy Constructor e operatore di
            assegnamento) coincidono con quelli di default, pertanto è inutile
            e ridondante specificarli.
        */

    };//fine struct

    element *_head;
    element *_tail;
    // Tipo di supporto privato della coda
    typedef unsigned int size_type; ///< @brief Tipo di supporto privato per
    ///< rappresentare il numero di elementi
    ///< inseriti nella coda (dimensione della coda)
    size_type _size; ///< @brief Numero di elementi inseriti nella coda (dimensione della coda)
    size_type _elementIn;
    Q _equals;
    // Funzioni private della coda


    // Funzioni helper private della coda

    /**
        @brief Rimozione ricorsiva degli elementi della coda a partire
        da un elemento (compreso)
        @param e puntatore all'elemento da cui iniziare la rimozione
               degli elementi della coda
        @post La memoria allocata dagli elementi della coda a partire da quello
              specificato (compreso) viene deallocata.
        @post Il numero di elementi inseriti nella coda viene decrementato
              di tante unità quanti sono gli elementi della coda a partire
              da quello specificato (compreso).
        @post Il puntatore alla coda punta ad una locazione di memoria ora
              non più valida.
    */
    void clear_helper(element *e) {
        if(e!= nullptr) {
            clear_helper(e->next);
            delete e;
            e = nullptr;
            _elementIn--;
        }
    }

public:
    // Metodi fondamentali della coda

    /**
        @brief Costruttore di default (METODO FONDAMENTALE)

        @description
        Costruttore di default per istanziare una coda vuota.
        I dati membro sono inizializzati tramite initialization list,
        per migliorare l'efficienza dell'inizializzazione.
        @note Questo è l'unico costruttore che può essere utilizzato
              per istanziare un eventuale array di code.
              Se non è specificato viene settata a 10
    */
    cbufferlist() : _head(nullptr), _tail(nullptr), _size(10), _elementIn(0) {} // initialization list

    /**
    @brief Costruttore secondario
            Costruttore secondario. Permette di istanziare un cbuffer con una data dimensione.
    @param size Dimensione del cbuffer da istanziare
    **/
    explicit cbufferlist(size_type size) : _head(nullptr), _tail(nullptr), _size(size), _elementIn(0) {}

    /**
        @brief Costruttore secondario
        Costruttore secondario. Permette di istanziare un cbuffer con una data dimensione
        e di inizializzare le celle dell'arrayptr con il valore dato
        @param other coda da copiare per istanziare quella corrente
        @param size grandezza del buffer
        @throw eccezione di allocazione di memoria
    **/
    cbufferlist(size_type size, const cbufferlist &other) : _size(0), _head(nullptr), _tail(nullptr), _elementIn(0) {
        _size = size;
        element *curr = other._head;
        try {
            while (curr != nullptr) {
                insert(curr->value);
                curr = curr->next;
            }
        }
        catch (...) { // eccezione di allocazione di memoria
            clear();
            throw;
        }
    }

    /**
     * copy costrctor
     * @param other
     */
    cbufferlist(const cbufferlist &other) :
            _head(nullptr), _tail(nullptr), _size(0), _elementIn(0) { // initialization list

        element *curr = other._head;
        _size=other._size;
        try {
            while(curr != nullptr) {
                insert(curr->value);
                curr = curr->next;
            }
        }
        catch(...) { // eccezione di allocazione di memoria
            clear();
            throw;
        }
    }

    /**
        @brief Operatore di assegnamento (METODO FONDAMENTALE)

        @description
        Operatore di assegnamento della coda, che permette la copia tra code.
        In caso di auto-assegnamento, l'operatore non compie alcuna operazione,
        restituendo semplicemente un riferimento alla coda corrente
        (che coincide con quella da copiare).
        @note Non è necessario gestire quest'eccezione direttamente all'interno
	          dell'operatore di assegnamento, poiché l'eventuale memoria
	          allocata dalla coda temporanea viene deallocata automaticamente
	          a fine scope, essendo un dato automatico istanziato nello stack.

		@param other coda come sorgente da copiare (operando di destra)

		@return riferimento alla coda corrente (this)
		@throw eccezione di allocazione di memoria
    */
    cbufferlist &operator=(const cbufferlist &other) {
        // Per evitare l'auto-assegnamento (self-assignment: this = this)
        if (this != &other) {
            cbufferlist tmp(other);
            std::swap(_head, tmp._head);
            std::swap(_tail, tmp._tail);
            std::swap(_size, tmp._size);
            std::swap(_elementIn, tmp._elementIn);
        }
        return *this;
    }

    /**
       @brief Costruttore secondario
       Costruttore secondario. Permette di istanziare un cbuffer su tipi T da un altro
       cbuffer che contiene tipi Q. La creazione è possibile solo se è possibile castare
       un tipo Q in un tipo T (il controllo lo fà il compilatore).
       @param pther cbuffer sorgente
   **/
    template<typename IterT>
    cbufferlist(IterT begin, IterT end):   _size(0), _head(nullptr), _tail(nullptr), _elementIn(0) {
        try {
            while (begin != end) {
                _size++;
                insert(static_cast<value_type>(*begin));
                ++begin;
            }
        }
        catch (...) {
            clear();
            throw;
        }
    }

    /**
        @brief Distruttore (METODO FONDAMENTALE)

        @description
        Distruttore della coda, che dealloca la memoria allocata da unbuffer.
        @note In questo modo, la deallocazione della memoria allocata
          da una coda comporta anche la deallocazione della memoria allocata
          da tutti i suoi elementi. Pertanto, non può esistere un elemento
          che non sia presente all'interno di una coda.
        @note Il distruttore è definito virtual, in modo da rendere polimorfo
          il metodo e, quindi, anche la classe (in caso di eventuale
          ereditarietà).
    @post La memoria allocata da tutti gli elementi della coda
          viene deallocata.
    @post Le locazioni di memoria allocate in precedenza dalla coda
          e da tutti i suoi elementi ora non sono più valide.
    */
    virtual ~cbufferlist() {
        clear();
    }

/**
    @brief Numero di elementi inseriti nella coda
    @description
    Metodo dell'interfaccia pubblica che restituisce la grandezza del buffer.
    Ciò avviene restituendo il valore dell'apposito dato membro _size.
    @return numero di elementi inseriti nella coda
*/
    size_type size() const {
        return _size;
    }

/**
       @brief Numero di elementi inseriti nella coda
       @description
       Metodo dell'interfaccia pubblica che restituisce quanti oggetti ci sono nel buffer.
       Ciò avviene restituendo il valore dell'apposito dato membro _elementIn.
       @return numero di elementi inseriti nella coda
   */
    size_type elementiIn() const {
        return _elementIn;
    }

/**
    @brief Inserimento di un singolo elemento nella coda

    @description
    Metodo dell'interfaccia pubblica che inserisce un singolo elemento
    nella coda.
    @note Non è necessario gestire quest'eccezione direttamente all'interno
          del metodo di inserimento, poiché, in caso di eccezione
          di allocazione di memoria per il nuovo elemento dinamico,
          questa non viene allocata.

    @param value valore dell'elemento da inserire nella coda
    @post Viene istanziato nell'heap un nuovo elemento dinamico,
          inizializzato con il valore passato come parametro.
    @post Il puntatore alla testa della coda viene eventualmente aggiornato,
          puntando al nuovo elemento.
    @post Il puntatore alla coda della coda viene aggiornato,
          puntando al nuovo elemento.
    @post Il numero di elementi inseriti nella coda viene incrementato
          di un'unità.
*/
    void insert(const value_type &value) {
            element *tmp = new element(value);
            if (_size > _elementIn) {
                if (_head == nullptr) {
                    _head = tmp;
                } else
                    _tail->next = tmp;
                _tail = tmp;
                _elementIn++;
            } else {
                element *temp = _head;
                _head = _head->next;
                delete temp;
                temp = nullptr;
                _tail->next = tmp;
                _tail = tmp;
            }
    }

/**
 @brief Rimozione dell'elemento più vecchio della coda
 @description
 Metodo dell'interfaccia pubblica che rimuove l'elemento più vecchio
 della coda (l'elemento in testa alla coda).
 @pre La coda non dev'essere vuota.
 @return valore dell'elemento rimosso
 @post Il secondo elemento più vecchio della coda diventa l'elemento
       in testa alla coda.
 @post La memoria allocata dall'elemento più vecchio della coda
       viene deallocata.
 @post Il numero di elementi inseriti nella coda viene decrementato
       di un'unità.
 @throw empty_queue_exception se la coda è vuota
*/
    value_type extract() {
        if (_size == 0)
            throw empty_buffer_exception("Impossibile rimuovere l'elemento piu' "
                                         "vecchio: la coda e' vuota.");
        value_type removed_value = _head->value;

        element *first = _head;
        _head = _head->next;
        _elementIn--;
        delete first;
        first = nullptr;

        return removed_value;
    }

/**
    @brief Accesso in lettura all'elemento più vecchio della coda
    @description
    Metodo dell'interfaccia pubblica che restituisce il valore dell'elemento
    più vecchio della coda
    @return valore dell'elemento più vecchio della coda
    @throw empty_queue_exception se la coda è vuota (non è presente
           un elemento più vecchio da leggere)
    @note L'eccezione dev'essere gestita adeguatamente nella funzione
          chiamante.
*/
    value_type &get_head() const {
        if (_elementIn == 0)
            throw empty_buffer_exception("Impossibile leggere l'elemento piu' "
                                         "vecchio: la coda e' vuota.");
        return _head->value;
    }

    value_type &get_tail() const {
        if (_elementIn == 0)
            throw empty_buffer_exception("Impossibile leggere l'elemento piu' "
                                         "recente: la coda e' vuota.");
        return _tail->value;
    }

/**
    @brief Esistenza nella coda di almeno un elemento di un certo valore
           dato
    @description
    Metodo dell'interfaccia pubblica che determina se la coda corrente
    contiene almeno un elemento di un certo valore dato, passato come
    parametro.
    @param value valore dell'elemento di cui determinare l'esistenza
           nella coda
    @return true se la coda contiene almeno un elemento del valore dato
    @return false altrimenti
*/
    bool contains(const value_type &value) const {
        element *curr = _head;

        while (curr != nullptr) {
            if (_equals(curr->value, value))
                return true;
            curr = curr->next;
        }

        return false;
    }

    value_type &operator[](size_type index) {
        if (index < _size) {
            element *curr = _head;
            while (index != 0) {
                curr=curr->next;
                index--;
            }
            return curr->value;
        } else
            throw empty_buffer_exception("Impossibile recuperare l'elemto"
                                         "l'indirizzo è maggiore di size");
    }


    /**
    @brief Rimozione dell'intero contenuto della coda
    @description
            Funzione privata che rimuove tutti gli elementi della coda.
    La rimozione viene effettuata ricorsivamente.
    @post La memoria allocata da tutti gli elementi della coda
    viene deallocata.
    */
    void clear() {
        clear_helper(_head);
        _tail = nullptr;
    }

    bool find(const value_type &value) const {
        element *curr = _head;

        while (curr != nullptr) {
            if (_equals(curr->value, value))
                return true;
            curr = curr->next;
        }
        return false;
    }
// Supporto agli iteratori della coda

    class const_iterator; // forward declaration dell'iteratore costante

    // Iteratore della coda in lettura e scrittura

    /**
		@brief Iteratore della coda in lettura e scrittura di tipo forward
	    @description
		Iteratore della coda in lettura e scrittura di tipo forward.
		Gli elementi sono ritornati seguendo la logica FIFO.
        La sovrascrittura di un elemento non ne cambia lanzianità.
	*/
    class iterator {

        // Dati membro privati dell'iteratore

        element *_e; ///< @brief Puntatore a un elemento della coda

    public:

        // Interfaccia pubblica dell'iteratore

        // Traits dell'iteratore

        typedef std::forward_iterator_tag iterator_category; ///< @brief
        ///< Categoria
        ///< dell'iteratore
        typedef T value_type; ///< @brief Tipo dei dati
        ///< puntati
        ///< dall'iteratore
        typedef ptrdiff_t difference_type; ///< @brief Tipo per
        ///< rappresentare la
        ///< differenza tra
        ///< due puntatori
        typedef T *pointer; ///< @brief Tipo di puntatore
        ///< ai dati puntati
        ///< dall'iteratore
        typedef T &reference; ///< @brief Tipo di
        ///< riferimento ai dati
        ///< puntati dall'iteratore

        // Metodi fondamentali dell'iteratore

        /**
			@brief Costruttore di default (METODO FONDAMENTALE)
            @description
			Costruttore di default per istanziare un iteratore che punta
            a nullptr.
		*/
        iterator() : _e(nullptr) {} // initialization list

        /**
			@brief Costruttore di copia/Copy Constructor (METODO FONDAMENTALE)
            @description
			Costruttore di copia/Copy Constructor dell'iteratore.
			Permette di istanziare un iteratore con i valori dei dati membro
            presi da un altro iteratore.
			@param other iteratore da copiare per istanziare quello corrente
		*/
        iterator(const iterator &other) : _e(other._e) {} // initialization list

        /**
			@brief Operatore di assegnamento (METODO FONDAMENTALE)
            @description
			Operatore di assegnamento dell'iteratore.
			Permette la copia tra iteratori.
			@param other iteratore come sorgente da copiare (operando di destra)
			@return riferimento all'iteratore corrente
		*/
        iterator &operator=(const iterator &other) {
            _e = other._e;
            return *this;
        }

        /**
			@brief Distruttore (METODO FONDAMENTALE)
            @description
			Distruttore dell'iteratore.
			Dealloca la memoria allocata da un iteratore e dai suoi dati membro.
		*/
        ~iterator() {}

        // Fine metodi fondamentali dell'iteratore

        // Ulteriori metodi dell'interfaccia pubblica dell'iteratore

        /**
			@brief Operatore di dereferenziamento
            @description
			Operatore di dereferenziamento dell'iteratore.
            Permette l'accesso in lettura e scrittura al valore dell'elemento
            puntato dall'iteratore.
			@return valore dell'elemento puntato dall'iteratore
		*/
        reference operator*() const {
            return _e->value;
        }

        /**
			@brief Operatore di accesso ai dati tramite puntatore
            @description
			Operatore di accesso, tramite puntatore, ai dati puntati
            dall'iteratore.
            Permette l'accesso in lettura e scrittura, tramite puntatore,
            al valore dell'elemento puntato dall'iteratore.
			@return puntatore al valore dell'elemento puntato dall'iteratore
		*/
        pointer operator->() const {
            return &(_e->value);
        }

        /**
			@brief Operatore di iterazione pre-incremento
            @description
			Operatore di iterazione pre-incremento dell'iteratore.
            Permette di incrementare l'iteratore di un'unità, puntando
            all'elemento successivo, e di utilizzarlo allo stato successivo
            all'incremento.
            @pre L'iteratore deve puntare ad una locazione di memoria interna
                 alla coda.
			@return riferimento all'iteratore corrente incrementato
            @throw queue_iterator_out_of_bounds_exception se l'iteratore,
                   incrementando di un'unità, punta ad una locazione di memoria
                   esterna alla coda
		*/
        iterator &operator++() {
            if (_e == nullptr)
                throw buffer_iterator_out_of_bounds_exception("Impossibile "
                                                              "incrementare "
                                                              "l'iteratore: "
                                                              "locazione di "
                                                              "memoria esterna "
                                                              "al buffer.");
            _e = _e->next;
            return *this;
        }

        /**
			@brief Operatore di iterazione post-incremento
            @description
			Operatore di iterazione post-incremento dell'iteratore.
            Permette di incrementare l'iteratore di un'unità, puntando
            all'elemento successivo, e di utilizzarlo allo stato precedente
            all'incremento.
            @pre L'iteratore deve puntare ad una locazione di memoria interna
                 al buffer.
            @param int place parameter per distinguere l'operatore di iterazione
                   post-incremento da quello di pre-incremento
			@return copia dell'iteratore corrente prima di essere incrementato
            @throw queue_iterator_out_of_bounds_exception se l'iteratore,
                   incrementando di un'unità, punta ad una locazione di memoria
                   esterna al buffer
		*/
        iterator operator++(int) {
            if (_e == nullptr)
                throw buffer_iterator_out_of_bounds_exception("Impossibile "
                                                              "incrementare "
                                                              "l'iteratore: "
                                                              "locazione di "
                                                              "memoria esterna "
                                                              "al buffer.");
            iterator tmp(*this);
            _e = _e->next;
            return tmp;
        }

        /**
			@brief Operatore di uguaglianza
            @description
			Operatore di uguaglianza dell'iteratore.
            Permette di confrontare due iteratori, verificando se sono uguali.
            @note Due iteratori sono definiti "uguali" se puntano allo stesso
                  elemento della coda.
			@param other iteratore da confrontare con quello corrente
			@return true se i due iteratori puntano allo stesso elemento
                    della coda
            @return false altrimenti
		*/
        bool operator==(const iterator &other) const {
            return (_e == other._e);
        }

        /**
			@brief Operatore di diversità
            @description
			Operatore di diversità dell'iteratore.
            Permette di confrontare due iteratori, verificando se sono diversi.
            @note Due iteratori sono definiti "diversi" se non puntano
                  allo stesso elemento della coda.
			@param other iteratore da confrontare con quello corrente
			@return true se i due iteratori non puntano allo stesso elemento
                    della coda
            @return false altrimenti
		*/
        bool operator!=(const iterator &other) const {
            return (_e != other._e);
        }

        /*
           Dati e metodi dell'interfaccia pubblica dell'iteratore
           per la compatibilità tra iteratori in lettura e scrittura
           e iteratori costanti
        */

        friend class const_iterator; // per dare accesso ai dati privati
        // dell'iteratore da parte dell'iteratore
        // costante

        /**
			@brief Operatore di uguaglianza tra un iteratore in lettura
                   e scrittura e un iteratore costante
            @description
			Operatore di uguaglianza dell'iteratore in lettura e scrittura
            per confrontarlo con un iteratore costante.
            Permette di confrontare un iteratore in lettura e scrittura
            (operando di sinistra) con un iteratore costante
            (operando di destra), verificando se sono uguali.
            @note Due iteratori di tipi diversi (uno in lettura e scrittura
                  e uno costante) sono definiti "uguali" se puntano allo stesso
                  elemento della coda.
			@param other iteratore costante da confrontare con l'iteratore
                   in lettura e scrittura corrente
			@return true se i due iteratori puntano allo stesso elemento
                    della coda
            @return false altrimenti
		*/
        bool operator==(const const_iterator &other) const {
            return (_e == other._e);
        }

        /**
			@brief Operatore di diversità tra un iteratore in lettura
                   e scrittura e un iteratore costante
			@description
            Operatore di diversità dell'iteratore in lettura e scrittura
            per confrontarlo con un iteratore costante.
            Permette di confrontare un iteratore in lettura e scrittura
            (operando di sinistra) con un iteratore costante
            (operando di destra), verificando se sono diversi.
            @note Due iteratori di tipi diversi (uno in lettura e scrittura
                  e uno costante) sono definiti "diversi" se non puntano
                  allo stesso elemento della coda.
			@param other iteratore costante da confrontare con l'iteratore
                   in lettura e scrittura corrente
			@return true se i due iteratori non puntano allo stesso elemento
                    della coda
            @return false altrimenti
		*/
        bool operator!=(const const_iterator &other) const {
            return (_e != other._e);
        }

    private:

        // Ulteriori dati membro privati dell'iteratore

        friend class cbufferlist; // per permettere alla classe container (queue)
        // di utilizzare il costruttore privato
        // di inizializzazione

        // Metodi privati dell'iteratore

        /**
			@brief Costruttore privato
			@description
            Costruttore privato di inizializzazione dell'iteratore.
            Permette di istanziare un iteratore, inizializzandolo con
            il puntatore a un elemento della coda.
            @note Questo costruttore è definito explicit per evitare che venga
		          utilizzato dal compilatore per effettuare conversioni di tipo
		          implicite da puntatore a elemento a iteratore.
            @note Questo costruttore è utilizzato dalla classe container (queue)
                  nelle funzioni membro che permettono di utilizzare
                  gli iteratori: begin() ed end().
			@param e puntatore a un elemento della coda
		*/
        explicit iterator(element *e) : _e(e) {} // initialization list

    }; // class iterator

    // Funzioni membro per l'utilizzo degli iteratori in lettura e scrittura

    /**
		@brief Iteratore che punta all'inizio della coda
        @description
		Funzione membro che restituisce un iteratore che punta all'inizio
        della coda (all'elemento in testa).
		@return iteratore che punta all'inizio della coda
	*/
    iterator begin() {
        return iterator(_head);
    }

    /**
		@brief Iteratore che punta alla fine della coda
        @description
		Funzione membro che restituisce un iteratore che punta alla fine
        della coda.
		@return iteratore che punta alla fine della coda
	*/
    iterator end() {
        return iterator(nullptr);
    }

    // Iteratore costante della coda

    /**
		@brief Iteratore costante della coda di tipo forward
	    @description
		Iteratore costante (in sola lettura) della coda di tipo forward.
		Gli elementi sono ritornati seguendo la logica FIFO.
	*/
    class const_iterator {

        // Dati membro privati dell'iteratore costante

        const element *_e; ///< @brief Puntatore a un elemento costante
        ///< della coda

    public:

        // Interfaccia pubblica dell'iteratore costante

        // Traits dell'iteratore costante

        typedef std::forward_iterator_tag iterator_category; ///< @brief
        ///< Categoria
        ///< dell'iteratore
        ///< costante
        typedef const T value_type; ///< @brief Tipo dei dati
        ///< puntati
        ///< dall'iteratore
        ///< costante
        typedef ptrdiff_t difference_type; ///< @brief Tipo per
        ///< rappresentare la
        ///< differenza tra
        ///< due puntatori
        typedef const T *pointer; ///< @brief Tipo di puntatore
        ///< ai dati puntati
        ///< dall'iteratore costante
        typedef const T &reference; ///< @brief Tipo di
        ///< riferimento ai dati
        ///< puntati dall'iteratore
        ///< costante

        // Metodi fondamentali dell'iteratore costante

        /**
			@brief Costruttore di default (METODO FONDAMENTALE)
            @description
			Costruttore di default per istanziare un iteratore costante
            che punta a nullptr.
		*/
        const_iterator() : _e(nullptr) {} // initialization list

        /**
			@brief Costruttore di copia/Copy Constructor (METODO FONDAMENTALE)
            @description
			Costruttore di copia/Copy Constructor dell'iteratore costante.
			Permette di istanziare un iteratore costante con i valori dei dati
            membro presi da un altro iteratore costante.
			@param other iteratore costante da copiare per istanziare quello
                   corrente
		*/
        const_iterator(const const_iterator &other) :
                _e(other._e) {} // initialization list

        /**
			@brief Operatore di assegnamento (METODO FONDAMENTALE)
            @description
			Operatore di assegnamento dell'iteratore costante.
			Permette la copia tra iteratori costanti.
			@param other iteratore costante come sorgente da copiare
                   (operando di destra)
			@return riferimento all'iteratore costante corrente
		*/
        const_iterator &operator=(const const_iterator &other) {
            _e = other._e;
            return *this;
        }

        /**
			@brief Distruttore (METODO FONDAMENTALE)
            @description
			Distruttore dell'iteratore costante.
			Dealloca la memoria allocata da un iteratore costante e dai suoi
            dati membro.
		*/
        ~const_iterator() {}

        // Fine metodi fondamentali dell'iteratore costante

        // Ulteriori metodi dell'interfaccia pubblica dell'iteratore costante

        /**
			@brief Operatore di dereferenziamento
            @description
			Operatore di dereferenziamento dell'iteratore costante.
            Permette l'accesso in sola lettura al valore costante dell'elemento
            puntato dall'iteratore costante.
			@return valore costante dell'elemento puntato dall'iteratore
                    costante
		*/
        reference operator*() const {
            return _e->value;
        }

        /**
            @brief Operatore di accesso ai dati tramite puntatore
            @description
			Operatore di accesso, tramite puntatore, ai dati puntati
            dall'iteratore costante.
            Permette l'accesso in sola lettura, tramite puntatore, al valore
            costante dell'elemento puntato dall'iteratore costante.
			@return puntatore al valore costante dell'elemento puntato
                    dall'iteratore costante
		*/
        pointer operator->() const {
            return &(_e->value);
        }

        /**
			@brief Operatore di iterazione pre-incremento
            @description
			Operatore di iterazione pre-incremento dell'iteratore costante.
            Permette di incrementare l'iteratore costante di un'unità, puntando
            all'elemento successivo, e di utilizzarlo allo stato successivo
            all'incremento.
            @pre L'iteratore costante deve puntare ad una locazione di memoria
                 interna alla coda.
			@return riferimento all'iteratore costante corrente incrementato
            @throw queue_iterator_out_of_bounds_exception se l'iteratore
                   costante, incrementando di un'unità, punta ad una locazione
                   di memoria esterna alla coda
		*/
        const_iterator &operator++() {
            if (_e == nullptr)
                throw buffer_iterator_out_of_bounds_exception("Impossibile "
                                                              "incrementare "
                                                              "l'iteratore "
                                                              "costante: "
                                                              "locazione di "
                                                              "memoria esterna "
                                                              "al buffer.");
            _e = _e->next;
            return *this;
        }

        /**
			@brief Operatore di iterazione post-incremento
            @description
			Operatore di iterazione post-incremento dell'iteratore costante.
            Permette di incrementare l'iteratore costante di un'unità, puntando
            all'elemento successivo, e di utilizzarlo allo stato precedente
            all'incremento.
            @pre L'iteratore costante deve puntare ad una locazione di memoria
                 interna alla coda.
			@param int place parameter per distinguere l'operatore di iterazione
                   post-incremento da quello di pre-incremento
			@return copia dell'iteratore costante corrente prima di essere
                    incrementato
            @throw queue_iterator_out_of_bounds_exception se l'iteratore
                   costante, incrementando di un'unità, punta ad una locazione
                   di memoria esterna alla coda
		*/
        const_iterator operator++(int) {
            if (_e == nullptr)
                throw buffer_iterator_out_of_bounds_exception("Impossibile "
                                                              "incrementare "
                                                              "l'iteratore "
                                                              "costante: "
                                                              "locazione di "
                                                              "memoria esterna "
                                                              "al buffer.");
            const_iterator tmp(*this);
            _e = _e->next;
            return tmp;
        }

        /**
			@brief Operatore di uguaglianza
            @description
			Operatore di uguaglianza dell'iteratore costante.
            Permette di confrontare due iteratori costanti, verificando se sono
            uguali.
            @note Due iteratori costanti sono definiti "uguali" se puntano
                  allo stesso elemento della coda.
			@param other iteratore costante da confrontare con quello corrente
			@return true se i due iteratori costanti puntano allo stesso
                    elemento della coda
            @return false altrimenti
		*/
        bool operator==(const const_iterator &other) const {
            return (_e == other._e);
        }

        /**
			@brief Operatore di diversità
            @description
			Operatore di diversità dell'iteratore costante.
            Permette di confrontare due iteratori costanti, verificando se sono
            diversi.
            @note Due iteratori costanti sono definiti "diversi" se non puntano
                  allo stesso elemento della coda.
			@param other iteratore costante da confrontare con quello corrente
			@return true se i due iteratori costanti non puntano allo stesso
                    elemento della coda
            @return false altrimenti
		*/
        bool operator!=(const const_iterator &other) const {
            return (_e != other._e);
        }

        /*
           Dati e metodi dell'interfaccia pubblica dell'iteratore costante
           per la compatibilità tra iteratori costanti e iteratori
           in lettura e scrittura
        */

        friend class iterator; // per dare accesso ai dati privati
        // dell'iteratore costante da parte
        // dell'iteratore in lettura e scrittura

        /**
			@brief Operatore di uguaglianza tra un iteratore costante
                   e un iteratore in lettura e scrittura
            @description
			Operatore di uguaglianza dell'iteratore costante per confrontarlo
            con un iteratore in lettura e scrittura.
            Permette di confrontare un iteratore costante (operando di sinistra)
            con un iteratore in lettura e scrittura (operando di destra),
            verificando se sono uguali.
            @note Due iteratori di tipi diversi (uno costante e uno in lettura
                  e scrittura) sono definiti "uguali" se puntano allo stesso
                  elemento della coda.
			@param other iteratore in lettura e scrittura da confrontare
                   con l'iteratore costante corrente
			@return true se i due iteratori puntano allo stesso elemento
                    della coda
            @return false altrimenti
		*/
        bool operator==(const iterator &other) const {
            return (_e == other._e);
        }

        /**
			@brief Operatore di diversità tra un iteratore costante
                   e un iteratore in lettura e scrittura
            @description
			Operatore di diversità dell'iteratore costante per confrontarlo
            con un iteratore in lettura e scrittura.
            Permette di confrontare un iteratore costante (operando di sinistra)
            con un iteratore in lettura e scrittura (operando di destra),
            verificando se sono diversi.
            @note Due iteratori di tipi diversi (uno costante e uno in lettura
                  e scrittura) sono definiti "diversi" se non puntano
                  allo stesso elemento della coda.
			@param other iteratore in lettura e scrittura da confrontare
                   con l'iteratore costante corrente
			@return true se i due iteratori non puntano allo stesso elemento
                    della coda
            @return false altrimenti
		*/
        bool operator!=(const iterator &other) const {
            return (_e != other._e);
        }

        /**
			@brief Costruttore di conversione da iteratore in lettura e
                   scrittura a iteratore costante
            @description
			Costruttore dell'iteratore costante di conversione da iteratore
            in lettura e scrittura a iteratore costante.
			Permette di convertire un iteratore in lettura e scrittura
            in un iteratore costante, istanziando quest'ultimo con i valori
            dei dati membro presi da un iteratore in lettura e scrittura.
			@param other iteratore in lettura e scrittura da copiare e
                   convertire per istanziare l'iteratore costante corrente
		*/
        const_iterator(const iterator &other) :
                _e(other._e) {} // initialization list

        /**
			@brief Operatore di assegnamento di un iteratore in lettura
                   e scrittura a un iteratore costante
            @description
			Operatore dell'iteratore costante di assegnamento di un iteratore
            in lettura e scrittura a un iteratore costante.
			Permette la copia da un iteratore in lettura e scrittura
            a un iteratore costante.
			@param other iteratore in lettura e scrittura come sorgente
                   da copiare (operando di destra)
			@return riferimento all'iteratore costante corrente
		*/
        const_iterator &operator=(const iterator &other) {
            _e = other._e;
            return *this;
        }

    private:

        // Ulteriori dati membro privati dell'iteratore costante

        friend class cbufferlist; // per permettere alla classe container (queue)
        // di utilizzare il costruttore privato
        // di inizializzazione

        // Metodi privati dell'iteratore costante

        /**
			@brief Costruttore privato
			@description
            Costruttore privato di inizializzazione dell'iteratore costante.
            Permette di istanziare un iteratore costante, inizializzandolo con
            il puntatore a un elemento costante della coda.
            @note Questo costruttore è definito explicit per evitare che venga
		          utilizzato dal compilatore per effettuare conversioni di tipo
		          implicite da puntatore a elemento costante a iteratore
		          costante.
            @note Questo costruttore è utilizzato dalla classe container (queue)
                  nelle funzioni membro che permettono di utilizzare
                  gli iteratori costanti: begin() e end().
			@param e puntatore a un elemento costante della coda
		*/
        explicit const_iterator(const element *e) :
                _e(e) {} // initialization list

    }; // class const_iterator

    // Funzioni membro per l'utilizzo degli iteratori costanti

    /**
		@brief Iteratore costante che punta all'inizio della coda
        @description
		Funzione membro che restituisce un iteratore costante che punta
        all'inizio della coda (all'elemento in testa).
		@return iteratore costante che punta all'inizio della coda
	*/
    const_iterator begin() const {
        return const_iterator(_head);
    }

    /**
		@brief Iteratore costante che punta alla fine della coda
        @description
		Funzione membro che restituisce un iteratore costante che punta
        alla fine della coda.
		@return iteratore costante che punta alla fine della coda
	*/
    const_iterator end() const {
        return const_iterator(nullptr);
    }

};

/*operatore di stream*/
template<typename T, typename Q>
std::ostream &operator<<(std::ostream &os, const cbufferlist<T, Q> &cbl) {
    typename cbufferlist<T, Q>::const_iterator iin, ifin;
    for (iin = cbl.begin(), ifin = cbl.end(); iin != ifin; iin++) {
        os << *iin;
        os << " ";
    }
    return os;
}

#endif //CBUFFERLIST_CBUFFERLIST_H
