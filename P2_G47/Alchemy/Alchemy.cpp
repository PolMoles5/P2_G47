//Código de Alchemy : Salvador Cerdà Holmager / Pol Moles Gil
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <windows.h>
#include <unordered_map>
#include <fstream>
#include <sstream>

//Con esta función podemos especificar que carácteres queremos que realizen un salto para separar los elementos introducidos por el usuario
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

//Creo un vector para la lista que se mostará en pantalla
std::vector<std::string> *lista = new std::vector<std::string>;
//Creamos un unordered_map para guardar las diferentes combinaciones y sus resultados
std::unordered_map<std::string, std::string> map;
//Creamos un vector para guardar las nuevas combinaciones realizadas por el jugador 
std::vector<std::string> *combin = new std::vector<std::string>;
int puntos = 0;

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
	
	std::cout << "Your current score: " << puntos << "\n" << "You have these elements:"<< std:: endl;
	for (int i = 0; i < lista->size(); i++) {
		std::cout << i << ":" << (*(lista))[i] << std::endl;
	}
	
}
//Función que añade los elementos básicos al final de la lista
void addBasics() {
	lista->push_back("Air");
	lista->push_back("Earth");
	lista->push_back("Fire");
	lista->push_back("Water");
}


void main() {


	//Cargamos el documento con las combinaciones posibles 
	std::ifstream infile("elements.dat");
	//Si el archivo elements.dat no se carga correctamente, se notifica al usuario y se pausa el programa
	if (!infile.is_open()){	
		std::cout << "El archivo elements.dat no se ha cargado correctamente " << std::endl;
		system("pause");
	}

	std::string line;
	//Este bucle leerá todas las líneas de "elements.dat"
	while (std::getline(infile, line))
	{
		//Creamos un vector de string en el que almacenaremos los resultados de las combinaciones
		std::vector<std::string> parts;
		//Separamos cada línea del documento en llegar al "=" 
		split(line, parts, " = ");

		//Este segundo vector de string almacenará ambos elementos a combinar
		std::vector<std::string> parts2;
		//Esto lo hará separando la segunda parte (a partir del " + ") del "split" que hicimos para separar el resultado de los elementos
		split(parts.at(1), parts2, " + ");

		map[parts2.at(0) + " + " + parts2.at(1)] = parts.at(0);
	}
	
	//Datos introducidos por el usuario
	std::string userCommand;

	//Elementos iniciales en la lista
	addBasics();
	showHelp();
	showList();

	//Bucle principal
	while (true) {
		std::getline(std::cin, userCommand);
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::vector<std::string>  arguments;
		split(userCommand, arguments, " ");
		system("cls");

		//Si el usuario introduce HELP
	    if (arguments.at(0).compare("help") == 0) {
			showHelp();
		}

		//Si el usuario introduce DELETE X
		else if (arguments.at(0).compare("delete") == 0) {
			lista->erase(lista->begin() + std::stoi(arguments.at(1)));
		}

		//Si el usuario introduce INFO X
		else if (arguments.at(0).compare("info") == 0) {
			int posicion = /*std::*/stoi(arguments.at(1));
		
			std::string link ("https://en.wikipedia.org/wiki/") ;
			std::string element(lista->at(posicion));
			link = link + element;
			ShellExecute(NULL, "open", link.c_str() , NULL, NULL, SW_SHOWNORMAL);
		}

		//Si el usuario introduce ADD X
		else if (arguments.at(0).compare("add") == 0 && !arguments.at(1).compare("basics") == 0) {
			int posicion = stoi(arguments.at(1));
			lista->push_back((lista->at(posicion)));
		}

		//Si el usuario introduce ADD BASICS
		else if (arguments.at(0).compare("add") == 0 && arguments.at(1).compare("basics") == 0) {
			addBasics();
		}

		//Si el usuario introduce CLEAN
		else if (arguments.at(0) =="clean") {
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

		//Si el usuario introduce SORT
		else if (arguments.at(0).compare("sort") == 0) {
			std::sort(lista->begin(), lista->end());
		}

		//Si el usuario introduce COMBINE X Y
		else if (arguments.at(0)=="combine" ) {
			std::string elemento1 = lista->at(stoi(arguments.at(1)));
			std::string elemento2 = lista->at(stoi(arguments.at(2)));
			

			//Para que no se pueda combinar elementos consigo misos que ocuppen el mismo sitio en la lista
			if (arguments.at(1) != arguments.at(2)) {
				std::string key = elemento1 + " + " + elemento2;
				//Si la combinación introducida es válida:
				if (map.count(key)) {
					lista->push_back(map[key]);
					lista->erase(std::remove(lista->begin(), lista->end(), elemento1), lista->end());
					lista->erase(std::remove(lista->begin(), lista->end(), elemento2), lista->end());
					if (std::find(combin->begin(), combin->end(), map[key]) == combin->end()){
						combin->push_back(map[key]);
						puntos++;
					}
				}

				//En el caso de que no lo sea:
				if (!map.count(key)) {
					//Se prueba cambiando el orden de lo elementos
					std::string key = elemento2 + " + " + elemento1;
					//Si el cambio de orden de los elementos resulta en una combinación válida
					if (map.count(key)) {
						lista->push_back(map[key]);
						lista->erase(std::remove(lista->begin(), lista->end(), elemento1), lista->end());
						lista->erase(std::remove(lista->begin(), lista->end(), elemento2), lista->end());
						if (std::find(combin->begin(), combin->end(), map[key]) == combin->end()){
							combin->push_back(map[key]);
							puntos++;
						}
					}
					//Si este cambio sigue sin ser válido
					if (!map.count(key)) {
						std::cout << "This combination is not possible. Try again" << std::endl;
					}
				}
			}
			else {
				std::cout << "Cannot combine the same element" << std::endl;
			}
		}

		//Si el comando introducido no existe
		else {
			std::cout << "This function is not available. Type 'help' for more info..." << std::endl;
		}
		showList();
	}
}