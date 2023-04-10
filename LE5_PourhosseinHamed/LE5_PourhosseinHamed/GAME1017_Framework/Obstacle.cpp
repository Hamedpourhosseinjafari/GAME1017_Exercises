#include "Obstacle.h"

#include <ctime>

#include "RenderManager.h"
#include "TextureManager.h"

Obstacle::Obstacle(const SDL_FRect dst, bool hasImage, const SDL_Rect src, const char* key)
	:m_hasImage(hasImage), m_pImage(nullptr)
{
	TEMA::Load("../Assets/img/spritesheet1.png", "Obstacles");
	m_src = { src };
	m_pos = { dst.x,dst.y };
	if (m_hasImage)
	{
		//create a new image object and pass the parameters .

		m_pImage = new Image(src, { dst.x, dst.y, 0.0f, 0.0f }, "Obstacles");

		//to do for lab 5
	}
	
}

Obstacle::~Obstacle()
{
	if (m_hasImage)
	{
		delete m_pImage;
		m_pImage = nullptr;
	}
}

void Obstacle::Update()
{
	m_pos.x -= kScrollSpeed;
	if (m_hasImage)
	{
		//updatethe image dest rex x.
		m_pImage->GetDst()->x = m_pos.x;
	}
}

void Obstacle::Render()
{
	SDL_FRect m_dst = { m_pos.x,m_pos.y, 128.0f,128.0f };
	if (m_hasImage)
	{
		//render the image.
		//SDL_RenderCopyF(....);// remember includes!
		
			SDL_RenderCopyF(REMA::GetRenderer(), TEMA::GetTexture("Obstacles"), &m_src, &m_dst);
			
		
		
		//red box for week 9 lab...
		//SDL_SetRenderDrawColor(REMA::GetRenderer(), 255, 0, 0, 255);
		//SDL_RenderFillRectF(REMA::GetRenderer(), &m_dst);
	}
	//Render border for just week 9 lab;
	//SDL_SetRenderDrawColor(REMA::GetRenderer(), 128, 0, 128, 255);
	//SDL_RenderDrawRectF(REMA::GetRenderer(), &m_dst);
}
