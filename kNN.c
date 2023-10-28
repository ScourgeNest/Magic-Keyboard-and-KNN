/* <Copyright Niculici Mihai-Daniel 2023 > */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "BST.h"

int main(void)
{
	// Allocate memory for the command
	b_tree_t *tree;
	char *command = malloc(MAX_STRING_SIZE * sizeof(char));
	int k;
	while (1) {
		// Read the command
		scanf("%s", command);
		// Which command is it?
		if (strcmp(command, "LOAD") == 0) {
			// Load the words from the file into the BST
			tree = load(tree, &k);
		} else if (strcmp(command, "NN") == 0) {
			// Initialize the vector of coordinates
			int *vector_of_coord = malloc(k * sizeof(int));
			DIE(!vector_of_coord, "vector_of_coord malloc failed!\n");

			// Initialize the result vector
			int *result = malloc(3 * k * sizeof(int));
			DIE(!result, "result malloc failed!\n");

			// Initialize the minimum distance
			int *min_distance = malloc(sizeof(int));
			DIE(!min_distance, "min_distance malloc failed!\n");

			*min_distance = INT_MAX;

			int size = 0;

			// Read the coordinates
			for (int i = 0; i < k; i++)
				scanf("%d", &vector_of_coord[i]);

			// Find the nearest neighbors
			NN(tree, tree->root, vector_of_coord, 0, k, &size, result,
			   min_distance);
			for (int i = 0; i < size; i++) {
				for (int j = 0; j < k; j++)
					printf("%d ", result[i * k + j]);
				printf("\n");
			}
			// Free the memory
			free(vector_of_coord);
			free(result);
			free(min_distance);
		} else if (strcmp(command, "RS") == 0) {
			// Initialize the vector of coordinates
			int *start = malloc(k * sizeof(int));
			DIE(!start, "start malloc failed!\n");

			int *end = malloc(k * sizeof(int));
			DIE(!end, "end malloc failed!\n");

			// Read the coordinates
			for (int i = 0; i < k; i++)
				scanf("%d %d", &start[i], &end[i]);

			// Search the points in the given range
			RS(tree, tree->root, k, start, end);

			// Free the memory
			free(start);
			free(end);
		} else if (strcmp(command, "EXIT") == 0) {
			// Free the memory and exit
			free(command);
			EXIT(tree);
		} else {
			printf("Invalid command\n");
		}
	}
	return 0;
}
