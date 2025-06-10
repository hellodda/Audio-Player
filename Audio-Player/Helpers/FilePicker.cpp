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
    LOG::LOG_INFORMATION("PickAndCopyFileAsync Called From FilePicker");
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
    if (file == nullptr)
    {
        LOG::LOG_INFORMATION("File Is Null!");
        co_return;
    }

    StorageFolder destFolder = co_await StorageFolder::GetFolderFromPathAsync(to);

    co_await file.CopyAsync(destFolder, file.Name(), NameCollisionOption::ReplaceExisting);
    LOG::LOG_INFORMATION("Called But Work?");
    co_return;
}
