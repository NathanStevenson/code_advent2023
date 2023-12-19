#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

using namespace std;

int main(){
    fstream file("../input/input_day11.txt");
    string line;
    int num_galaxies = 0, num_galaxies_row = 0, row_count = 0;
    // vectors to track rows and columns without galaxies (hard coded num_cols easily soft-coded if read one line), vector is hashmap like
    vector<int> empty_rows(140), empty_cols(140, 1); 
    // vector of vector<int>, where each index is (row, col) of position of galaxy
    vector< vector<int> > galaxy_info;

    while(getline(file, line)){
        // iterate thru the line and count the number of galaxies
        num_galaxies_row = 0;
        for(int i=0; i < line.size(); i++){
            // count the number of galaxies in a row, total num of galaxies, column has a galaxy, store galaxy info
            if(line[i] == '#'){
                num_galaxies++, num_galaxies_row++;
                empty_cols[i] = 0;
                galaxy_info.push_back({row_count, i});
            }
        }
        if(num_galaxies_row == 0){ empty_rows[row_count] = 1; }
        row_count++;
    }
    // if index in empty_rows or cols is a 1 then that row is empty
    // have to find the closest distance between all pairs. just x2-x1 + y2-y1
    long long total_sum = 0;
    for(int i=0; i < num_galaxies; i++){
        for(int j=i+1; j < num_galaxies; j++){
            int min_row = (galaxy_info[j][0] < galaxy_info[i][0]) ? galaxy_info[j][0] : galaxy_info[i][0];
            int max_row = (galaxy_info[j][0] < galaxy_info[i][0]) ? galaxy_info[i][0] : galaxy_info[j][0];
            int min_col = (galaxy_info[j][1] < galaxy_info[i][1]) ? galaxy_info[j][1] : galaxy_info[i][1];
            int max_col = (galaxy_info[j][1] < galaxy_info[i][1]) ? galaxy_info[i][1] : galaxy_info[j][1];

            total_sum += (max_row-min_row) + (max_col-min_col);
            for(int row=min_row; row < max_row; row++){
                // make the expansion penalty more
                if(empty_rows[row] == 1){ total_sum += 999999; }
            }
            for(int col=min_col; col < max_col; col++){
                if(empty_cols[col] == 1){ total_sum += 999999; }
            }
        }
    }
    
    cout << total_sum << endl;
 
    return 0;
}