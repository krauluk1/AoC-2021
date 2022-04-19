# Task: Find out, how many numbers are bigger than the previous ones
# See: Advent of Code 2021, Day 1: Sonar Sweep
# Made by: krauluk1

class Sonar(object):
    def __init__(self):
        self.reset()
        # self.sliding_window = False for TASK 1
        # self.sliding_window = True for TASK 2
        self.sliding_window = True

    def reset(self):
        self.__counter_increase = 0
        self.__counter_decrease = 0
        self.__counter_same = 0
        self.__previous_number = None

    def read_txt(self, path):
        val_1 = None
        val_2 = None
        val_3 = None
        with open(path, "r") as f:
            for contents in f:
                split_content = contents.split()
                for cont in split_content:
                    try:
                        v = int(cont)
                        if not(self.sliding_window):
                            self.count_distance_change(v)
                        else:
                            if(val_1 == None):
                                val_1 = v
                            elif(val_2 == None):
                                val_2 = v
                            else:
                                val_3 = v

                            if(val_1 != None and val_2 != None and val_3 != None):
                                self.count_distance_change(
                                    val_1 + val_2 + val_3)
                                val_1 = val_2
                                val_2 = val_3

                    except ValueError:
                        print("Warning: <<" + cont + ">> is not a number")

    def count_distance_change(self, number):
        if(self.__previous_number == None):
            self.__previous_number = number
            print(number, "(N/A - no previous measurement)")
        elif(number > self.__previous_number):
            self.__counter_increase += 1
            print(number, "(increased)")
        elif(number < self.__previous_number):
            self.__counter_decrease += 1
            print(number, "(decreased)")
        else:
            self.__counter_same += 1
            print(number, "(no change)")

        self.__previous_number = number

    def get_counter_increase(self):
        return self.__counter_increase

    def get_counter_decrease(self):
        return self.__counter_decrease

    def get_counter_same(self):
        return self.__counter_same


son = Sonar()
son.read_txt('measurement.txt')


print(son.get_counter_increase(), "total increases")
print(son.get_counter_decrease(), "total decreases")
print(son.get_counter_same(), "no changes")
