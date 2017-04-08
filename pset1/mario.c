#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int height = 0 ;
    int spaces = 0 ;
    int hashes = 0 ;
  /*
  
  asking for the height .
  and check if its a negtive number or greater than 23.
  
  */
    do
    {
        printf("Please give me the Height of the half pyramid,must be Postive Number And Not bigger than 23 \n");
        height = GetInt();
    }
    while (height < 0 || height > 23);
  
  
    spaces = height - 1 ; 
    hashes = 2 ;
    // loop for the height of the pyramid.
    for (int i = 0;i<height;i++)
    {
        //loop for number of spaces of each row.
        for(int j = 0 ; j < spaces ; j++)
            printf(" ");
        //loop for number of hashes of each row.
        for(int j = 0 ; j < hashes ; j++)
            printf("#");
            
        
        printf("\n");
        spaces--;
        hashes++;
    }
}