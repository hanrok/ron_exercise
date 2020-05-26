#include <stdio.h>

#define STRING_SIZE 100

// this function return how many words there is in `str`
int numberOfWords(char *str, int stringSize) {
    int i = 0, wordCount = 0;
    while (i < stringSize && str[i] != '\0') {
        if (str[i] == ' ') {
            wordCount++;
            // we can have in the string more than one space in a row
            // so we need to move forward till the next word
            while (str[i] == ' ') {
                i++;
            }
            
            // we don't want to get to the next one before
            i--;
        }
        
        // so we can get to the next character (letter) next run
        i++;
    }
    
    if (i == 0) {
        // we got an empty string
        return 0;
    } 
    
    // adding 1 because of the last word (there is no space after)
    // for example: "This is   my string" - "string", the last word doesn't count
    return wordCount + 1;
}

// this function prints for each word in `str` how many letters in it
void printNumberOfLetters(char *str, int stringSize) {
    int i = 0, letterCount = 0;
    
    while (i < stringSize && str[i] != '\0') {
        if (str[i] == ' ') {
            printf(" %d\n", letterCount);
            letterCount = 0;
            
            // we can have in the string more than one space in a row
            // so we need to move forward till the next word
            while (str[i] == ' ') {
                i++;
            }
            
            // we don't want to get to the next one before
            i--;
        } else {
            printf("%c", str[i]);
            letterCount++;
        }
        
        // so we can get to the next character (letter) next run
        i++;
    }
    
    if (letterCount != 0) {
        // we have last word in the end of the string for example "this is thisthisthis"
        // we need to print the last word count
        printf(" %d\n", letterCount);
    }
}

// this function returns the position of the longest word in the string
int getLongestWordPosition(char *str, int stringSize) {
    int i = 0, letters = 0, longest = 0, longest_pos = 0;
    
    // we stop if we get to NULL ('\0') or we got to the size of the string
    while (i < stringSize && str[i] != '\0') {
        // we count the letters till we get space (' ') or NULL('\0') or the size of the string
        // if you are not familiar with `for` loop, this is much like while accept it has
        // 2 more sections. for example this while loop:
        // i = 0;
        // while (i < 10) {
        //  printf("%d", i);
        //  i++;
        // }
        // is the same as the for loop:
        // for (i = 0; i < 10; i++) {
        //  printf("%d", i)
        // }
        for (letters = 0; str[i] != '\0' && str[i] != ' ' && i < stringSize; i++) {
            letters++;
        }
        
        // if we found a word that it's larger than what we already found
        if (letters > longest) {
            longest = letters;
            longest_pos = i - longest;
        }

        // in the exercise written that could be more than one space between words
        // so we need to move forward till we "see" a letter that isn't a space
        while (str[i] == ' ') {
            i++;
        }
    }
    
    return longest_pos;
}

// this function prints the longest word using getLongestWordPosition function
void printLongestWord(char *str, int stringSize) {
    // getting the longest word position in the string
    int pos = getLongestWordPosition(str, stringSize);
    // we want to start from that position
    int i = pos;
    
    // we stop if we get to the length of the string, or if we get to NULL
    // or if we get to space
    while (str[i] != '\0' && str[i] != ' ' && i < stringSize) {
        // printing only one letter, without any newline
        // so that if the word is "this" than in each loop cycle we will print
        // one letters: 't' than 'h' than 'i' and finally 's'
        // so the output will look like 'this'
        printf("%c", str[i]);
        i++;
    }
    
    // printing newline at the end
    printf("\n");
}

// please take a look how we did the longest word, it's more of the same
int getShortestWordPosition(char *str, int stringSize) {
    int i = 0, letters = 0, shortest = stringSize, shortest_pos = 0;
    
    while (i < stringSize && str[i] != '\0') {
        for (letters = 0; str[i] != '\0' && str[i] != ' ' && i < stringSize; i++) {
            letters++;
        }
        
        if (letters < shortest) {
            shortest = letters;
            shortest_pos = i - shortest;
        }

        while (str[i] == ' ') {
            i++;
        }
    }
    
    return shortest_pos;
}

