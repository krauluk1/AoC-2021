# See: Advent of Code 2021, Day 15: Chiton
# Made by: krauluk1

import heapq

class Chiton(object):
    def __init__(self, path):
        data = self.read_file(path)
        part1, part2 = self.solve(data)
        print("Answer Part 1", part1)
        print("Answer Part 2", part2)

    def read_file(self, path):
        grid = {}
        # Identify number by row, col => (row, column) : value
        with open(path) as file:
            for y, line in enumerate(file.read().splitlines()):
                for x, number in enumerate(line):
                    grid[(y, x)] = int(number)
        return grid

    def find_path(self, grid, end, start=(0, 0), risk=0):
        queue = [(risk, start)]
        minimum_risk = {start: risk}
        visited = {start}

        while queue:
            risk, (x, y) = heapq.heappop(queue)

            if (x, y) == end:
                return risk

            for neighbour in ((x+1, y), (x, y+1), (x-1, y), (x, y-1)):
                if neighbour not in grid or neighbour in visited:
                    continue
                visited.add(neighbour)
                newRisk = risk + grid[neighbour]
                if newRisk < minimum_risk.get(neighbour, 999999):
                    minimum_risk[neighbour] = newRisk
                    heapq.heappush(queue, (newRisk, neighbour))
        

    def solve(self, input):
        # Size of mat, max dist point
        max_value_x, max_value_y = map(max, zip(*input))
        # Path finding algo
        part1 = self.find_path(input, (max_value_x, max_value_y))

        input2 = {}
        for j in range(5):
            for i in range(5):
                for (x, y), value in input.items():
                    new_value_x_y = (x + (max_value_x+1) * i, y + (max_value_y+1) * j)
                    new_value = value + i + j
                    input2[new_value_x_y] = new_value if new_value < 10 else new_value % 9

        max_value_x, max_value_y = map(max, zip(*input2))
        part2 = self.find_path(input2, (max_value_x, max_value_y))

        return part1, part2


c = Chiton('input.txt')