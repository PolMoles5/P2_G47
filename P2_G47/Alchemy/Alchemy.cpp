#include <iostream>
#include <string>
#include <vector>
#include<stdio.h>


//Creamos una lista global
std::vector<std::string> *lista = new std::vector<std::string>;

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
	std::cout << "-Enter the word 'help' to show this tutorial." << std::endl;
}


void main() {
	//Datos introducidos por el usuario
	std::string userCommand;

	//Elementos iniciales en la lista
	lista->push_back("Air");
	lista->push_back("Earth");
	lista->push_back("Fire");
	lista->push_back("Water");

	//Ejecutamos la funcion showHelp() al iniciar el programa
	showHelp();

}

