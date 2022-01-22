#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string fn,vector<string> &name,vector<int> &score,vector<char> &grade){
    string text;
    char format[] = "%[^:]: %d %d %d";
    int a,b,c,total;
    char n[100];
    ifstream source(fn);
    while(getline(source,text)){
        sscanf(text.c_str(),format,n,&a,&b,&c);
        total = a+b+c;
        score.push_back(total);
        grade.push_back(score2grade(total));
        name.push_back(n);
    }
    source.close();
}

void getCommand(string &c,string &k){
    string input;
    cout << "Please input your command: ";
    getline(cin,input);
    int idx = input.find_first_of(" ");
    c = input.substr(0,idx);
    k = input.substr(idx+1);
}

void searchName(vector<string> name,vector<int> score,vector<char> grade,string k){
    bool has = false;
    cout << "---------------------------------\n";
    for(unsigned int i=0 ; i<name.size() ; i++){
        if(k==toUpperStr(name[i])){
            printf("%s's score = %d\n",name[i].c_str(),score[i]);
            printf("%s's grade = %c\n",name[i].c_str(),grade[i]);
            has = true;
        }
    }
    if(!has) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> name,vector<int> score,vector<char> grade,string k){
    bool has = false;
    cout << "---------------------------------\n";
    for(unsigned int i=0 ; i<grade.size() ; i++){
        if(*k.c_str()==grade[i]){
            printf("%s (%d)\n",name[i].c_str(),score[i]);
            has = true;
        }
    }
    if(!has) cout << "Cannot found.\n";
    cout << "---------------------------------\n";
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}