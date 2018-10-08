#include <bits/stdc++.h>

using namespace std;
const int POPULATION_SIZE = 5000;
const double ACCURACY_WT = 1;
const double WASTEFUL_WT = 1;
const double USEFUL_WT = 1;
const double OVERTIME_WT = 1;
const double AVGSCORE_WT = 1;
const double SKIPRATE_WT = 1;
const double USERRATING_WT = 1;
const double AVGTIME_WT = 1;
const double CD_WT = 0.6;
const double AD_WT = 0.4;
double DD;

class gene{
    public:
        double level;
        double accuracy;
        double wasteful;
        double useful;
        double overTime;
        double skipRate;
        double avgScore;
        double userRating;
        double avgTime;
        vector< string > conceptList;
};

vector< gene > quesBank(1000);

class Encoding{
    public:
    double fitness;
    vector< int > code;
    double probability;
    Encoding() : code(20), fitness(0), probability(0) {}

    double getConceptDifficulty(){

        double ans = 0;
        double conceptCount = 0;
        for(int i=0;i<20;i++){
            ans += quesBank[this->code[i]].level * quesBank[this->code[i]].conceptList.size();
            conceptCount += quesBank[this->code[i]].conceptList.size();
        }
        ans = ans/conceptCount;
        return ans;

    }

    double getAccuracy(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += quesBank[this->code[i]].accuracy;
        }
        ans /= 20;
        ans = 100.0 - ans;
        ans = ACCURACY_WT * ans;
        return ans;
    }

    double getWasteful(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += quesBank[this->code[i]].wasteful;
        }
        ans /= 20;
        ans = WASTEFUL_WT * ans;
        return ans;
    }

    double getUseful(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += quesBank[this->code[i]].useful;
        }
        ans /= 20;
        ans = 100.0 - ans;
        ans = USEFUL_WT * ans;
        return ans;
    }

    double getOverTime(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += quesBank[this->code[i]].overTime;
        }
        ans /= 20;
        ans = OVERTIME_WT * ans;
        return ans;
    }

    double getSkipRate(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += quesBank[this->code[i]].skipRate;
        }
        ans /= 20;
        ans = SKIPRATE_WT * ans;
        return ans;
    }

    double getUserRating(){
        double ans = 0;
        for(int i=0;i<20;i++){
            ans += quesBank[this->code[i]].userRating;
        }
        ans /= 20;
        ans = USERRATING_WT * ans;
        return ans;
    }

    double getAvgScore(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += quesBank[this->code[i]].avgScore;
        }
        ans /= 20;
        ans = AVGSCORE_WT * ans;
        return ans;
    }

    double getAvgTime(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += quesBank[this->code[i]].avgTime;
        }
        ans /= 20;
        ans = AVGTIME_WT * ans;
        return ans;
    }
    double getAttemptDifficulty(){
        double ans = 0;
        ans += this->getAvgTime();
        ans += this->getAvgScore();
        ans += this->getUserRating();
        ans += this->getSkipRate();
        ans += this->getUseful();
        ans += this->getWasteful();
        ans += this->getOverTime();
        ans += this->getAccuracy();
        ans /= 8;
        return ans;
    }
    void calculateFitness(){
        double fa = CD_WT * getConceptDifficulty() + AD_WT * getAttemptDifficulty();
        double fb = DD;
        double F = abs(fa - fb);
        this->fitness = ((double)1)/F;
    }

};


vector< Encoding > chromosome(POPULATION_SIZE);

// POPULATION INITIALIZATION

void init(double d){
    srand(time(NULL));
    DD = d;
    for(int i=0;i<POPULATION_SIZE;i++){
        for(int j=0;j<20;j++){
            chromosome[i].code[j] = rand() % 1000;
        }
        chromosome[i].calculateFitness();
    }
}
// SELECTION

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

    for (int i = 0; i < POPULATION_SIZE; i++) {
        offset += chromosome[i].probability;
        if (rndNumber < offset) {
            pick = i;
            break;
        }
}
    return pick;
}
// CROSSOVER
void getCrossover(int a,int b){
    for(int i=0;i<20;i++){
        if(i & 1){
            chromosome[a].code[i] = chromosome[b].code[i];
        }
        else
        {
            chromosome[b].code[i] = chromosome[a].code[i];
        }
    }
    chromosome[a].calculateFitness();
    chromosome[b].calculateFitness();
}

void crossover(double PC){
    double CROSSOVER_SIZE = 0;
    while(CROSSOVER_SIZE <= PC*POPULATION_SIZE){
        int a = selection();
        int b = selection();
        getCrossover(a,b);
        CROSSOVER_SIZE ++;
    }
}

// MUTATION
void getMutation(int a,int x){
    chromosome[a].code[x] = rand() % 1000;
    chromosome[a].calculateFitness();
}

void mutation(double PM){
    srand((unsigned)time(NULL));
    double MUTATION_SIZE = 0;
    while(MUTATION_SIZE <= PM*POPULATION_SIZE){
        int a = selection();
        getMutation(a,rand()%20);
        MUTATION_SIZE++;
    }
}


int main(){
    init(60.00);
    // NXG is the no of generations.
    // We try for different values of NXG till inflection is reached.
    // That NXG will be reached when the average fitness of the population becomes more or less constant.
    // Initially we take NXG as 1000.
    int NXG = 1000;

    for(int i=0;i<NXG;i++){
        //Crossover with probability 0.5
        crossover(0.5);
        //Mutation with probability 0.05
        mutation(0.05);
    }
    //Final solution has highest fitness.
    double SOL_FIT = 0;
    Encoding solution;
    for(int i=0;i<POPULATION_SIZE;i++){
        if(chromosome[i].fitness > SOL_FIT){
            solution = chromosome[i];
        }
    }
}
