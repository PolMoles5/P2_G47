//Codigo Repaso 1
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <unordered_map>
#include <fstream>
#include <sstream>


unsigned int split(const std::string &txt, std::vector<std::string> &strs, std::string ch)
{
	unsigned int pos = txt.find(ch);
    int initialPos = 0 ;
	strs.clear();
	int offset = 0;
	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos));
		initialPos = pos + ch.length();
		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, (std::min)(pos, txt.size()) - initialPos + 1));

	return strs.size();
}



//Creamos una lista global
std::vector<std::string> *lista = new std::vector<std::string>;

std::unordered_map<std::string, std::string> map;

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
	std::ifstream infile("elements.dat");
	std::string line;
	while (std::getline(infile, line))
	{
		std::vector<std::string> parts;
		split(line, parts, " = ");
std::string resultat = parts.at(0);
std::string resultat1 = parts.at(1);


		std::vector<std::string> parts2;
		split(parts.at(1), parts2, " + ");

		
		map[parts2.at(0) + " + " + parts2.at(1)] = parts.at(0);
	}
	std::vector<std::string> ans;
	split("combine 3 1", ans, " ");
	std::cout << ans.at(0) << "|" << ans.at(1) << "|" << ans.at(2) << std::endl;

	std::vector<std::string> ans2;
	split("Lawn Mower = Scissors + Combustion Engine", ans2, " = ");
	std::cout << ans2.at(0) << "|" << ans2.at(1) << std::endl;

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
		split(userCommand, arguments, " ");


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
		if (arguments.at(0).compare("add") == 0 && !arguments.at(1).compare("basics") == 0) {
			int posicion = stoi(arguments.at(1));
			std::cout <<"\n" << std::endl;
			lista->push_back((lista->at(posicion)));
		}

		//Si el usuario introduce ADD BASICS
		if (arguments.at(0).compare("add") == 0 && arguments.at(1).compare("basics") == 0) {

			lista->push_back("Air");
			lista->push_back("Earth");
			lista->push_back("Fire");
			lista->push_back("Water");
		}
		if (arguments.at(0) =="clean") {
			std::vector<std::string> *newLista = new std::vector<std::string>;
			for (int i = 0; i < lista->size();i++) {
				std::string actual = lista->at(i);
				if (std::find(newLista->begin(), newLista->end(), actual) != newLista->end()) {

				}
				else {
					newLista->push_back(actual);
				}
			}
			delete lista;
			lista = newLista;
		}

		if (arguments.at(0).compare("sort") == 0) {
			std::sort(lista->begin(), lista->end());
		}

		if (arguments.at(0)=="combine" ) {
			std::string elemento1 = lista->at(stoi(arguments.at(1)));
			std::string elemento2 = lista->at(stoi(arguments.at(2)));
			
			std::cout << "Combinando " << elemento1 << " con " << elemento2 << std::endl;

			std::string key = elemento1 + " + " + elemento2;
			
			lista->push_back(map[key]);
			lista->erase(lista->begin() + std::stoi(arguments.at(1)));
			lista->erase(lista->begin() + std::stoi(arguments.at(2)));
		}



		showList();
	}



}