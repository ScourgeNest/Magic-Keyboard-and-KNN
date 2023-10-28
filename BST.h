/* <Copyright Niculici Mihai-Daniel 2023 > */

#ifndef BST_H_
#define BST_H_

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <math.h>

#define MAX_NODES 150000
#define MAX_STRING_SIZE 512
#define INT_MAX 2147483647

#define DIE(assertion, call_description)  \
	do {                                  \
										  \
		if (assertion) {                  \
										  \
			fprintf(stderr, "(%s, %d): ", \
					__FILE__, __LINE__);  \
			perror(call_description);     \
			exit(errno);                  \
		}                                 \
	} while (0)

typedef struct b_node_t b_node_t;
struct b_node_t {
	/* left child */
	b_node_t *left;
	/* right child */
	b_node_t *right;

	/* data contained by the node */
	void *data;
};

typedef struct b_tree_t b_tree_t;
struct b_tree_t {
	/* root of the tree */
	b_node_t *root;

	/* size of the data contained by the nodes */
	size_t data_size;
};

typedef struct queue_t queue_t;
struct queue_t {
	/* Dimensiunea maxima a cozii */
	unsigned int max_size;
	/* Dimensiunea cozii */
	unsigned int size;
	/* Dimensiunea in octeti a tipului de date stocat in coada */
	unsigned int data_size;
	/* Indexul de la care se vor efectua operatiile de front si dequeue */
	unsigned int read_idx;
	/* Indexul de la care se vor efectua operatiile de enqueue */
	unsigned int write_idx;
	/* Bufferul ce stocheaza elementele cozii */
	void **buff;
};

/* Helper queue data structure definitions */
queue_t *q_create(unsigned int data_size, unsigned int max_size);
unsigned int q_get_size(queue_t *q);
unsigned int q_is_empty(queue_t *q);
void *q_front(queue_t *q);
int q_dequeue(queue_t *q);
int q_enqueue(queue_t *q, void *new_data);
void q_clear(queue_t *q);
void q_free(queue_t *q);

b_node_t *__b_node_create(void *data, size_t data_size);
b_tree_t *b_tree_create(size_t data_size);
b_node_t *b_tree_insert(b_tree_t *b_tree, b_node_t *root, void *data,
						int level, int k);
void b_tree_print_inorder(b_node_t *root);
void __b_tree_free(b_node_t *b_node);
void b_tree_free(b_tree_t *b_tree);

b_tree_t *load(b_tree_t *tree, int *k);
void NN(b_tree_t *tree, b_node_t *root, int *vector_of_coord, int level,
		int k, int *size, int *result, int *min_distance);
void RS(b_tree_t *tree, b_node_t *root, int k, int *start, int *end);
void EXIT(b_tree_t *tree);

#endif /* BST_H_ */
