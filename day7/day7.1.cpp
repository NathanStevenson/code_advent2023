#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <queue>
#include <unordered_map>
using namespace std;

// unordered map of camel card values
unordered_map<char, int> card_values;

// maintain 7 different priority queues, one for each level, ordering determined by second lvl ordering rule
class Compare {
    public:
    // sort so that highest element is at the top when done
        bool operator()(string first, string second){
            for(int i=0; i < first.length(); i++){
                // if same continue loop
                if(first[i] == second[i]){ continue; }
                // if the card value of the first is less than second then we do not want to swap; we want lower cards first ascending order
                if(card_values.at(first[i]) < card_values.at(second[i])){ return false; }
                // if card value of first is greater than second then we want to swap the first with second; want high cards later so rank is more
                if(card_values.at(first[i]) > card_values.at(second[i])){ return true; }
            }
            return true;
        }
};

int main(){
    fstream file("../input/input_day7.txt");
    string line, hand, temp, cards = "23456789TJQKA";
    int bid = 0;

    // seven different PQs
    priority_queue<string, vector<string>, Compare> five, four, full, three, two, one, high;
    unordered_map<string, int> hand_to_bid;

    // populate the card values map
    for(int i=0; i < cards.length(); i++){
        card_values.insert(make_pair(cards[i], i));
    }

    while(getline(file, line)){
        // convert each line into its corresponding hand and bid
        stringstream ss(line);
        ss >> hand;
        ss >> temp;
        bid = stoi(temp);
        // store the hand to bid mapping
        hand_to_bid.insert(make_pair(hand, bid));

        // determine what type of hand it is, place in respective PQ
        unordered_map<char, int> character_tracker;
        for(int i=0; i < hand.size(); i++){
            auto it = character_tracker.find(hand[i]);
            // if not found insert with value 1
            if(it == character_tracker.end()){
                character_tracker.insert(make_pair(hand[i], 1));
            }else{
                // if found increment the count
                it->second++;
            }
        }
        int map_size = character_tracker.size();
        // five of a kind
        if(map_size == 1){ five.push(hand); }
        // four or full
        else if(map_size == 2){
            // go thru and see if it has a 4 if so then 4 else full
            bool is_four = false;
            for(auto it=character_tracker.begin(); it != character_tracker.end(); it++){
                if(it->second == 4){ is_four = true; }
            }
            if (is_four){ four.push(hand); }
            else{ full.push(hand); }
        }
        // three or two
        else if(map_size == 3){
            // go thru and see if it has a 3 if so then 3 else full
            bool is_three = false;
            for(auto it=character_tracker.begin(); it != character_tracker.end(); it++){
                if(it->second == 3){ is_three = true; }
            }
            if (is_three){ three.push(hand); }
            else{ two.push(hand); }
        }
        // one
        else if(map_size == 4){ one.push(hand); }
        // high
        else if(map_size == 5){ high.push(hand); }
        // invalid
        else{ continue; }
    }

    // once we have the PQs full go thru from worst to best and sum their ranks
    int rank = 1, sum = 0;
    while(!high.empty()){
        // add the bid corresponding with the hand times the rank
        sum += (hand_to_bid.at(high.top()) * rank);
        high.pop();
        rank++;
    }
    while(!one.empty()){
        // add the bid corresponding with the hand times the rank
        sum += (hand_to_bid.at(one.top()) * rank);
        one.pop();
        rank++;
    }
    while(!two.empty()){
        // add the bid corresponding with the hand times the rank
        sum += (hand_to_bid.at(two.top()) * rank);
        two.pop();
        rank++;
    }
    while(!three.empty()){
        // add the bid corresponding with the hand times the rank
        sum += (hand_to_bid.at(three.top()) * rank);
        three.pop();
        rank++;
    }
    while(!full.empty()){
        // add the bid corresponding with the hand times the rank
        sum += (hand_to_bid.at(full.top()) * rank);
        full.pop();
        rank++;
    }
    while(!four.empty()){
        // add the bid corresponding with the hand times the rank
        sum += (hand_to_bid.at(four.top()) * rank);
        four.pop();
        rank++;
    }
    while(!five.empty()){
        // add the bid corresponding with the hand times the rank
        sum += (hand_to_bid.at(five.top()) * rank);
        five.pop();
        rank++;
    }
    cout << sum << endl;

    return 0;
}