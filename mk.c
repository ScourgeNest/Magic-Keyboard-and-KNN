/* <Copyright Niculici Mihai-Daniel 2023 > */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "trie.h"

int main(void)
{
	// Allocate memory for the command
	char *command = malloc(MAX_STRING_SIZE);
	int k;
	DIE(!command, "command malloc failed!\n");

	// Create the trie
	trie_t *trie = trie_create(ALPHABET_SIZE, ALPHABET);

	// Read commands
	while (1) {
		scanf("%s", command);
		// Which command is it?
		switch (which_command(command)) {
		case INSERT:
			// Read the word to be inserted
			scanf("%s", command);
			trie_insert(trie, command);
			break;

		case LOAD:
			// Load the words from the file into the trie
			scanf("%s", command);
			trie_load(trie, command);
			break;

		case REMOVE:
			// Remove the word from the trie
			scanf("%s", command);
			trie_remove(trie, command);
			break;

		case AUTOCORRECT:
			// Autocorrect the word
			scanf("%s", command);
			scanf("%d", &k);
			trie_autocorrect(trie, command, k);
			break;

		case AUTOCOMPLETE:
			// Autocomplete the word
			scanf("%s", command);
			scanf("%d", &k);
			trie_autocomplete(trie, command, k);
			break;

		case EXIT:
			// Free the memory and exit
			trie_free(&trie);
			free(command);
			return 0;

		default:
			// Wrong command
			continue;
		}
	}
}
