/* <Copyright Niculici Mihai-Daniel 2023 > */

#include "BST.h"
#include <math.h>

/******************************************************************************
 * This function creates a binary tree node and initializes it with the given
 * data.
 *
 * @param data - The data to be stored in the node.
 * @param data_size - The size of the data.
 *
 * @return b_node_t* - A pointer to the newly created binary tree node.
*****************************************************************************/
b_node_t *__b_node_create(void *data, size_t data_size)
{
	b_node_t *b_node;

	b_node = malloc(sizeof(*b_node));
	DIE(!b_node, "b_node malloc");

	b_node->left = NULL;
	b_node->right = NULL;

	b_node->data = malloc(data_size);
	DIE(!b_node->data, "b_node->data malloc");
	memcpy(b_node->data, data, data_size);

	return b_node;
}

/******************************************************************************
 * This function creates a binary tree and initializes it.
 *
 * @param data_size - The size of the data to be stored in the tree nodes.
 *
 * @return b_tree_t* - A pointer to the newly created binary tree.
*****************************************************************************/
b_tree_t *b_tree_create(size_t data_size)
{
	b_tree_t *b_tree;

	b_tree = malloc(sizeof(*b_tree));
	DIE(!b_tree, "b_tree malloc");

	b_tree->root = NULL;
	b_tree->data_size = data_size;

	return b_tree;
}

/******************************************************************************
 * This function inserts a node into a binary tree.
 *
 * @param b_tree - A pointer to the binary tree.
 * @param root - The node of the binary tree.
 * @param data - The data to be inserted into the node.
 * @param level - The current level of the tree.
 * @param k - The number of dimensions (coordinates) of the data.
 *
 * @return b_node_t* - The root of the modified binary tree.
*****************************************************************************/
b_node_t *b_tree_insert(b_tree_t *b_tree, b_node_t *root, void *data,
						int level, int k)
{
	int *vector_of_coord = (int *)data;

	if (!root)
		return __b_node_create(data, b_tree->data_size);
	int coordonates = vector_of_coord[level % k];

	if (coordonates < ((int *)root->data)[level % k])
		root->left = b_tree_insert(b_tree, root->left, vector_of_coord,
								   level + 1, k);
	else
		root->right = b_tree_insert(b_tree, root->right, vector_of_coord,
									level + 1, k);
	return root;
}

/******************************************************************************
 * This function frees the memory allocated for a binary tree node and its
 * children.
 *
 * @param b_node - The node to be freed.
*****************************************************************************/
void __b_tree_free(b_node_t *b_node)
{
	if (!b_node)
		return;

	__b_tree_free(b_node->left);
	__b_tree_free(b_node->right);
	free(b_node->data);
	free(b_node);
}

/******************************************************************************
 * This function frees the memory allocated for a binary tree and its nodes.
 *
 * @param b_tree - The binary tree to be freed.
*****************************************************************************/
void b_tree_free(b_tree_t *b_tree)
{
	__b_tree_free(b_tree->root);
	free(b_tree);
}

/******************************************************************************
 * This function creates and initializes a queue.
 *
 * @param data_size - The size of each element in the queue.
 * @param max_size - The maximum size of the queue.
 *
 * @return queue_t* - A pointer to the created queue.
*****************************************************************************/
queue_t *q_create(unsigned int data_size, unsigned int max_size)
{
	queue_t *q = calloc(1, sizeof(*q));
	DIE(!q, "calloc queue failed");

	q->data_size = data_size;
	q->max_size = max_size;

	q->buff = malloc(max_size * sizeof(*q->buff));
	DIE(!q->buff, "malloc buffer failed");

	return q;
}

/******************************************************************************
 * This function returns the size of a queue.
 *
 * @param q - A pointer to the queue.
 *
 * @return unsigned int - The size of the queue.
*****************************************************************************/
unsigned int q_get_size(queue_t *q)
{
	return !q ? 0 : q->size;
}

/******************************************************************************
 * This function checks if a queue is empty.
 *
 * @param q - A pointer to the queue.
 *
 * @return unsigned int - 1 if the queue is empty, 0 otherwise.
*****************************************************************************/
unsigned int q_is_empty(queue_t *q)
{
	return !q ? 1 : !q->size;
}

