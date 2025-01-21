#include "algorithm.h"
#include "cli.h"
#include "io.h"


int main(int n, char * params[]){
    std::string input,output;
    double capacity;
	int num_in_generation,num_of_generations;
    bool test=parameters(n, params,input,output,capacity,num_in_generation,num_of_generations);
    //bool test=1;
    if(!test){
        return 0;
    }



	std::vector<Items> items=import(input);
    if(items.size()>0){
    //std::cout<<"wyswietlam przedmioty"<<std::endl;
	//items_printing(items);
    
    }
    else{
        std::cout<<"podany plik wejsciowy nie istnieje koncze dzialanie programu"<<std::endl;
        return 0;
    }
	
	std::cout<<std::endl;
    
	std::cout<<std::endl;

	int genome_size=items.size();
	
	//losowanie wartosci
	std::vector<Subjects> subjects=subject_creation(num_in_generation,genome_size);
	

	fitness(items,subjects,capacity);
	
	std::vector<Generations> generations;
	generations.push_back({0,subjects}); 


	std::vector<Subjects> next_generation;
	for(int i=1;i<=num_of_generations;i++){
		
		next_generation=crossover(items,generations[i-1].generation,capacity,num_in_generation);
		
		if(next_generation.size()>num_in_generation){
		next_generation.resize(num_in_generation);
		}
		generations.push_back({i,next_generation});
	}

	
	/*std::cout<<std::endl;
	std::cout<<"wyswietlam najlepsze rozwiazanie z kazdego pokolenia"<<std::endl;
	std::cout<<std::endl;*/
	saving(items,generations,output);
	
	
	return 0;
}
