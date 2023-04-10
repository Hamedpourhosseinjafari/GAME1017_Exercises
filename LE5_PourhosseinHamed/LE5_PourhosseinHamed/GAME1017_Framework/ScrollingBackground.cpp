#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground()
{
	m_backgrounds.reserve(10);
	m_backgrounds.push_back(new Background({ 0,0,1024,768 }, { 0.0f,0.0f,1024.0f,768.0f }, 1.0f));
	m_backgrounds.push_back(new Background({ 0,0,1024,768 }, { 1024.0f,0.0f,1024.0f,768.0f }, 1.0f));

	m_backgrounds.push_back(new Background({ 1024,0,256,512 }, { 0.0f,0.0f,256.0f,512.0f }, 2.0f));
	m_backgrounds.push_back(new Background({ 1024,0,256,512 }, { 256.0f,0.0f,256.0f,512.0f }, 2.0f));
	m_backgrounds.push_back(new Background({ 1024,0,256,512 }, { 512.0f,0.0f,256.0f,512.0f }, 2.0f));
	m_backgrounds.push_back(new Background({ 1024,0,256,512 }, { 768.0f,0.0f,256.0f,512.0f }, 2.0f));
	m_backgrounds.push_back(new Background({ 1024,0,256,512 }, { 1024.0f,0.0f,256.0f,512.0f }, 2.0f));


	m_backgrounds.push_back(new Background({ 1024,512,512,256 }, { 0.0f,512.0f,512.0f,256.0f }, 2.2f));
	m_backgrounds.push_back(new Background({ 1024,512,512,256 }, { 512.0f,512.0f,512.0f,256.0f }, 2.2f));
	m_backgrounds.push_back(new Background({ 1024,512,512,256 }, { 1024.0f,512.0f,512.0f,256.0f }, 2.2f));

}

ScrollingBackground::~ScrollingBackground()
{
	for ( auto background : m_backgrounds)
	{
		delete background;
		background = nullptr;//optional
	}
	m_backgrounds.clear();
}

void ScrollingBackground::Update()
{
	for (const auto background : m_backgrounds)
		background->Update();
}

void ScrollingBackground::Render()
{
	for (const auto background : m_backgrounds)
		background->Render();
}
