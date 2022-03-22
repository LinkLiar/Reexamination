import random
import string

minSize = 16    # 字符串长度上限
maxSize = 50    # 字符串长度下限
generateTime = 100000    # 生成多少基准字符串
errorPerNchar = 8    # 控制基准字符串错误量上限
rowPerString = 5    # 每个基准字符串生成多少错误字符串
txtName = "sample.txt"

# TO DO: 添加限制，使不能对基准字符串上的同个位置进行 rowPerString/2 以上次数的修改

characters = string.ascii_uppercase + string.digits + string.ascii_lowercase    # 字符集 = 大写 + 数字 + 小写
f = open(txtName, 'w')
def GenerateRandomStrings(count , char):    # 字符串错误量不超过正确结果字数的1/n
    for i in range(0 , count):
        size = random.randint(minSize, maxSize)    # 随机生成基准字符串长度
        tempRaw = ''.join(random.sample(characters,size))
        f.write(tempRaw + '\n')
        tempRaw = list(tempRaw)
        for _ in range(0,rowPerString):
            temp = tempRaw.copy()
            errorTime = random.randint(0, int(size/errorPerNchar))
            pos = []
            for _ in range(0, errorTime):
                if(len(temp) != 1):
                    errorType = random.randint(0,2)
                else:
                    errorType = random.randint(0,1)
                if (errorType == 0):    # 修改一个字符
                    revise(temp,pos)
                elif (errorType == 1):    # 添加一个字符
                    add(temp)
                elif (errorType == 2):    # 删除一个字符
                    delete(temp)
            f.write(''.join(temp) + '\n')
        f.write('\n')

def revise(temp,pos):    # 修改一个字符
    p = random.randint(0,len(temp)-1)
    temp[p] = characters[random.randint(0,len(characters)-1)]
    pos.append(p)

def add(temp):    # 添加一个字符
    p = random.randint(0,len(temp)-1)
    temp.insert(p,characters[random.randint(0,len(characters)-1)])

def delete(temp):    # 删除一个字符
    p = random.randint(0,len(temp)-1)
    temp.pop(p)
    
if __name__ == '__main__':
    GenerateRandomStrings(generateTime, characters)