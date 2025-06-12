#pragma once

#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>

#include <Framework/ILogger.h>
#include <Models/SongModel.h>
#include "ISongProvider.h"

using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winrt::Audio_Player::Framework
{
    struct SongProvider : ISongProvider
    {
        SongProvider() = default;
        SongProvider(std::shared_ptr<ILogger> logger);

        IAsyncOperation<IVector<SongModel>> GetAllSongsAsync() override;
        IAsyncOperation<SongModel> GetSongByIdAsync(int id) override;
        IAsyncAction DeleteSongByIdAsync(int id) override;

        hstring GetDefaultPath() const override;

        hstring FolderName() const noexcept;
        void FolderName(hstring const& folderName) noexcept;

    private:

        IAsyncAction InitializeFolderAsync();
        IAsyncAction PopulateSongModelAsync(StorageFile const& file, int id, SongModel& model);
        IAsyncOperation<hstring> GetSongPathByIdAsync(int id);

        std::shared_ptr<ILogger> m_logger;            
        StorageFolder m_localFolder{ nullptr };    
        StorageFolder m_songsFolder{ nullptr };    
        hstring m_folderName{ L"Songs" };         
    };
}
