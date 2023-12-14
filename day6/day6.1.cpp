#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

int main(){
    fstream file("../input/input_day6.txt");
    string line, temp;
    vector<int> times, distances;
    int ways = 1;

    // time and max distance record. track number of potential ways to beat the best record and multiply together in the end
    // each ms button is held your boat goes 1mm/s faster

    // read file into time and distance vectors
    while(getline(file, line)){
        stringstream ss (line);
        ss >> temp;
        if(temp == "Time:"){
            while(ss >> temp){ times.push_back(stoi(temp)); }
        }else{
            while(ss >> temp){ distances.push_back(stoi(temp)); }
        }
    }

    // go thru each vector and total the # of ways you can win, when done go thru array and multiply them
    for(int i=0; i < times.size(); i++){
        int count = 0;
        for(int j = 0; j < times[i]; j++){
            int your_dist = (times[i] - j) * j;
            if(your_dist > distances[i]){
                count++;
            }
            // little optimization, if we are on the descend we can break out early
            if(your_dist < distances[i] && count > 0){ break; }
        }
        ways *= count;
    }
    // output number of ways
    cout << ways << endl;

    return 0;
}