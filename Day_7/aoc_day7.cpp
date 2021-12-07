// See: Advent of Code 2021, Day 7: The Treachery of Whales
// Made by: krauluk1
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>


class Crabs
{
    private:
        std::vector<int> group;
        std::vector<int> process_string(const std::string str);
        std::vector<int> read_txt(const std::string path);

        int min_number = 0;
        int max_number = 0;

    public:
        Crabs(std::string path);

        int calculate_min_fuel(bool crab_formation);
};

Crabs::Crabs(std::string path){
    group = read_txt(path);
    auto [min, max] = std::minmax_element(std::begin(group), std::end(group));
    min_number = *min;
    max_number = *max;
}

std::vector<int> Crabs::read_txt(const std::string path){
    std::ifstream infile(path);

    std::string line;
    std::vector<int> vector_full;
    std::vector<int> vector_line;

    while (infile >> line)
    {
        vector_line = process_string(line);
        vector_full.insert(vector_full.end(), vector_line.begin(), vector_line.end());
    }
    return vector_full;
}

std::vector<int> Crabs::process_string(std::string st){
    std::stringstream full_str(st);
    std::string segment;
    std::vector<int> seglist;

    while(std::getline(full_str, segment, ','))
    {
        seglist.push_back(std::stoi(segment));
    }

    return seglist;
}

int Crabs::calculate_min_fuel(bool crab_formation){
    // Part One
    // Positions from negative - positive + 0 pos
    std::vector<int> fuel(max_number - min_number + 1, 0);

    for(auto f:group){
        for(auto i = 0; i < fuel.size(); i++){
            int val = i - f;
            if(val < 0){
                val = -val;
            }

            if(crab_formation){
                int sum = 0;
                
                for(int j = 1; j < val + 1; j ++){
                    sum+=j;
                }

                fuel[i] += sum;
            }else{
                fuel[i] += val;    
            }
        }
    }

    auto min = std::min_element(std::begin(fuel), std::end(fuel));
    return *min;
}

int main()
{
    Crabs d("input.txt");
    std::cout << "Solution Task 1: " << d.calculate_min_fuel(false) << std::endl;
    std::cout << "Solution Task 2: " << d.calculate_min_fuel(true) << std::endl;
    return 0;
}
