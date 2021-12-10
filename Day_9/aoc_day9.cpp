// See: Advent of Code 2021, Day 9: Smoke Basin
// Made by: krauluk1
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <map>
#include<set>


class SmokeBasin
{
    private:
        std::vector<std::vector<int>> group;

        std::vector<std::vector<int>> read_txt(const std::string path);
        std::vector<int> process_string(const std::string str);
        std::vector<int> calculate_neighbors(std::vector<std::vector<int>> data, int height, int width);
        std::set<std::string> calculate_neighbors_positions(std::vector<std::vector<int>> data, int height, int width);

    public: 
        SmokeBasin(std::string path);
        int calculate_minimum();
        int calculate_basin_size();
};

SmokeBasin::SmokeBasin(std::string path){
    group = read_txt(path);
}



std::set<std::string> SmokeBasin::calculate_neighbors_positions(std::vector<std::vector<int>> data, int height, int width){
    // Get all Neighbors if exists
    int number = data[height][width];
     std::set<std::string> neighbors;

    if(number != 9){
        neighbors.insert(std::to_string(height) + "|" + std::to_string(width));
    }

    // Look out for up, down, right and left neightbors
    
    if(height>0){
        // Top position
        if(data[height-1][width] != 9){
            neighbors.insert(std::to_string(height-1) + "|" + std::to_string(width));
        }
    }
        // Top position
    

    if(height < data.size()-1){
        // Bottom
        if(data[height+1][width] != 9){
            neighbors.insert(std::to_string(height+1) + "|" + std::to_string(width));
        }
    }

    if(width > 0){
        // Left position
        if(data[height][width-1] != 9){
            neighbors.insert(std::to_string(height) + "|" + std::to_string(width-1));
        }
    }

    if(width < data[0].size()-1){
        // Right position
        if(data[height][width+1] != 9){
            neighbors.insert(std::to_string(height) + "|" + std::to_string(width+1));
        }
    }

    return neighbors;
}




int SmokeBasin::calculate_basin_size(){
    std::vector<std::vector<int>> data = group;
    std::vector<std::set<std::string>> mymap;
    
    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data[i].size(); j++){
            if(data[i][j] != 9)
            {
                mymap.push_back(calculate_neighbors_positions(data, i, j));
            }
        }
    }



        


    for(auto it = mymap.begin(); it!=mymap.end(); it++){
         for(auto it1 = mymap.begin()+1; it1!=mymap.end(); it1++){
            std::vector<int> common_data;
            set_intersection(it.begin(),it.end(),it1.begin(),it1.end(), std::back_inserter(common_data));
        

    }

    for(auto it = my1.begin(); it!=my1.end(); it++){
        for(auto i:it){
            std::cout << i << std::endl;
        }   
    }

    
    return 0;
}


int SmokeBasin::calculate_minimum(){
    std::vector<std::vector<int>> data = group;
    // Loop over multi vector
    int risk_lvl = 0;

    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data[0].size(); j ++){
            bool isMin = true;
            std::vector<int> neighbors = calculate_neighbors(data, i, j);
            for(int n:neighbors){
                if(data[i][j] >= n){
                    isMin = false;
                }
            }
            if(isMin){
                risk_lvl+=data[i][j] + 1;
            }
        }
    }

    return risk_lvl;
}

std::vector<int> SmokeBasin::calculate_neighbors(std::vector<std::vector<int>> data, int height, int width){
    // Get all Neighbors if exists
    //int number = data[height][width];
    std::vector<int> neighbors;

    // Look out for up, down, right and left neightbors
    if(height>0){
        // Top position
        neighbors.push_back(data[height-1][width]);
    }

    if(height < data.size()-1){
        // Bottom
        neighbors.push_back(data[height+1][width]);
    }

    if(width > 0){
        // Left position
        neighbors.push_back(data[height][width-1]);
    }

    if(width < data[0].size()-1){
        // Right position
        neighbors.push_back(data[height][width+1]);
    }

    return neighbors;
}

std::vector<std::vector<int>> SmokeBasin::read_txt(const std::string path){
    std::ifstream infile(path);

    std::string line;
    std::vector<int> vector_line;
    std::vector<std::vector<int>> vector_data;

    while (infile >> line)
    {
        vector_line = process_string(line);
        vector_data.push_back(vector_line);
    }
    return vector_data;
}

std::vector<int> SmokeBasin::process_string(const std::string str){
    std::vector<int> seglist;
    
    for(auto i:str){
        seglist.push_back(i-'0');
    }

    return seglist;
}


int main()
{
    SmokeBasin d("example.txt");
    std::cout << "Solution taks 1: " << d.calculate_minimum() << std::endl;
    std::cout << "Solution taks 2: " << d.calculate_basin_size() << std::endl;
    return 0;
}
