# See: Advent of Code 2021, Day 14: Extended Polymerization
# Made by: krauluk1
from collections import defaultdict
from copy import copy


class ExtendedPolymerization(object):

    def __init__(self, path):
        self.read_file(path)

    def read_file(self, path):
        with open(path) as file:
            lines = file.read().splitlines()
            self.data = list(lines.pop(0))
            self.dict = {}
            self.counter = {}

            for line in lines:
                if line != '':
                    line = line.split(' -> ')
                    self.dict[line[0]] = line[1]
                    self.counter[line[0]] = 0

    def quantity_difference(self):
        return max(self.dict_of_occurents.values()) - min(self.dict_of_occurents.values())

    def count_element(self):
        self.dict_of_occurents = {}
        self.dict_of_occurents = {
            item: self.data.count(item) for item in self.data}

    def multiple_steps(self, steps):
        for i in range(steps):
            self.new_step()

    def new_step(self):
        for i in range(len(self.data)-1, 0, -1):
            if(self.data[i-1] + self.data[i] in self.dict.keys()):
                self.data.insert(i, self.dict[self.data[i-1] + self.data[i]])

    # -------------------
    def add_val(self, rounds):
        counter_double = copy(self.counter)
        for first, second in list(zip(self.data, self.data[1:])):
            self.counter[first + second] += 1

        for i in range(rounds):
            self.counter = self.round_data(copy(counter_double))

        char_dict = {}
        for i in self.counter.keys():
            char_dict[i[0]] = 0
            char_dict[i[1]] = 0

        for i in self.counter.keys():
            char_dict[i[0]] += self.counter[i]
            char_dict[i[1]] += self.counter[i]

        char_dict[self.data[0]] += 1
        char_dict[self.data[-1]] += 1

        return int((max(char_dict.values()) - min(char_dict.values())) / 2)

    def round_data(self, zero):
        for key in self.counter.keys():
            value = self.counter[key]
            zero[key[0] + self.dict[key]] += value
            zero[self.dict[key] + key[1]] += value
        return zero


e1 = ExtendedPolymerization("input.txt")
# e1.multiple_steps(10)
# e1.count_element()
# print("Answer 1: ", e1.quantity_difference())

print("Answer 2: ", e1.add_val(40))
