#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include "struct.h"
/** Funkcja wpisuje do wektora przedmioty z pliku wejściowego
 * @param path to sciezka pliku wejsciowego
 * @return vector wpisanych przedmiotow
 */
std::vector<Items> import(std::string path);

/** Funkcja obsługująca zapis do wskazanego pliku wyjściowego
 * @param przedmioty to vector wszystkich przedmiotów mogących znaleźć się w plecaku
 * @param pokolenia vector wszystkich pokoleń
 * @param wyjscie scieżka pliku wyjściowego
 */
void saving(std::vector<Items>& items,std::vector<Generations>& generations, std::string output);