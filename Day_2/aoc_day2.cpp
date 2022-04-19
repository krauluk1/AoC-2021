// Task: Track the Position
// See: Advent of Code 2021, Day 2: Drive!
// Made by: krauluk1
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

class Drive
{
    private:
        // Task 1
        int horizontal_position_t1 = 0;
        int depth_t1 = 0;
        void add_position_t1(std::string com, int num);

        // Task 2
        int aim_t2 = 0;
        int horizontal_position_t2 = 0;
        int depth_t2 = 0;
        void add_position_t2(std::string com, int num);

    public:

        void read_txt(const std::string path);

        // Task 1
        int calculate_solution_t1() const;

        // Taks 2
        int calculate_solution_t2() const;
};

void Drive::read_txt(const std::string path)
{
    std::ifstream infile(path);

    std::string command;
    int number;

    while (infile >> command >> number)
    {
            add_position_t1(command, number);
            add_position_t2(command, number);
    }
}

// Task 1
void Drive::add_position_t1(std::string com, int num)
{
    std::transform(com.begin(), com.end(), com.begin(), ::toupper);

    if(com.compare("FORWARD") == 0){
        horizontal_position_t1 += num;
    }else if (com.compare("DOWN") == 0){
        depth_t1 += num;
    }else if(com.compare("UP") == 0){
        depth_t1 -= num;
    }
}

int Drive::calculate_solution_t1() const
{
    return horizontal_position_t1*depth_t1;
}

// Task 2
void Drive::add_position_t2(std::string com, int num)
{
    std::transform(com.begin(), com.end(), com.begin(), ::toupper);

    if(com.compare("FORWARD") == 0){
        horizontal_position_t2 += num;
        depth_t2 += aim_t2 * num;
    }else if (com.compare("DOWN") == 0){
        aim_t2 += num;
    }else if(com.compare("UP") == 0){
        aim_t2 -= num;
    }
}

int Drive::calculate_solution_t2() const
{
    return horizontal_position_t2*depth_t2;
}

int main()
{
    Drive d;
    d.read_txt("input.txt");
    std::cout << "The solution for Puzzle 1 is: " << d.calculate_solution_t1() << std::endl;
    std::cout << "The solution for Puzzle 2 is: " << d.calculate_solution_t2() << std::endl;

    return 0;
}
