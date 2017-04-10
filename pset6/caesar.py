import sys

while True:
    if len(sys.argv) != 2 :
        print("You didn't submit a valid encryption key.");
        print("Please check your input and re-run the programm.");
        print("We require an integer as encryption key.");
        exit(1)
    else:
        key = int(sys.argv[1])
        keySuccessful = True
    
    if  keySuccessful == True:
        break
text = input("plaintext:")
InputLength = len(text)
print("ciphertext:",end="")
for i in range(InputLength):
    if text[i].isalpha():
        if text[i].islower():
            
            print(chr(((((ord(text[i])-97)+key)%26)+97)),end="")  
        else:
            print(chr(((((ord(text[i])-65)+key)%26)+65)),end="")
    else:
        print(text[i],end="")
print("")