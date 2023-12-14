#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(){
    // starting params
    string line, temp;
    ifstream file("../input/input_day2.txt");

    int sum = 0, cubes = 0;
    
    // read file line by line, put into stringstream to separate on spaces
    while(getline(file, line)){
        stringstream ss(line);
        // store the game number
        ss >> temp;
        ss >> temp;
        int game_num = stoi(temp);
        int valid = 0;

        while(ss >> temp){
            // if it is a number get it and then see if it violates max
            if(isdigit(temp[0])){
                cubes = stoi(temp);
            }
            ss >> temp;
            string color = temp;
            // check
            if(color[0] == 'r'){ valid = cubes <= 12; }
            if(color[0] == 'g'){ valid = cubes <= 13; }
            if(color[0] == 'b'){ valid = cubes <= 14; }

            if (valid == 0){ break; }
        }
        sum += game_num * valid;
    }

    cout << sum << endl;

    // close file
    file.close();

    return 0;
}