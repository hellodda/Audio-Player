#pragma once

#include "App.xaml.g.h"

namespace winrt::Audio_Player::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

        void ConfigureDependencies();

        auto ConfigureInjector();

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}
