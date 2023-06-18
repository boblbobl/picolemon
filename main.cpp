#include "picosystem.hpp"
#include "spritesheet.hpp"

using namespace picosystem;
using namespace std;

struct {
	int8_t x = 56;
	int8_t y = 52;
	int8_t dx = 0;
	int8_t dy = 0;
	int8_t sid = 0;
	int8_t sprite = 0;
	bool flipped = false;
} player;

struct lemon {
	int8_t x;
	int8_t y;
};

vector<lemon> lemons;

const int8_t PLAYER_SPEED = 2;
int32_t score = 0;
int32_t playerAnimationTime = 0;
int32_t animationWait = 100;

void new_lemon() {
	int8_t x = player.x;
	int8_t y = player.y;

	while (intersects(x, y, 8, 8, player.x, player.y, 16, 16)) {
		x = static_cast<int8_t>(rand() % 112);
		y = static_cast<int8_t>(rand() % 112);
	}
	lemons.push_back({.x = x, .y = y});
}

void init() {
	spritesheet(custom_sprite_sheet);

	for (int i = 0; i < 4; i++) {
		new_lemon();
	}
}

void step() {
	if ((time() - playerAnimationTime) > animationWait) {
		if (player.sid < 3) {
			player.sid++;
		}
		else if (player.sid == 3) {
			player.sid = 0;
			//player.flipped = !player.flipped;
		}

		player.sprite = player.sid*2;
		if (player.dx != 0) {
			player.sprite = player.sprite+16;
			if (player.dx == PLAYER_SPEED) {
				player.flipped = false;
			}
			else {
				player.flipped = true;
			}
		}
		else if (player.dy == -PLAYER_SPEED) {
			player.sprite = player.sprite+32;
		}


		playerAnimationTime = time();
	}
}

void update(uint32_t tick) {
	player.dx = 0;
	player.dy = 0;
	
	if (button(UP)) {
		player.dy -= PLAYER_SPEED;
		step();
	} else if (button(DOWN)) {
		player.dy += PLAYER_SPEED;
		step();
	} else if (button(LEFT)) {
		player.dx -= PLAYER_SPEED;
		step();
	} else if (button(RIGHT)) {
		player.dx += PLAYER_SPEED;
		step();
	}
	
	int8_t newX = player.x + player.dx;
	int8_t newY = player.y + player.dy;

	if (newX < 104 && newX > 0) {
		player.x = newX;
	}
	if (newY < 104 && newY > 0) {
		player.y = newY;
	}
	
	for (int i=0; i < lemons.size(); i++) {
		lemon l = lemons[i];
		if (intersects(l.x, l.y, 8, 8, player.x, player.y, 16, 16)) {
			lemons.erase(lemons.begin() + i);
			score++;
			new_lemon();
			break;
		}
	}
}

void draw(uint32_t tick) {
	//draw black background
	pen(0, 0, 0);
	clear();

	//draw current score
	pen(15, 15, 15);
	sprite(49, 0, 0);
	text(str(score), 10, 0);

	//draw player
	if (player.flipped) {
		sprite(player.sprite, player.x, player.y, 2, 2, 16, 16, HFLIP);
	}
	else {
		sprite(player.sprite, player.x, player.y, 2, 2, 16, 16);
	}

	//draw lemons
	for (lemon l : lemons) {
		sprite(48, l.x, l.y);
	}
}
