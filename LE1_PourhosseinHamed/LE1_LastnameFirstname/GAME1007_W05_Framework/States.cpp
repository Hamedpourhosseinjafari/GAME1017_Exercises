#include "States.h"
#include "StateManager.h"
#include "Engine.h"
#include <iostream>
void State::Render()
{
	SDL_RenderPresent(Engine::Instance().GetRenderer());
}

TitleState::TitleState(){}

void TitleState::Enter()
{
	cout << "Entering TitleState!" << endl;
	// Load music track, add it to map, and play it
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{
		cout << "changing to GameState!" << endl;
		STMA::ChangeState(new GameState() );
	}
}

void TitleState::Render()
{
	
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	// any unique rendering in TitleState goes here...

	State::Render(); // this invokes SDL_RenderPResent.
}

void TitleState::Exit()
{
	cout << "exiting TitleState!" << endl;
	// make sure to invoke Mix_freemusic.
}

GameState::GameState(){}

void GameState::Enter()
{
	cout << "Entering GameState!" << endl;
	// // Load music track, add it to map
	// load sfx tracks and add them to map x2.
	//and play it
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		cout << "changing to PauseState!" << endl;
		// pause the music track.
		//STMA::PushState(new PAuseState());
	}
	// Parse 'x' scan code and change to new EndState.
	// parse 1 key and play first sfx
	// parse 2 key and play first sfx
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 0, 255, 0, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());

	// any unique rendering in GameState goes here...
	// if the current state in the vector is the gameState 
	if (dynamic_cast<GameState*>(STMA::GetStates().back()))
	State::Render(); // this invokes SDL_RenderPResent.
}

void GameState::Exit()
{
	cout << "exiting TitleState!" << endl;
	// make sure to invoke mix_freemusic
	// make sure to invoke mis_freechunk
}

void GameState::Resume()
{
	cout << "resume gameState!" << endl;
	// resume music playing track
	State::Resume();
}
