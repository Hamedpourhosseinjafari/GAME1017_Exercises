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
	//m_pGuile2 = Mix_LoadMUS("../Assets/aud/bac.mp3");
	//Mix_PlayMusic(m_pGuile2, -1);
	/*m_sfx.emplace(["back1"], Mix_LoadMUS("../Assets/aud/bac.mp3");*/
	m_sfx.emplace("back1", Mix_LoadWAV("../Assets/aud/bac.wav"));
	Mix_PlayChannel(1, m_sfx["back1"], -1);
	
}

void TitleState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_N))
	{
		//Mix_PauseMusic();
		Mix_FreeChunk(m_sfx["back1"]);
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
	
	//Mix_Music* m_pGuile3;
	//m_pGuile3 = Mix_LoadMUS("../Assets/aud/bac.mp3");
	//Mix_PlayMusic(m_pGuile3, -1);
	
	m_sfx.emplace("back2", Mix_LoadWAV("../Assets/aud/ba.wav"));
	Mix_PlayChannel(-1, m_sfx["back2"], 0);
}

void GameState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_P))
	{
		cout << "Changing to PauseState!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		//pause the music track
		Mix_PauseMusic();
		STMA::ChangeState(new PauseState() );
			
	}
	// Parse 'x' scan code and change to new EndState.
	if (Engine::Instance().KeyDown(SDL_SCANCODE_X))
	{
		cout << "Changing to EndState!?????????????????????????????????????????????????????????????" << endl;

		STMA::ChangeState(new EndState() );
	}
	// parse 1 key and play first sfx
	// parse 2 key and play first sfx
	//if (Engine::Instance().KeyDown(SDL_SCANCODE_1))
	//{
	//	Mix_PlayChannel(-1, m_sfx["slacker"], 0);
	//}
	//if (Engine::Instance().KeyDown(SDL_SCANCODE_2))
	//{
	//	Mix_PlayChannel(-1, m_sfx["jump"], 0);
	//}
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
	cout << "exiting GameState!" << endl;
	// make sure to invoke mix_freemusic
	// make sure to invoke mis_freechunk
	Mix_FreeChunk(m_sfx["back1"]);
	Mix_FreeChunk(m_sfx["back2"]);
	
}

void GameState::Resume()
{
	cout << "resume gameState!" << endl;
	// resume music playing track
	State::Resume();
	Mix_ResumeMusic();
}

PauseState::PauseState(){}

void PauseState::Enter()
{
	cout << "Entering PauseState!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
}

void PauseState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		cout << "Changing to GameState!" << endl;
		STMA::ChangeState(new GameState());

	}
}

void PauseState::Render()
{
	
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 100, 100, 100, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	//Any unique rendering in TitleState goes here....


	
	State::Render();
}

void PauseState::Exit()
{
	cout << "Exiting PauseState!" << endl;
}

EndState::EndState(){}

void EndState::Enter()
{
	cout << "Entering EndState!" << endl;
}

void EndState::Update()
{
	if (Engine::Instance().KeyDown(SDL_SCANCODE_R))
	{
		cout << "Changing to TitleState!" << endl;
		STMA::ChangeState(new TitleState());
	}
}

void EndState::Render()
{
	SDL_SetRenderDrawColor(Engine::Instance().GetRenderer(), 100, 255, 205, 255);
	SDL_RenderClear(Engine::Instance().GetRenderer());
	//Any unique rendering in TitleState goes here....


	
	State::Render();
}

void EndState::Exit()
{
	cout << "Exiting EndState!" << endl;
}

