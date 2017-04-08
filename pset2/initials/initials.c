#include<stdio.h>
#include<cs50.h>
#include<ctype.h>
#include<string.h>

int main(void)
{
    
    string UserName;
    UserName = get_string(); // Accept the User Name
    
    int length = strlen(UserName); // Return the Lenth Of the User Name
    /*
    * print the first char of the name 
    * and make it upper case
    */
    printf("%c",toupper(UserName[0]));
    
    
    for(int i = 0 ; i < length ; i++ ) // loop to the rest of the Name
    {
        /*
        * check for the second name 
        * print the first char of the second name
        * and make it upper case
        */
        if(UserName[i]== ' ' && UserName[i + 1] != '\0' ){
            printf("%c",toupper(UserName[i + 1]));
        }
    }
    
    printf("\n"); // To Make New line
}