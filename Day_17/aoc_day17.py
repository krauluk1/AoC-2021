# See: Advent of Code 2021, Day 17: Trick Shot
# Made by: krauluk1

class TrickShot(object):
    def __init__(self, path) -> None:
        fi = self.read_file(path)
        self.prepare_data(fi)

    def read_file(self, path):
        with open(path) as f:
            fi = f.readline()
        return fi

    def prepare_data(self, data):
        left, right = data.strip().split(',')
        minx, maxx = left.split('=')[1].split('..')
        miny, maxy = right.split('=')[1].split('..')
        self.minx = int(minx)
        self.miny = int(miny)
        self.maxx = int(maxx)
        self.maxy = int(maxy)

    def calculate_heigt_1(self):
        xvel = yvel = 1
        max_height = -9999
        for x in range(200):
            for y in range(-200, 200):
                height = self.shoot(xvel+x, yvel+y)
                if height and height > max_height:
                    max_height = height
        print("Answer 1: ", max_height)

    def calculate_velocity_2(self):
        xvel = yvel = 1
        count = 0
        for x in range(200):
            for y in range(-200, 200):
                count += self.shoot(xvel+x, yvel+y, 2)
        print("Answer 2: ", count)

    def within_target(self, loc):
        x, y = loc
        return self.minx <= x <= self.maxx and self.miny <= y <= self.maxy

    def too_deep(self, loc):
        x, y = loc
        return x > self.maxx

    def too_short(self, loc):
        x, y = loc
        return x < self.minx and y < self.miny

    def too_high(self, loc):
        x, y = loc
        return y < self.miny

    def shoot(self, xvel, yvel, mode=1):
        x = y = 0
        max_height = -1 if (mode == 1) else -9999
        while True:
            x += xvel
            y += yvel
            if y > max_height:
                max_height = y
            if self.within_target((x, y)):
                return max_height if (mode == 1) else True
            if self.too_high((x, y)) or self.too_deep((x, y)):
                return False
            if xvel > 0:
                xvel -= 1
            elif xvel < 0:
                xvel += 1
            yvel -= 1


t1 = TrickShot("input.txt")
t1.calculate_heigt_1()
t1.calculate_velocity_2()
