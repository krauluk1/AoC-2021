# See: Advent of Code 2021, Day 8: Seven Segment Search
# Made by: krauluk1
import numpy


class SevenSegmentSearch(object):
    def __init__(self, path):
        # Prepare Data
        self.number_len = {0: 6, 1: 2, 2: 5, 3: 5,
                           4: 4, 5: 5, 6: 6, 7: 3, 8: 7, 9: 6}
        self.data = self.__read_txt(path)

    def __read_txt(self, path):
        # Get TXT as list
        with open(path, "r") as f:
            line = f.read().splitlines()
            for i in range(len(line)):
                line[i] = line[i].split('|')
                for j in range(len(line[i])):
                    line[i][j] = line[i][j].split()
        return line

    def compare_str(self, list1, list2):
        # Found in list 2
        same = ''
        # Not found in list 2
        not_same = ''

        if(len(list1) != 0 and len(list2) != 0):
            for i in list1[0]:
                if(i in list2[0]):
                    same += i
                else:
                    not_same += i

            return same, not_same

        return False, False

    def decode_input(self):
        max_value = 0
        code = {'a': '', 'b': '', 'c': '', 'd': '', 'e': '', 'f': '', 'g': ''}
        # Similarities: a - > g (7)
        for line in self.data:
            can_0_6_9 = list()  # 6
            can_2_3_5 = list()  # 5

            for j in line:
                for signal in j:
                    if(len(signal) == self.number_len[1]):
                        one = set(signal)
                    elif(len(signal) == self.number_len[4]):
                        four = set(signal)
                    elif(len(signal) == self.number_len[7]):
                        seven = set(signal)
                    elif(len(signal) == self.number_len[8]):
                        eight = set(signal)
                    elif(len(signal) == self.number_len[0]):
                        can_0_6_9.append(set(signal))
                    elif(len(signal) == self.number_len[2]):
                        can_2_3_5.append(set(signal))

            # Look for a
            code['a'] = seven.difference(one)

            # Look for d and g
            inter = set.intersection(*can_2_3_5)
            code['d'] = set.intersection(inter, four)
            code['g'] = inter.difference(code['a'], code['d'])

            # Look for b and f
            inter = set.intersection(*can_0_6_9)
            code['b'] = inter.difference(seven, code['g'])
            code['f'] = inter.difference(code['a'], code['b'], code['g'])

            # Look for e and c
            code['c'] = one.difference(code['f'])
            code['e'] = eight.difference(four, code['a'], code['g'])

            # 0 - 9
            numbers = []
            # 0
            numbers.append(eight.difference(code['d']))
            # 1
            numbers.append(one)
            # 2
            numbers.append(eight.difference(code['b'], code['f']))
            # 3
            numbers.append(eight.difference(code['b'], code['e']))
            # 4
            numbers.append(four)
            # 5
            numbers.append(eight.difference(code['c'], code['e']))
            # 6
            numbers.append(eight.difference(code['c']))
            # 7
            numbers.append(seven)
            # 8
            numbers.append(eight)
            # 9
            numbers.append(eight.difference(code['e']))

            num = ''
            for s in range(len(line[1])):
                d = set(line[1][s])
                if(d == numbers[0]):
                    num += '0'
                elif(d == numbers[1]):
                    num += '1'
                elif(d == numbers[2]):
                    num += '2'
                elif(d == numbers[3]):
                    num += '3'
                elif(d == numbers[4]):
                    num += '4'
                elif(d == numbers[5]):
                    num += '5'
                elif(d == numbers[6]):
                    num += '6'
                elif(d == numbers[7]):
                    num += '7'
                elif(d == numbers[8]):
                    num += '8'
                elif(d == numbers[9]):
                    num += '9'
            max_value += int(num)

        return max_value

    def calculate_easy_digets(self):
        # Calculate the digits of the easy numbers 1, 4, 7, 8 depending of the number of segments
        counter = {1: 0, 4: 0, 7: 0, 8: 0}

        for i in self.data:
            for j in i[1]:
                if(len(j) == self.number_len[1]):
                    counter[1] += 1
                elif(len(j) == self.number_len[4]):
                    counter[4] += 1
                elif(len(j) == self.number_len[7]):
                    # Look after number 7
                    counter[7] += 1
                elif(len(j) == self.number_len[8]):
                    # Look for number 8
                    counter[8] += 1

        sum = 0
        for item in counter.values():
            sum += item

        return sum


h = SevenSegmentSearch('Day_8\input.txt')
print("Solution Task 1: ", h.calculate_easy_digets())
print("Solution Task 2: ", h.decode_input())
