#include <iostream>
#include "States.h"
#include "StateManager.h"
#include "CollisionManager.h"
#include "EventManager.h"
#include "RenderManager.h"
#include "TextureManager.h"
#include "Bullet.h"
using namespace std;

void State::Render()
{
	SDL_RenderPresent(REMA::Instance().GetRenderer());
}

TitleState::TitleState(){}

void TitleState::Enter()
{
	
}

void TitleState::Update()
{
	if (EVMA::KeyPressed(SDL_SCANCODE_N))
	{
		STMA::ChangeState( new GameState() );
	}
}

void TitleState::Render()
{
	SDL_SetRenderDrawColor(REMA::Instance().GetRenderer(), 0, 0, 255, 255);
	SDL_RenderClear(REMA::Instance().GetRenderer());
	State::Render();
}

void TitleState::Exit()
{
	
}

void GameState::ClearTurrets()
{
	for (unsigned i = 0; i < m_turrets.size(); i++)
	{
		delete m_turrets[i];
		m_turrets[i] = nullptr;
	}
	m_turrets.clear();
	m_turrets.shrink_to_fit();
	// You can assimilate some parts of this code for deleting bullets and enemies.
}

GameState::GameState():m_spawnCtr(1) {}

void GameState::Enter()
{
	TEMA::Load("../Assets/img/Turret.png", "turret");
	TEMA::Load("../Assets/img/Enemies.png", "enemy");
	s_enemies.push_back(new Enemy({ 80,0,40,57 }, { 512.0f, -57.0f, 40.0f, 57.0f }));
	// Create the DOM and load the XML file.
	// Iterate through the Turret elements in the file and push_back new Turrets into the m_turrets vector.
		// Keep the width and height as 100.
	// Look at the last two XML examples from Week 3
	m_xmlDoc.LoadFile("../Assets/dat/turrets.xml");
	tinyxml2::XMLElement* Proot = m_xmlDoc.FirstChildElement();
	if (Proot == nullptr)
	{
		return;
	}
	tinyxml2::XMLElement* PTurretElement = Proot->FirstChildElement();
	while (PTurretElement != nullptr)
	{
		if (strcmp(PTurretElement->Value(),"turret") == 0)
		{
			float x = PTurretElement->FloatAttribute("x.POS");
			float y = PTurretElement->FloatAttribute("y.POS");
			int kills = PTurretElement->IntAttribute("kills");
			auto turret = new Turret({ 0,0,100,100 }, { x,y,100.f,100.f });
			m_turrets.push_back(turret);

		}
		PTurretElement = PTurretElement->NextSiblingElement();
	}

}

void GameState::Update()
{
	// Parse T and C events.
	if (EVMA::KeyPressed(SDL_SCANCODE_T))
	{
		m_turrets.push_back(new Turret({0,0,100,100},
			{50.0f, 615.0f, 100.0f,100.0f}));
	}
	if (EVMA::KeyPressed(SDL_SCANCODE_C))
	{
		ClearTurrets();
	}
	// Update all GameObjects individually. Spawn enemies. Update turrets. Update enemies. Update bullets.
	if (m_spawnCtr++ % 180 == 0)
	{
		s_enemies.push_back(new Enemy({ 80,0,40,57 },
			{ (float)(rand() % (1024 - 40)), -57.0f, 40.0f, 57.0f }));
	}
	for (auto turret : m_turrets)
		turret->Update();
	for (auto enemy : s_enemies)
		enemy->Update();
	for (auto bullet : s_bullets)
		bullet->Update();

		// for all enemies, similar to above

	// Check for collisions with bullets and enemies.
	
		// for all bullets
			// for all enemies
				// check collision (use AABB check with SDL_FRect and SDL_FRect)
				// if (COMA::AABBCheck(/*SDL_FRect*/, /*SDL_FRect*/));
					// Then colliding and do the thing
	for(auto bullet : s_bullets)
	{
		for (auto enemy : s_enemies)
		{
			if (COMA::AABBCheck(*bullet->GetDst(),*enemy->GetDst()))
			{
				bullet->m_parent->m_Kills + 1;
				enemy->m_deletMe = true;
				bullet->m_deleteMe = true;
				
				break;
			}
		}
	}
	// Cleanup bullets and enemies that go off screen.

	// for all bullets
		// if bullet goes off screen (four bounds checks)
		// or
		// if deleteMe of bullet is true
			// delete s_bullets[i]
			// set s_bullets[i] to nullptr
	for (int i = 0; i < static_cast<int>(s_bullets.size()); ++i)
	{
		if (s_bullets[i]->m_deleteMe)
		{
			s_bullets.erase(s_bullets.begin() + i);
			
		}
	}

	for (int i = 0; i < static_cast<int>(s_enemies.size()); ++i)
	{
		if (s_enemies[i]->m_deletMe)
		{
			s_enemies.erase(s_enemies.begin() + i);
		}
	}
}

void GameState::Render()
{
	SDL_SetRenderDrawColor(REMA::Instance().GetRenderer(), 0, 0, 0, 255);
	SDL_RenderClear(REMA::Instance().GetRenderer());

	for (unsigned i = 0; i < m_turrets.size(); i++)
		m_turrets[i]->Render();
	for (unsigned i = 0; i < s_enemies.size(); i++)
		s_enemies[i]->Render();
	for (unsigned i = 0; i < s_bullets.size(); i++)
		s_bullets[i]->Render();

	SDL_Rect spawnBox = { 50, 618, 100, 100 };
	SDL_SetRenderDrawColor(REMA::Instance().GetRenderer(), 255, 255, 255, 255);
	SDL_RenderDrawRect(REMA::Instance().GetRenderer(), &spawnBox);

	// This code below prevents SDL_RenderPresent from running twice in one frame.
	if ( dynamic_cast<GameState*>( STMA::GetStates().back() ) ) // If current state is GameState.
		State::Render();
}

void GameState::Exit()
{
	
	// You can clear all children of the root node by calling .DeleteChildren(); and this will essentially clear the DOM.
	m_xmlDoc.DeleteChildren();
	tinyxml2::XMLNode* Proot = m_xmlDoc.NewElement("Info");
	m_xmlDoc.InsertEndChild(Proot);
	tinyxml2::XMLElement* pTurretElement;
	// Iterate through all the turrets and save their positions as child elements of the root node in the DOM.
	for (auto turret : m_turrets)
	{
		pTurretElement = m_xmlDoc.NewElement("turret");
		pTurretElement->SetAttribute("x.POS", turret->GetDst()->x);
		pTurretElement->SetAttribute("y.POS", turret->GetDst()->y);
		pTurretElement->SetAttribute("kills", turret->m_Kills);
		Proot->InsertEndChild(pTurretElement);
	}
	// Make sure to save to the XML file.
		// xmlDoc.SaveFile("Turrets.xml");
	m_xmlDoc.SaveFile("../Assets/dat/turrets.xml");
	ClearTurrets(); // Deallocate all turrets, then all other objects.
	for (unsigned i = 0; i < s_enemies.size(); i++)
	{
		delete s_enemies[i];
		s_enemies[i] = nullptr;
	}
	s_enemies.clear();
	s_enemies.shrink_to_fit();
	for (unsigned i = 0; i < s_bullets.size(); i++)
	{
		delete s_bullets[i];
		s_bullets[i] = nullptr;
	}
	s_bullets.clear();
	s_bullets.shrink_to_fit();
}

void GameState::Resume()
{
	
}

// This is how static properties are allocated.
std::vector<Bullet*> GameState::s_bullets;
std::vector<Enemy*> GameState::s_enemies;