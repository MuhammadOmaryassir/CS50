#include<stdio.h>
#include<cs50.h>
#include<math.h>

int main(void)
{
    
    int count = 0;
    printf("How much change is owed?\n");
    float change = GetFloat();
    
    // make sure the input is not a negtive number
    while(change < 0 ) 
    {
        printf("How much change is owed?\n");
        change = GetFloat();
    }
        // change float -> int 
        // cent -> $
        int amount =  round(change * 100);
    // the algorithm
    while(amount > 0)
    {
        if((amount - 25) >= 0 ){
            amount = amount - 25;
            count++;
        }
        else if((amount - 10) >= 0 ){
            amount = amount - 10 ;
            count++;
        }
         else if((amount - 5) >= 0 ){
            amount = amount - 5 ;
            count++;
        }
         else if((amount - 1) >= 0 ){
            amount = amount - 1 ;
            count++;
        }
    }
    printf("%d\n", count);
}