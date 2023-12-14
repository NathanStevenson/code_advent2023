#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iostream>

using namespace std;

// want to go in reverse in part 2
long long transform_num(vector<long long> &map, long long number){
    // dest, src, range
    if(map[0] <= number && number <= map[0]+map[2]){
        return number + (map[1] - map[0]);
    }
    return number;
}

// check if the seed is valid from the seeds array we populated earlier
bool check_seed(vector<long long> &seeds, long long seed_num){
    for(int i=0; i < seeds.size(); i+=2){
        long long base = seeds[i];
        long long bounds = seeds[i+1];
        // if the seed num is within the range
        if(base <= seed_num && seed_num < (base+bounds)){ return true; }
    }
    return false;
}

// WE KNOW THE MINIMUM LOCATION THAT MAPPED PRIOR IS: 84470622. THUS THIS IS NEW MAXIMUM
// WE NEED TO GO FROM 0 to 84470622 (location -> seed), if we find location that maps to seed then break we are done

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

    // start at the end of the map with location 0 and end with location of 84470622
    // start with humidity-to-loc map and work our way back to the first map
    // once we get the seed number check if it is within our bounds we found when first reading in the seeds in the seeds array
    for(long long loc=0; loc < 84470622; loc++){
        long long new_num = loc, old_num = loc;
        // looping thru all maps in reverse
        for(int i=all_maps.size()-1; i >= 1; i--){
            // going thru each map
            for(int j=0; j < all_maps[i].size(); j++){
                new_num = transform_num(all_maps[i][j], old_num);
                // break out of the loop and update old num value, need to break bc we found mapping and we dont want to map and then keep checking in same map
                if(new_num != old_num){
                    old_num = new_num;
                    break;
                }
            }
        }
        // once we go thru all the maps the new number will now be a seed number and we need to check if valid
        bool is_valid = check_seed(seeds, new_num);
        // if it is valid break out and see what location it is
        if (is_valid){ 
            cout << "Location: " << loc << " | Seed Number: " << new_num << endl;
            break;
        }
    }

    return 0;
}