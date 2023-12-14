#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

// take number and map and see if number can be transformed, if not leave return current value
long long transform_num(vector<long long> &map, long long number){
    // dest, src, range
    if(map[1] <= number && number <= map[1]+map[2]){
        //cout << number << ": " << map[0] << " " << map[1] << "|" << (number + (map[0] - map[1])) << endl;
        return number + (map[0] - map[1]);
    }
    return number;
}

int main(){
    string line, temp;
    fstream file("../input/input_day5.txt");
    vector <long long> seeds;
    vector< vector< vector <long long> > > all_maps;
    vector< vector< long long> > cur_map;
    long long minimum = LLONG_MAX;

    // read the file and load the 
    while (getline(file, line)){
        stringstream ss(line);
        temp = "";
        ss >> temp;

        if(temp == "seeds:"){
            while(ss >> temp){
                seeds.push_back(stoll(temp));
            }
        }

        // if first char is not a digit then append old map to all_maps and empty old map
        else if(!isdigit(temp[0]) && temp != ""){
            all_maps.push_back(cur_map);
            cur_map = {};
        }
        // else the first char is a digit and we know that this is useful info
        else if(isdigit(temp[0])){
            vector<long long> range_info;
            range_info.push_back(stoll(temp));
            while(ss >> temp){
                range_info.push_back(stoll(temp));
            }
            cur_map.push_back(range_info);
        }
        else{ continue; }
    }

    // pass each seed thru all of the maps to get its final location, once loop is done then all final locs will be in seeds array
    for(int seed=0; seed < seeds.size(); seed++){

        // loop thru the map and call the function to transform each seed into a location
        // all_maps[i] --> individual map, all_maps[i][j] --> individual src to dest vector
        for(int i=1; i < all_maps.size(); i++){
            // grab the updated seed num between each map
            long long seed_num = seeds[seed];

            for(int j=0; j < all_maps[i].size(); j++){
                long long map_seed_num = transform_num(all_maps[i][j], seed_num);
                seeds[seed] = map_seed_num;
                // once a map transforms it break and go to the next map
                if(map_seed_num != seed_num){ 
                    break;
                }
            }
        }
        // once done track the minimum number
        if(seeds[seed] < minimum){
            minimum = seeds[seed];
        }
    }
    cout << minimum << endl;

    return 0;
}