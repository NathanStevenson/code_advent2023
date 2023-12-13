#include <iostream>
#include <vector>
#include <string>
#include <fstream>

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

// function that determine if the number is adjacent to a non-digit or non-period
bool is_adj(vector<string> &map, int index, int row, int length){
    bool top = 0, bottom = 0, left = 0, right = 0;
    // starting index is whatever is greater
    int start = (index - 1 >= 0) ? index-1 : 0;
    int end = (index + length < map[row].length()) ? index+length : map[row].length()-1;
    // check if special part is in row above
    if(row-1 >= 0){
        for(int i=start; i <= end; i++){
            // found special char
            if (map[row-1][i] != '.' && !isdigit(map[row-1][i]))  { top = 1; }
        }
    }

    // check if special part is in row below
    if(row+1 < map.size()){
        for(int i=start; i <= end; i++){
            // found special char
            if (map[row+1][i] != '.' && !isdigit(map[row+1][i]))  { bottom = 1; }
        }
    }

    // check if special part is in col to left
    if (map[row][start] != '.' && !isdigit(map[row][start]))      { left = 1; }

    // check if special part is in col to right
    if (map[row][end] != '.' && !isdigit(map[row][end]))          { right = 1; }


    return top || bottom || left || right;
}

int main(){
    ifstream file("./input/input_day3.txt");
    string line;
    int sum = 0;
    vector<string> part_map;

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
                bool is_part = is_adj(part_map, j, i, length);
                cout << number << ": " << is_part << endl;
                sum += is_part * number;

                // incr j accordingly
                j += length;
            }
        }
    }

    cout << sum << endl;

    return 0;
}