#include "cli.h"

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
    for(int i=0;i<n-1;i++){
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
