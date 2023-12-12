#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

int main(){
    // starting params
    string line, temp;
    ifstream file("./input/input_day2.txt");

    int sum = 0, cubes = 0;
    
    // read file line by line, put into stringstream to separate on spaces
    while(getline(file, line)){
        stringstream ss(line);
        // store the game number
        ss >> temp;
        ss >> temp;
        int game_num = stoi(temp);
        int red_max = 0, green_max = 0, blue_max = 0;

        while(ss >> temp){
            // if it is a number get it then see if you need to update the current max of cubes
            if(isdigit(temp[0])){
                cubes = stoi(temp);
            }

            // get the next color
            ss >> temp;
            // if color is bigger than current max of color
            if(temp[0] == 'r' && cubes > red_max)  { red_max   = cubes; }
            if(temp[0] == 'g' && cubes > green_max){ green_max = cubes; }
            if(temp[0] == 'b' && cubes > blue_max) { blue_max  = cubes; }
        }
        // total the power sets
        sum += red_max*green_max*blue_max;
    }

    cout << sum << endl;

    // close file
    file.close();

    return 0;
}