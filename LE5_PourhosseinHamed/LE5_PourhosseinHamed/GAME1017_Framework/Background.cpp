#include "Background.h"

Background::Background(const SDL_Rect src, const SDL_FRect dst, float speed) : Image(src, dst, "temple"), m_scrollSpeed(speed)
{
	m_startX = m_dst.x; // or dst.x , or getdst()->x .
	m_endX = m_startX - m_dst.w; // scrolling left.
}

void Background::Update()
{
	// check to see if background is at end of journey
	if (m_dst.x <= m_endX)
		m_dst.x = m_startX;
	// scroll the background
	m_dst.x -= m_scrollSpeed;
}

void Background::Render()
{
	Image::Render(); // Redirect to render of base class.
}
