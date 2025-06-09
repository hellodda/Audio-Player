#pragma once

#include "MainWindow.g.h"

#include <ViewModels/MainViewModel.h>

namespace winrt::Audio_Player::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            InitializeComponent();
            Setup();
        }

        void Inject(Audio_Player::MainViewModel const& viewModel, std::shared_ptr<Framework::ILogger> logger);

        winrt::Audio_Player::MainViewModel MainViewModel();

    private:

        void Setup();

        Audio_Player::MainViewModel m_viewModel;
        std::shared_ptr<Framework::ILogger> m_logger;

    public:
      
    };
}

namespace winrt::Audio_Player::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
