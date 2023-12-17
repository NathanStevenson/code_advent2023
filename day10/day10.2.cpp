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
    // manually determine what piece S shoud be 
    tube_map[start_pos] = '7';    

    // continually loop until BFS is empty, the tube connects no more places to go, last "cur_depth" is the answer
    while(!bfs.empty()){
        // get the current position/depth of tube
        int cur_position = bfs.front(), cur_depth = pos_info_map.at(cur_position);
        bfs.pop();
        // get top/bottom/left/right positions
        int top_pos = cur_position-line_size, bot_pos = cur_position+line_size, right_pos = cur_position+1, left_pos = cur_position-1;
        
        auto it_top   = pos_info_map.find(top_pos);
        auto it_bot   = pos_info_map.find(bot_pos);
        auto it_left  = pos_info_map.find(left_pos);
        auto it_right = pos_info_map.find(right_pos);
        
        // F (bottom/right) | L (top/right) | 7 (bottom/left) | J (top/left) | | (bottom/top) | - (left/right)
        if(tube_map[cur_position] == 'F'){ 
            if(it_bot == pos_info_map.end())   { pos_info_map.insert(make_pair(bot_pos, cur_depth+1));       bfs.push(bot_pos);   }
            if(it_right == pos_info_map.end()) { pos_info_map.insert(make_pair(right_pos, cur_depth+1));     bfs.push(right_pos); }
        }
        // L
        else if(tube_map[cur_position] == 'L'){ 
            if(it_top == pos_info_map.end())   { pos_info_map.insert(make_pair(top_pos, cur_depth+1));       bfs.push(top_pos);   }
            if(it_right == pos_info_map.end()) { pos_info_map.insert(make_pair(right_pos, cur_depth+1));     bfs.push(right_pos); }
        }
        // J
        else if(tube_map[cur_position] == 'J'){ 
            if(it_top == pos_info_map.end())   { pos_info_map.insert(make_pair(top_pos, cur_depth+1));       bfs.push(top_pos);   }
            if(it_left == pos_info_map.end())  { pos_info_map.insert(make_pair(left_pos, cur_depth+1));      bfs.push(left_pos);  }
        }
        // 7
        else if(tube_map[cur_position] == '7'){ 
            if(it_bot == pos_info_map.end())   { pos_info_map.insert(make_pair(bot_pos, cur_depth+1));       bfs.push(bot_pos);   }
            if(it_left == pos_info_map.end())  { pos_info_map.insert(make_pair(left_pos, cur_depth+1));      bfs.push(left_pos);  }
        }
        // |
        else if(tube_map[cur_position] == '|'){ 
            if(it_bot == pos_info_map.end())   { pos_info_map.insert(make_pair(bot_pos, cur_depth+1));       bfs.push(bot_pos);   }
            if(it_top == pos_info_map.end())   { pos_info_map.insert(make_pair(top_pos, cur_depth+1));       bfs.push(top_pos);   }
        }
        // -
        else if(tube_map[cur_position] == '-'){ 
            if(it_left == pos_info_map.end())  { pos_info_map.insert(make_pair(left_pos, cur_depth+1));      bfs.push(left_pos);  }
            if(it_right == pos_info_map.end()) { pos_info_map.insert(make_pair(right_pos, cur_depth+1));     bfs.push(right_pos); }
        }
        else{ continue; }
        
        // if at the end the Q is empty then we know that this is the last element, print cur_depth
        if(bfs.empty()){ cout << cur_depth << endl; }
    }

    // we have the tube map string and a hashmap of whether a piece is in the pipe
    // go thru the string with the inloop boolean set to false and any |, F, J, L, 7 can change it
    // Any | flips it from, a 7 when the last character was a L changes, and J when last was F
    // I, F, L can be treated as opener and I, J, 7 as closers. Do not want to flip for L-J or F-7 bc if we were already within the loop
    // we still will be once we are done for both. However for L-7 and F-J we will either go from out of loop into or into loop then out
    bool in_loop = false;
    int total_area = 0;
    char prev_corner;
    // hardcoded but the starting position 'S' should be a 7
    for(int i=0; i < map_size; i++){

        // if in loop and the piece is not in the hash map then increment
        auto it = pos_info_map.find(i);
        if (in_loop && it == pos_info_map.end()){
            total_area++;
        }
        
        // flip the boolean on any of these conditions
        if(it != pos_info_map.end()){
            if(tube_map[i] == '|' || (tube_map[i] == '7' && prev_corner == 'L') || (tube_map[i] == 'J' && prev_corner == 'F')){
                in_loop = !in_loop;
            }
        }

        // track the previous corner piece
        if(tube_map[i] == '7' || tube_map[i] == 'L' || tube_map[i] == 'J' || tube_map[i] == 'F'){
            prev_corner = tube_map[i];
        }
    } 

    cout << total_area << endl;
    
    return 0;
}