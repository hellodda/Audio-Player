#pragma once

#include "MainWindow.g.h"
#include "ViewModels/MainViewModel.h"
#include "ViewModels/Locator.h"

namespace winrt::Audio_Player::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            InitializeComponent();
            Setup();
        }

        winrt::Audio_Player::MainViewModel MainViewModel();

    private:

        void Setup();

    public:
      
    };
}

namespace winrt::Audio_Player::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
