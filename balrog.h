static enum Inputs command1 = {HP};
static enum Inputs command2 = {UP};

static struct Move moves[] = {
	{
		.id = 1,
		.command = &command1
	},
	{
		.id = 2,
		.command = &command2
	}
};

static enum Inputs inputs[INPUTS_LENGTH];

const struct Character balrog = {
	.health = 15000,
	.name = "Balrog",
	.moves = moves,
	.inputs = inputs
};
