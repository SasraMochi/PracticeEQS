#include "Game.h"
#include "Scene/TitleScene.h"
#include "Scene/GamePlayScene.h"
#include "Scene/EditBehaviorTreeScene.h"

#include "Image.h"

Game::Game(const int screenX, const int screenY) {
	Image::Load();
	SetGraphMode(screenX, screenY, 128);
	SetWindowSize(screenX, screenY);
}

void Game::start() {
	scene_manager_.add("TitleScene", new TitleScene());
	scene_manager_.add("GamePlayScene", new GamePlayScene());
	scene_manager_.add("EditBehaviorTreeScene", new EditBehaviorTreeScene());
	scene_manager_.change("TitleScene");
}

void Game::update() {
	scene_manager_.update();
}

void Game::draw() {
	scene_manager_.draw();
}

void Game::draw_debug()
{
	scene_manager_.draw_debug();
}

void Game::end() {
	scene_manager_.end();
}
