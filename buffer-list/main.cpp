#include <iostream>
#include <cassert>
#include "cbufferlist.h"

/**
 * versione da presenrtare e funzionante
 */
struct equalInt {
    bool operator()(int a, int b) const {
        return a == b;
    }
};

struct equalString {
    bool operator()(const std::string &a, const std::string &b) const {
        return a.compare(b) == 0;
    }
};

struct complex {
    int real;
    int imaginary;

    complex(int re, int im) :
            real(re), imaginary(im) {} // initialization list
};

std::ostream &operator<<(std::ostream &os, const complex &c) {
    std::cout << "(" << c.real << ", " << c.imaginary << ")";
    return os;
}

struct equal_complex {
    bool operator()(const complex &c1, const complex &c2) const {
        return (c1.real == c2.real) && (c1.imaginary == c2.imaginary);
    }
};

typedef cbufferlist<int, equalInt> cbfl;


struct equalBufferInt{
    bool operator()(const cbfl &cbuff1, const cbfl &cbuff2){
        return (cbuff1.size() == cbuff2.size());
    }
};

void fondamentalTest() {

    std::cout << "creazione di un buffer con valori di default (size 10) e popolameto" << std::endl;
    cbfl buffer1;
    buffer1.insert(99);
    buffer1.insert(58);
    buffer1.insert(21);
    buffer1.insert(28);
    buffer1.insert(56);
    buffer1.insert(23);
    buffer1.insert(90);
    buffer1.insert(2);
    buffer1.insert(3);
    buffer1.insert(1);

    std::cout << "stampa cbufferlist dopo iserimenti" << std::endl
              << buffer1 << std::endl;

    std::cout << "copy costructor" << std::endl;
    cbfl buffer2(buffer1);
    std::cout << "stampa buffer2" << std::endl
              << buffer2 << std::endl;

    std::cout << "operatore di asseganmento" << std::endl;
    cbfl buffer3;
    buffer3 = buffer1;
    std::cout << "stampa buffer3" << std::endl
              << buffer3 << std::endl;
    std::cout << "size buffer3" << std::endl
              << buffer3.size() << std::endl;
    std::cout << "numero elementi in buffer3" << std::endl
              << buffer3.elementiIn() << std::endl;

    std::cout << "creazione di un buffer con una size predecisa" << std::endl;
    cbfl buffer7(4);
    buffer7.insert(1);
    buffer7.insert(2);
    buffer7.insert(3);
    buffer7.insert(4);
}

void useCbufferlistInt() {
    std::cout<<"******** Test su creazione di un buffer di interi ********"<<std::endl;
    int array[5] = {3, 2, 30, 4, 76};
    cbfl cbf(array, array + 5);

    std::cout << "stampa di cbf costruito con gli iteratori"
              << std::endl << cbf << std::endl;

    std::cout << "size di cbf: " << cbf.size() << std::endl;
    assert(cbf.size() == 5);
    assert(cbf.get_head() == 3);
}

void test_cbufferlist_Int(cbfl &other) {
    std::cout<<"******** Test su un buffer di interi ********"<<std::endl;
    std::cout << "popolamento di un cbuffer di interi"<< std::endl;
    std::cout<<"Insertimento dei valori 1, 2, 3, 4, 5"<<std::endl;
    other.insert(5);
    assert(other.get_head()==5);
    other.insert(6);
    other.insert(7);
    other.insert(8);
    other.insert(9);
    std::cout<<"size cbuffer: "<< other.size() <<std::endl;
    std::cout<<"elementi dentro cbuffer: "<< other.elementiIn() <<std::endl;

    std::cout << "sovraccarico di cbuffer"<< std::endl;
    assert(other.get_head()==5);
    other.insert(90);
    assert(other.get_tail()==90);

    std::cout<<"Stampa con operator<<"<<std::endl;
    std::cout<<other<<std::endl;

    std::cout<<"Dimensione della lista: "<<other.size()<<std::endl;

    std::cout<<"Stampa con iteratori"<<std::endl;

    cbfl::const_iterator i,ie;

    for(i=other.begin(),ie=other.end(); i!=ie; ++i)
        std::cout<<*i<<std::endl;

    std::cout<<"test extract e size"<<std::endl;
    assert(other.extract()==6);
    assert(other.size()==5);
    std::cout<<other.size()<<std::endl;

    int value=other[3];
    std::cout << "ricerca con operatore[]"<< std::endl;
    std::cout<<value<<std::endl;
}

void test_const_list_int(const cbfl &other) {
    std::cout<<"******** Test su un buffer costante di interi ********"<<std::endl;

    // add non e' chiamabile su un oggetto const

    std::cout<<"Stampa con operator<<"<<std::endl;
    std::cout<<other<<std::endl;

    std::cout<<"Dimensione della lista: "<<other.size()<<std::endl;

    std::cout<<"Stampa con iteratori"<<std::endl;

    cbfl ::const_iterator i,ie;

    for(i=other.begin(),ie=other.end(); i!=ie; ++i)
        std::cout<<*i<<std::endl;

    // clear non e' chiamabile su un oggetto const
}

