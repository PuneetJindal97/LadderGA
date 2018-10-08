#include <bits/stdc++.h>
#include <fstream>
using namespace std;

string feature_set[] = {"difficulty","accuracy","concepts_list","wasteful_attempts","useful_attempts",
              "overtime_attempts","avg_attempt_time","skip_rate","avg_score","user_rating"};
class gene{
    public:
        double difficulty;
        double accuracy;
        vector< string > conceptList;
        double wasteful;
        double useful;
        double overTime;
        double avgTime;
        double skipRate;
        double avgScore;
        double userRating;
        
        void print()
        {
        	cout<<this->difficulty<<" ";
        	cout<<this->accuracy<<" ";
        	cout<<this->wasteful<<" ";
        	cout<<this->useful<<" ";
        	cout<<this->overTime<<" ";
        	cout<<this->avgTime<<" ";
        	cout<<this->skipRate<<" ";
        	cout<<this->avgScore<<" ";
        	cout<<this->userRating<<" ";
        	for(int i=0;i<this->conceptList.size();i++)
        	cout<<this->conceptList[i]<<" ";
        	cout<<"\n";
		}
};
int main() {
	// your code goes here
	ifstream file1;
	file1.open("chromosome3.txt");
	
	string s1="";
	vector<gene> quesBank;
	
	int cnt=0;
	while(!file1.eof())
	{
		gene g1;
		file1>>s1;
		g1.difficulty = stod(s1);
		file1>>s1;
		g1.accuracy = stod(s1);
		file1>>s1;
		int g = stoi(s1);
		for(int k=0;k<g;k++)
		{
			file1>>s1;
			g1.conceptList.push_back(s1);
		}
		file1>>s1;
		g1.wasteful = stod(s1);
		file1>>s1;
		g1.useful = stod(s1);
		file1>>s1;
		g1.overTime = stod(s1);
		file1>>s1;
		g1.avgTime = stod(s1);
		file1>>s1;
		g1.skipRate = stod(s1);
		file1>>s1;
		g1.avgScore = stod(s1);
		file1>>s1;
		g1.userRating = stod(s1);
		
		quesBank.push_back(g1);
//		cnt++;
//		if(cnt==20)
//		{
//			solutions.push_back(ladder);
//			ladder.clear();
//			cnt=0;
//		}
	}
	
	//cout<<quesBank.size()<<" ";
	for(int i=0;i<quesBank.size()-1;i++)
	{
		quesBank[i].print();
	}
//	for(int i=0;i<solutions.size();i++)
//	{
//		for(int j=0;j<solutions[i].size();j++)
//		{
//			gene g2 = solutions[i][j];
//			g2.print();
//		}
//	}


	return 0;
}
