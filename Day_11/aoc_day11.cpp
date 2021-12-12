// See: Advent of Code 2021, Day 11: Dumbo Octopus
// Made by: krauluk1

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include<set>


class DumboOctopus
{
    private:
        std::vector<std::vector<int>> group;

        std::vector<std::vector<int>> read_txt(const std::string path);

        std::vector<int> process_string(const std::string str);

        void newStep(std::vector<std::vector<int>> &mat, int ste);

        void flashMatrix(std::vector<std::vector<int>> &mat, int *cou, bool *alf);

        void changeNumbers(std::vector<std::vector<int>> &m, int r, int c);

        void changeSingleNumber(std::vector<std::vector<int>> &ma, int ro, int co);


    public: 
        DumboOctopus(std::string path);

        int flash(int steps, bool task2);
};

DumboOctopus::DumboOctopus(std::string path){
    group = read_txt(path);
}


int DumboOctopus::flash(int steps, bool task2){
    int counter = 0;
    std::vector<std::vector<int>> data = group;

    // Iterate over steps
    for(int step = 1; step < steps+1; step++){
        // All Numbers + 1
        newStep(data, step);

        // Save already flashed Positions in this step
        bool all_flashed = true;
        while(all_flashed){
            flashMatrix(data, &counter, &all_flashed);
        }

        std::cout << "\nMatrix " << step << std::endl;
        for(int row = 0; row < data.size(); row++){
            for(int col = 0; col < data[0].size(); col++){
                std::cout << data[row][col] << " "; 
            }
            std::cout << "\n";
        }

        if(task2){
            long zero = 0;
            for(int row = 0; row < data.size(); row++){
                for(int col = 0; col < data[0].size(); col++){
                    zero += data[row][col];
                }
            }

            if(zero == 0){
                return step;
            }
        }
    }

    return counter;
}

void DumboOctopus::newStep(std::vector<std::vector<int>> &mat, int ste){
    for(int row = 0; row < mat.size(); row++){
        for(int col = 0; col < mat[0].size(); col++){
            mat[row][col] += 1;
        }
    }
}

void DumboOctopus::flashMatrix(std::vector<std::vector<int>> &mat, int *cou, bool *alf){
    // Check for flashes: Current value > 9
    *alf = false;

    for(int row = 0; row < mat.size(); row++){
        for(int col = 0; col < mat[0].size(); col++){
            if(mat[row][col]>9){
                changeNumbers(mat, row, col);
                *cou += 1;
                *alf = true;
            }
        }
    }
}


void DumboOctopus::changeNumbers(std::vector<std::vector<int>> &m, int r, int c){
    // If a flash is detected, it wont change in this run again

    // Add the 1 to the neighbors
    for(int x = -1; x <=1; x++){
        for(int y = -1; y<=1; y++){
            changeSingleNumber(m, r+x, c+y); 
        }
    }
    m[r][c] = 0;
}

void DumboOctopus::changeSingleNumber(std::vector<std::vector<int>> &ma, int ro, int co){
    // Add a 1 to the entry if it is available
    if(ro >= 0 && co >= 0 && ro <ma.size() && co < ma[0].size()){
        if(ma[ro][co] != 0){
            ma[ro][co] += 1;
        }
    }
}


std::vector<std::vector<int>> DumboOctopus::read_txt(const std::string path){
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

std::vector<int> DumboOctopus::process_string(const std::string str){
    std::vector<int> seglist;
    
    for(auto i:str){
        seglist.push_back(i-'0');
    }

    return seglist;
}


int main()
{
    DumboOctopus d("input.txt");
    long bombs = d.flash(100, false);
    long loop = d.flash(500, true);

    std::cout << "\nSolution taks 1: " << bombs << std::endl;
    std::cout << "Solution taks 2: " << loop << std::endl;
    return 0;
}
