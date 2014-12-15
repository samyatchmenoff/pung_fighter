enum Inputs {NEUTRAL, UP, RIGHT, DOWN, LEFT, LP, MP, HP, LK, MK, HK, START, SELECT};

struct Box {
	double x1;
	double y1;
	double x2;
	double y2;
};

struct MoveFrame {
	int moveId;
	int damage;
	int priority;
	int x;
	int y;
	char* sprite;
	struct Box attbox;
	struct Box hitbox;
	int overrideMoveIds[OVERRIDES_LENGTH];
};

struct Move {
	int id;
	enum Inputs commands[COMMAND_VARIATION_LENGTH][COMMAND_LENGTH];
	struct MoveFrame animation[ANIMATION_LENGTH];
};

struct Character {
	int health;
	char* name;
	int x;
	int y;
	struct Move moves[MOVES_LENGTH];
	struct MoveFrame* animation;
	enum Inputs inputs[INPUTS_LENGTH];
};

void addInput(enum Inputs* inputs, enum Inputs input);
struct Move* findMove(enum Inputs* inputs, struct Move* moves);
int isCancellable(int moveId, struct MoveFrame* frame);
void clearInput(enum Inputs* inputs);
struct MoveFrame* copyMove(struct MoveFrame* animation);
