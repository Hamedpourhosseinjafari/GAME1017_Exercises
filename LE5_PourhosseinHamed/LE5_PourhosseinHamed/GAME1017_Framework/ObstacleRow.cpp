#include "ObstacleRow.h"

#include <ctime>

#include "RenderManager.h"

ObstacleRow::ObstacleRow() :m_gapCtr(0), m_gapMax(3)
{
	// Create the vector now.
	for (int i = 0; i < 9; i++)
	{
		m_obstacles.push_back(new Obstacle({ 128.0f * i,384.0f,128.0f,128.0f }));
	}
	m_obstacles.shrink_to_fit();
}

void ObstacleRow::Update()
{
	//when the first obstacle goes comepelty off screen
	if (m_obstacles[0]->GetPos().x <= -128.0f)
	{
		//pop the fisrt obstacle off
		delete m_obstacles[0];
		m_obstacles[0] = nullptr;
		m_obstacles.erase(m_obstacles.begin());//pop front
		//add a new obstacle to the end
		if (m_gapCtr++ % m_gapMax == 0)
		{
			srand(time(0));
			int r = rand() % 3;
			switch (r)
			{
			case 0:
				m_obstacles.push_back(new Obstacle({ 1024.0f,450.0f,128.0f,128.0f }, true, { 0,0,128,128 }, "Obstacles"));
				break;
			case 1:
				 m_obstacles.push_back(new Obstacle({ 1024.0f,450.0f,128.0f,128.0f }, true, { 128,0,128,128 }, "Obstacles"));
				break;
			case 2:
				m_obstacles.push_back(new Obstacle({ 1024.0f,280.0f,128.0f,128.0f }, true, { 256,0,128,128 }, "Obstacles"));
				break;
			}
			//note for labex5 , you'll need last two parameters of obstacle constructor,
			//you'll also need to randomize the obstacles ( defeniltly for a2).
		}
		else//creat an empty obstacle.
		{
			m_obstacles.push_back(new Obstacle({ 1024.0f, 384.0f, 128.0f, 128.0f }));
		}
		m_obstacles.shrink_to_fit();
	}
	for (const auto obstacle : m_obstacles)
		obstacle->Update();
}

void ObstacleRow::Render()
{
	// Blue line under obstacles.
	SDL_SetRenderDrawColor(REMA::GetRenderer(), 0, 0, 255, 255);
	SDL_RenderDrawLine(REMA::GetRenderer(), 0, 512, 1024, 512);
	// Render the obstacles.
	// 
	for (const auto obstacle : m_obstacles)
	{
		obstacle->Render();
	}

}
