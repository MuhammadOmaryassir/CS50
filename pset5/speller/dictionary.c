/**
 * Implements a dictionary's functionality.
 */
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


#include "dictionary.h"


 /**
  * gloabal varibale
  * initialized to = 0 
  **/
 unsigned int dictionary_count = 0;
 
 
/**
 * hash function 
 * returns Hashed value
 **/
int hash_it(char* needs_hashing)
{
    unsigned int hash = 0;
    for (int i=0, n=strlen(needs_hashing); i<n; i++)
        hash = (hash << 2) ^ needs_hashing[i];
    return hash % HASHTABLE_SIZE;
}

/**
 * initialize a a hash table
 * 
 * crate a hash table array 
 * make every element  in the array = NULL
 **/
node *hashtable[HASHTABLE_SIZE] = {NULL};


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // get the length of the word
    int length = strlen(word);
    // make array of chars 
    char wordCpy[length + 1];
    // make every alphaptic in the word to lower case 
    for(int i = 0 ;  i < length ;i++)
    {
        // copy the new word 
        wordCpy[i] = tolower(word[i]);
    }
    // add trimenated point end of the word 
    wordCpy[length] = '\0';
    
    // hash the copy of the word 
    int Index = hash_it(wordCpy);
    
    // go to the head of the linked list
    node *PTR = hashtable[Index];
    
    while(PTR != NULL)
    {
        // strcmp function to compare between 
        if( strcmp(PTR->word , wordCpy) == 0  )
        {
            return true;
        }
        // else move to the next node
        else
        PTR = PTR->next ;
    }
    
    
    
    return false;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    
    /**
     * make a file pointer 
     * and open a file in read mode
     **/
    
    FILE* infile = fopen(dictionary, "r");
    if (infile == NULL)
    {
        printf("Could not open file");
        return false;
    }
    
    // loop until the end of the file 
    while(!feof(infile))
    {
        
        // make a new nood and allocate memory in heap
        node* Newnode = malloc(sizeof(node));
        if(Newnode == NULL)
        {
            unload();
            return false ; 
        }
        
        // read the words from the file
        fscanf(infile , "%s" , Newnode -> word);
        
        //make the ponter next of this  node  = null
        Newnode->next = NULL;
        
        if (feof(infile))
        {
            // hit end of file
            free(Newnode);
            break;
        }
        
        dictionary_count++;
        
        // hash the words 
        int index = hash_it(Newnode->word);
        
        /**
         * this part to check if you gonna put the new word 
         * in begining of the linked list or 
         * in the middle of the linked list
         * 
         * and add 1 to dictonary count every time
         **/
        if(hashtable[index] == NULL)
        {
            hashtable[index] = Newnode;
            
        }
        
        else
        {
            
            Newnode->next = hashtable[index];
            hashtable[index] = Newnode ;
            
        }
        
    }
    
    // close the file 
    fclose(infile);
    
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionary_count ;

   
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    for (int i = 0 ; i < HASHTABLE_SIZE ; i++)
    {
        node *preptr = hashtable[i];
        while(preptr != NULL )
        {
            node *PReptr = preptr ;
            preptr = preptr->next;
            free(PReptr);
        }
    }
    return true;
}