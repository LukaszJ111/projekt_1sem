#pragma once
#include<iostream>
#include<vector>
#include<sstream>


/**Wyświetla pomoc odnośnie obsługi uruchomienia programu z linii poleceń
 * 
 */
void help();

/** Funkcja przekazuje poprzez parametry funkcji przekazuje do zmiennych parametry wywołania programu
 * @param n liczba parametrow
 * @param wejscie_przedmioty ścieżka pliku wejściowego
 * @param wyjscie_wynik ścieżka pliku wyjściowego
 * @param ladownosc zakładana maksymalna ładowność plecaka
 * @param liczba_osob_pokolenie liczba osobników w pokoleniu
 * @param liczba_pokolen liczba pokoleń
 */
bool parameters(int n, char * params[],std::string & input,std::string & output, double & capacity, int & num_in_generation,int & num_of_generations);