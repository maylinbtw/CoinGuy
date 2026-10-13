#pragma once
#include <memory>
#include <vector>
#include "State.h"

class StateMachine
{
public:
    void change(std::unique_ptr<State> newState);
    void push(std::unique_ptr<State> newState);
    void pop();
    void applyPending();

    State* current();
    bool isEmpty() const;

private:
    std::vector<std::unique_ptr<State>> m_states;

    struct Pending
    {
        enum class Action { Change, Push, Pop } action;
        std::unique_ptr<State> state;
    };

    std::vector<Pending> m_pending;
};