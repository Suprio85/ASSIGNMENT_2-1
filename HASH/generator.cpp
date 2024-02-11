#include<bits/stdc++.h>
using namespace std;

#define test_num 10000

class generator {


public :

generator(){
    //srand(time(0));
}

int random_size(){
    return rand()%6+5;
}

string random_string(){
    int size = random_size();
    string s;
    for(int i=0;i<size;i++){
        s.push_back('a'+rand()%26);
    }
    return s;   
}

vector<string> unique_data(){
    vector<string> data;

    int uniqueCounter = 0;  
    while(uniqueCounter<test_num){
        string s = random_string();
        if(find(data.begin(),data.end(),s)==data.end()){
            data.push_back(s);
            uniqueCounter++;
        }
        else{
          //  cout<<"Duplicate found and negleted"<<endl;
        }
    }
    return data;
}

};

// int main(){
//     freopen("out.txt","w",stdout);
//     generator g;
//     vector<string> data = g.unique_data();
//     for(int i=0;i<test_num;i++){
//         cout<<data[i]<<"  "<<i+1<<endl;
//     }
// }