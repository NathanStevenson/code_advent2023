#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>

using namespace std;

int main(){
    fstream file("../input/input_day8.txt");
    string line, temp, directions, start, left, right;
    unordered_map <string, vector<string> > desert_map;
    // put the first line of the file into directions
    getline(file, directions);

    while(getline(file, line)){
        stringstream ss(line);
        vector <string> left_right;
        while(ss >> temp){
            // if length is 3 then it is the starting point
            if(temp.length() == 3){ start = temp; }
            // if length is 5 then it is left direction and is 4 then right direction
            if(temp.length() == 5){ left = temp.substr(1, 3); }
            if(temp.length() == 4){ right = temp.substr(0, 3); }
        }
        left_right.push_back(left);
        left_right.push_back(right);
        desert_map.insert(make_pair(start, left_right));
    }

    // start at AAA and then follow the directions and count the steps
    string cur_node = "AAA";
    int num_steps = 0, directions_length = directions.length();

    while(cur_node != "ZZZ"){
        int index = 0;
        // if directions are a L then read from index 0 of vector else read from 1
        if(directions[num_steps % directions_length] == 'L'){ index = 0; }
        else{ index = 1; }

        // update the current node based on decision from directions string, increment number of steps
        cur_node = desert_map.at(cur_node)[index];
        num_steps++;
    }

    cout << num_steps << endl;

    return 0;
}