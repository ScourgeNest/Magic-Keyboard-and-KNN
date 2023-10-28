/* <Copyright Niculici Mihai-Daniel 2023 > */

#ifndef TRIE_H_
#define TRIE_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_STRING_SIZE 512

#define LOAD 121

#define INSERT 12321

#define EXIT -1

#define REMOVE 770497235

#define AUTOCORRECT 4321234

#define AUTOCOMPLETE 32123

#define DIE(assertion, call_description)				\
	do {								\
		if (assertion) {					\
			fprintf(stderr, "(%s, %d): ",			\
					__FILE__, __LINE__);		\
			perror(call_description);			\
			exit(errno);				        \
		}							\
	} while (0)

#define ALPHABET_SIZE 26
#define ALPHABET "abcdefghijklmnopqrstuvwxyz"

typedef struct trie_node_t trie_node_t;
struct trie_node_t {
	int end_of_word;

	trie_node_t **children;
	int n_children;
};

typedef struct trie_t trie_t;
struct trie_t {
	trie_node_t *root;

	/* Number of keys */
	int size;

	/* Trie-Specific, alphabet properties */
	int alphabet_size;
	char *alphabet;

	/* Optional - number of nodes, useful to test correctness */
	int nnodes;
};

int which_command(char *command);

trie_node_t *trie_create_node(void);
trie_t *trie_create(int alphabet_size, char *alphabet);
void trie_insert(trie_t *trie, char *key);
void *trie_search(trie_t *trie, char *key);
void trie_remove_helper(trie_t *trie, trie_node_t *node, char *key, int index);
void trie_remove(trie_t *trie, char *key);
void trie_helper_free(trie_node_t *node);
void trie_free(trie_t **ptrie);
void trie_load(trie_t *trie, char *filename);
void trie_autocorrect(trie_t *trie, char *word, int k);
void trie_autocomplete(trie_t *trie, char *prefix, int k);

void DFS_autocorrect(trie_node_t *node, char *word, int k, char *trie_word,
					 int level, int *ok);

#endif /* TRIE_H_ */