/******************************************************************************
 * This function returns the front element of a queue.
 *
 * @param q - A pointer to the queue.
 *
 * @return void* - A pointer to the front element of the queue.
*****************************************************************************/
void *q_front(queue_t *q)
{
	if (!q || !q->size)
		return NULL;

	return q->buff[q->read_idx];
}

/******************************************************************************
 * This function dequeues an element from a queue.
 *
 * @param q - A pointer to the queue.
 *
 * @return int - 1 if the dequeue was successful, 0 otherwise.
*****************************************************************************/
int q_dequeue(queue_t *q)
{
	if (!q || !q->size)
		return 0;

	free(q->buff[q->read_idx]);

	q->read_idx = (q->read_idx + 1) % q->max_size;
	--q->size;
	return 1;
}

/******************************************************************************
 * This function enqueues an element into a queue.
 *
 * @param q - A pointer to the queue.
 * @param new_data - The data to be enqueued.
 *
 * @return int - 1 if the enqueue was successful, 0 otherwise.
*****************************************************************************/
int q_enqueue(queue_t *q, void *new_data)
{
	void *data;
	if (!q || q->size == q->max_size)
		return 0;

	data = malloc(q->data_size);
	DIE(!data, "malloc data failed");
	memcpy(data, new_data, q->data_size);

	q->buff[q->write_idx] = data;
	q->write_idx = (q->write_idx + 1) % q->max_size;
	++q->size;

	return 1;
}

/******************************************************************************
 * This function clears a queue.
 *
 * @param q - A pointer to the queue.
*****************************************************************************/
void q_clear(queue_t *q)
{
	unsigned int i;
	if (!q || !q->size)
		return;

	for (i = q->read_idx; i != q->write_idx; i = (i + 1) % q->max_size)
		free(q->buff[i]);

	q->read_idx = 0;
	q->write_idx = 0;
	q->size = 0;
}

/******************************************************************************
 * This function frees the memory allocated for a queue.
 *
 * @param q - A pointer to the queue.
*****************************************************************************/
void q_free(queue_t *q)
{
	if (!q)
		return;

	q_clear(q);
	free(q->buff);
	free(q);
}

/******************************************************************************
 * This function loads data from a file and creates a binary tree.
 *
 * @param tree - The binary tree to load the data into.
 * @param k - A pointer to the value representing the number of coordinates.
 *
 * @return b_tree_t* - A pointer to the loaded binary tree.
*****************************************************************************/
b_tree_t *load(b_tree_t *tree, int *k)
{
	// Read the filename
	char *filename = malloc(MAX_STRING_SIZE * sizeof(char));
	DIE(!filename, "filename malloc failed!\n");
	scanf("%s", filename);

	// Open the file
	FILE *file = fopen(filename, "r");
	DIE(!file, "fopen malloc failed!\n");

	// Read the number of coordinates
	int n, m;
	fscanf(file, "%d %d", &n, &m);
	*k = m;

	// Read the coordinates
	tree = b_tree_create(m * sizeof(int));
	for (int i = 0; i < n; i++) {
		// Allocate memory for the vector of coordinates
		int *vector_of_coord = malloc(m * sizeof(int));
		DIE(!vector_of_coord, "vector_of_coord malloc failed!\n");
		// Insert the coordinates into the binary tree
		for (int j = 0; j < m; j++)
			fscanf(file, "%d", &vector_of_coord[j]);
		tree->root = b_tree_insert(tree, tree->root, vector_of_coord, 0, m);
		free(vector_of_coord);
	}
	// Close the file and free the memory
	fclose(file);
	free(filename);
	return tree;
}

