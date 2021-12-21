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

    def dijkstra(self, grid, target, start=(0, 0), risk=0):
        queue = [(risk, start)]
        minRisk = {start: risk}
        visited = {start}

        while queue:
            risk, (x, y) = heapq.heappop(queue)
            print("risk", risk, "x", x, "y", y)

            if (x, y) == target:
                return risk

            for neighb in ((x+1, y), (x, y+1), (x-1, y), (x, y-1)):
                if neighb not in grid or neighb in visited:
                    continue
                visited.add(neighb)
                newRisk = risk + grid[neighb]
                if newRisk < minRisk.get(neighb, 999999):
                    minRisk[neighb] = newRisk
                    heapq.heappush(queue, (newRisk, neighb))
        

    def solve(self, puzzle):
        maxX, maxY = map(max, zip(*puzzle))
        print("maxX ", maxX, " maxY ", maxY)
        part1 = self.dijkstra(puzzle, (maxX, maxY))
        print("Part 1", part1)

        puzzle2 = {}
        for j in range(5):
            for i in range(5):
                for (x, y), value in puzzle.items():
                    newXY = (x + (maxX+1) * i, y + (maxY+1) * j)
                    newVal = value + i + j
                    puzzle2[newXY] = newVal if newVal < 10 else newVal % 9

        maxX, maxY = map(max, zip(*puzzle2))
        part2 = self.dijkstra(puzzle2, (maxX, maxY))

        return part1, part2


c = Chiton('example.txt')