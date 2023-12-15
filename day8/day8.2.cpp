#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <numeric>
using namespace std;

int main(){
    fstream file("../input/input_day8.txt");
    string line, temp, directions, start, left, right;
    unordered_map <string, vector<string> > desert_map;
    vector<string> cur_nodes;
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
        // if it ends with "A" then it is a starting node (add it to list)
        if(start[2] == 'A'){ cur_nodes.push_back(start); }
        left_right.push_back(left);
        left_right.push_back(right);
        desert_map.insert(make_pair(start, left_right));
    }

    // start at AAA and then follow the directions and count the steps
    int num_finished = 0;
    int num_steps = 0, directions_length = directions.length();
    int node_size = cur_nodes.size();

    vector<int> cycle_time(node_size);
    
    while(num_finished != node_size){
        int index = 0;
        // if directions are a L then read from index 0 of vector else read from 1
        if(directions[num_steps % directions_length] == 'L'){ index = 0; }
        else{ index = 1; }
        num_steps++;
        // update each nodes position based on decision from directions string, increment number of steps
        for(int i=0; i < cur_nodes.size(); i++){
            cur_nodes[i] = desert_map.at(cur_nodes[i])[index];
            // if last digit of a new node we havent seen finished before is 'Z' track it and add num_steps to array

            // WE ARE TRACKING THE NUMBER OF STEPS IT TAKES FOR EACH ONE TO GET TO ITS ENDPOINT
            // THIS IS EXACTLY ONE CYCLE, CYCLES ALL HAVE SAME NUM_STEPS. Once answer for all then find LCM of cycles
            if(cur_nodes[i][2] == 'Z' && cycle_time[i] == 0){ 
                cycle_time[i] = num_steps;
                num_finished++;
            }
        }
    }

    // for all to finish at the same time each cycle must complete together (find LCM of array)
    // first level
    long long lcm1 = lcm(cycle_time[0], cycle_time[1]);
    long long lcm2 = lcm(cycle_time[2], cycle_time[3]);
    long long lcm3 = lcm(cycle_time[4], cycle_time[5]);

    // 2nd level
    long long mid_lcm = lcm(lcm1, lcm2);
    // final
    long long final = lcm(mid_lcm, lcm3);

    cout << final << endl;

    return 0;
}