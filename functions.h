#pragma once
#include<iostream>
#include<vector>
#include<fstream>
#include<chrono>
#include<random>
#include<sstream>
#include "struct.h"
/** Funkcja wpisuje do wektora przedmioty z pliku wejściowego
 * @param path to sciezka pliku wejsciowego
 * @return vector wpisanych przedmiotow
 */
std::vector<Items> import(std::string path);


/** Funkcja wypisuje przedmioty z wektora ktore byly wczesniej wpisane z pliku
 * @param items to wektor przedmiotów które zostaną wypisane
 */
void items_printing(std::vector<Items>& items);


/** Funkcja losowo tworzy genom (w algorytmach genetycznych nazywanu również czasami chromosomem) osobnika o podanej dlugosci
 * @param n dlugosc genomu (liczba przedmiotow które mogą znaleźć się w plecaku)
 * @return losowy genom w vector<bool>
 */
std::vector<bool> random_genome(int n);

/** Tworzy okreslona liczbe osobnikow z losowym genomem o podanej dlugosci
 * @param n liczba osobnikow ktore ma stworzyc funkcja
 * @param length dlugosc genomu (liczba przedmiotow które mogą znaleźć się w plecaku)
 * @return zwraca vektor osobnikow
 */
std::vector<Subjects> subject_creation(int n,int length);


/** Funkcja wyswietla vector osobnikow 
 * @param subjects vector osobnikow do wyswietlenia
 */
void subjects_printing(std::vector<Subjects>& subjects);


/** Funkcja obliczająca ocenę dla każdego osobnika na podstawie jego ladownosci naszego plecaka, jego wagi i wartosci przedmiotow
 * funkcja oblicza ocene za pomocą wzoru: 
 * penalty=capicity/100;
 * bonus=5;
 * jeżeli waga przekroczy ładowność: (weight>capacity)
 *     fitness=(value+bonus*(value/weight))*penalty*(capacity/weight);
 * else
 *		fitness=value+bonus*(value/weight);
 * w przeciwnym przypadku:
 *      fitness=value+bonus*(value/weight);
 * 
 * gdzie:
 * weight- całkowita (zsumowana) waga przedmiotów w plecaku dla danego osobnika
 * value -całkowita (zsumowana) wartość przedmiotów w plecaku dla danego osobnika
 * 
 * @param items to vector wszystkich przedmiotów mogących znaleźć się w plecaku
 * @param subject vector osobników którym zostanie przypisana ocena (przekazywany przez referencję czyli ocena zostanie ustawiona dla osobnikow w tym vectorze)
 * @param capacity to maksymalna ladownosc naszego plecaka
 */
void fitness(std::vector<Items>& items,std::vector<Subjects>& subject, double capacity);


/** Funkcja sortuje osobnikow w pokoleniu malejąco po ich ocenie
 * @param subjects vector osobników do posortowania
 * @return posortowany vector<Osobniki> aby nie zmieniać wartości pierwotnego przekazywanego przez parametr
 */
std::vector<Subjects> sort_generations(std::vector<Subjects> subjects);


/** Funkcja dokonuje krzyżowania osobników na podstawie stosunku wartosc/waga
 * elitaryzm - przepisujemy 20% najlepszych osobników z poprzedniego pokolenia
 * wybieramy 50% najlepszych osobnikow z kazdego pokolenia jako rodzice następnego, 
 * krzyżujemy rodziców każdy z każdym
 *	"suma" genomu rodziców i sprawdzanie od indeksu przedmiotu o najwiekszym stosunku wartosc/waga (vals_poz_sort)
 *	sprawdzanie i odrzucanie jezeli waga>ladownosc
 * @param items to vector wszystkich przedmiotów mogących znaleźć się w plecaku
 * @param subjects vector osobników z których część będziemy ze sobą krzyżować
 * @param capacity zakładana maksymalna ladowność naszego plecaka
 * @param num_in_generation zakładana maksymalna liczba osobników w pokoleniu
 * @return vector skrzyżowanych osobników
 */
std::vector<Subjects> crossover(std::vector<Items>& items,std::vector<Subjects>& subjects,double capacity,int num_in_generation);


/** Funkcja obsługująca zapis do wskazanego pliku wyjściowego
 * @param przedmioty to vector wszystkich przedmiotów mogących znaleźć się w plecaku
 * @param pokolenia vector wszystkich pokoleń
 * @param wyjscie scieżka pliku wyjściowego
 */
void saving(std::vector<Items>& items,std::vector<Generations>& generations, std::string output);


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