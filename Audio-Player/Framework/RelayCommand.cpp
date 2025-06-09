#include "pch.h"
#include "RelayCommand.h"

namespace winrt::Audio_Player::Framework
{
	void RelayCommand::Execute(winrt::Windows::Foundation::IInspectable const&) const
	{
		if (m_execute) m_execute();
	}
	bool RelayCommand::CanExecute(winrt::Windows::Foundation::IInspectable const&) const
	{
		return m_canExecute ? m_canExecute() : true;
	}
	winrt::event_token RelayCommand::CanExecuteChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler)
	{
		return m_canExecuteChanged.add(handler);
	}
	void RelayCommand::CanExecuteChanged(winrt::event_token const& token) noexcept
	{
		m_canExecuteChanged.remove(token);
	}
	void RelayCommand::RaiseCanExecuteChanged()
	{
		m_canExecuteChanged(nullptr, nullptr);
	}
}