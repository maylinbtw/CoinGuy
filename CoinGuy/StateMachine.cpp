#include "StateMachine.h"

void StateMachine::change(std::unique_ptr<State> newState)
{
    m_pending.push_back({ Pending::Action::Change, std::move(newState) });
}

void StateMachine::push(std::unique_ptr<State> newState)
{
    m_pending.push_back({ Pending::Action::Push, std::move(newState) });
}

void StateMachine::pop()
{
    m_pending.push_back({ Pending::Action::Pop, nullptr });
}

void StateMachine::applyPending()
{
    for (auto& p : m_pending)
    {
        switch (p.action)
        {
        case Pending::Action::Change:
            m_states.clear();
            m_states.push_back(std::move(p.state));
            break;
        case Pending::Action::Push:
            m_states.push_back(std::move(p.state));
            break;
        case Pending::Action::Pop:
            if (!m_states.empty())
                m_states.pop_back();
            break;
        }
    }
    m_pending.clear();
}

State* StateMachine::current()
{
    if (m_states.empty()) return nullptr;
    return m_states.back().get();
}

bool StateMachine::isEmpty() const
{
    return m_states.empty();
}