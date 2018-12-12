#pragma once

#include <memory>
#include <stack>

#include "State.hpp"

namespace CourseWork
{
	typedef std::unique_ptr<State> StateReference;

	class StateMachine
	{
	public:
		StateMachine() {}
		~StateMachine() {}

		void AddState(StateReference newState, bool isReplacing = true);
		void RemoveState();
		// Runs at start of each loop in Game.cpp
		void ProcessStateChanges();

		StateReference &GetActiveState();

	private:
		std::stack<StateReference> _states;
		StateReference _newState;

		bool _isRemoving;
		bool _isAdding;
		bool _isReplacing;
	};
}