#include "Map.h"
#include "Character.h"
#include "MainGameClass.h"
#include <iostream>

int main() {
	MainGameClass game;
	while (game.GetGame()) {
		game.Draw();
		game.EnteractPlayer();
	}
}