void  test_buffer_stinghe(){
    std::cout << "***** Test su stringhe *****" << std::endl;

    cbufferlist<std::string, equalString> cbffstr(5);
    cbffstr.insert("gino");
    cbffstr.insert("pippo");
    cbffstr.insert("cipp");
    cbffstr.insert("jhonny");
    cbffstr.insert("value");

    std::cout<<"Stampa con operator<<"<<std::endl;
    std::cout<<cbffstr<<std::endl;

    std::cout<<"Dimensione della lista: "<<cbffstr.size()<<std::endl;

    std::cout<<"Ricerca di 'cip': "<< cbffstr.find("cip")<<std::endl;
    std::cout<<"Ricerca di 'cipp': "<< cbffstr.find("cipp")<<std::endl;

    std::cout << "ricerca con operatore[]"<< std::endl;
    std::cout<<cbffstr[3]<<std::endl;

    std::string com = "ciao";
    cbffstr[3] = com;
    std::cout << "modifica con operatore[]"<< std::endl;
    std::cout<<cbffstr[3]<<std::endl;


}

void test_buffer_complex(){
    cbufferlist<complex, equal_complex> cbcx(5);
    cbcx.insert(complex(1,5));
    cbcx.insert(complex(2,6));
    cbcx.insert(complex(43,90));
    cbcx.insert(complex(21,12));
    cbcx.insert(complex(1,0));

    std::cout<<"Stampa con operator<<"<<std::endl;
    std::cout<<cbcx<<std::endl;

    std::cout<<"Dimensione della lista: "<<cbcx.size()<<std::endl;

    std::cout<<"Stampa con iteratori"<<std::endl;

    cbufferlist<complex, equal_complex>:: const_iterator i,ie;

    for(i=cbcx.begin(),ie=cbcx.end(); i!=ie; ++i)
        std::cout<<*i<<std::endl;

    std::cout<<"Ricerca di '(1,5)': "<<cbcx.find(complex(1,5))<<std::endl;
    std::cout<<"Ricerca di '(2,2)': "<<cbcx.find(complex(2,2))<<std::endl;

    cbcx.insert(complex(4,5));
    std::cout<<"Ricerca di '(1,5)' dopo sovrascrittura: "<<cbcx.find(complex(1,5))<<std::endl;
    std::cout<<"Ricerca di '(4,5)'dopo sovrascrittura: "<<cbcx.find(complex(4,5))<<std::endl;

    complex c = cbcx.extract();
    std::cout << c << std::endl;
    std::cout<<"Ricerca di '(2,6)'estrazione: "<<cbcx.find(complex(2,6))<<std::endl;

    std::cout << "ricerca con operatore[]"<< std::endl;
    std::cout<<cbcx[3]<<std::endl;

    complex com(2,3);
    cbcx[3] = com;
    std::cout << "modifica con operatore[]"<< std::endl;
    std::cout<<cbcx[3]<<std::endl;

}

void test_buffer_int_buffer(){
    cbufferlist<cbfl, equalBufferInt> cbffcbffint(2);
    cbfl buff1(2);
    buff1.insert(1);
    buff1.insert(2);
    cbfl buff2(3);
    buff2.insert(4);
    buff2.insert(5);
    buff2.insert(5);
    cbffcbffint.insert(buff1);
    cbffcbffint.insert(buff2);

    std::cout<<"Stampa con operator<<"<<std::endl;
    std::cout<<cbffcbffint<<std::endl;

    std::cout<<"Dimensione della lista: "<<cbffcbffint.size()<<std::endl;

    std::cout<<"Stampa con iteratori"<<std::endl;

    cbufferlist<cbfl, equalBufferInt>:: const_iterator i,ie;

    for(i=cbffcbffint.begin(),ie=cbffcbffint.end(); i!=ie; ++i)
        std::cout<<*i<<std::endl;

    std::cout << "ricerca con operatore[]"<< std::endl;
    std::cout<<cbffcbffint[1]<<std::endl;

    cbfl com (4);
    com.insert(1);
    com.insert(2);
    com.insert(4);
    com.insert(5);
    cbffcbffint[1] = com;
    std::cout << "modifica con operatore[]"<< std::endl;
    std::cout<<cbffcbffint[1]<<std::endl;

}

int main() {
    fondamentalTest();
    useCbufferlistInt();
    cbfl buff1(5);
    test_cbufferlist_Int(buff1);
    test_const_list_int(buff1);
    test_buffer_stinghe();
    test_buffer_complex();
    test_buffer_int_buffer();
    return 0;
}

