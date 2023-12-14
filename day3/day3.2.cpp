#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>

using namespace std;

// function that returns the number
int str_to_int(int index, string &input){
    string number = "";
    while(isdigit(input[index])){
        number += input[index];
        index++;
    }
    return stoi(number);
}

int num_length(int index, string &input){
    int length = 0;
    while(isdigit(input[index])){
        index++, length++;
    }
    return length;
}

// function that builds hash table mapping int (position of gear) -> vector<int> numbers adj to gear
void is_adj(vector<string> &map, int index, int row, int length, unordered_map<int, vector<int> > &gear_map, int number){
    bool top = 0, bottom = 0, left = 0, right = 0;
    // starting index is whatever is greater
    int start = (index - 1 >= 0) ? index-1 : 0;
    int end = (index + length < map[row].length()) ? index+length : map[row].length()-1;
    vector<int> base = {number};
    // check if special part is in row above
    if(row-1 >= 0){
        for(int i=start; i <= end; i++){
            // found gear
            if (map[row-1][i] == '*')  { 
                int position = (row-1)*map.size() + i;
                // if gear not in map yet insert, otherwise append list
                auto it = gear_map.find(position);
                if(it == gear_map.end()){
                    gear_map.insert(make_pair(position, base));
                }else{
                    (it->second).push_back(number);
                }
            }
        }
    }

    // check if special part is in row below
    if(row+1 < map.size()){
        for(int i=start; i <= end; i++){
            // found special char
            if (map[row+1][i] == '*')  { 
                int position = (row+1)*map.size() + i;
                // if gear not in map yet insert, otherwise append list
                auto it = gear_map.find(position);
                if(it == gear_map.end()){
                    gear_map.insert(make_pair(position, base));
                }else{
                    (it->second).push_back(number);
                }
            }
        }
    }

    // check if special part is in col to left
    if (map[row][start] == '*')        { 
        int position = (row)*map.size() + start;
        // if gear not in map yet insert, otherwise append list
        auto it = gear_map.find(position);
        if(it == gear_map.end()){
            gear_map.insert(make_pair(position, base));
        }else{
            (it->second).push_back(number);
        }   
    }

    // check if special part is in col to right
    if (map[row][end] == '*')          { 
        int position = (row)*map.size() + end;
        // if gear not in map yet insert, otherwise append list
        auto it = gear_map.find(position);
        if(it == gear_map.end()){
            gear_map.insert(make_pair(position, base));
        }else{
            (it->second).push_back(number);
        } 
    }

}


int main(){
    ifstream file("../input/input_day3.txt");
    string line;
    int sum = 0;
    vector<string> part_map;
    unordered_map<int, vector<int> > gear_map;

    // read file into an array of strings
    while(getline(file, line)){ 
        part_map.push_back(line);
    }
    file.close();

    for (int i=0; i < part_map.size(); i++){
        // scan thru and look for first number
        for (int j=0; j < part_map[i].length(); j++){
            int number = 0, length = 0;
            // if you see a number extract the number and figure out its length
            if (isdigit(part_map[i][j])){
                length = num_length(j, part_map[i]);
                number = str_to_int(j, part_map[i]);

                // once you know the length of the number determine whether it is valid
                is_adj(part_map, j, i, length, gear_map, number);

                // incr j accordingly
                j += length;
            }
        }
    }

    // check the contents of the hashmap
    for(auto it = gear_map.begin(); it != gear_map.end(); it++){
        if((it->second).size() == 2){
            sum += it->second[0] * it->second[1];
        }
    }

    cout << sum << endl;

    return 0;
}