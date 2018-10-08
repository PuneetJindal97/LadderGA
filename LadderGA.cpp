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

class gene{
    public:
        int level;
        int accuracy;
        int wasteful;
        int useful;
        int overTime;
        int skipRate;
        int avgScore;
        int userRating;
        int avgTime;
        vector< string > conceptList;
};

class Encoding{
    public:
    double fitness;
    vector<gene> code;
    double probability;
    Encoding() : code(20), fitness(0), probability(0) {}

    double getConceptDifficulty(){

        double ans = 0;
        double conceptCount = 0;
        for(int i=0;i<20;i++){
            ans += this->code[i].level * this->code[i].conceptList.size();
            conceptCount += this->code[i].conceptList.size();
        }
        ans = ans/conceptCount;
        ans = ans * 10;
        return ans;

    }

    double getAccuracy(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += this->code[i].accuracy;
        }
        ans /= 20;
        ans = 100 - ans;
        ans = ACCURACY_WT * ans;
        return ans;
    }

    double getWasteful(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += this->code[i].wasteful;
        }
        ans /= 20;
        ans = WASTEFUL_WT * ans;
        return ans;
    }

    double getUseful(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += this->code[i].useful;
        }
        ans /= 20;
        ans = 100 - ans;
        ans = USEFUL_WT * ans;
        return ans;
    }

    double getOverTime(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += this->code[i].overTime;
        }
        ans /= 20;
        ans = OVERTIME_WT * ans;
        return ans;
    }

    double getSkipRate(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += this->code[i].skipRate;
        }
        ans /= 20;
        ans = SKIPRATE_WT * ans;
        return ans;
    }

    double getUserRating(){
        double ans = 0;
        for(int i=0;i<20;i++){
            ans += this->code[i].userRating;
        }
        ans /= 20;
        ans = USERRATING_WT * ans;
        return ans;
    }

    double getAvgScore(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += this->code[i].avgScore;
        }
        ans /= 20;
        ans = AVGSCORE_WT * ans;
        return ans;
    }

    double getAvgTime(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += this->code[i].avgTime;
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
        this->fitness = CD_WT * getConceptDifficulty() + AD_WT * getAttemptDifficulty();
    }

};


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

    for (int i = 0; i < POPULATION_SIZE; i++) {
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
