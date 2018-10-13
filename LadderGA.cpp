#include <bits/stdc++.h>

using namespace std;
const int POPULATION_SIZE = 500;
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
double MAX_FITNESS;
double MIN_FITNESS;

class gene{
    public:
        double level;
        double accuracy;
        vector< string > conceptList;
        double wasteful;
        double useful;
        double overTime;
        double avgTime;
        double skipRate;
        double avgScore;
        double userRating;

};

vector< gene > quesBank(1000);

class Encoding{
    public:
    double fitness;
    double fb;
    double fa;
    double F;
    vector< int > code;
    double probability;
    Encoding() : code(20), fitness(0), fa(0), fb(0), F(0), probability(0) {}

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
        ans = 100.0 - ans;
        ans = USERRATING_WT * ans;
        return ans;
    }

    double getAvgScore(){

        double ans = 0;
        for(int i=0;i<20;i++){
            ans += quesBank[this->code[i]].avgScore;
        }
        ans /= 20;
        ans  = 100.0 - ans;
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
        fa = CD_WT * getConceptDifficulty() + AD_WT * getAttemptDifficulty();
        fb = DD;
        F = abs(fa - fb);
        fitness = ((double)1)/F;
    }
};


vector< Encoding > chromosome(POPULATION_SIZE);

// POPULATION INITIALIZATION

void init(double d){
    //srand(time(NULL));
    srand(time(NULL));
    freopen("Input.txt", "r", stdin);
    int conceptNumber;
    for(int i=0;i<1000;i++){
        cin >> quesBank[i].level;
        cin >> quesBank[i].accuracy;
        cin >> conceptNumber;
        for(int j=0;j<conceptNumber;j++){
            string sin;
            cin >> sin;
            quesBank[i].conceptList.push_back(sin);
        }
        cin >> quesBank[i].wasteful;
        cin >> quesBank[i].useful;
        cin >> quesBank[i].overTime;
        cin >> quesBank[i].avgTime;
        cin >> quesBank[i].skipRate;
        cin >> quesBank[i].avgScore;
        cin >> quesBank[i].userRating;
    }

    DD = d;
    for(int i=0;i<POPULATION_SIZE;i++){
        for(int j=0;j<20;j++){
            chromosome[i].code[j] = rand() % 1000;

        }
        chromosome[i].calculateFitness();
    }
}
// SELECTION

int getSelection(){
    double rndNumber = rand() / (double) RAND_MAX;
    double offset = 0.0;
    int pick = 0;

    for (int i = 0; i < POPULATION_SIZE; i++) {
        offset += chromosome[i].probability;
        if (rndNumber < offset) {
            pick = i;
            break;
        }
    }
    return pick;
}

void selection(){
    double totalFitness=0;
    double totalProbability=0;
    double probability=0;
    for(int i=0;i<POPULATION_SIZE;i++){
        totalFitness += chromosome[i].fitness;
    }

    for(int i=0;i<POPULATION_SIZE;i++){
        chromosome[i].probability = chromosome[i].fitness/totalFitness;
    }
    vector< Encoding > tocopy(POPULATION_SIZE);
    for(int i = 0;i < POPULATION_SIZE;i++){
        int pick = getSelection();
        tocopy[i] = chromosome[pick];
    }
     for(int i = 0;i < POPULATION_SIZE;i++){
        chromosome[i] = tocopy[i];
    }
}
// CROSSOVER
void getCrossover(int a,int b){
    int pt = rand() % 20;
    for(int i=0;i<pt;i++){
        swap(chromosome[a].code[i],chromosome[b].code[i]);
    }
    chromosome[a].calculateFitness();
    chromosome[b].calculateFitness();
}

void crossover(double PC){
    for(int i = 0;i < POPULATION_SIZE;i += 2){
        double rndNumber = rand() / (double) RAND_MAX;
        if(rndNumber <= PC){
            getCrossover(i,i+1);
        }
    }
}

