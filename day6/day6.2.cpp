#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(){
    fstream file("../input/input_day6.txt");
    string line, temp, time, distance;
    int count = 0;
    long long num_time = 0, num_distance = 0;

    // read file into time and distance values
    while(getline(file, line)){
        stringstream ss (line);
        ss >> temp;
        if(temp == "Time:"){
            while(ss >> temp){ time += temp; }
            num_time = stoll(time);
        }else{
            while(ss >> temp){ distance += temp; }
            num_distance = stoll(distance);
        }
    }

    // iterate thru the different possibilites depending on how much time you hold the button
    for(long long i=0; i < num_time; i++){
        long long your_dist = (num_time - i) * i;
        // holds symmetric properties
        if(your_dist > num_distance){
            int num_ways = num_time - 2*i + 1;
            cout << num_ways << endl;
            break;
        }
    }

    return 0;
}