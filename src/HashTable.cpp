//
//  HashTable.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include "HashTable.h"
#include <string>
#include <iostream>

using namespace std;

// Variável pra registrarmos que uma posição foi deletada
// Fazemos um cast de (-1) para um ponteiro para HashEntry,
// ou seja, fazemos apontar para uma região inválida
HashEntry<std::string, std::string> *ENTRY_DELETED = (HashEntry<std::string,std::string>*)(-1);

/**
 Construtor que usa tamanho default da tabela.
 */
HashTable::HashTable()
{
    this->size = TABLE_SIZE;
    init();
}

/**
 Construtor que recebe tamanho como parâmetro.
 */
HashTable::HashTable(const int size)
{
    this->size = size;
    init();
}

/**
 Método auxiliar que é chamado pelos dois construtores.
 Este método quem de fato inicia o array interno da tabela.
 */
void HashTable::init()
{
    this->data = new HashEntry<std::string, string>*[this->size];
    this->quantity = 0;
    for( int i = 0; i < this->getSize(); i++ )
    {
        // Atribui-se nulo às posições da tabela para termos certeza de que estão vazias
        // O cast na atribuição é só pra ficar explícito o tipo de cada elemento do array
        this->data[i] = (HashEntry<string, string>*) nullptr;
    }
}

/**
 Destroi todas as entradas da tabela e a própria tabela.
 */
HashTable::~HashTable()
{
    for( int i = 0; i < this->getSize(); i++ )
    {
        HashEntry<string, string>* entry = this->data[i];
        
        if( entry != nullptr && entry != ENTRY_DELETED )
        {
            delete entry;
        }
    }
    delete [] data;
}

/**
 Este método deve retornar o 'value' da HashEntry cuja atributo 'key' == parâmetro key.
 Caso contrário, deve retornar string vazia ("").
 Quantidade de itens na tabela não é modificada.
 */
string HashTable::get(const string key)
{
    unsigned long i = this->hash(key);
    long d = 1;
    while(this->data[i] != nullptr && d < this->size){
        if(this->data[i] == ENTRY_DELETED){
            // pular as entradas removidas para evitar erro na chamada do if
        }else if(this->data[i]->getKey() == key){
            return this->data[i]->getValue();
        };
        i = (this->hash(key) + d++) % this->size;
    };
    return "";
}

/**
 Este método deve inserir na tabela um novo HashEntry com 'key' e 'value' recebidos como parâmetros. Neste caso, a quantidade de itens na tabela deve ser incrementada e retorna-se 'true'.
 Caso já exista um HashEntry com atributo 'key' == parâmetro 'key', deve apenas atualizar o atributo 'value' do HashEntry. Neste caso, a quantidade de itens na tabela não é modificada e retorna-se 'true'.
 */
bool HashTable::put(const string key, const string value)
{
    if(this->isFull()){
        cout << "Esta cheio! Nao eh possivel adicionar nada." << endl;
        return false;
    };
    unsigned long i = this->hash(key);
    long d = 1;
    long wasRemoved = -1;
    while(this->data[i] != nullptr && d < this->size){
        if(wasRemoved == -1 && this->data[i] == ENTRY_DELETED){
            wasRemoved = i;
        }else if(this->data[i]->getKey() == key){
            this->data[i]->setValue(value);
            return true;
        };
        i = (this->hash(key) + d++) % this->size;
    };
    if(wasRemoved != -1){
        d = (d >= this->size ? this->size-1 : d); // verificar caso o vetor não tenha entradas nulas, mas tenha entradas removidas
        i = wasRemoved;
    };
    if(d < this->size){
        HashEntry<std::string, std::string> *newEntry = new HashEntry<std::string,std::string>(key, value);
        this->data[i] = newEntry;
        this->quantity++;
        return true;
    };
    return false;
}

/**
 Este método deve remover da tabela o HashEntry cujo atributo 'key' == parâmetro 'key'. Neste caso, a quantidade de itens na tabela deve ser dencrementada e retorna-se 'true'.
 Caso não exista um HashEntry com atributo 'key' == parâmetro 'key',a quantidade de itens na tabela não é modificada e retorna-se 'false'.
 */
bool HashTable::remove(const string key)
{
    unsigned long i = this->hash(key);
    long d = 1;
    while(this->data[i] != nullptr && d < this->size){
        if(this->data[i] == ENTRY_DELETED){
            // pular as entradas removidas para evitar erro na chamada do if
        }else if(this->data[i]->getKey() == key){
            this->data[i] = ENTRY_DELETED;
            this->quantity--;
            return true;
        };
        i = (this->hash(key) + d++) % this->size;
    };
    return false;
}

/**
 Este método calcular um valor numérico para a string 'key'.
 */
unsigned long HashTable::preHash(const string key)
{
    unsigned long x = 0;
    for(unsigned int i = 0; i < key.size(); i++)
    {
        // Não mudar!
        // Coloquei propositalmente uma versão simples pra facilitar a criação de colisões nos testes!
        x += key.at(i);
    }
    return x;
}

/**
 Este método calcular o hash para a string 'key'.
 */
unsigned long HashTable::hash(const string key)
{
    unsigned long hashValue = this->preHash(key);
    return hashValue % this->getSize();
}

/**
 Método que imprime o conteúdo da tabela. Use para ajudar a depurar o programa.
 */
void HashTable::print()
{
    for(int i = 0; i < this->getSize(); i++)
    {
        HashEntry<string, string> * entry = data[i];
        if( entry == ENTRY_DELETED )
        {
            std::cout << i << ": DELETED" << std::endl;
        }
        else if( entry != nullptr )
        {
            std::cout << i << ": " << entry->getKey() << ":" << entry->getValue() << std::endl;
        }
        else
        {
            std::cout << i << ": []" << std::endl;
        }
    }
}

int HashTable::getSize()
{
    return this->size;
}

int HashTable::getQuantity()
{
    return this->quantity;
}

bool HashTable::isEmpty()
{
    return this->quantity == 0;
}

bool HashTable::isFull()
{
    return this->quantity == this->getSize();
}
