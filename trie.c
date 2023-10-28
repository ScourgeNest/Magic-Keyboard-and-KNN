/* <Copyright Niculici Mihai-Daniel 2023 > */

#include "trie.h"

/******************************************************************************
 * This function creates a node by dynamically allocating it, then returns it.
 *
 * @param ----------------
 *
 * @return node - A pointer to the node created.
 *****************************************************************************/
trie_node_t *trie_create_node(void)
{
	// Allocating memory for the node
	trie_node_t *node = (trie_node_t *)malloc(sizeof(trie_node_t));
	DIE(!node, "Failed to allocate memory for trie node");

	// Allocate memory for the children vector
	node->children = (trie_node_t **) malloc(sizeof(trie_node_t *) *
											 ALPHABET_SIZE);
	DIE(!node->children, "Failed to allocate memory for trie node children");

	// We initialize each of the children with NULL
	for (int i = 0; i < ALPHABET_SIZE; i++)
		node->children[i] = NULL;

	// We set the other fields to 0.
	node->n_children = 0;
	node->end_of_word = 0;

	// Return the node
	return node;
}

/******************************************************************************
 * This function creates a trie, allocates it dynamically, and then returns it.
 *
 * @param alphabet_size: the size of the alphabet
 * @param alphabet: the alphabet
 *
 * @return trie - A pointer to the trie created.
 *****************************************************************************/
trie_t *trie_create(int alphabet_size, char *alphabet)
{
	// Allocating memory for the trie
	trie_t *trie = (trie_t *)malloc(sizeof(trie_t));
	DIE(!trie, "Failed to allocate memory for trie");

	// We create the root node
	trie->root = trie_create_node();

	// We set the other fields to 0.
	trie->size = 0;
	trie->alphabet_size = alphabet_size;
	trie->alphabet = alphabet;
	trie->nnodes = 1;

	// Return the trie
	return trie;
}

/******************************************************************************
 * This function inserts a word into the trie.
 *
 * @param trie - A pointer to the trie data structure.
 * @param key - The word that has to be inserted in the trie.
 *****************************************************************************/
void trie_insert(trie_t *trie, char *key)
{
	// Start from the root
	trie_node_t *node = trie->root;

	// Iterate through the word
	for (int i = 0; i < (int)(strlen(key)); i++) {
		// If the current letter is not in the trie, we add it
		if (node->children[key[i] - 'a'] == NULL) {
			// Create a new node
			node->children[key[i] - 'a'] = trie_create_node();

			// Increment the number of children of the current node
			node->n_children++;

			// Increment the number of nodes in the trie
			trie->nnodes++;
		}

		// Go to the next node
		node = node->children[key[i] - 'a'];
	}
	// Mark the end of the word
	node->end_of_word++;

	// Increment the size of the trie
	trie->size++;
}

/******************************************************************************
 * This function searches for a word in the trie and returns it.
 *
 * @param trie - A pointer to the trie data structure.
 * @param key - The word that has to be searched in the trie.
 *
 * @return node - A pointer to the node that contains the word.
 *****************************************************************************/
void *trie_search(trie_t *trie, char *key)
{
	// Verify if the word exists
	if (!key[0])
		return trie->root;

	// Start from the root
	trie_node_t *node = trie->root;

	// Iterate through the word
	for (int i = 0; i < (int)(strlen(key)); i++) {
		// If the current letter is not in the trie, return NULL
		if (node->children[key[i] - 'a'] == NULL)
			return NULL;
		// Go to the next node
		node = node->children[key[i] - 'a'];
	}
	// If the word exists, return the node
	if (node->end_of_word != 0)
		return node;
	// Otherwise, return NULL
	return NULL;
}

/******************************************************************************
 * This function is a helper function used to remove a node from a trie data
 * structure. It is called recursively to remove the nodes associated with the
 * given word.
 * @param trie - A pointer to the trie data structure.
 * @param node - A pointer to the current node being processed.
 * @param key - The word that has to be removed from the trie.
 * @param index - The index of the current character in the key being processed.
 **************************************************************************/
