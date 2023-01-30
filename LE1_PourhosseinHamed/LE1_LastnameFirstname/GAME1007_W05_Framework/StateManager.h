#pragma once
#ifndef __STATEMANAGER_H__
#define __STATEMANAGER_H__

#include "States.h"
#include <vector>

class StateManager // Purely "static class", not Singleton.
{
public:
	// Lifecycle/passthrough methods:
	static void Update();
	static void Render();
	// Unique to StateManager:
	static void PushState(State* pState);
	static void PopState();
	static void ChangeState(State* pState);
	static void Quit();
	static std::vector<State*>& GetStates();
private:
	StateManager() = default;
	static std::vector<State*> s_states; // Manage current state.
};

#endif

typedef StateManager STMA;