import sys

count = 0
change = float(input("How much change is owed?\n"))
while True:
    if change > 0:
        break
    change = float(input("How much change is owed?\n"))
amount = round(change * 100)
while amount > 0:
    if (amount-25)>=0:
        amount-=25
        count+=1
    elif (amount-10)>=0:
        amount-=10
        count+=1
    elif (amount-5)>=0:
        amount-=5
        count+=1
    elif(amount-1)>=0:
        amount-=1
        count+=1
print(count)        