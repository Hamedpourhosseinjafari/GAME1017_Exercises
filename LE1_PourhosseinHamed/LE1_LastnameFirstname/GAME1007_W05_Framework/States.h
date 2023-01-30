#pragma once
#ifndef __STATES_H__
#define __STATES_H__

class State // Abstract base class.
{ // No objects of State can be created.
public:
	virtual void Enter() = 0; // Pure virtual function. No definition.
	virtual void Update() = 0;
	virtual void Render(); // Will be defined in State.
	virtual void Exit() = 0;
	virtual void Resume() {}; // Considered defined for all subclasses.
protected: // Private but inherited.
	State() = default;
};

class TitleState: public State
{
public:
	TitleState();
	virtual void Enter();
	virtual void Update();
	virtual void Render(); 
	virtual void Exit();
private:
	//map for music track goes here

};

// make definition for pause state here
class GameState : public State
{
public:
	GameState();
	virtual void Enter();
	virtual void Update();
	virtual void Render();
	virtual void Exit();
	virtual void Resume();
private:
	//map for music track goes here
	// map for sound effects goes here
};


#endif