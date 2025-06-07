#include "pch.h"
#include "BindableBase.h"


namespace winrt::Audio_Player::Framework
{
    winrt::event_token BindableBase::PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void BindableBase::PropertyChanged(winrt::event_token const& token) noexcept
    {
        m_propertyChanged.remove(token);
    }
	void BindableBase::RaisePropertyChanged(winrt::hstring const& propertyName)
	{
		m_propertyChanged(*this, winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventArgs{ propertyName });
	}
}


