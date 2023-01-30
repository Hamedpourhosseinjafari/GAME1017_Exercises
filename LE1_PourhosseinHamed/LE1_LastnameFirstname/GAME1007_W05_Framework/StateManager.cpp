#include "StateManager.h"

void StateManager::Update()
{
    if (!s_states.empty()) // If the state vector is NOT empty. (Always)
        s_states.back()->Update(); // Invoke the Update of the "current state" 
}

void StateManager::Render()
{
    if (!s_states.empty())
        s_states.back()->Render();
}
// used where there need to be two states in the vector e.g. Game and pause.
void StateManager::PushState(State* pState)
{
    s_states.push_back(pState);
    s_states.back()->Enter(); // Enter is used fo initialization.
        
}
// used where there need to be two states in the vector e.g. Game and pause.
void StateManager::PopState()
{
    if (s_states.size() <= 1) return; // only run this function if there are less than two states in vector.

    s_states.back()->Exit();
    delete s_states.back();
    s_states.back() = nullptr;
    s_states.pop_back();

    s_states.back()->Resume();
}

void StateManager::ChangeState(State* pState)
{
if(!s_states.empty()) // we are changing state
{
    s_states.back()->Exit();
    delete s_states.back();
    s_states.back() = nullptr;
    s_states.pop_back();
}
	s_states.push_back(pState);
	s_states.back()->Enter();
}

void StateManager::Quit()
{
	while (!s_states.empty())
	{
        s_states.back()->Exit();
        delete s_states.back();
        s_states.back() = nullptr;
        s_states.pop_back();
	}
}

std::vector<State*>& StateManager::GetStates()
{
    return s_states;
}

std::vector<State*> StateManager::s_states; // Now this will be allocated.