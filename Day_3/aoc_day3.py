# See: Advent of Code 2021, Day 3: Binary Diagnostic
# Made by: krauluk1

class BinaryDiagnostic(object):

    def __init__(self, path) -> None:
        super().__init__()
        self.gamma_rate = 0
        self.epsilon_rate = 0
        self.data = self.read_txt(path)

        self.oxygen_rating = 0
        self.co2_rating = 0

    def read_txt(self, path):
        with open(path, "r") as f:
            return f.read().splitlines()

    def test1(self):
        self.analyse_1(self.data)
        print("Gamma", self.gamma_rate, "Epsilon", self.epsilon_rate)
        print("Answer 1 is: ", self.binary_to_int(self.gamma_rate)
              * self.binary_to_int(self.epsilon_rate))

    def test2(self):
        self.analyse_2(self.data)
        print("oxigen", self.oxygen_rating, "co2", self.co2_rating)
        print("Answer 2 is: ", self.binary_to_int(self.oxygen_rating)
              * self.binary_to_int(self.co2_rating))

    def analyse_1(self, data):
        gamma_rate = []
        power_consumption = []
        copy_data = data[:]
        number_total = len(copy_data)
        number_len = len(list(copy_data[0]))
        counter_0 = [0] * number_len
        counter_1 = [0] * number_len

        for i in range(0, number_total):
            copy_data[i] = list(copy_data[i])

            for j in range(0, number_len):
                if(int(copy_data[i][j]) == 0):
                    counter_0[j] += 1

                elif(int(copy_data[i][j]) == 1):
                    counter_1[j] += 1

        for i in range(0, len(counter_0)):
            if(counter_0[i] > counter_1[i]):
                gamma_rate.append('0')
                power_consumption.append('1')
            else:
                gamma_rate.append('1')
                power_consumption.append('0')

        self.gamma_rate = ''.join(gamma_rate)
        self.epsilon_rate = ''.join(power_consumption)

    def analyse_2(self, data):
        copy_data = data[:]
        number_total = len(copy_data)
        oxygen_rating = []
        co2_rating = []

        for i in range(0, number_total):
            copy_data[i] = list(copy_data[i])

        oxygen_rating = copy_data[:]
        for j in range(0, len(oxygen_rating[0])):

            self.analyse_1(oxygen_rating)

            if not (len(oxygen_rating) > 1):
                break

            for i in range(len(oxygen_rating)-1, -1, -1):
                if not(int(list(self.gamma_rate)[j]) == int(oxygen_rating[i][j])):
                    oxygen_rating.pop(i)
        self.oxygen_rating = ''.join(oxygen_rating[0])

        co2_rating = copy_data[:]
        for j in range(0, len(co2_rating[0])):

            self.analyse_1(co2_rating)

            if not (len(co2_rating) > 1):
                break

            for i in range(len(co2_rating)-1, -1, -1):
                if not(int(list(self.epsilon_rate)[j]) == int(co2_rating[i][j])):
                    co2_rating.pop(i)
        self.co2_rating = ''.join(co2_rating[0])

    def binary_to_int(self, bin):
        return int(bin, 2)


b = BinaryDiagnostic('.\Day_3\input.txt')
b.test1()

b.test2()
