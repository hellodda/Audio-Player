#pragma once
#include <winrt/Microsoft.UI.Xaml.Data.h>

namespace winrt::Audio_Player::Framework
{
    struct BindableBase : winrt::implements<BindableBase, winrt::Microsoft::UI::Xaml::Data::INotifyPropertyChanged>
    {
        BindableBase() = default;

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler);

        void PropertyChanged(winrt::event_token const& token) noexcept;

    protected:

        void RaisePropertyChanged(winrt::hstring const& propertyName);

    private:
        winrt::event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
    };
}