/******************************************************************************
 * This function finds the nearest neighbors in a binary tree to a given vector
 * of coordinates.
 *
 * @param tree - The binary tree to search for nearest neighbors in.
 * @param node - The node of the binary tree.
 * @param vector_of_coord - The vector of coordinates for which to find the
 *							nearest neighbors.
 * @param level - The current level of the tree.
 * @param k - The number of coordinates.
 * @param size - A pointer to the variable storing the size of the result
 *				 array.
 * @param result - An array to store the nearest neighbors.
 * @param min_distance - A pointer to the variable storing the minimum distance
 *						 to the nearest neighbor.
*****************************************************************************/
void NN(b_tree_t *tree, b_node_t *node, int *vector_of_coord, int level, int k,
		int *size, int *result, int *min_distance)
{
	// If the node is NULL, return
	if (!node)
		return;

	int *vector_of_coord_node = (int *)node->data;
	double distance = 0;

	// Calculate the distance between the two points
	for (int i = 0; i < k; i++) {
		distance += (vector_of_coord[i] - vector_of_coord_node[i]) *
		(vector_of_coord[i] - vector_of_coord_node[i]);
	}

	// If the distance is smaller than the minimum distance, update the
	// minimum distance
	if (distance < *min_distance) {
		*min_distance = distance;
		*size = 1;
		for (int i = 0; i < k; i++)
			result[i] = vector_of_coord_node[i];
	}

	// If the distance is equal to the minimum distance, add the point to
	// the result array
	else if (distance == *min_distance) {
		for (int i = 0; i < k; i++)
			result[*size * k + i] = vector_of_coord_node[i];
		*size = *size + 1;
	}
	// If the coordinate of the current level is smaller than the coordinate
	// of the node, search the left subtree
	if (vector_of_coord[level % k] < vector_of_coord_node[level % k]) {
		NN(tree, node->left, vector_of_coord, level + 1, k, size, result,
		   min_distance);
		// If the distance between the current point and the node is smaller
		// than the minimum distance, search the right subtree
		if (vector_of_coord[level % k] + (*min_distance) >=
			vector_of_coord_node[level % k]) {
			NN(tree, node->right, vector_of_coord, level + 1, k, size, result,
			   min_distance);
		}
	} else {
		// If the coordinate of the current level is greater than the coordinate
		// of the node, search the right subtree
		NN(tree, node->right, vector_of_coord, level + 1, k, size, result,
		   min_distance);
		if (vector_of_coord[level % k] - (*min_distance) <=
			vector_of_coord_node[level % k]) {
			NN(tree, node->left, vector_of_coord, level + 1, k, size, result,
			   min_distance);
		}
	}
}

/******************************************************************************
 * This function performs range search in a binary tree.
 *
 * @param tree - The binary tree to perform range search in.
 * @param node - The node of the binary tree.
 * @param k - The number of coordinates.
 * @param start - An array representing the starting point of the range.
*****************************************************************************/
void RS(b_tree_t *tree, b_node_t *node, int k, int *start, int *end)
{
	// If the node is NULL, return
	int ok = 1;
	if (!node)
		return;

	// If the coordinates of the node are outside the range, return
	RS(tree, node->right, k, start, end);
	RS(tree, node->left, k, start, end);
	int *vector_of_coord_node = (int *)node->data;

	//Verify if the coordinates of the node are inside the range
	for (int i = 0; i < k; i++) {
		if (vector_of_coord_node[i] < start[i] ||
			vector_of_coord_node[i] > end[i]) {
			ok = 0;
			break;
		}
	}
	// If the coordinates of the node are inside the range, print them
	if (ok == 1) {
		for (int i = 0; i < k; i++)
			printf("%d ", vector_of_coord_node[i]);
		printf("\n");
	}
}

/******************************************************************************
 * This function performs the necessary cleanup and exits the program.
 *
 * @param tree - The binary tree to be freed.
*****************************************************************************/
void EXIT(b_tree_t *tree)
{
	// Free the memory and exit
	b_tree_free(tree);
	exit(0);
}

/******************************************************************************
 * This function prints the nodes of a binary tree in inorder traversal.
 *
 * @param node - The node of the binary tree.
*****************************************************************************/
void b_tree_print_inorder(b_node_t *node)
{
	// If the node is NULL, return
	if (!node)
		return;
	// Print the nodes in inorder traversal
	b_tree_print_inorder(node->left);
	int *vector_of_coord = (int *)node->data;
	// Print the coordinates of the node
	for (int i = 0; i < 2; i++)
		printf("%d ", vector_of_coord[i]);
	printf("\n");
	b_tree_print_inorder(node->right);
}
