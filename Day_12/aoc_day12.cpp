// See: Advent of Code 2021, Day 12: Passage Pathing
// Made by: krauluk1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <map>
#include <string_view>

class PassagePathing
{
    private:
        std::map<std::string, std::vector<std::string>> data;
        std::map<std::string, std::vector<std::string>> read_txt(const std::string path);
        std::vector<std::string> process_string(std::string st);
        bool isLower(const std::string& s);
        void print_map(std::string_view comment, const std::map<std::string, std::vector<std::string>>& m);
        bool selection1(std::string key, std::vector<std::string> values);

    public: 
        PassagePathing(std::string path);
        int Task1(bool in);
};

int PassagePathing::Task1(bool in){
    std::map<std::string, std::vector<std::string>> way = data;
    //print_map("Map 1", way);

    std::vector<std::vector<std::string>> all_paths;
    std::vector<std::vector<std::string>> cases;
    std::vector<bool> visited;

    cases.push_back({"start"});
    visited.push_back(in);

    bool change_detected = true;

    while(cases.size()){
        
        std::vector<std::string> sol_1 = cases.back();
        bool vis_1 = visited.back();
        cases.pop_back();
        visited.pop_back();

        if(sol_1.back() == "end"){
            all_paths.push_back(sol_1);
            continue;
        }

        if(selection1(sol_1.back(), sol_1)){
            if(sol_1.back() == "start" || vis_1){
                continue;
            }
            vis_1 = true;
        }

        for(auto c:way[sol_1.back()]){
            std::vector<std::string> sol_tmp = sol_1;
            sol_tmp.push_back(c);
            cases.push_back(sol_tmp);
            visited.push_back(vis_1);
        }

    }

    return all_paths.size();
}

bool PassagePathing::selection1(std::string key, std::vector<std::string> values){
    return isLower(key) && (std::find(values.begin(), values.end()-1, key) != values.end()-1);
}

bool PassagePathing::isLower(const std::string& s) {
    return std::all_of(s.begin(), s.end(), [](unsigned char c){ return std::islower(c); });
}

PassagePathing::PassagePathing(std::string path){
    data = read_txt(path);
}

void PassagePathing::print_map(std::string_view comment, const std::map<std::string, std::vector<std::string>>& m)
{
    std::cout << "\n" << comment << std::endl;
    for (const auto& [key, value] : m) {

        std::cout << key << " = ";

        for (const auto i:value){
            std::cout << i << " ";
        }
        std::cout << "\n";
    }
}

std::map<std::string, std::vector<std::string>> PassagePathing::read_txt(const std::string path){
    std::ifstream infile(path);

    std::string line;
    std::vector<std::string> data_o;
    std::map<std::string, std::vector<std::string>> map_o;

    while (infile >> line)
    {
        data_o = process_string(line);
        std::string first = data_o[0];
        std::string second = data_o[1];
        if(second!="start"){
            map_o[first].push_back(second);}
        if(second!="end"){
            map_o[second].push_back(first);}
    }
    return map_o;
}

std::vector<std::string> PassagePathing::process_string(std::string st){
    std::stringstream full_str(st);
    std::string segment;
    std::vector<std::string> seglist;

    while(std::getline(full_str, segment, '-'))
    {
        seglist.push_back(segment);
    }

    return seglist;
}

int main()
{
    PassagePathing d("input.txt");
    int t1 = d.Task1(true);
    int t2 = d.Task1(false);
    std::cout << "Solution taks 1: " << t1 << std::endl;
    std::cout << "Solution taks 2: " << t2 << std::endl;
    return 0;
}
