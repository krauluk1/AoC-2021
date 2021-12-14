# See: Advent of Code 2021, Day 14: Extended Polymerization
# Made by: krauluk1

class ExtendedPolymerization(object):

    def __init__(self, path):
        self.read_file(path)

    def read_file(self, path):
        with open(path) as file:
            lines = file.read().splitlines()
            self.data= list(lines.pop(0))
            self.dict = {}

            for line in lines:
                if line != '':
                    line = line.split(' -> ')
                    self.dict[line[0]] = line[1]

    def quantity_difference(self):
        return max(self.dict_of_occurents.values()) - min(self.dict_of_occurents.values())

    def count_element(self):
        self.dict_of_occurents = {}
        self.dict_of_occurents = {item:self.data.count(item) for item in self.data}

    def multiple_steps(self, steps):
        for i in range(steps):
            self.new_step()

    def new_step(self):
        for i in range(len(self.data)-1, 0, -1):
            if(self.data[i-1] + self.data[i] in self.dict.keys()):
                self.data.insert(i, self.dict[self.data[i-1] + self.data[i]])

    

e1 = ExtendedPolymerization("input.txt")
e1.multiple_steps(10)
e1.count_element()
print("Answer 1: ", e1.quantity_difference())


e1.multiple_steps(30)
e1.count_element()
print("Answer 2: ", e1.quantity_difference())
