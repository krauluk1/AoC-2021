# See: Advent of Code 2021, Day 13: Transparent Origami
# Made by: krauluk1

class TransparentOrigami(object):
    def __init__(self, path):
        # Prepare Data
        data, fold, max_x, max_y = self.__read_txt(path)
        paper = self.make_paper(data, max_x, max_y)
        paper_sol = self.fold_paper(paper, fold)
        print("Output Taks 1: ", self.count_marker(paper_sol))
        
        paper_sol = self.fold_paper(paper, fold, False)

    
    def count_marker(self, paper):
        counter = 0
        for i in paper:
            for j in i:
                if(j == '#'):
                    counter+=1
        return counter

    def output_matr(self, mat, message):
        print(message)
        for i in mat:
            st = ""
            for j in i:
                if(j == '#'):
                    st+='#'
                else:
                    st+=' '
            print(st)
        

    def fold_paper(self, paper, fold, test1 = True):
        for f in fold:
            if(f[0]=='x'):
                paper = self.fold_vertical(paper, int(f[1]))
            else:
                paper = self.fold_horizontal(paper, int(f[1]))
            if(test1):
                break
        if not test1: self.output_matr(paper, "Solution test 2: ")
        return paper
    
    def fold_horizontal(self, paper, y):
        input_paper = paper[0:y]
        fold_paper = paper[:y:-1]
        
        for i in range(len(fold_paper)):
            for j in range(len(fold_paper[0])):
                if(fold_paper[i][j] == '#'):
                    input_paper[i][j] = '#'
        return input_paper

    def fold_vertical(self, paper, x):
        output_paper = []
        for i in range(len(paper)):
            input_li = paper[i][:x]
            fold_li = paper[i][:x:-1]
            for i in range(len(fold_li)):
                if(fold_li[i] == '#'):
                    input_li[i] = '#'
            output_paper.append(input_li)
        return output_paper
    

    def make_paper(self, data, x, y):
        paper = [['.']*(x+1) for item in range(y+1)]
        for i in data:
            paper[i[1]][i[0]] = '#'
        return paper

    def __read_txt(self, path):
        # Get TXT as list
        data1 = []
        fold1 = []
        fold_st = "fold along"
        max_x = 0
        max_y = 0
        with open(path, "r") as f:
            line = f.read().splitlines()
            for lin in line:
                if fold_st in lin and lin != '':
                    lin = lin.split()
                    fold1.append(lin[2].split('='))    
                elif lin!='':
                    data2 = list(map(int, lin.split(',')))
                    if(max_x < data2[0]):
                        max_x = data2[0]
                    if(max_y < data2[1]):
                        max_y = data2[1]
                    data1.append(data2)
                
            return data1, fold1, max_x, max_y

  

h = TransparentOrigami('input.txt')
