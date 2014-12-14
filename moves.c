#include <stdio.h>
#include "config.h"
#include "moves.h"

void characterInputUnshift(enum Inputs* inputs, enum Inputs input) {
	for (int i = INPUTS_LENGTH; i >= 1; i--) {
		inputs[i] = inputs[i - 1];
	}

	inputs[0] = input;

	for (int i = 0; i < INPUTS_LENGTH; i++) {
		printf("%d, ", inputs[i]);
	}
}
