#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "moves.h"

void addInput(enum Inputs* inputs, enum Inputs input) {
	for (int i = INPUTS_LENGTH - 1; i >= 1; i--) {
		inputs[i] = inputs[i - 1];
	}

	inputs[0] = input;
}

struct Move* findMove(enum Inputs* inputs, struct Move* moves) {
	//default to neutral, should always be 0
	int longestMoveIndex = 0;
	//default to 0
	int length = 0;

	for (int i = 0; i < MOVES_LENGTH; i++) {
		struct Move move = moves[i];

		//went through all of the moves
		if (i > 0 && move.id == 0) {
			break;
		}

		for (int m = 0; m < COMMAND_VARIATION_LENGTH; m++) {
			//end of command variations array
			if (move.commands[m][0] == 0) {
				break;
			}

			int innerOffset = INPUTS_LENGTH;
			int found = 0;

			for (int k = 0; k < COMMAND_LENGTH; k++) {
				enum Inputs com = move.commands[m][k];

				//no command uses neutral, so we can assume this is the end of the array
				if (com == NEUTRAL) {
					printf("%d %d %d %d %d\n", m, move.id, found, k, length);
					//we have a match!
					if (k == found && k > length) {
						longestMoveIndex = i;
						printf("MATCH %d ", longestMoveIndex);
						length = k;
					}
					break;
				}

				for (int j = innerOffset - 1; j >= 0; j--) {
					if (inputs[j] == com) {
					printf("FOUND %d %d %d %d\n", m, j, inputs[j], com);
						innerOffset = j;
						found += 1;
						break;
					}
				}
			}
		}
	}

	return &moves[longestMoveIndex];
}

int isCancellable(int moveId, struct MoveFrame* frame) {
	//neutral cancels into itself
	if (moveId == 0 && (*frame).moveId == 0) {
		return 1;
	}
	//neutral cancels nothing
	if (moveId == 0) {
		return 0;
	}

	int* overrides = (*frame).overrideMoveIds;

	for (int i = 0; i < OVERRIDES_LENGTH; i++) {
		if (moveId == overrides[i]) {
			return 1;
		}
	}

	return 0;
}

void clearInput(enum Inputs* inputs) {
	for (int i = 0; i < INPUTS_LENGTH; i++) {
		inputs[i] = 0;
	}
}

struct MoveFrame* copyMove(struct MoveFrame* animation) {
	struct MoveFrame* output = malloc(ANIMATION_LENGTH * sizeof(struct MoveFrame));

	for (int i = 0; i < ANIMATION_LENGTH; i++) {
		output[i] = animation[i];

		//this means we've hit an empty struct, so stop
		if (animation[i].moveId == 0) {
			break;
		}

	}

	return output;
}
