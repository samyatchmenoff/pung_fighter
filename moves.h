enum Inputs {UP, RIGHT, DOWN, LEFT, LP, MP, HP, LK, MK, HK, START, SELECT};

struct Box {
	double x1;
	double y1;
	double x2;
	double y2;
};

struct Move {
	int id;
	enum Inputs* command;
};

struct MoveFrame {
	int damage;
	int priority;
	int x;
	int y;
	char* sprite;
	struct Box hitbox;
	struct Box movebox;
	enum Inputs* overrides;
};

struct Character {
	int health;
	char* name;
	int x;
	int y;
	struct Move* moves;
	struct MoveFrame* animation;
	enum Inputs* inputs;
};

void characterInputUnshift(enum Inputs* inputs, enum Inputs input);
