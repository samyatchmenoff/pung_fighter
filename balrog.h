const struct Character balrog = {
	.health = 15000,
	.name = "Balrog",
	.moves = {
		{
			.id = 0,
			.commands = {
				{NEUTRAL}
			},
			.animation = {
				{
					0,
					0,
					0,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{1, 2, 10, 20, 30}
				}
			}
		},
		{
			.id = 10,
			.commands = {
				{RIGHT}
			},
			.animation = {
				{
					10,
					0,
					0,
					10,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{1, 2, 10, 20, 30}
				}
			}
		},
		{
			.id = 1,
			.commands = {
				{LP}
			},
			.animation = {
				{
					1,
					201,
					100,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{20}
				},
				{
					1,
					202,
					100,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{20}
				},
				{
					1,
					203,
					100,
					0,
					0,
					"blahblah",
					{50, 20, 150, 30},
					{0, 0, 50, 100},
					{}
				},
				{
					1,
					204,
					100,
					0,
					0,
					"blahblah",
					{50, 20, 150, 30},
					{0, 0, 50, 100},
					{}
				}
			}
		},
		{
			.id = 2,
			.commands = {
				{MP}
			},
			.animation = {
				{
					2,
					401,
					100,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{20}
				},
				{
					2,
					402,
					100,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{20}
				},
				{
					2,
					402,
					100,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					402,
					100,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					403,
					100,
					0,
					0,
					"blahblah",
					{50, 20, 200, 30},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					403,
					100,
					0,
					0,
					"blahblah",
					{50, 20, 200, 30},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					403,
					100,
					0,
					0,
					"blahblah",
					{50, 20, 200, 30},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					403,
					100,
					0,
					0,
					"blahblah",
					{50, 20, 200, 30},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					403,
					100,
					0,
					0,
					"blahblah",
					{50, 20, 200, 30},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					404,
					100,
					0,
					0,
					"blahblah",
					{50, 20, 200, 30},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					402,
					100,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					402,
					100,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					402,
					100,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{}
				},
				{
					2,
					402,
					100,
					0,
					0,
					"blahblah",
					{0, 0, 0, 0},
					{0, 0, 50, 100},
					{}
				}
			}
		},
		//test move
		{
			.id = 20,
			.commands = {
				{LP, MP},
				{MP, LP}
			},
			.animation = {
				{
					20,
					401,
					100,
					0,
					0,
					"blahblah",
					{100, 100, 100, 100},
					{0, 0, 50, 100},
					{}
				}
			}
		},
		//test move
		{
			.id = 30,
			.commands = {
				{LP, MP, LP}
			},
			.animation = {
				{
					30,
					401,
					100,
					0,
					0,
					"blahblah",
					{100, 100, 100, 100},
					{0, 0, 50, 100},
					{}
				}
			}
		}
	}
};
