# See: Advent of Code 2021, Day 6: Lanternfish
# Made by: krauluk1
import numpy

class Lanternfish(object):
    def __init__(self, path):
        # Prepare Data
        self.data_start = self.__read_txt(path)

    def __read_txt(self, path):
        # Get TXT as list
        with open(path, "r") as f:
            line = f.read().splitlines()
            for i in range(len(line)):
                line[i] = list(map(int,line[i].split(',')))
            return numpy.array(line).ravel().tolist()

    # -------------
    # much faster and more effective
    def calculate_fish_nr2(self, days):
        # 0 till max 8 days
        counter =[0]*9
        data_stop = self.data_start[:]

        # Fill counter
        for i in data_stop:
            counter[i]+=1

        for day in range(1, days+1):
            zeros = counter.pop(0)
            # New fishes
            counter.append(zeros)
            # Reset counter for normal fishes
            counter[6] += zeros

        return numpy.sum(counter)

    
    # -------------
    # not fast and effective, but the same output as in the example.
    def __new_day(self, data):
        for fish in range(len(data)-1, -1, -1):
            if(data[fish] == 0):
                # Reset timer
                data[fish] = 7
                # Create new fish
                data = numpy.append(data, 8)
            data[fish] -= 1
        return data

    def calculate_fish_nr1(self, days):
        data_stop = self.data_start[:]
        print("Initial state:", data_stop)

        for i in range(1, days+1):
            data_stop = self.__new_day(data_stop)
            print("After", i, "day:", data_stop)
        return len(data_stop)
    # ------------------

h = Lanternfish('Day_6\input.txt')
print("Answer taks 1:", h.calculate_fish_nr2(80))
print("Answer taks 2:", h.calculate_fish_nr2(256))