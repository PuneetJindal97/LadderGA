#include <bits/stdc++.h>

using namespace std;

class gene{
    public:
        int level;
        int accuracy;
        int wasteful;
        int useful;
        int overTime;
        int skipRrate;
        int avgScore;
        int userRating;
        vector< string > conceptList;
};

class Encoding{
public:
    vector< gene > code(20)
    double fitness;
    double probability;
};

void calculateFitness(){

}

vector< Encoding > chromosome(POPULATION_SIZE);

int selection(){
    double totalFitness=0;
    double totalProbability=0;
    double probability=0;
    srand((unsigned)time(NULL));
    double rndNumber = rand() / (double) RAND_MAX;
    double offset = 0.0;
    int pick = 0;

    for(int i=0;i<POPULATION_SIZE;i++){
        totalFitness += chromosome[i].fitness;
    }

    for(int i=0;i<POPULATION_SIZE;i++){
        chromosome[i].probability = chromosome[i].fitness/totalFitness;
    }

    for (i = 0; i < POPULATION_SIZE; i++) {
        offset += chromosome[i].probability;
        if (rndNumber < offset) {
            pick = i;
            break;
        }
}
    return pick;
}

int main(){

}
