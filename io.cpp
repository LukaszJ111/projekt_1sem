#include "io.h"
#include "algorithm.h"
std::vector<Items> import(std::string path){
	std::ifstream input(path);
	std::vector<Items> items;
	if (!input) {
    std::cerr << "Nie udalo sie otworzyc pliku!" << std::endl;
	return items={};
	}
	else{
	int counter{0};
	Items temp_item;
	while(input>>temp_item.name>>temp_item.weight>>temp_item.value){
		temp_item.id=counter;
		temp_item.ratio=temp_item.value/temp_item.weight;
		items.push_back(temp_item);
		counter++;
	}
	}
	return items;
}
void saving(std::vector<Items>& items,std::vector<Generations>& generations, std::string output){
    std::ofstream result(output);
	//mozna dodać referencje do zmiennej ale wtedy pokolenia bedą posortowane
	for(auto tmp:generations){
        
		std::cout<<"pokolenie "<<tmp.id_generation<<", ";
        result<<"pokolenie "<<tmp.id_generation<<", ";
		sort_generations(tmp.generation);
        if(tmp.generation.size()!=0){
		std::cout<<" waga: "<<tmp.generation[0].weight<<", wartosc: "<<tmp.generation[0].value<<std::endl;
        result<<" waga: "<<tmp.generation[0].weight<<", wartosc: "<<tmp.generation[0].value<<std::endl;
		for(int i=0;i<tmp.generation[0].genome.size();i++){
			if(tmp.generation[0].genome[i])
			std::cout<<items[i].name<<" waga: "<<items[i].weight<<" wartosc: "<<items[i].value<<std::endl;
            result<<items[i].name<<" waga: "<<items[i].weight<<" wartosc: "<<items[i].value<<std::endl;
			
		}
        }
        else{
            std::cout<<std::endl;
            std::cout<<"w poprzednim pokoleniu znaleziono juz optymalne rozwiazanie"<<std::endl;
            result<<std::endl;
            result<<"w poprzednim pokoleniu znaleziono juz optymalne rozwiazanie"<<std::endl;
        }
		std::cout<<std::endl;
        result<<std::endl;
	}
}