// MUTATION
void getMutation(int a,double PM){
    for(int i=0;i<20;i++){
        double rndNumber = rand() / (double) RAND_MAX;
        if(rndNumber <= PM){
            chromosome[a].code[i] = rand() % 1000;
        }
    }
    chromosome[a].calculateFitness();
}

void mutation(double PM){
    for(int i = 0;i < POPULATION_SIZE;i ++){
        getMutation(i,PM);
    }

}


class CSVWriter{
	string fileName;
	string delimiter;
	int linesCnt;

	public :
	CSVWriter(string filename,string delim=",") : fileName(filename), delimiter(delim), linesCnt(0) {}

	template<typename T>
	void addDataInRow(T first,T last);
};

template<typename T>
void CSVWriter::addDataInRow(T first,T last){
	fstream file;
	file.open(fileName,ios::out | (linesCnt ? ios::app : ios::trunc));

	for(;first!=last;)
	{
		file << *first;
		if(++first!=last)
		{
			file << delimiter;
		}
		file << "\n";
	}
	//file << "\n";
	linesCnt++;
	file.close();
}









int main(){
    int NXG;
    cin >> NXG;
    CSVWriter writer("Gen_avg_data.csv");
	CSVWriter writer2("Gen_max_data.csv");

	vector<double> gen_avg(NXG+1),gen_max(NXG+1);

	for(int iter = 0;iter < 50; iter++){
        init(50.00);
        // NXG is the no of generations.
        // We try for different values of NXG till inflection is reached.
        // That NXG will be reached when the average fitness of the population becomes more or less constant.
        // Initially we take NXG as 1000.
        Encoding pbest;
        int best,worst;
        MAX_FITNESS = 0;
        MIN_FITNESS = (double)(INT_MAX);

        double sum_init = 0.0;
        for(int j=0;j<POPULATION_SIZE;j++){
                if(chromosome[j].fitness > MAX_FITNESS){
                     best = j;
                     MAX_FITNESS = chromosome[j].fitness;
                }
                if(chromosome[j].fitness < MIN_FITNESS){
                    worst = j;
                    MIN_FITNESS = chromosome[j].fitness;
                }
                sum_init+=chromosome[j].fitness;
        }
        double avg_init = sum_init/POPULATION_SIZE;
        pbest = chromosome[best];

        //cout << avg_init << "\t" << pbest.fitness << "\n";

        gen_max[0] += pbest.fitness;
        gen_avg[0] += avg_init;

        for(int i=1;i<=NXG;i++){
            //Selection of mating pool
            selection();
            //Crossover with probability 0.5
            crossover(0.5);
            //Mutation with probability 0.05
            mutation(0.05);

            MAX_FITNESS = 0;
            MIN_FITNESS = (double)(INT_MAX);
            double ans = 0;
            double sum = 0;
            for(int j=0;j<POPULATION_SIZE;j++){

                if(chromosome[j].fitness > MAX_FITNESS){
                    best  = j;
                    MAX_FITNESS = chromosome[j].fitness;
                }
                if(chromosome[j].fitness < MIN_FITNESS){
                    worst = j;
                    MIN_FITNESS = chromosome[j].fitness;
                }
                sum += chromosome[j].fitness;
            }
            ans = sum/POPULATION_SIZE;
            //if(pbest.fitness > chromosome[best].fitness){
                chromosome[worst] = pbest;
            //}
            //else{
                if(pbest.fitness < chromosome[best].fitness)
                    pbest = chromosome[best];
            //}
            gen_max[i] += pbest.fitness;
            gen_avg[i] += ans;
            //cout << ans << "\t" << pbest.fitness << "\n";
        }
	}
	for(int i=0;i<=NXG;i++){
        gen_max[i] /= 50.0;
        gen_avg[i] /= 50.0;
	}
    writer.addDataInRow(gen_avg.begin(),gen_avg.end());
    writer2.addDataInRow(gen_max.begin(),gen_max.end());
}
