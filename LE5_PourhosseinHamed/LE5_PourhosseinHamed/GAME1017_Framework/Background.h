#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_
#include "Primitives.h"

class Background : public Image
{
public:
	Background(const SDL_Rect src, const SDL_FRect dst, float speed);
	void Update();
	void Render();

private:
	float m_scrollSpeed; // Based on pixels/frame for now
	float m_startX, m_endX; // Start and end position (x) for a background.

};

#endif
