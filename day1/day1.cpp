#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// O(N) Solution for both parts
// always update the end digit, but only update the start digit if first number
// sliding window for words looking if they are valid and then using index in array for their value

int main(){
    // starting params
    string line;
    ifstream file("../input/input_day1.txt");

    vector<string> numbers = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

    int start_digit = -1, end_digit = -1, sum = 0;

    // read file line by line
    while(getline(file, line)){
        // go thru each line and find the first and last digit
        for(int i=0; i < line.size(); i++){
            // try and find word
            string three = line.substr(i, 3);
            string four  = line.substr(i, 4);
            string five  = line.substr(i, 5);
            
            auto it3 = find(numbers.begin(), numbers.end(), three);
            auto it4 = find(numbers.begin(), numbers.end(), four);
            auto it5 = find(numbers.begin(), numbers.end(), five);

            // ALWAYS populate end digit, only populate start digit if hasnt been found
            // (digit)
            if (isdigit(line[i])){
                if(start_digit == -1){ start_digit = line[i] - '0'; }
                end_digit = line[i] - '0';
            }

            // (word)
            if ((it3 != numbers.end() || it4 != numbers.end() || it5 != numbers.end())){
                if(it3 != numbers.end()){
                    if(start_digit == -1){ start_digit = distance(numbers.begin(), it3) + 1; }
                    end_digit = distance(numbers.begin(), it3) + 1;
                }
                if(it4 != numbers.end()){
                    if(start_digit == -1){ start_digit = distance(numbers.begin(), it4) + 1; }
                    end_digit = distance(numbers.begin(), it4) + 1;
                }
                if(it5 != numbers.end()){
                    if(start_digit == -1){ start_digit = distance(numbers.begin(), it5) + 1; }
                    end_digit = distance(numbers.begin(), it5) + 1;
                }
            }
        }
        sum += (start_digit*10) + end_digit;
        // reset start/end digit
        start_digit = -1;
        end_digit = -1;
    }

    cout << sum << endl;

    // close file
    file.close();

    return 0;
}