# <p style="text-align: center;">Copyright Niculici Mihai-Daniel 2023</p>


# <p style="text-align: center;">Tema 3 SDA</p>

# <p style="text-align: center;">Task 1 - Magic Keyboard</p>

        To solve this Task I used the Trie data structure to store in an efficient way the words that are entered.

        The program reads commands endlessly until it encounters the "EXIT" command, at which point it frees the dynamically allocated memory and the program execution ends.

    Valid commands are:
        - INSERT <word> - inserts the word into the Trie
        - LOAD <file> - loads the words from the file into the Trie
        - REMOVE <word> - removes the word from the Trie
        - AUTOCORRECT <word> <tolerance> - Autocorrects the word with the given tolerance
        - AUTOCOMPLETE <prefix> <task> - Autocompletes the prefix with the given task
        - EXIT - exits the program

## <p style="text-align: center;">Commands explained</p>

* When the "INSERT" command is encountered, the word is read, then it is inserted into the trie.
    - To do this we need to create nodes for each letter of the word.

#

* When the "LOAD" command is encountered, the file name is read, then the words from the file are inserted into the trie.
    - To do this we need to open the file, read the words from the file and insert them into the trie.

#
* When the "REMOVE" command is encountered, the word is read, then it is removed from the trie.
    - To do this we need to find the word in the trie and then delete it if it doesn't affect the other words in the trie.

#
* When the "AUTOCORRECT" command is encountered, the word and the tolerance are read, then the words that are at a distance of at most the tolerance from the given word are printed.
    - To do this, we need to go through all the words in the trie and check if they are at a distance of at most the tolerance from the given word.

#
* When the "AUTOCOMPLETE" command is encountered, the prefix and the task are read
    - 0: if I encounter the task 0, then I print the lexicographically smallest word, the shortest word,
    and the word with the highest frequency.
        - I use all the functions below to find these words.

    - 1: if I encounter the task 1, then I print the lexicographically smallest word

        - To find this word, I must always go to the left side of the trie.
    - 2: if I encounter the task 2, then I print the shortest word
        - To find this word I have to go through all the words that have the given prefix and when the word is longer than the smallest word found up to the given time, I stop to save the execution time.
    - 3: if I encounter the task 3, then I print the word with the highest frequency
        - To find this word I have to go through all the words that have the given prefix and when the frequency of the word is greater than the frequency of the word found up to the given time, I change the word found up to the given time with the current word.
#

* When the "EXIT" command is encountered, the program ends and the memory is freed.
#
### <p style="text-align: center;">Conclusion:</p>
    The Trie does quite well when extraordinarily many words are inserted compared to the other data structures.
        - But even when the trie is used, the execution time is quite high!!!
#
#
# <p style="text-align: center;">Task 2 - kNN</p>

    To solve this task we used the data structure (BST) Binary Search Tree (or ABC in Romanian).

    The program reads commands endlessly until it encounters the "EXIT" command, at which point it frees the dynamically allocated memory and the program execution ends.

    Valid commands are:
        - LOAD <file> - loads the words from the file into the BST
        - NN <set_of_coord> - finds the nearest neighbor of the given set of coordinates of a point
        - RS <range_of_searching> - finds the points in the BST that are in the given range of searching
        - EXIT - frees the memory and exits the program

#

## <p style="text-align: center;">Commands explained</p>


* When the "LOAD" command is encountered, the file name is read, then the points from the file are inserted into the BST.
    - To do this we need to open the file, read the points from the file and insert them into the BST.

#

* When the "NN" command is encountered, the set of coordinates is read, then the nearest neigbours of the given set of coordinates are printed.
    - To do this we need to binary search the points in the BST and find the nearest neighbours of the given set of coordinates. (I have no idea how to do this more efficiently)

#

* When the "RS" command is encountered, the range of searching is read, then the points in the BST that are in the given range of searching are printed.
    - To do this we need to go through all the points in the BST and check if they are in the given range of searching.

#

* When the "EXIT" command is encountered, the program ends and the memory is freed.

#
### <p style="text-align: center;">Conclusion:</p>
    The BST does quite well when extraordinarily many points are inserted compared to the other data structures and I am sure that my implementation is not the most efficient.
        - But even when the BST is used, the execution time is quite high!!!
    

