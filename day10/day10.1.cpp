#include <vector>
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
#include <fstream>

using namespace std;

int main(){
    fstream file("../input/input_day10.txt");
    string line;
    int start_row = 0, counter = 0, start_col = 0, line_size = 0, start_pos = 0, map_size = 0;
    // store the map given to us as one long string that we can index into (+1/-1 to check right/left, +line_size/-line_size to check top/bottom)
    string tube_map = "";
    // If tube piece is in the map then piece has been visited, the value it is mapped to is # steps piece is in the tube (S -> 0...)
    unordered_map<int, int> pos_info_map;
    // queue to perform BFS in order to go down both paths fairly, stores position we are at
    queue<int> bfs;
    // read the file into tube map and find row/col where S is located in the process
    while(getline(file, line)){
        int found = line.find("S");
        if(found != string::npos){ 
            start_row = counter;
            start_col = found;
            line_size = line.size();
        }
        tube_map += line;
        counter++;
    }
    // add S position to the hash map with # steps = 0, and push it to queue
    start_pos = (start_row*line_size) + start_col;
    pos_info_map.insert(make_pair(start_pos, 0));
    bfs.push(start_pos);
    map_size = tube_map.size();

    /*              - Each pipe can only connect to two other pipes (one of which it came from, will be in hashmap)
        1 2 3       - Valid pieces for 2 (top): "|", "7", "F"
        4 X 5       - Valid pieces for 5 (right): "-", "7", "J"
        6 7 8       - Valid pieces for 7 (bottom): "|", "L", "J"
                    - Valid pieces for 4 (left): "-", "L", "F"
    */
    // continually loop until BFS is empty, the tube connects no more places to go, last "cur_depth" is the answer
    while(!bfs.empty()){
        // get the current position/depth of tube
        int cur_position = bfs.front(), cur_depth = pos_info_map.at(cur_position);
        bfs.pop();
        // get top/bottom/left/right positions
        int top_pos = cur_position-line_size, bot_pos = cur_position+line_size, right_pos = cur_position+1, left_pos = cur_position-1;
        // check top, bottom, left, and right
        auto it_top = pos_info_map.find(top_pos);
        // if not in hashmap and is within string bounds then check if it is a valid piece
        if(it_top == pos_info_map.end() && top_pos >= 0){
            if(tube_map[top_pos] == '|' || tube_map[top_pos] == '7' || tube_map[top_pos] == 'F'){
                bfs.push(top_pos);
                pos_info_map.insert(make_pair(top_pos, cur_depth+1));
            }
        }

        auto it_bot = pos_info_map.find(bot_pos);
        // if not in hashmap and is within string bounds then check if it is a valid piece
        if(it_bot == pos_info_map.end() && bot_pos < map_size){
            if(tube_map[bot_pos] == '|' || tube_map[bot_pos] == 'L' || tube_map[bot_pos] == 'J'){
                bfs.push(bot_pos);
                pos_info_map.insert(make_pair(bot_pos, cur_depth+1));
            }
        }

        auto it_right = pos_info_map.find(right_pos);
        // if not in hashmap and is within string bounds then check if it is a valid piece
        if(it_right == pos_info_map.end() && right_pos < map_size){
            if(tube_map[right_pos] == '-' || tube_map[right_pos] == '7' || tube_map[right_pos] == 'J'){
                bfs.push(right_pos);
                pos_info_map.insert(make_pair(right_pos, cur_depth+1));
            }
        }

        auto it_left = pos_info_map.find(left_pos);
        // if not in hashmap and is within string bounds then check if it is a valid piece
        if(it_left == pos_info_map.end() && left_pos >= 0){
            if(tube_map[left_pos] == '-' || tube_map[left_pos] == 'L' || tube_map[left_pos] == 'F'){
                bfs.push(left_pos);
                pos_info_map.insert(make_pair(left_pos, cur_depth+1));
            }
        }
        // if at the end the Q is empty then we know that this is the last element, print cur_depth
        if(bfs.empty()){ cout << cur_depth << endl; }
    }
    
    return 0;
}