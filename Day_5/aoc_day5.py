# See: Advent of Code 2021, Day 5: Hydrothermal Venture
# Made by: krauluk1
import numpy

class HydrothermalVenture(object):
    def __init__(self, path):
        # data is (right, down) = (x, y)
        # Prepare Data
        data = self.read_txt(path)
        diagramm = self.make_empty_diagramm(data)

        # Evaluate Horizontal and Vertical
        diagramm = self.consider_horizontal_vertical(data, diagramm)
        print("Solution Task 1: ", self.count_overlap1(diagramm))

        # Evaluate Diagonals
        diagramm = self.consider_diagonals(data, diagramm)
        print("Solution Task 2: ", self.count_overlap1(diagramm))

    def read_txt(self, path):
        # Get TXT as list
        with open(path, "r") as f:
            line = f.read().splitlines()
            for i in range(len(line)):
                line[i] = line[i].split(' -> ')
                line[i] = [list(map(int,line[i][0].split(','))), list(map(int,line[i][1].split(',')))]
            return line  

    def make_empty_diagramm(self, data):
        # Figure out highest number
        x = 0
        y = 0
        for i in data:
            for j in i:
                if(j[0] > x):
                    x = j[0]
                if(j[1] > y):
                    y = j[1]

        # +1 cause it starts with 0
        return numpy.zeros((x+1, y+1))

    def consider_horizontal_vertical(self, data, diagramm):
        # Info: Consider only horizontals x1 = x2 and verticals y1 = y2
        for i in data:
            start = i[0]
            stop = i[1]

            if(start[0] == stop[0] or start[1] == stop[1]):
        
                if(start[0] > stop[0] or start[1] > stop[1]):
                    start, stop = self.swap(start, stop)

                if(start[1] < stop[1]):
                    for y in range(start[1], stop[1]+1):
                        diagramm[y][start[0]] += 1

                elif(start[0] < stop[0]):
                    for x in range(start[0], stop[0]+1):
                        diagramm[start[1]][x] += 1

                elif(start[0] == stop[0] and start[1] == stop[1]):
                    diagramm[start[1]][start[0]] += 1
                    
        return diagramm

    def consider_diagonals(self, data, diagramm):
        # Info: Task 2 consider Verticals
        for i in data:
            start = i[0]
            stop = i[1]

            if(start[0] != stop[0] and start[1] != stop[1]):

                if(start[0] > stop[0]):
                    start, stop = self.swap(start, stop)
                
                for step in range(stop[0] - start[0] + 1):
                    if(start[1] < stop[1]):
                        diagramm[start[1]+step][start[0]+step] += 1
                    elif(start[1] > stop[1]):
                        diagramm[start[1]-step][start[0]+step] += 1                        

        return diagramm

    def swap(self, x, y):
        return y, x

    def count_overlap1(self, diagramm):
        # Get Anz(value > 1)
        sum  = 0
        for line in diagramm:
            for value in line:
                if(value > 1):
                    sum+=1
        return sum


h = HydrothermalVenture('Day_5\input.txt')
