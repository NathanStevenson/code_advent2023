#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// recursive function called to make predictions for each input
int make_prediction(vector<int>& original){
    // need a boolean b/c there are negatives in the mix (may accidentally sum to 0 even if not all 0s in space)
    int vec_size = original.size();
    bool done = true;
    vector<int> differences;
    // loop thru the array tracking the sum of the numbers in it and also creating the next array
    for(int i=0; i < vec_size; i++){
        // if any value in array is not 0, then we are not done - else we are
        if(original[i] != 0){ done = false; }
        // do not calulcate difference for last value in array
        if(i != (vec_size - 1)){ 
            differences.push_back((original[i+1] - original[i])); 
        }
    }
    // base condition, if all the values are 0 then the predicted value is 0
    if(done){ return 0; }
    // else recurse further, add last element of current vector with value of predicted below
    else{ return original[vec_size-1] + make_prediction(differences); }
}

int main(){
    fstream file("../input/input_day9.txt");
    string line, temp;
    vector<int> original_nums;
    int sum = 0;
    while(getline(file, line)){
        stringstream ss(line);
        // add the numbers to the original nums vector
        while(ss >> temp){
            original_nums.push_back(stoi(temp));
        }
        // call recursive make prediction function to generate the value (function returns predicted value ... total these)
        sum += make_prediction(original_nums);
        // at the end of the line empty original nums to prepare for the next line of inputs
        original_nums = {};
    }
    cout << sum << endl;
    return 0;
}