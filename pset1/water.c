#include<cs50.h>
#include<stdio.h>

int main(void) 
{
    
    // Asking For The Length of the Shower In Minutes
    printf("Please Give Me The Length Of Your Shower In Minutes\n");
    int minutes = get_float();
    
    int bottles = (minutes*12);
    
    //Display the number of minutes and bottles
    printf("Minutes: %i\n", minutes);
    printf("Bottles: %i\n", bottles);
    
}