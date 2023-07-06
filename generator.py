import random
import os

def fake_word_generator(list):
    l=len(list[0])
    i=random.randint(0,len(list)-1)
    r=random.randint(0,l)
    if random.randint(0,1)==0:
        for j in range(l):
            word=list[i]
            for k in range(l):
                word=word+bits_to_char(random.randint(0,3))
            if word[r:r+l] not in list:
                # print(word[r:r+l])
                return word[r:r+l]
    for j in range(l):
        word=""
        for k in range(l):
            word=word+bits_to_char(random.randint(0,3))
        word=word+list[i]
        if word[r:r+l] not in list:
            # print(word[r:r+l])
            return word[r:r+l]
    return list[i]

def sub_words(list,n):
    for i in range(n):
        list.pop(random.randint(0,len(list)-1))
    return list
def add_words(list,n):
    for i in range(n):
        list.append(fake_word_generator(list))
    return list
    
def bits_to_char(k):
    if k==0:
        return 'A'
    elif k==1:
        return 'C'
    elif k==2:
        return 'T'
    return 'G'
def split_to_pices(word,l):
    words=[]
    for i in range(len(word)-l+1):
        words.append(word[i:i+l-1])
    return words
def main(n,l,amount):
    #n=int(input("Podaj n:"))
    #l=int(input("Podaj l:"))
    #amount=int(input("Podaj reliczbę instancji:"))
    add=0 #int(input("Podaj liczbę dodawanych słów:"))
    sub=0#int(input("Podaj liczbę usuwanych słów:"))
    folder=str(n)+"-"+str(l)+"-"+str(amount)
    print(folder)
    #input("Podaj nazwę folderu do zapisu:")
    # add=20
    # sub=20
    # n=100
    # l=10
    # amount=1
    # folder="generated"
    
    if not os.path.exists(folder):
        os.mkdir(folder)
    list_of_words=[]
    for i in range(amount):
        word=""
        for j in range(n):
            word=word+bits_to_char(random.randint(0,3))
        # print(word)
        list_of_words=split_to_pices(word,l)
        list_of_words=sub_words(list_of_words,sub)
        list_of_words=add_words(list_of_words,add)
        list_of_words.sort()
        print(len(list_of_words))
        suma=add-sub
        if suma>=0:
            c='+'
        else:
            c=''
        with open(folder+'/'+str(i)+'.'+str(n)+c+str(suma), "w") as file:
            for word in list_of_words:
                file.write(word)
                file.write("\n")
    
if __name__ == "__main__":
    random.seed(999)
    n=500
    amount=50
    l=15
    for n in range(100,1600,100):
        main(n,l,amount)