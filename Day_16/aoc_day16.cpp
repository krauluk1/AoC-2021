// See: Advent of Code 2021, Day 16: Packet Decoder
// Made by: krauluk1

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <algorithm>


class PacketDecoder
{
    private:
        std::string binary;
        void read_txt(const std::string path);
        const char* hex_to_bin(char c);
        void PacketDecoder::parse_package();

    public: 
        PacketDecoder(std::string path);
};

PacketDecoder::PacketDecoder(std::string path){
    read_txt(path);
}

void PacketDecoder::parse_package(){
    // package Version
    std::string str_version{binary.begin(), binary.begin() + 3};
	binary.erase(binary.begin(), binary.begin() + 3);
    int version = std::stoi(str_version, nullptr, 2);

    // ID
    std::string str_id{binary.begin(), binary.begin() + 3};
	binary.erase(binary.begin(), binary.begin() + 3);
    int id = std::stoi(str_id, nullptr, 2);

    if(id == 4){
        
    }

}

void PacketDecoder::read_txt(const std::string path){
    std::ifstream infile(path);
    std::string line;
    
    // Change Hex to binary
    while (infile >> line)
    {
        for(char c:line){
           binary.append(hex_to_bin(c)); 
        }
    }
}

const char* PacketDecoder::hex_to_bin(char c)
{
	switch (c)
	{
	case '0': return "0000";
	case '1': return "0001";
	case '2': return "0010";
	case '3': return "0011";
	case '4': return "0100";
	case '5': return "0101";
	case '6': return "0110";
	case '7': return "0111";
	case '8': return "1000";
	case '9': return "1001";
	case 'A': return "1010";
	case 'B': return "1011";
	case 'C': return "1100";
	case 'D': return "1101";
	case 'E': return "1110";
	case 'F': return "1111";
	}
}

int main()
{
    PacketDecoder d("input.txt");
    std::cout << "\nSolution taks 1: " << "" << std::endl;
    return 0;
}
