
#include "functions.h"
void items_printing(std::vector<Items>& items){
	for(int i=0;i<items.size();i++){
	std::cout<<"id: "<<items[i].id<<
	"; nazwa: "<<items[i].name<<
	"; waga: "<<items[i].weight<<
	"; wartosc: "<<items[i].value<<
	"; val: "<<items[i].ratio<<std::endl;
	}
}


std::vector<Items> import(std::string path){
	std::ifstream input(path);
	std::vector<Items> items;
	if (!input) {
    std::cerr << "Nie udało się otworzyć pliku!" << std::endl;
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

	
std::vector<bool> random_genome(int n){
    std::vector<bool> arr;
	int sum=0; //do sprawdzania czy wektor nie jest pusty
	bool temp; 
    std::default_random_engine random_generator;
    random_generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> range{ 0, 1 };
    while(sum==0){
	for (int i = 0; i < n; i++) {
		temp=range(random_generator);
        arr.push_back(temp);
		if(temp){
			sum++;
		}
    }
	}
    return arr;
}
std::vector<Subjects> subject_creation(int n,int length){
	//n= liczba osobnikow w pokoleniu
	std::vector<Subjects> subjects;
	Subjects temp_subject;
	int wartosci;
	for(int i=0;i<n;i++){
		temp_subject.id_subject=i;
		temp_subject.genome=random_genome(length);
		temp_subject.fitness=0;
		subjects.push_back(temp_subject);
	}
	return subjects;
}

void subjects_printing(std::vector<Subjects>& subjects){
	for(int i=0;i<subjects.size();i++){
		std::cout<<"id: "<<subjects[i].id_subject<<"; genom ";
		for(int j=0;j<subjects[0].genome.size();j++){
		std::cout<<subjects[i].genome[j];
		}
		std::cout<<"; ocena "<<subjects[i].fitness<<
		"; waga "<<subjects[i].weight<<
		"; wartosc "<<subjects[i].value<<std::endl;
	}
}

void fitness(std::vector<Items>& items,std::vector<Subjects>& subjects, double capacity){
	//int i=genom.size()-1;
	// double waga=0;
	// int wartosc=0;
	double val, penalty, bonus,fit; //st wartosc/waga, kara za przekroczenie wagi, bonus za duzy val
	for(int i=0;i<subjects.size();i++){
		double weight=0;
		int value=0;
		std::vector<bool> genome=subjects[i].genome;
		int n=genome.size();
		for(int i=0;i<n;i++){
		if(genome[i]){
			weight+=items[i].weight;
			value+=items[i].value;
		}
		penalty=capacity/100;
		bonus=5;
		if(weight>capacity)
			fit=(value+bonus*(value/weight))*penalty*(capacity/weight);
		else
			fit=value+bonus*(value/weight);
		}
		subjects[i].fitness=fit;
		subjects[i].weight=weight;
		subjects[i].value=value;
		//std::cout<<" waga "<<weight<<"; wartosc "<<value<<"; ocena= "<<fit<<std::endl;
	}
	//return wynik;
}

std::vector<Subjects> sort_generations(std::vector<Subjects> subjects){
	std::vector<Subjects> subjects_sort;
	int max_id;
	double max_ocena;
	for(int i=0;i<subjects.size();i++){
		max_ocena=0;
		for(int j=0;j<subjects.size();j++){
			if(subjects[j].fitness>max_ocena){
				max_ocena=subjects[j].fitness;
				max_id=j;
			}
		}
		subjects_sort.push_back(subjects[max_id]);
		subjects[max_id].fitness=0;
	}
	
	return subjects_sort;
}

std::vector<Subjects> crossover(std::vector<Items>& items,std::vector<Subjects>& subjects,double capacity,int num_in_generation){
	std::vector<double> ratios; //wartosc/waga
	
	for(int i=0;i<items.size();i++){
		ratios.push_back(items[i].ratio);
		//std::cout<<"i: "<<i<<" val: "<<vals[i]<<std::endl;
	}

	//tworzenie posortowanej tablicy ID przedmiotów malejąco po ich stosunku wartosc/waga
	std::vector<int> ratios_pos_sort;
	double max;
	int maxid;
	for(int i=0;i<items.size();i++){
		max=0;
		for(int j=0;j<items.size();j++){
			if(max<ratios[j]){
				max=ratios[j];
				maxid=j;
			}
		}
		ratios_pos_sort.push_back(maxid);
		ratios[maxid]=0;
		//std::cout<<vals_poz_sort[i]<<std::endl;
	}

	std::vector<Subjects> subjects_sort=sort_generations(subjects);
	//wyswietlanie_osobnikow(osobniki_sort,osobniki[0].genom.size());
	
	/*
	20% przepisujemy
	50% rodzice, kazdy z kazdym
	krzyzowanie oparte o wartosc/waga
	sort od najlepszych w pokoleniu, wybieranie 50% rodzicow
	kazdy rodzic z kazdym
	"suma" genomu rodziców i sprawdzanie od indeksu przedmiotu o najwiekszym stosunku wartosc/waga (vals_poz_sort)
	sprawdzanie i odrzucanie jezeli waga>ladownosc
	*/

	int parents_n=0.5*subjects_sort.size();
	int elit=0.2*subjects_sort.size();
	subjects_sort.resize(parents_n);

	
	

	/*losowanie rodzicow
	c) Selekcja rankingowa
	robienie kazdy z kazdym z najlepszych rodzicow
	*/


	
	std::vector<bool> temp_descen;
	int descen_id=0;
	double sum_weight; 
	std::vector<Subjects> new_generation;
	Subjects temp_subject;
	for(int i=0;i<subjects_sort.size();i++){
		for(int j=i+1;j<subjects_sort.size();j++){
			
			sum_weight=0;
			auto parent1=subjects_sort[i];
			auto parent2=subjects_sort[j];

			//pomijanie takich samych osobnikow
			if(parent1.genome==parent2.genome){
			//std::cout<<"genomy rodzicow sa takie same"<<" i= "<<i<<" j= "<<j<<std::endl;
			continue;
			}

			for(int i=0;i< parent1.genome.size();i++){
			temp_descen.push_back(parent1.genome[i]+parent2.genome[i]);
			}


			/*wybieramy te przedmioty o najwiekszej wartosci i 
			to je pierwsze dodajemy do plecaka*/
			for(int i:ratios_pos_sort){
				if(temp_descen[i]){
					if(sum_weight+items[i].weight>capacity)
					temp_descen[i]=0;
			
				}
				if(temp_descen[i])
				sum_weight+=items[i].weight;


			}
					temp_subject={descen_id,temp_descen,0,0,0};
					descen_id++;
					new_generation.push_back(temp_subject);
					sum_weight=0;
					temp_descen.clear();
		}
	}
	fitness(items, new_generation,capacity);

	/*elitaryzm, przepisywanie 20% najlepszych osobnikow z poprzedniego pokolenia do nastepnego*/
	
	//std::cout<<"elit: "<<elit<<std::endl;
	for(int i=0;i<elit;i++){
		int id=new_generation.size();
		temp_subject=subjects_sort[i];
		temp_subject.id_subject=id;
		new_generation.push_back(temp_subject);
	}
	return new_generation;
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
void help(){
    
    std::cout<<"program wywoluje sie w nastepujacy sposob: skompilowany_plik.exe ARGUMENTY_PROGRAMU"<<std::endl;
    std::cout<<"gdzie ARGUMENTY_PROGRAMU to:"<<std::endl;
    std::cout<<"-i plik wejsciowy opisujacy zbior przedmiotow"<<std::endl;
    std::cout<<"-o plik wyjsciowy z najlepszymi rozwiazaniami w kolejnych pokoleniach"<<std::endl;
    std::cout<<"-p ladownosc plecaka"<<std::endl;
    std::cout<<"-g liczba pokolen"<<std::endl;
    std::cout<<"-n liczba osobnikow w pokoleniu"<<std::endl;
    std::cout<<"(kolejnosc podawania argumentow jest dowolna i nie ma znaczenia na dzialanie programu)"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"przyklad wywolania: wynik.exe -i wejscie.txt -o wyjscie.txt -p 21 -g 5 -n 7"<<std::endl;
    std::cout<<std::endl;

}

bool parameters(int n, char * params[],std::string & input,std::string & output, double & capacity, int & num_in_generation,int & num_of_generations){
    std::vector<std::string> args;
    if(n!=11){
        std::cout<<"podano niewlasciwa liczbe argumentow wykonania programu!"<<std::endl;
        help();
        return 0;
    }
    for(int i=1;i<n;i++){
        args.push_back(params[i]);
    }
    for(int i=0;i<n;i++){
        if(args[i]=="-i"){
            input=args[i+1];
            i++;
            continue;
        }
        else if(args[i]=="-o"){
            output=args[i+1];
            i++;
            continue;
        }
        else if(args[i]=="-p"){
            std::stringstream (args[i+1])>>capacity;
            i++;
            continue;
        }
        else if(args[i]=="-g"){
            std::stringstream (args[i+1])>>num_of_generations;
            i++;							
            continue;
        }
        else if(args[i]=="-n"){
            std::stringstream (args[i+1])>>num_in_generation;
            i++;
            continue;
        }
    }
    return 1;
}
