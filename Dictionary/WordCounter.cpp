//
//  WordCounter.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <list>
#include "Dictionary.h"

using namespace std;

int main(int argc, char const *argv[])
{
    if (argc < 2)
    {
        cout << "ERRO: Programa deve receber nome de arquivo como parâmetro de entrada.\n";
        return 1;
    }
    
    string fileName = argv[1];
    
    ifstream file(fileName);
    
    
    if (!file.is_open())
    {
        cout << "ERRO: Programa não conseguiu abrir o arquivo '" + fileName + "'.\n";
        return 1;
    }
    
    Dictionary<string, list<int>> dic;
    
    while (!file.eof())
    {
        string line;
        getline(file,line);
        
        // Transforma todos caracteres para caixa alta (maiúsculo)
        transform(line.begin(), line.end(), line.begin(), ::toupper);
        
        istringstream iss(line);
        
        string word;
        while(iss>>word)
        {
            // Apaga todos caracteres que não são letras nem números
            word.erase( std::remove_if(word.begin(), word.end(), not1(::ptr_fun((int(*)(int))::isalnum))), word.end() );
            if( !word.empty() )
            {
                 // Seu código vai majoritariamente aqui
 
                 cout << word << endl;
            }
        }
    }
    file.close();
    
        for( auto word : {"BELA", "GRIMM", "REI", "FILHO", "JARDIM", "MESMO"} )
        {
            cout << "These are the lines where I found: " << word << endl;
            
            if( !dic.contains(word) )
            {
                cout << "Not found" << endl;
            }
            else
            {
                auto l = dic.get( word );
                for( auto s : l )
                {
                    cout << s << " ";
                }
                cout << endl << endl;
            }
        }
}