void trie_remove_helper(trie_t *trie, trie_node_t *node, char *key, int index)
{
	// If the index is equal to the length of the key, we reached the end of
	// the word.
	if (index == (int)(strlen(key))) {
		// If there is end_of_word, we remove the word
		if (node->end_of_word != 0) {
			node->end_of_word = 0;

			// We decrement the size of the trie
			trie->size--;

			// If the node has no children, we remove it
			if (node->n_children == 0) {
				free(node->children);
				node->children = NULL;
			}
		}
		// Otherwise, we do nothing
		return;
	}

	// If the current letter is not in the trie, we return
	if (node->children[key[index] - 'a'] == NULL)
		return;

	// We go to the next node
	trie_remove_helper(trie, node->children[key[index] - 'a'], key, index + 1);

	// If the node has no children and it is not the end of a word, we remove it
	if (node->children[key[index] - 'a']->n_children == 0 &&
		node->children[key[index] - 'a']->end_of_word == 0) {
		// We free the memory of the children vector
		if (node->children[key[index] - 'a']->children) {
			free(node->children[key[index] - 'a']->children);
			node->children[key[index] - 'a']->children = NULL;
		}

		// We free the node
		if (node->children[key[index] - 'a']) {
			free(node->children[key[index] - 'a']);
			node->children[key[index] - 'a'] = NULL;
		}

		// We decrement the number of children of the current node
		node->n_children--;

		// We decrement the number of nodes in the trie
		trie->nnodes--;
	}
}

/******************************************************************************
 * This function removes a word from the trie.
 *
 * @param trie - A pointer to the trie data structure.
 * @param key - The word that has to be removed from the trie.
 *****************************************************************************/
void trie_remove(trie_t *trie, char *key)
{
	// Start from the root
	trie_node_t *node = trie->root;

	// Call the helper function
	trie_remove_helper(trie, node, key, 0);
}

/******************************************************************************
 * This function is a helper function that is used to free the memory
 * allocated by trie.
 *
 * @param node - A pointer to the node that has to be freed.
 *****************************************************************************/
void trie_helper_free(trie_node_t *node)
{
	// If the node is NULL, return
	if (!node)
		return;

	// If the node has children, we free the memory allocated for the children
	for (int i = 0; i < ALPHABET_SIZE; i++)
		trie_helper_free(node->children[i]);

	// Free the memory allocated for the children vector
	free(node->children);
	node->children = NULL;

	// Free the node
	free(node);
	node = NULL;
}

/******************************************************************************
 * This function frees the memory allocated by a trie.
 *
 * @param ptrie - A double pointer to the trie data structure.
 *****************************************************************************/
void trie_free(trie_t **ptrie)
{
	trie_helper_free((*ptrie)->root);
	free(*ptrie);
	*ptrie = NULL;
}

/******************************************************************************
 * This function compares the command read from the keyboard with the commands
 * preset by mk.
 *
 * @param command - The command read from the keyboard.
 *****************************************************************************/
int which_command(char *command)
{
	// We compare the command with the preset commands
	if (strcmp(command, "LOAD") == 0)
		return LOAD;
	if (strcmp(command, "INSERT") == 0)
		return INSERT;
	if (strcmp(command, "REMOVE") == 0)
		return REMOVE;
	if (strcmp(command, "EXIT") == 0)
		return -1;
	if (strcmp(command, "AUTOCORRECT") == 0)
		return AUTOCORRECT;
	if (strcmp(command, "AUTOCOMPLETE") == 0)
		return AUTOCOMPLETE;

	// If the command is not preset, we return -1
	return -1;
}

/******************************************************************************
 * This function inserts in a trie all the words that are in the file given as
 * a parameter.
 *
 * @param trie - A pointer to the trie data structure.
 * @param filename - The name of the file that contains the words.
 *****************************************************************************/
void trie_load(trie_t *trie, char *filename)
{
	// Open the file
	FILE *file = fopen(filename, "r");
	DIE(!file, "Failed to open file");

	// Allocate memory for the word
	char *word = malloc(MAX_STRING_SIZE * sizeof(char));
	DIE(!word, "Failed to allocate memory for word");

	// Read the words from the file and insert them in the trie
	while (!feof(file)) {
		// Read the word
		fscanf(file, "%s", word);

		// Insert the word in the trie
		trie_insert(trie, word);
	}

	// Close the file
	fclose(file);

	// Free the memory allocated for the word
	free(word);
}

