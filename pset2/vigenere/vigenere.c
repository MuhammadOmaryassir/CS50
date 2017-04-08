 /*
 *
 * author:Omaroove
 * Momar.codex@gmail.com
 *
 */
 #include<cs50.h>
 #include<stdlib.h>
 #include<stdio.h>
 #include<math.h> 
 #include<ctype.h> 
 #include<string.h>
		/*
		* Handle Errors Argv must be 2 No LessNo More
		* The First Argument Cipher Key Must Be Alphaptics
 		* Get the Key
 		*/

 	int main(int argc, string argv[]) {
 		
 		if (argc != 2) { 
 			printf("You didn't submit a valid encryption key.\n");
 			printf("Please check your input and re-run the programm.\n");
 			printf("We require an string as encryption key.\n");
 			return 1;
 		} else {
 			int len = strlen(argv[1]);
 			for (int i = 0; i < len; i++) {
 				if (!isalpha(argv[1][i])) {
 					printf("You didn't submit a valid encryption key.\n");
 					printf("Please check your input and re-run the programm.\n");
 					printf("We require an string as encryption key.\n");
 					return 1;

 				}
 			}

 		}
 		/*
 		 * Get the Key
 		 * Get The PlainText
 		 */
 		printf("plaintext:");
 		string Text = get_string();
 		string Key = argv[1];

 	
 		int arglen = strlen(Key); // Getting the Length Of Key
 		int Index[arglen]; // Aray To Store the Index of the Key 
 		int c = 0;
 		int x = 0;
 		int cipher;
 		int m = 0;


 		
 		int length = strlen(Text); // Getting PlainText Length

 		char UpperLetter[26]; // array to store upper case letters
 		char LowerLetter[26]; // array to store lower case letters
 		char Big = 'A'; // var for the upper Letters 
 		char Small = 'a'; // var for lower letters


 		for (int j = 0; j < 26; j++) // to store capital letters in array
 		{
 			UpperLetter[j] = Big;
 			Big++; // incremeant the Letters from A to Z
 		}

 		for (int j = 0; j < 26; j++) // to store small letters in array
 		{

 			LowerLetter[j] = Small;
 			Small++; // incremeant the Letters from a to z
 		}

 		for (x = 0; x < arglen; x++) { // Loop on the key 
 			for (c = 0; c < 26; c++) { // loop On the Alphaptics
 				if ((Key[x] == UpperLetter[c]) || (Key[x] == LowerLetter[c])) { 

 					Index[x] = c; // Store the Key char index in the array 

 					

 				}
 			}
 		}
 		printf("ciphertext:");
 		for (int i = 0; i < length; i++) { // loop on the Text entered by the User
 			if (isupper(Text[i])) { // check if the char is Upper case


 				for (int j = 0; j < 26; j++) { // loop on the all alphaptics


 					if (Text[i] == UpperLetter[j]) { // compare between the alphaptics and the text entered 
 						for (; m < arglen ;) { // loop and use the Index Array 
 							cipher = (Index[m] + j) % 26; // the equation for the encryption 
 							printf("%c", UpperLetter[cipher]); // print the char after been ciphered
 							break;

 						}
 						m++; // Increase M 
 						if (m == arglen) {
 							m = 0; // return m to 0 to loop again in the Key  index
 						}

 					}
 				}

 			} else if (islower(Text[i])) { // check if the char is Lower case
 				for (int j = 0; j < 26; j++) { // loop on the all alphaptics


 					if (Text[i] == LowerLetter[j]) { // compare between the alphaptics and the text entered
 						
 						for (; m < arglen;) { // loop and use the Index Array
 							cipher = (Index[m] + j) % 26; // the equation for the encryption 

 							printf("%c", LowerLetter[cipher]); // print the char after been ciphered
 							break;

 						}
 						m++;
 						if (m == arglen) {
 							m = 0; // return m to 0 to loop again in the Key  index
 						}

 					}
 				}

 			} else // print  any sign or spaces ex->[!,#,.]

 				printf("%c", Text[i]);

 		}



 		printf("\n");
 	}