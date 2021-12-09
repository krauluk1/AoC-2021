// See: Advent of Code 2021, Day 9: Smoke Basin
// Made by: krauluk1
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>


class SmokeBasin
{
    private:
        std::vector<std::vector<int>> group;
        std::vector<std::vector<int>> read_txt(const std::string path);
        std::vector<int> process_string(const std::string str);
        std::vector<int> calculate_neighbors(std::vector<std::vector<int>> data, int height, int width);

    public:
        SmokeBasin(std::string path);
        int calculate_minimum();
        int calculate_basin_size();
};

SmokeBasin::SmokeBasin(std::string path){
    group = read_txt(path);
}

int SmokeBasin::calculate_basin_size(){
    std::vector<int> number;
    std::vector<std::vector<int>> data = group;
    std::vector<std::vector<int>> groupe(data.size(), std::vector<int>(data[0].size(), 1000000));

    int counter = 0;

    for(int i = 0; i < data.size(); i++){
        for(int j = 0; j < data[0].size(); j++){
            int curr_val = data[i][j];
            std::vector<int> gr = calculate_neighbors(groupe, i, j);
            // Is there any group right next to here?
            int curr_group = 1000000;
            std::cout << "\nValue " << curr_val << std::endl;
            for(int x:gr){
                if(x!=1000000 && curr_val!=9){
                    std::cout << "x " << x << std::endl;
                    curr_group = x;
                }
            }

        
            if(curr_group==1000000 && curr_val != 9){
                std::cout << "New counter " << counter << std::endl;
                number.push_back(1);
                groupe[i][j] = counter;
                counter+=1;
            }else if(curr_val != 9){
                std::cout << "Use counter "<< curr_group <<std::endl;
                number[curr_group]+=+1;
                groupe[i][j] = curr_group;
            }            
        }
    }

    std::cout <<"output "<< number[0] << " " << number[1] << " " << number[2]<< std::endl;
    std::sort(number.begin(), number.end(), [](const int & a, const int & b){ return a > b; });
    return number[0]*number[1]*number[2];
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
    }else{
        neighbors.push_back(1000000);
    }

    if(height < data.size()-1){
        // Bottom
        neighbors.push_back(data[height+1][width]);
    }else{
        neighbors.push_back(1000000);
    }

    if(width > 0){
        // Left position
        neighbors.push_back(data[height][width-1]);
    }else{
        neighbors.push_back(1000000);
    }

    if(width < data[0].size()-1){
        // Right position
        neighbors.push_back(data[height][width+1]);
    }else{
        neighbors.push_back(1000000);
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
