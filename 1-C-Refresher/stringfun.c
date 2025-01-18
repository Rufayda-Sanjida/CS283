#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define BUFFER_SZ 50
#define SPACE_CHAR ' '

//prototypes
void usage(char *);
void print_buff(char *, int);
int  setup_buff(char *, char *, int);

//prototypes for functions to handle required functionality
int  count_words(char *, int, int);
char *reverseString(char *, int, int);
void word_print(char *, int, int);

//add additional prototypes here

char * reverseString(char *str, int bufferSize, int user_str_len){
    int end_idx = user_str_len-1; 
    int start_idx = 0;
    char tmp_char;

    while(end_idx > start_idx){
        // 2a. swap the characters in str[start_idx] and str[end_idx]
        char tmp_char = str[start_idx];
        str[start_idx] = str[end_idx];
        str[end_idx] = tmp_char;

        // 2b. increment start_idx by 1
        start_idx++;

        // 2c. decrement end_indx by 1
        end_idx--;
    }

    return str;
}

void  word_print(char *str, int bufferSize, int user_str_len){
    //suggested local variables
    int len = user_str_len;              //length of string - aka strlen(str);
    int last_char_idx = user_str_len-1;  //index of last char - strlen(str)-1;
    int wc = 0;                          //counts words
    int wlen = 0;                        //length of current word
    bool word_start = false;             //am I at the start of a new word

    printf("Word Print\n----------\n");
    for (int i = 0; i < len; i++){  
        char currentCharacter = str[i];
        
        if (word_start == false) {
            if (currentCharacter == SPACE_CHAR ) {
                continue; // if YES, continue loop (a.k.a) goto top with "continue;"
            } else {
                wc++; //if NO, we are at the start of a new word
                word_start = true;
                wlen = 0; // 2. Now, set wlen to zero, as we will be counting characters in each word
                printf("%d. ", wc);  //3. Since we are starting a new word we can printf("%d. ", wc);
                
            }
        }

        if (word_start) {
            if (currentCharacter == SPACE_CHAR || i == last_char_idx) {
                if (currentCharacter != SPACE_CHAR) {
                    printf("%c", currentCharacter);
                    wlen++;
                }
                printf("(%d)\n", wlen);
                word_start = false;
                wlen = 0;
            } else {
                printf("%c", currentCharacter);
                wlen++;
            }
        }  
    }
    printf("\n");
    printf("Number of words returned: %d\n", wc);
    
}

int setup_buff(char *buff, char *user_str, int len){
    //TODO: #4:  Implement the setup buff as per the directions
    // user_str = string, len = 50 aka BUFFER_SZ, buff = memory

    bool lastCharWasSpace = false; 
    int i = 0;
    int k = 0;
    char currentCharacter;

    while (user_str[i] == ' ') {
        i++;
    }

    while(len > 0) {
        currentCharacter = user_str[i];
        if (currentCharacter == SPACE_CHAR){ // if current character is space increment
            if (lastCharWasSpace == false ){
                lastCharWasSpace = true;
                buff[k] = currentCharacter; //setting buffer to space 
                k++; 
                i++; 
                len--;
            }
            else {
                lastCharWasSpace = true;
                i++;
                continue; // essentially skipping the space
            }
        }
        else if (currentCharacter == '\0' ){  // if current character is LAST ITEM DO NOT INCREMENT
            break; // start putting stars in available space in buffer 
        } else {
            lastCharWasSpace = false;
            buff[k] = currentCharacter; //setting buffer to current char 
            k++; 
            i++; 
            len--;
        }
    }

    // while statement will fill the buffer with the sentance with clean spaces (no extra white space) 
    // then you have to check whether all of the sentance was put in the buffer 
    // if all of it was not put in the buffer, fill the buffer out with ... but before that save how many actual characters are in the buffer before filling it up

    int count = 0;
    char check = user_str[i];

    if (len == 0 && (!(user_str[i] == '\0'))) {
        // we ran out of space!
        return -1;
    } else if (user_str[i] == '\0'){
        count = k;
    } else if (currentCharacter == '\0') {
        count = k;
    }

    if (k > 0 && buff[k - 1] == ' ') {
        k--;
        len++;
    }

    while (len > 0) {
        buff[k++] = '.'; 
        len--;
    }
    
    return count;   
}

void print_buff(char *buff, int len){
    //printf("Buffer:  ");
    printf("Buffer:  [");
    for (int i=0; i<len; i++){
        putchar(*(buff+i));
    }
    printf("]\n");
}

void usage(char *exename){
    printf("usage: %s [-h|c|r|w|x] \"string\" [other args]\n", exename);

}

