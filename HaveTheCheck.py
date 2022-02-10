peopleList = []
peopleMap = {}
peopleReverseMap = {}
sequenceNumber = int(97)
activities = []
allCheck = {}
sumCheck = {}
while(True):
    people = str(input("添加成员："))
    if(people == ''):
        break
    if(people in peopleList):
        print(str(people) + " 已存在，请重新输入。")
        continue
    else:
        peopleMap[chr(sequenceNumber)] = people
        peopleReverseMap[people] = chr(sequenceNumber)
        sequenceNumber+=1
        peopleList.append(people)
        
print("成员已添加完毕：")
print(peopleList)
print("/n")

while(True):
    people = str(input("活动的支付人："))
    if(people == ''):
        break
    if(people not in peopleList):
        print("支付人不在成员名单内，请重新输入。")
        continue
    costMoney = int(input("活动的支付金额："))
    if(costMoney<1):
        print("输入的支付金额不合法，请重新输入。。")
        continue
    
    activities.append(str(people)+ "/t支付了:/t" + str(costMoney))

    for theOne in peopleList:
        if(theOne == people):
            continue
        if(peopleReverseMap[theOne]+peopleReverseMap[people] in allCheck):
            allCheck[peopleReverseMap[theOne]+peopleReverseMap[people]] += costMoney / len(peopleList)
        allCheck[peopleReverseMap[theOne]+peopleReverseMap[people]] = costMoney / len(peopleList)
        print(allCheck)
print(activities)

allCheckList = list(allCheck.items())

for check in allCheckList:
    flag = 0
    allCheckList.remove(check)
    debt = check[0]
    reverseDebt = ''.join(reversed(debt))
    for tempCheck in allCheckList:
        flag = 1
        allCheckList.remove(tempCheck)
        tempDebt = tempCheck[0]
        if(reverseDebt == tempDebt):
            money = check[1]
            tempMoney = tempCheck[1]
            if(money > tempMoney):
                sumCheck[debt] = money - tempMoney
            else:
                sumCheck[reverseDebt] = tempMoney - money
            break
    if(not flag):
        sumCheck[check[0]] = check[1]
    
    
print(sumCheck)
print("结账：")
