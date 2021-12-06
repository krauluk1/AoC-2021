// See: Advent of Code 2021, Day 6: Lanternfish
// Made by: krauluk1
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>


class Laternfish
{
    private:
        std::vector<int> group;
        std::vector<int> process_string(const std::string str);

    public:
        Laternfish(std::string path);
        std::vector<int> read_txt(const std::string path);
        long long count_fishes(int days);
};

Laternfish::Laternfish(std::string path){
    group = read_txt(path);
}

std::vector<int> Laternfish::read_txt(const std::string path){
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

std::vector<int> Laternfish::process_string(std::string st){
    std::stringstream full_str(st);
    std::string segment;
    std::vector<int> seglist;

    while(std::getline(full_str, segment, ','))
    {
        seglist.push_back(std::stoi(segment));
    }

    return seglist;
}

long long Laternfish::count_fishes(int days){
    // Initialize Counter
    // Need a big datatype, size of int not enough
    std::vector<long long> number(9, 0);

    for(int i:group){
        number[i]+=1;
    }

    for(int i = 1; i < days+1; i++){
        long long zeros = number[0];
        number.erase(number.begin());
        number.push_back(zeros);
        number[6] += zeros;
    }  

    long long sum = 0;
    for(long long i:number){
        sum+=i;
    }
    return sum;
}


int main()
{
    Laternfish d("input.txt");
    std::cout << "Solution Task 1: " << d.count_fishes(80) << std::endl;
    std::cout << "Solution Task 2: " << d.count_fishes(256) << std::endl;
    return 0;
}
