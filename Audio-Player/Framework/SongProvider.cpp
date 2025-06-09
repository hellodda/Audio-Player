#include "pch.h"
#include "SongProvider.h"

using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;

namespace winrt::Audio_Player::Framework
{
    SongProvider::SongProvider(std::shared_ptr<ILogger> logger) :
        m_logger(std::move(logger))
    {
        m_localFolder = ApplicationData::Current().LocalFolder();
    }

    IAsyncOperation<IVector<SongModel>> SongProvider::GetAllSongsAsync()
    {
        m_logger->LogInfo("GetAllSongs Called From SongProvider");

        co_await InitializeFolderAsync();

        StorageFolder folder = co_await m_localFolder.GetFolderAsync(m_folderName);
        if (!folder)
        {
            m_logger->LogWarning("Folder is null or could not be opened.");
 
            co_return single_threaded_vector<SongModel>({});
        }
        IVector<SongModel> songs = single_threaded_vector<SongModel>({});

        auto files = co_await folder.GetFilesAsync();
        for (auto const& file : files)
        {
            SongModel model{};
         
            model.Title(file.DisplayName());  
            songs.Append(model);
        }

        co_return songs;
    }

    hstring SongProvider::FolderName()
    {
        return m_folderName;
    }

    void SongProvider::FolderName(hstring const& folderName)
    {
        m_folderName = folderName;
    }

    IAsyncAction SongProvider::InitializeFolderAsync()
    {
        m_logger->LogInfo("InitializeFolderAsync Called From SongProvider");

        IStorageItem item = co_await m_localFolder.TryGetItemAsync(m_folderName);

        if (!item || !item.IsOfType(StorageItemTypes::Folder))
        {
            co_await m_localFolder.CreateFolderAsync(
                m_folderName,
                CreationCollisionOption::OpenIfExists);
            m_logger->LogInfo("Folder created or already existed.");
        }
        else
        {
            m_logger->LogInfo("Folder already exists.");
        }

        co_return;
    }
}
