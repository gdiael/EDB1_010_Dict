//
//  main.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include <iostream>
#include <string>
#include <list>
#include "Dictionary.h"

using namespace std;

int main(int argc, const char * argv[]) {
    
    cout << "Testing Dictionary of (string, int) \n";
    
    // Cria um dicionário
    Dictionary<string, int> dicStrInt;
    
    cout << "\nDictionary before insertion: \n";
    
    dicStrInt.print();
    
    string key = "aaa";
    int value = 1;
    
    // Associa a string "aaa" ao inteiro 1
    dicStrInt.put( key, value );
    // Em outras palavras, guardei o par ("aaa", 1) no dicionário
    
    cout << "\nDictionary after inserting pair (" << key << "," << value << "):\n";
    
    dicStrInt.print();
    
    // Busca o valor associado à string "aaa"
    try{
        // Neste caso, vai ser encontrado, então o cout abaixo será executado
        int result1 = dicStrInt.get( key );
        cout << "\nValue associated with '" << key << "' is " << result1 << std::endl;
    }
    catch( std::out_of_range e)
    {
        cerr << "\tKey '" << key << "' not found" << endl;
        cerr << e.what() << endl;
    }
    
    value = 10;
    
    // Associa a string "aaa" ao inteiro 10
    dicStrInt.put( key, value );
    // Em outras palavras, atualizei o valor associado a "aaa" para 10
    
    cout << "\nDictionary after updating key '" << key << "': \n";
    
    dicStrInt.print();
    
    // Remove o par cuja chave é "aaa"
    dicStrInt.remove( key );
    
    std::cout << "\nDictionary after removing '" << key << "': \n";
    dicStrInt.print();
    
    // Busca o valor associado à string "aaa"
    try{
        // Agora, ao buscar o valor associado à string "aaa", irá lançar uma exceção do tipo 'out_of_range', que é tratada abaixo.
        // Como uma exceção ocorre ao invocarmos o método get, o cout abaixo não será executado
        
        std::cout << "\nAfter removing '" << key << "', the operation 'get' results in: \n";
        int result1 = dicStrInt.get( key );
        
        cout << "\tValue associated with '" << key << "' is " << result1 << std::endl;
    }
    catch( std::out_of_range e)
    {
        cerr << "Key '" << key << "' not found" << endl;
        cerr << "Error message: " << e.what() << endl;
    }
    
    std::cout << "\n\nTesting Dictionary of (string, list<int>) \n";
    
    // Agora vamos criar um dicionário que associa uma string a uma lista de inteiros
    Dictionary<string, list<int>> dic;
    // Vamos usar este dicionário para guardar em quais posições de um array a string aparece
    
    // Por exemplo, no array abaixo, a string "a" aparece nas posições 0 e 4
    string v[] = {"a", "b", "c", "d", "a", "b", "c"};
    // Logo, deverá existir no dicionário 'dic' um par ("a", {0, 4})
    // indicando que a string "a" aparece nas posições {0, 4}
    
    cout << "Input array is:\n\t{ ";
    for( auto s : v )
    {
        cout << s << ",";
    }
    cout << "}" << std::endl;
    
    int i = 0;
    for(auto s : v)
    {
        // Checa se a chave está no dicionário
        if( !dic.contains(s) )
        {
            // Se executou aqui, quer dizer que ainda não existe par com chave igual à string 's'
            // Em outras palavras, é a primeira vez que encontramos esta string no array de entrada
            // Como esta é a primeira vez que encontramos a string 's' no array de entrada,
            // precisamos criar uma lista 'l' para guardar no dicionário o par ('s', 'l')
            list<int> l; //= new list<int>();
            
            // Guardamos a posição 'i' na lista 'l', que é a posição onde ocorre a string 's'
            l.push_back(i);
            
            // Guardamos o par ('s', 'l') no dicionário
            dic.put( s, l );
        }
        else
        {
            // Se executou aqui, é porque já existe um par no dicionário cuja chave é igual a string 's'
            // Neste caso, basta guardarmos a posição 'i' na lista que é retornada pelo dicionário
            list<int> r = dic.get(s);
            
            // Guardamos a posição 'i' na lista retornada
            r.push_back(i);
            
            // Atualizamos o dicionário com a lista modificada
            // Ou seja, neste caso, como já existe um par com chave igual a 's', o método 'put' irá atualizar o valor associado a 's'
            dic.put( s, r );
        }
        
        ++i;
    }
    
    std::cout << "Dictionary content is:\n";
    
    // Neste for eu simplesmente percorro todas as strings do array de entrada
    // E pego do dicionário as listas que estão associadas à cada string
    for(auto s : {"a", "b", "c", "d"})
    {
        list<int> r = dic.get(s);
        
        cout << "\t('" << s << "', {";
        for( auto j : r )
        {
            cout << j << ", ";
        }
        cout << "} )\n";
    }
    
    return 0;
}
