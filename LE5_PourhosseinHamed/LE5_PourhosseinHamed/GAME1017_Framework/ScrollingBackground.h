#ifndef __SCROLLINGBACKGROUND_H__
#define __SCROLLINGBACKGROUND_H__

#include "GameObject.h"
#include "Background.h"
#include <vector>


class ScrollingBackground : public GameObject
{// just a container for all the background
public:
	ScrollingBackground();
	~ScrollingBackground();
	void Update() ;
	void Render();
private:
	std::vector<Background*> m_backgrounds;
};

#endif