int count_words(char *buff, int len, int str_len){

    int wc = 0;
    bool word_start = false; 

    for (int i = 0; i < len; i++){  
        char currentCharacter = buff[i];
        
        if (word_start == false) {
            if (currentCharacter == SPACE_CHAR ) {
                continue; // if YES, continue loop (a.k.a) goto top with "continue;"
            } else {
                wc++; //if NO, we are at the start of a new word
                word_start = true;
            }
        } else {
            if (currentCharacter == SPACE_CHAR ) {
                word_start = false;// if YES we just ended a word, set word_start to false
            }
        }
    }
    return wc;
}

//ADD OTHER HELPER FUNCTIONS HERE FOR OTHER REQUIRED PROGRAM OPTIONS

int main(int argc, char *argv[]){

    char *buff;             //placehoder for the internal buffer
    char *input_string;     //holds the string provided by the user on cmd line
    char opt;               //used to capture user option from cmd line
    int  rc;                //used for return codes
    int  user_str_len;      //length of user supplied string

    char* reversedWord; 

    //TODO:  #1. WHY IS THIS SAFE, aka what if arv[1] does not exist?
    // this this part of the code validates the first option the user can input which is the flag or the 
    // operation to be performed on the provided string. It checks whether the user has provided at least 
    // two arguments. argv[0] is the file name and argv[1] is the option flag. if the user doesn't provide 
    // at least 2 arguments then the program will exit after displaying the help message so if arv[1] does
    // not exist, it doesn't matter because it will never be checked. The second part of the condition 
    // checks the first argument to see if it starts with a '-' because without it, it is not a valid
    // option for flags. the second part is never checked if the first part fails.


    if ((argc < 2) || (*argv[1] != '-')){
        usage(argv[0]);
        exit(1);
    }

    opt = (char)*(argv[1]+1);   //get the option flag

    //handle the help flag and then exit normally
    if (opt == 'h'){
        usage(argv[0]);
        exit(0);
    }

    //WE NOW WILL HANDLE THE REQUIRED OPERATIONS

    //TODO:  #2 Document the purpose of the if statement below
    // This checks if there's a third argument (argc < 3). If there isn't one, the program exits 
    // because it means the input string (argv[2]) is missing. The program can't do anything without 
    // that string since it's what the rest of the operations are supposed to process. By checking this, 
    // it makes sure we don't try to access something that doesn't exist, which would cause an error. 
    
    if (argc < 3){
        usage(argv[0]);
        exit(1);
    }

    input_string = argv[2]; //capture the user input string

    //TODO:  #3 Allocate space for the buffer using malloc and
    //          handle error if malloc fails by exiting with a 
    //          return code of 99
    // CODE GOES HERE FOR #3

    buff = malloc(BUFFER_SZ);
    if (buff == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(99);
    }

    user_str_len = setup_buff(buff, input_string, BUFFER_SZ);     //see todos
    if (user_str_len < 0){
        printf("Error setting up buffer, error = %d", user_str_len);
        exit(2);
    }

    switch (opt){
        case 'c':
            rc = count_words(buff, BUFFER_SZ, user_str_len);  
            if (rc < 0){
                printf("Error counting words, rc = %d", rc);
                exit(2);
            }
            printf("Word Count: %d\n", rc);
            break;

        case 'r':
            reversedWord = reverseString(buff, BUFFER_SZ, user_str_len);  
            //printf("Buffer:  [%s]\n", reversedWord);
            break;

        case 'w':
            word_print(buff, BUFFER_SZ, user_str_len);  
            break;
        //TODO:  #5 Implement the other cases for 'r' and 'w' by extending
        //       the case statement options
        
        default:
            usage(argv[0]);
            exit(1);
    }

    //TODO:  #6 Dont forget to free your buffer before exiting
    print_buff(buff, BUFFER_SZ);
    free(buff);
    exit(0);
}

//TODO:  #7  Notice all of the helper functions provided in the 
//          starter take both the buffer as well as the length.  Why
//          do you think providing both the pointer and the length
//          is a good practice, after all we know from main() that 
//          the buff variable will have exactly 50 bytes?
//  
//          PLACE YOUR ANSWER HERE:

//   Providing both the pointer (buff) and the length as arguments is a good practice 
//   because it adds flexibility and makes the code easier to maintain. If the size 
//   of the buffer needs to be changed in the future (by modifying the #define BUFFER_SZ 50 
//   global variable), this approach ensures that the change won't break the functionality 
//   of helper functions or require updating multiple instances in the code. It also simplifies 
//   debugging since the buffer size is explicitly passed, making it clear how much of the 
//   buffer is being used. This way, we only need to update BUFFER_SZ in one place, avoiding 
//   the need to track and adjust buffer size references throughout the program. Overall, it 
//   improves both the flexibility and maintainability of the code.
