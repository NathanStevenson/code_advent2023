#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cmath>

using namespace std;

int main(){
    ifstream file("./input/input_day4.txt");
    string line, temp;
    int sum = 0;

    while(getline(file, line)){
        stringstream ss (line);
        unordered_map<int, int> winning_nums;
        // remove card info
        ss >> line;
        ss >> line;
        int matches = 0;
        
        // flag is 0 add to winning, flag is 1 add to your nums
        bool flag = 0;
        // unload the ss
        while (ss >> temp){
            // if it is the bar adjust the flag and continue on
            if(temp == "|"){
                flag = 1;
                continue;
            }
            // insert the number into the hash table if winning num
            if(!flag){ winning_nums.insert(make_pair(stoi(temp), 1)); }

            // check if your number is a winner
            else{ 
                auto it = winning_nums.find(stoi(temp));
                // if matches winning
                if(it != winning_nums.end()){
                    matches++;
                }
            }
        }
        // after totalling the matches increment the sum by the correct num of matches
        if(matches == 0){ sum += 0; }
        else{ sum += pow(2, (matches-1)); }
    }

    cout << sum << endl;

    return 0;
}