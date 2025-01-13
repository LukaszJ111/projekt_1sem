#pragma once
struct Items {
		int id;
		std::string name;
		double weight;
		double value;
		double ratio;
	} ;
struct Subjects{
	int id_subject;
	std::vector<bool> genome;
	double fitness;
	double weight;
	double value;
	
};
struct Generations{
	int id_generation;
	std::vector<Subjects> generation;
};