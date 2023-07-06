
import os


dna = []

def calculate_weight(a, b):
    for i in range(1, len(a)):
        if a[i:] == b[:-i]:
            return i*i
    return -1


def main(name):
    with open(os.path.join(ins_dir+'/', name), 'r') as file:
        lines = file.readlines()
        for line in lines:
            dna.append(line.strip())

        neighbours = [[0 for i in range(len(dna))] for j in range(len(dna))]
        for i in range(len(dna)):
            for j in range(len(dna)):
                weightval = calculate_weight(dna[i], dna[j])
                neighbours[i][j]= weightval
                    
        print(neighbours)
        dna.clear()
              
if __name__ == "__main__":
    folders=["test"]
    for i, folder in enumerate(folders):
        print(folder)
        ins_dir = folder
        for filename in os.listdir(ins_dir):
            print(filename)
            main(filename)
            