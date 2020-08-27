# cbuffer
Una librearia che implementa un buffer circolare finito.
Il buffer ha una capacità fissa, decisa a costruzione. L'inserimento accoda gli
elementi finché il buffer non raggiunge la capacità massima. Una volta
riempito, i nuovi dati vengono scritti partendo dall'inizio del buffer e
sovrascrivendo i vecchi.
La classe, oltre ai metodi di uso comune (metodi fondamentali, capacità,
numero elementi inseriti, etc), deve permettere:
1) la costruzione di un cbuffer anche a partire da una sequenza di dati
generici Q identificata da una coppia di iteratori generici. Questo
costruttore prende in input: la dimensione del buffer, l’iteratore di inizio
sequenza, l’iteratore di fine sequenza. Lasciate al compilatore la gestione
della conversione di dati tra Q e T.
2) l’inserimento di un nuovo elemento in coda al buffer
3) la cancellazione dell’elemento attualmente in testa al buffer
4) l’accesso in lettura e scrittura dell'elemento i-esimo tramite operatore []
5) il supporto agli iteratori in lettura e scrittura
L'inizio del buffer circolare (begin) coincide con l'elemento “più vecchio” che è
stato inserito. Eventuali modifiche agli elementi non cambiano la loro “età di
inserimento”. Tutti i metodi di accesso (operatori, iteratori, etc.) devono tenere
in considerazione questa convenzione:
cbuffer[0] è l'elemento più vecchio
cbuffer.begin() è l'iteratore all'elemento più vecchio
Testale la classe sia su tipi primitivi che su tipi custom e con diversi predicati P.
