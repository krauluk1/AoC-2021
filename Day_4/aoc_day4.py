# See: Advent of Code 2021, Day 4: Giant Squid
# Made by: krauluk1
class Puzzle(object):

    def __init__(self, data):
        self.height = len(data)
        self.width = len(data[0])
        self.data = data
        self.taken = [[False]*self.width for i in range(self.height)]

        self.bingo = None
        self.line = None

    def show_puzzle(self):
        # Show Puzzle
        print("\nShow Puzzle")
        print("Puzzle")
        for i in self.data:
            print(i)
        print("Status")
        for i in self.taken:
            print(i)

    def get_puzzle(self):
        return self.data

    def have_entry(self, number):
        # Check if number in entry
        for i in range(0, self.height):
            for j in range(0, self.width):
                if(self.data[i][j] == number):
                    self.taken[i][j] = True

    def print_bingo_data(self):
        print("Bingo in " + self.bingo, self.line + 1)

    def check_bingo(self):
        # Check row
        for i in range(0, self.height):
            bingo = True

            for j in range(0, self.width):
                if(self.taken[i][j] == False):
                    bingo = False

            if(bingo):
                self.bingo = "ROW"
                self.line = i
                return True

        # Check col
        for i in range(0, self.width):
            bingo = True
            for j in range(0, self.height):
                if(self.taken[j][i] == False):
                    bingo = False

            if(bingo):
                self.bingo = "COL"
                self.line = i
                return True

        return False

    def sum_uncalled(self):
        sum = 0
        for i in range(0, self.height):
            for j in range(0, self.width):
                if(self.taken[i][j] == False):
                    sum += self.data[i][j]
        return sum


class Bingo(object):
    def __init__(self, path, height=5, width=5) -> None:
        super().__init__()
        self.height = height
        self.width = width

        data = self.read_txt(path)
        self.input = self.get_number_input(data)
        self.puzzle_obj = self.make_puzzle(data)

    def read_txt(self, path):
        with open(path, "r") as f:
            line = f.read().splitlines()
            return line

    def get_number_input(self, liste):
        # The first line are the single numbers
        liste = liste.pop(0)
        liste = liste.split(',')
        return list(map(int, liste))

    def make_puzzle(self, liste):
        liste = [x for x in liste if x]
        puzzles = []

        while(len(liste) >= 1):
            input = []
            for i in range(0, self.height):
                li = liste.pop(0)
                li = li.split()
                li = list(map(int, li))
                input.append(li)
            b = Puzzle(input)
            puzzles.append(b)

        return puzzles

    def game_1(self):
        # Play the first game
        for number in self.input:
            # Fill the Puzzles
            for puz in self.puzzle_obj:
                puz.have_entry(number)
                if(puz.check_bingo()):
                    print("BINGO")
                    puz.print_bingo_data()
                    puz.show_puzzle()
                    print("Solution task1: ", puz.sum_uncalled()*number)
                    return True
        return False

    def game_2(self):
        # Play the second game
        last_number = 0
        for number in self.input:
            # Fill the Puzzles
            for puz in range(len(self.puzzle_obj)-1, -1, -1):
                self.puzzle_obj[puz].have_entry(number)
                if(self.puzzle_obj[puz].check_bingo()):
                    last_puzzle = self.puzzle_obj.pop(puz)
                    last_number = number

        print("\nThe last winner is: ")
        last_puzzle.show_puzzle()
        print("Solution task2: ", last_puzzle.sum_uncalled()*last_number)


b = Bingo("Day_4\input.txt")
b.game_1()
b.game_2()
