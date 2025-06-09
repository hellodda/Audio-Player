#include "pch.h"
#include "FilePicker.h"

using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Storage::Pickers;
using namespace Windows::Foundation;
using namespace winrt::Microsoft::UI::Xaml;
using namespace Windows::Storage::AccessCache;


IAsyncAction winrt::Audio_Player::Helpers::FilePicker::PickAndCopyFileAsync(XamlRoot const& root, hstring const& to)
{
    FileOpenPicker picker;
    picker.ViewMode(PickerViewMode::List);
    picker.SuggestedStartLocation(PickerLocationId::MusicLibrary);

    auto hwnd = GetActiveWindow();
    picker.as<IInitializeWithWindow>()->Initialize(hwnd);

    picker.FileTypeFilter().Append(L".mp3");
    picker.FileTypeFilter().Append(L".wav");
    picker.FileTypeFilter().Append(L".m4a");
    picker.FileTypeFilter().Append(L".aac");
    picker.FileTypeFilter().Append(L".flac");

    StorageFile file = co_await picker.PickSingleFileAsync();
    if (file == nullptr) co_return;

    StorageFolder destFolder = co_await StorageFolder::GetFolderFromPathAsync(to);

    co_await file.CopyAsync(destFolder, file.Name(), NameCollisionOption::ReplaceExisting);
    co_return;
}