// please take a look how we did the longest word, it's more of the same
void printShortestWord(char *str, int stringSize) {
    int pos = getShortestWordPosition(str, stringSize);
    int i = pos;
    
    while (str[i] != '\0' && str[i] != ' ' && i < stringSize) {
        printf("%c", str[i]);
        i++;
    }
    
    printf("\n");
}

// this function prints how many appearances there is for the shortest word in the
// string in the longest word of the string
// to be honest, I don't know if I understand well the exercise and if that what they
// expect us to do.
// I'm doing it by moving to the position of the start of the longest word than
// moving forward each letter and check if the letter is the same as the shortest word
// letter
// please tell me if you don't understand something
void printShortestWordAppearance(char *str, int stringSize) {
    int shortestPos = getShortestWordPosition(str, stringSize);
    int longestPos = getLongestWordPosition(str, stringSize);
    int pos = 0, relativePos = 0, i = 0, appears = 0, shortestSize = 0;
    
    if (shortestPos == longestPos) {
        // the longest word and the shortest word are the same word (in the same position)
        return 1;
    }
    
    // computing how long is the shortest word
    pos = shortestPos;
    while(str[pos] != '\0' && str[pos] != ' ' && pos < stringSize) {
        shortestSize++;
        pos ++;
    }
    
    pos = longestPos;
    while (str[pos] != '\0' && str[pos] != ' ' && pos < stringSize) {
        // check if we get the same letter in the longest word
        // say we have for example the word "asdfisasdf" as the longest and "is" as the shortest
        // so we want to move, 'a', 's' ... till we get 'i' because the shortest word starts with 'i'
        if (str[pos] == str[shortestPos]) {
            // we are using `relativePos` instead of `pos` because there might be more the one occurence
            // of the word. let's say the longest word is "isisibbf" and the short is "isi" we will find only
            // one occurence if we don't use the relative because we will find the start "isi.." but we 
            // wouldn't find the second "..isibbf" because we skipped it
            relativePos = pos;
            i = 0;
            while (i < shortestSize && str[relativePos] == str[shortestPos + i] && str[relativePos] != '\0' && str[relativePos] != ' ' && relativePos < stringSize) {
                i++;
                relativePos++;
            }
            
            if (i == shortestSize) {
                // we got a match :)
                appears++;
            }
        }
        pos++;
    }
    
    printf("The shortest word appears %d times in the longest word\n", appears);
}

int main()
{
    char inputString[STRING_SIZE];
    int userChoice = 0;
    
    printf("Please enter the string: ");
    gets(inputString);
    
    while (userChoice != 6) {
        printf("\nEnter your choice:\n\n");
        printf("1 - Print number of words\n");
        printf("2 – Print number of letters in every word\n");
        printf("3 – Print longest word\n");
        printf("4 – Print shortest word\n");
        printf("5 – Print how many times shortest word appears in longest word\n");
        printf("6 – Exit from the program Enter your choice:\n\n");
        
        scanf("%d", &userChoice);
        printf("User choice: %d\n", userChoice);
        
        if (userChoice == 1) {
            printf("Number of words: %d\n", numberOfWords(inputString, STRING_SIZE));
        } else if (userChoice == 2) {
            printNumberOfLetters(inputString, STRING_SIZE);
        } else if (userChoice == 3) {
            printLongestWord(inputString, STRING_SIZE);
        } else if (userChoice == 4) {
            printShortestWord(inputString, STRING_SIZE);
        } else if (userChoice == 5) {
            printShortestWordAppearance(inputString, STRING_SIZE);
        } else if (userChoice != 6) {
            printf("\nPlease enter a valid choice (1-6)\n");
        }
    }
    
    return 0;
}