/******************************************************************************
 * This function performs depth-first search (DFS) for autocorrect in a trie.
 *
 * @param node: Pointer to the trie node
 * @param word: The word to autocorrect
 * @param k: The maximum number of allowed differences between words
 * @param trie_word: The current word formed in the trie traversal
 * @param level: The current level of the trie traversal
 * @param ok: Pointer to a flag indicating if an autocorrected word was found
 *****************************************************************************/
void DFS_autocorrect(trie_node_t *node, char *word, int k, char *trie_word,
					 int level, int *ok)
{
	// If the node is NULL, return
	if (!node)
		return;

	// If the node is the end of a word, we verify if the word is valid
	if (node->end_of_word != 0 && level == (int)strlen(word)) {
		trie_word[strlen(word)] = '\0';
		int count = 0;
		// We compare the word with the trie_word
		for (int j = 0; j < (int)strlen(word); j++) {
			if (word[j] != trie_word[j])
				count++;
		}
		if (count <= k) {
			*ok = 1;
			printf("%s\n", trie_word);
			return;
		}
	}
	if (level > (int)strlen(word))
		return;

	// If the node has children, we continue the DFS
	if (node->n_children != 0) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			// If the current letter is in the trie, we continue the DFS
			if (node->children[i]) {
				// We add the current letter to the trie_word
				trie_word[level] = i + 'a';

				// We continue the DFS
				DFS_autocorrect(node->children[i], word, k, trie_word,
								level + 1, ok);
			}
		}
	}
}

/******************************************************************************
 * This function performs autocorrect on a trie.
 *
 * @param trie: Pointer to the trie structure
 * @param word: The input word to autocorrect
 * @param k: The maximum number of allowed differences between words
 *****************************************************************************/
void trie_autocorrect(trie_t *trie, char *word, int k)
{
	// Start from the root
	trie_node_t *node = trie->root;
	int ok = 0;

	// Allocate memory for the trie_word
	char *trie_word = malloc(MAX_STRING_SIZE * sizeof(char));
	DIE(!trie_word, "Failed to allocate memory for trie_word");

	// We call the DFS function
	DFS_autocorrect(node, word, k, trie_word, 0, &ok);

	// If the word is not valid, we print "No words found"
	if (ok == 0)
		printf("No words found\n");

	// Free the memory allocated for the trie_word
	free(trie_word);
}

/******************************************************************************
 * This function prints the result of task_1 in the autocomplete process.
 *
 * @param ok_1 - Flag indicating if a word was found (1) or not (0).
 * @param lex_word - The lexicographically smallest word found.
*****************************************************************************/
void print_task_1(int ok_1, char *lex_word)
{
	if (ok_1 == 0)
		printf("No words found\n");
	else
		printf("%s\n", lex_word);
}

/******************************************************************************
 * This function prints the result of task_2 in the autocomplete process.
 *
 * @param ok_2 - Flag indicating if a word was found (1) or not (0).
 * @param shortest_word - The shortest word found.
*****************************************************************************/
void print_task_2(int ok_2, char *shortest_word)
{
	if (ok_2 == 0)
		printf("No words found\n");
	else
		printf("%s\n", shortest_word);
}

/******************************************************************************
 * This function prints the result of task_3 in the autocomplete process.
 *
 * @param ok_3 - Flag indicating if a word was found (1) or not (0).
 * @param freq_word - The word with the highest frequency found.
*****************************************************************************/
void print_task_3(int ok_3, char *freq_word)
{
	if (ok_3 == 0)
		printf("No words found\n");
	else
		printf("%s\n", freq_word);
}

