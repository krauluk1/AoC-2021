// See: Advent of Code 2021, Day 16: Packet Decoder
// Made by: krauluk1

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <algorithm>

using ull_int = unsigned long long int;

class PacketDecoder{
    private:
        std::string binary;
        int sum_version = 0;
        ull_int express;

        void read_txt(const std::string path);
        const char* hex_to_bin(char c);
        ull_int parse_packet();

    public: 
        PacketDecoder(std::string path);
        int get_sum_version();
        ull_int get_expression();
};

PacketDecoder::PacketDecoder(std::string path){
    read_txt(path);
    express = parse_packet();
}

ull_int PacketDecoder::get_expression(){
    return express;
}

int PacketDecoder::get_sum_version(){
    return sum_version;
}

ull_int PacketDecoder::parse_packet(){
    // Version
    std::string str_version{binary.begin(), binary.begin() + 3};
	binary.erase(binary.begin(), binary.begin() + 3);
    int version = std::stoi(str_version, nullptr, 2);

    // ID
    std::string str_id{binary.begin(), binary.begin() + 3};
	binary.erase(binary.begin(), binary.begin() + 3);
    int id = std::stoi(str_id, nullptr, 2);

	// Task 1: Add all versions
    sum_version += version;

	if (id == 4){
		// Literal value, description in task 1 
		// Binary number is padded with zeros 
		bool last_pkg = false;
		std::string value;
		while (!last_pkg){
			// If leading is a zero, it is the last pkg
			// Others are paddings
			if (binary.front() == '0')
				last_pkg = true;
			// Delete description
			binary.erase(binary.begin());
			// Data of pkg
			value.append({ binary.begin(), binary.begin() + 4 });
			binary.erase(binary.begin(), binary.begin() + 4);
		}
		// Change value to
		return std::stoll(value, nullptr, 2);
	}
	else
	{
		// Operator, see task 1 for description
		// Contains one or more pkg
		std::vector<ull_int> sub_packets;

		// ID = 0 => 15 bits
		// ID = 1 => 11 bits
		char lenght_type_id{binary.front()};
		binary.erase(binary.begin());
		if (lenght_type_id == '0'){

			// Get total length of bits
			std::string lenght_str{ binary.begin(), binary.begin() + 15 };
			binary.erase(binary.begin(), binary.begin() + 15);
			int lenght = std::stoi(lenght_str, nullptr, 2);

			// Get Sub-Packets 
			size_t curr_size = binary.size();
			while (binary.size() > curr_size - lenght){
				sub_packets.push_back(parse_packet());
			}
		}else{
			std::string packet_nb_str{ binary.begin(), binary.begin() + 11 };
			binary.erase(binary.begin(), binary.begin() + 11);
			int packet_nb = std::stoi(packet_nb_str, nullptr, 2);

			for (int i = 0; i < packet_nb; i++)
				sub_packets.push_back(parse_packet());
		}

		// Task 2
		if (id == 0){
			// Sum
			ull_int value = 0;
			for (auto& i : sub_packets)
				value += i;
			return value;
		}else if (id == 1){
			// Product
			ull_int value = 1;
			for (auto& i : sub_packets)
				value *= i;
			return value;
		}else if (id == 2){
			// Minimum
			return *std::min_element(sub_packets.begin(), sub_packets.end());
		}else if (id == 3){
			// Maximum
			return *std::max_element(sub_packets.begin(), sub_packets.end());
		}else if (id == 5){
			// greater than
			return (ull_int)(sub_packets[0] > sub_packets[1]);
		}else if (id == 6){
			// less than
			return (ull_int)(sub_packets[0] < sub_packets[1]);
		}else if (id == 7){
			// equal to
			return (ull_int)(sub_packets[0] == sub_packets[1]);
		}
	}
}

void PacketDecoder::read_txt(const std::string path){
    std::ifstream infile(path);
    std::string line;
    
    // Change Hex to binary
    while (infile >> line)
    {
        for(char c:line){
			// Change Hex to binary
           binary.append(hex_to_bin(c)); 
        }
    }
}

const char* PacketDecoder::hex_to_bin(char c){
	switch (c){
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

int main(){
    PacketDecoder d("input.txt");
    int t1 = d.get_sum_version();
    ull_int t2 = d.get_expression();
    std::cout << "\nSolution taks 1: " << t1 << std::endl;
    std::cout << "\nSolution taks 2: " << t2 << std::endl;
    return 0;
}
