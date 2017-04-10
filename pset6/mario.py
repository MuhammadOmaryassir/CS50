import sys

hight = 0
spaces = 0
hashes = 0

while True :
    hight = int(input("Please give me the Height of the half pyramid,must be Postive Number And Not bigger than 23\n"))
    if hight > 0 and hight < 23 :
        break
    
spaces = hight - 1 
hashes = 2

for i in range(hight) :
    for j in range(spaces) :
        print(" ",end="")
    for x in range(hashes) :
        print("#",end="")
        
    print("\n",end="")
    spaces-=1
    hashes+=1
    