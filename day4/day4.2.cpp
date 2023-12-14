#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cmath>
#include <vector>

using namespace std;

int main(){
    ifstream file("../input/input_day4.txt");
    string line, temp;
    int sum = 0;
    vector<int> num_matches, individual_cards;

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
        num_matches.push_back(matches);
        individual_cards.push_back(1);
    }

    // go thru the matches array to calculate how many extra cards you won
    for(int i=0; i < individual_cards.size(); i++){
        for(int j=i+1; j <= i+num_matches[i]; j++){
            individual_cards[j] += individual_cards[i];
        }
        sum += individual_cards[i];
    }

    cout << sum << endl;

    return 0;
}