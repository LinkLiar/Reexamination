from os import error
import random
import string
maxSize = 30
generateTime = 1000
characters = string.ascii_uppercase + string.digits + string.ascii_lowercase
f = open('sample.txt', 'w')
def GenerateRandomStrings(count , char):    # 字符串错误量不超过正确结果字数的1/4
    for i in range(0 , count):
        size = random.randint(6, maxSize)
        tempRaw = ''.join(random.sample(characters,size))
        f.write(tempRaw + '\n')
        tempRaw = list(tempRaw)
        print("correct:" + str(size))
        for _ in range(0,5):
            temp = tempRaw.copy()
            errorTime = random.randint(0, int(size/6))
            print("correct:" + str(size))
            pos = []
            for _ in range(0, errorTime):
                if(len(temp) != 1):
                    errorType = random.randint(0,2)
                else:
                    errorType = random.randint(0,1)
                if (errorType == 0):
                    revise(temp,pos)
                elif (errorType == 1):
                    add(temp)
                elif (errorType == 2):
                    delete(temp)
            f.write(''.join(temp) + '\n')
        f.write('\n')

def revise(temp,pos):
    p = random.randint(0,len(temp)-1)
    # while(p in pos):
    #     p = random.randint(0,len(temp)-1)
    #     if(len(temp)<3 & len(pos)>1):
    #         break
    #     print(p) 
    temp[p]=characters[random.randint(0,len(characters)-1)]
    pos.append(p)

def add(temp):
    p = random.randint(0,len(temp)-1)
    temp.insert(p,characters[random.randint(0,len(characters)-1)])

def delete(temp):
    p = random.randint(0,len(temp)-1)
    temp.pop(p)
    
    
# temp = list("abcabcabcabcabc")
# pos = []
# revise(temp,pos)
GenerateRandomStrings(1000, characters)

# # print(choices)
# # optional shuffle, since they are produced in order of `chars`
# random.shuffle(choices)
# # Test: output how many distinct values there are:
# print(choices[1])
# print (len(choices))