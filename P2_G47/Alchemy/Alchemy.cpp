//Codigo Repaso 1
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include<stdio.h>
#include <windows.h>


unsigned int split(const std::string &txt, std::vector<std::string> &strs, char ch)
{
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, (std::min)(pos, txt.size()) - initialPos + 1));

	return strs.size();
}



//Creamos una lista global
std::vector<std::string> *lista = new std::vector<std::string>;

//Función que imprime las instrucciones del programa
void showHelp() {
	std::cout << "-------------" << std::endl;
	std::cout << "  ALCHEMIST" << std::endl;
	std::cout << "-------------" << std::endl;
	std::cout << "-Enter two numbers of your elements list  to combine them." << std::endl;
	std::cout << "-Enter the word 'add' and then the number of an element to add it to a new instance of that element." << std::endl;
	std::cout << "-Enter 'add basics' to add new instances of the 4 basic elements." << std::endl;
	std::cout << "-Enter the word 'delete' and the number of an element to erase it from your list. " << std::endl;
	std::cout << "-Enter the word 'info' and the number of an element to get information about it in the explorer." << std::endl;
	std::cout << "-Enter the word 'sort' to sort by alphabetical order in the elements in the list." << std::endl;
	std::cout << "-Enter the word 'clean' to delete all the instances of of repeated elements." << std::endl;
	std::cout << "-Enter the word 'help' to show this tutorial." << std::endl << "\n";
}

//Función que imprime la lista de elementos
void showList() {
	for (int i = 0; i < lista->size(); i++) {
		std::cout << i << ":" << (*(lista))[i] << std::endl;
	}
}


void main() {
	//Datos introducidos por el usuario
	std::string userCommand;

	//Elementos iniciales en la lista
	lista->push_back("Air");
	lista->push_back("Earth");
	lista->push_back("Fire");
	lista->push_back("Water");

	showHelp();
	showList();

	while (true) {
		std::getline(std::cin, userCommand);
		std::vector<std::string>  arguments;
		split(userCommand, arguments, ' ');


		//Si el usuario introduce HELP
		if (arguments.at(0).compare("help") == 0) {
			showHelp();
		}

		//Si el usuario introduce DELETE X
		if (arguments.at(0).compare("delete") == 0) {
			std::cout << "borrando" << arguments.at(1) <<"\n" <<std::endl;
			lista->erase(lista->begin() + std::stoi(arguments.at(1)));
		}

		//Si el usuario introduce INFO X
		if (arguments.at(0).compare("info") == 0) {
			int posicion = /*std::*/stoi(arguments.at(1));
			std::cout << "Buscando info de " << lista->at(posicion) << "\n" << std::endl;
		
			std::string link ("https://en.wikipedia.org/wiki/") ;
			std::string element(lista->at(posicion));
			link = link + element;
			ShellExecute(NULL, "open", link.c_str() , NULL, NULL, SW_SHOWNORMAL);
		}

	
		//Si el usuario introduce ADD X
		if (arguments.at(0).compare("add") == 0) {
			int posicion = stoi(arguments.at(1));
			std::cout <<"\n" << std::endl;
			lista->push_back((lista->at(posicion)));


		}
		
		showList();
	}



}