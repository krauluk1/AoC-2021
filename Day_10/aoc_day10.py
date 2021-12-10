# See: Advent of Code 2021, Day 10: Syntax Scoring
# Made by: krauluk1
import numpy

class SyntaxScoring(object):
    def __init__(self, path):
        # Prepare Data
        self.data = self.__read_txt(path)
        self.brackets_open = {'(':')', '[':']', '{':'}', '<':'>'}
        self.brackets_close = {v:k for k,v in self.brackets_open.items()}
        self.corrupted = []

    def __read_txt(self, path):
        # Get TXT as list
        with open(path, "r") as f:
            line = f.read().splitlines()
            for i in range(len(line)):
                line[i] = list(line[i])
            return line

    def find_corrupted(self):
        # Task 1 & Task 2
        counter = 0
        points = {')':3, ']':57, '}':1197, '>':25137}

        for point in range(len(self.data)-1, -1, -1):
            line = self.data[point]

            close = []
            for c in line:
                if c in self.brackets_open:
                    close.append(self.brackets_open[c])
                elif c == close[-1]:
                    close.pop(-1)
                elif c in self.brackets_close:
                    counter+= points[c]
                    self.corrupted.append(self.data.pop(point))
                    break

        return counter

    def repair_incomplete(self):
        # Task 2
        points = {')':1, ']':2, '}':3, '>':4}
        score = []

        for point in range(len(self.data)):
            line = self.data[point]

            close = []
            for c in line:
                if c in self.brackets_open:
                    close.append(self.brackets_open[c])
                elif c == close[-1]:
                    close.pop(-1)

            counter = 0      
            for i in range(len(close)-1, -1, -1):
                counter = counter * 5 + points[close[i]]
            score.append(counter)

        score.sort()
        return score[len(score)//2]
                
                



h = SyntaxScoring('input.txt')
print("Output Task 1: " + str(h.find_corrupted()))
print("Output Task 2: " + str(h.repair_incomplete()))