/******************************************************************************
 * This function performs a depth-first search on a trie data structure,
 * starting from a given node and a specified prefix. It searches for the
 * lexicographically smallest word that matches the prefix and updates the
 * lex_word parameter accordingly.
 *
 * @param node - A pointer to the current node in the trie.
 * @param prefix - The prefix to match.
 * @param lex_word - The lexicographically smallest word found so far.
 * @param aux - An auxiliary buffer to store the current word being constructed
 * @param level - The current level in the trie.
 * @param ok_1 - A pointer to a flag indicating if a valid word has been found.
*****************************************************************************/
void task_1(trie_node_t *node, char *prefix, char *lex_word, char *aux,
			int level, int *ok_1)
{
	// If the node is NULL, return
	if (!node)
		return;

	// If the level is 0, we iterate through the prefix
	if (level == 0) {
		for (int i = 0; i < (int)strlen(prefix); i++) {
			if (node->children[prefix[i] - 'a'] != NULL) {
				aux[level] = prefix[i];
				node = node->children[prefix[i] - 'a'];
				level++;
			} else {
				return;
			}
		}
	}

	// If the node is the end of a word, we verify if the word is valid
	if (node->end_of_word != 0) {
		aux[level] = '\0';
		if (strcmp(aux, lex_word) < 0) {
			*ok_1 = 1;
			strcpy(lex_word, aux);
			return;
		}
	}

	// If the node has children, we continue the DFS
	if (node->n_children != 0) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			// If the current letter is in the trie, we continue the DFS
			if (node->children[i]) {
				// We add the current letter to the trie_word
				aux[level] = i + 'a';

				// We continue the DFS
			   task_1(node->children[i], prefix, lex_word, aux, level + 1,
					  ok_1);
			}
		}
	}
}

/******************************************************************************
 * This function finds the shortest word in a trie that matches a given prefix.
 *
 * @param node - A pointer to the current node in the trie.
 * @param prefix - The prefix to match.
 * @param shortest_word - The shortest word found so far.
 * @param aux - An auxiliary buffer to store the current word being constructed
 * @param level - The current level in the trie.
 * @param ok_2 - A pointer to a flag indicating if a valid word has been found.
*****************************************************************************/
void task_2(trie_node_t *node, char *prefix, char *shortest_word, char *aux,
			int level, int *ok_2)
{
	// If the node is NULL, return
	if (!node)
		return;

	// If the level is greater than the length of the shortest word, we return
	if (level > (int)strlen(shortest_word))
		return;

	// If the level is 0, we iterate through the prefix
	if (level == 0) {
		for (int i = 0; i < (int)strlen(prefix); i++) {
			if (node->children[prefix[i] - 'a']) {
				aux[level] = prefix[i];
				node = node->children[prefix[i] - 'a'];
				level++;
			} else {
				return;
			}
		}
	}

	// If the node is the end of a word, we verify if the word is valid
	if (node->end_of_word != 0) {
		aux[level] = '\0';
		if (strlen(aux) < strlen(shortest_word)) {
			*ok_2 = 1;
			strcpy(shortest_word, aux);
		}
	}

	// If the node has children, we continue the DFS
	if (node->n_children != 0) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			// If the current letter is in the trie, we continue the DFS
			if (node->children[i]) {
				// We add the current letter to the trie_word
				aux[level] = i + 'a';

				// We continue the DFS
				task_2(node->children[i], prefix, shortest_word, aux,
					   level + 1, ok_2);
			}
		}
	}
}

