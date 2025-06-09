#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

#include <Framework/Logger.h>
#include <boost/di.hpp>
#include <Framework/SongProvider.h>

//req!!! \/ \/ \/ \/ \/ \/ \/ \/

#if __has_include("module.g.cpp")
#  include "module.g.cpp"
#endif

#undef TERMINATE_APPLICATION_AFTER_EXCEPTION

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

namespace winrt::Audio_Player::implementation
{
    App::App()
    {
#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION

        UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
        {
            if (IsDebuggerPresent())
            {
                auto errorMessage = e.Message();

                #ifdef TERMINATE_APPLICATION_AFTER_EXCEPTION

                __debugbreak();

                #endif
            }
        });
#endif

    }

    void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
    {
        Framework::Logger::OPEN_CONSOLE();

        ConfigureDependencies();

        window.Activate();

        Framework::Logger::LOG_INFORMATION("is working?");
    }

    auto App::ConfigureInjector()
    {
        auto injector = boost::di::make_injector(
            boost::di::bind<Framework::ILogger>.to<Framework::Logger>(),
            boost::di::bind<Framework::ISongProvider>.to<Framework::SongProvider>()
        );

        return injector;
    }

    void App::ConfigureDependencies()
    {
        
        auto injector = ConfigureInjector();
    
        auto logger = injector.create<std::shared_ptr<Framework::ILogger>>();

        auto songProvider = injector.create<std::shared_ptr<Framework::ISongProvider>>();

        auto mainViewModel = winrt::make<implementation::MainViewModel>();

        mainViewModel.as<implementation::MainViewModel>()->Inject(logger, songProvider);

        window = make<MainWindow>();

        window.as<MainWindow>()->Inject(
            winrt::Audio_Player::MainViewModel{ mainViewModel },
            logger
        );
    }
}
