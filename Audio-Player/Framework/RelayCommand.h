#pragma once

#include <winrt/Windows.Foundation.h>
#include <winrt/Microsoft.UI.Xaml.Input.h>
#include <functional>

namespace winrt::Audio_Player::Framework
{

    struct RelayCommand : winrt::implements<RelayCommand, Microsoft::UI::Xaml::Input::ICommand>
    {
        RelayCommand(std::function<void()> execute, std::function<bool()> canExecute = nullptr)
            : m_execute(std::move(execute)), m_canExecute(std::move(canExecute)) {
        }
        winrt::event<winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>> m_canExecuteChanged;

        void Execute(winrt::Windows::Foundation::IInspectable const&) const;

        bool CanExecute(winrt::Windows::Foundation::IInspectable const&) const;

        winrt::event_token CanExecuteChanged(winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable> const& handler);

        void CanExecuteChanged(winrt::event_token const& token) noexcept;

        void RaiseCanExecuteChanged();


    private:
        std::function<void()> m_execute;
        std::function<bool()> m_canExecute;
    };
}