/******************************************************************************
 * This function finds the word with the highest frequency in a trie that
 * matches a given prefix.
 *
 * @param node - A pointer to the current node in the trie.
 * @param prefix - The prefix to match.
 * @param freq_word - The word with the highest frequency found so far.
 * @param aux - An auxiliary buffer to store the current word being constructed
 * @param level - The current level in the trie.
 * @param ok_3 - A pointer to a flag indicating if a valid word has been found.
 * @param max_freq - A pointer to the maximum frequency found so far.
*****************************************************************************/
void task_3(trie_node_t *node, char *prefix, char *freq_word, char *aux,
			int level, int *ok_3, int *max_freq)
{
	// If the node is NULL, return
	if (!node)
		return;

	// If the level is 0, we iterate through the prefix
	if (level == 0) {
		for (int i = 0; i < (int)strlen(prefix); i++) {
			if (node->children[prefix[i] - 'a']) {
				aux[level] = prefix[i];
				node = node->children[prefix[i] - 'a'];
				level++;
			} else {
				return;
			}
		}
	}

	// If the node is the end of a word, we verify if the word is valid
	if (node->end_of_word != 0) {
		aux[level] = '\0';
		if (node->end_of_word > *max_freq) {
			*ok_3 = 1;
			strcpy(freq_word, aux);
			*max_freq = node->end_of_word;
		}
	}

	// If the node has children, we continue the DFS
	if (node->n_children != 0) {
		for (int i = 0; i < ALPHABET_SIZE; i++) {
			// If the current letter is in the trie, we continue the DFS
			if (node->children[i]) {
				// We add the current letter to the trie_word
				aux[level] = i + 'a';

				// We continue the DFS
				task_3(node->children[i], prefix, freq_word, aux, level + 1,
					   ok_3, max_freq);
			}
		}
	}
}

/******************************************************************************
 * This function performs autocomplete on a trie given a prefix and returns
 * results based on the specified criteria.
 *
 * @param trie - A pointer to the trie data structure.
 * @param prefix - The prefix to match.
 * @param k - The criteria for autocomplete results:
 *      - k = 0: Returns the lexicographically smallest word, the shortest word,
 *               and the word with the highest frequency.
 *      - k = 1: Returns the lexicographically smallest word.
 *      - k = 2: Returns the shortest word.
 *      - k = 3: Returns the word with the highest frequency.
*****************************************************************************/
void trie_autocomplete(trie_t *trie, char *prefix, int k)
{
	// We allocate memory for the words
	int ok_1 = 0;
	int ok_2 = 0;
	int ok_3 = 0;

	int max_freq = 0;

	// Allocate memory for the words
	char *lex_word = malloc(MAX_STRING_SIZE * sizeof(char));
	DIE(!lex_word, "Failed to allocate memory for lexicographic_word");
	strcpy(lex_word, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");

	char *freq_word = malloc(MAX_STRING_SIZE * sizeof(char));
	DIE(!freq_word, "Failed to allocate memory for frequency_word");
	strcpy(freq_word, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");

	char *shortest_word = malloc(MAX_STRING_SIZE * sizeof(char));
	DIE(!shortest_word, "Failed to allocate memory for shortest_word");
	strcpy(shortest_word, "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz");

	char *aux = malloc(MAX_STRING_SIZE * sizeof(char));
	DIE(!aux, "Failed to allocate memory for aux");
	strcpy(aux, "");

	// We call the task functions
	switch (k) {
	// If k = 0, we call all the task functions
	case 0:
		task_1(trie->root, prefix, lex_word, aux, 0, &ok_1);

		print_task_1(ok_1, lex_word);

		// We reset the auxiliary buffer
		strcpy(aux, "");

		task_2(trie->root, prefix, shortest_word, aux, 0, &ok_2);

		print_task_2(ok_2, shortest_word);

		// We reset the auxiliary buffer
		strcpy(aux, "");

		task_3(trie->root, prefix, freq_word, aux, 0, &ok_3, &max_freq);

		print_task_3(ok_3, freq_word);

		// We reset the auxiliary buffer
		strcpy(aux, "");
		break;

	// If k = 1, we call the task_1 function
	case 1:
		task_1(trie->root, prefix, lex_word, aux, 0, &ok_1);
		print_task_1(ok_1, lex_word);
		break;

	// If k = 2, we call the task_2 function
	case 2:
		task_2(trie->root, prefix, shortest_word, aux, 0, &ok_2);
		print_task_2(ok_2, shortest_word);
		break;

	// If k = 3, we call the task_3 function
	case 3:
		task_3(trie->root, prefix, freq_word, aux, 0, &ok_3, &max_freq);
		print_task_3(ok_3, freq_word);
		break;

	default:
		// If the command is not preset, we return
		break;
	}

	// Free the memory allocated for the words
	free(lex_word);
	free(freq_word);
	free(shortest_word);
	free(aux);
}
