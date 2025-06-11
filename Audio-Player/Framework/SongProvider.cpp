#include "pch.h"
#include "SongProvider.h"

using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage::FileProperties;
using namespace Windows::Storage::Streams;
using namespace winrt::Microsoft::UI::Xaml::Media::Imaging;

namespace winrt::Audio_Player::Framework
{
    SongProvider::SongProvider(std::shared_ptr<ILogger> logger) :
        m_logger(std::move(logger))
    {
        m_logger->LogInfo("SongProvider: Constructor called");
        m_localFolder = ApplicationData::Current().LocalFolder();
        m_logger->LogInfo("SongProvider: LocalFolder initialized: " + winrt::to_string(m_localFolder.Path()));
    }

    IAsyncOperation<IVector<SongModel>> SongProvider::GetAllSongsAsync()
    {
        m_logger->LogInfo("GetAllSongsAsync: Called");

        co_await InitializeFolderAsync();

        m_logger->LogInfo("GetAllSongsAsync: Getting folder '" + winrt::to_string(m_folderName) + "'");
        StorageFolder folder = co_await m_localFolder.GetFolderAsync(m_folderName);
        if (!folder)
        {
            m_logger->LogWarning("GetAllSongsAsync: Folder is null or could not be opened: " + winrt::to_string(m_folderName));
            co_return single_threaded_vector<SongModel>({});
        }

        IVector<SongModel> songs = single_threaded_vector<SongModel>({});
        m_logger->LogInfo("GetAllSongsAsync: Folder opened successfully: " + winrt::to_string(folder.Path()));

        auto files = co_await folder.GetFilesAsync();
        m_logger->LogInfo("GetAllSongsAsync: Number of files found: " + std::to_string(files.Size()));

        int index{ 0 };
        for (auto const& file : files)
        {
            m_logger->LogInfo("GetAllSongsAsync: Processing file [" + std::to_string(index) + "]: " + winrt::to_string(file.Name()));

            SongModel model{};

            auto thumbnail = co_await file.GetThumbnailAsync(ThumbnailMode::MusicView, 512);
            if (thumbnail && thumbnail.Type() == ThumbnailType::Image)
            {
                BitmapImage map{};
                co_await map.SetSourceAsync(thumbnail);
                model.Image(map);
            }
            else
            {
                BitmapImage map{};
                map.UriSource(Uri{ L"ms-appx:///Assets/DefaultCover.jpg" });
                model.Image(map);
                m_logger->LogInfo("GetAllSongsAsync: No valid thumbnail, using default image");
            }

            model.Title(file.DisplayName());
            model.Id(index);
            model.SongPath(file.Path());
            model.MediaSource(winrt::Windows::Media::Core::MediaSource::CreateFromUri(Uri(file.Path())));

            m_logger->LogInfo("GetAllSongsAsync: SongModel populated - Title: " + winrt::to_string(model.Title()) +
                ", Path: " + winrt::to_string(model.SongPath()) +
                ", Id: " + std::to_string(model.Id()));

            songs.Append(model);
            m_logger->LogInfo("GetAllSongsAsync: Song added to list: " + winrt::to_string(model.Title()));

            ++index;
        }

        m_logger->LogInfo("GetAllSongsAsync: Completed, total songs appended: " + std::to_string(songs.Size()));
        co_return songs;
    }

    IAsyncAction SongProvider::DeleteByIdAsync(int id)
    {
        m_logger->LogInfo("DeleteByIdAsync: Called with ID: " + std::to_string(id));

       
        auto songs = co_await GetAllSongsAsync();
        m_logger->LogInfo("DeleteByIdAsync: Retrieved " + std::to_string(songs.Size()) + " songs");

        bool songFound = false;
        for (auto& song : songs)
        {
            if (song.Id() == id)
            {
                songFound = true;
                m_logger->LogInfo("DeleteByIdAsync: Found song to delete - Title: " + winrt::to_string(song.Title()) +
                    ", Path: " + winrt::to_string(song.SongPath()));

                try
                {
                    auto file = co_await m_localFolder.GetFileAsync(song.SongPath());
                    m_logger->LogInfo("DeleteByIdAsync: Deleting file: " + winrt::to_string(file.Path()));
                    co_await file.DeleteAsync();
                    m_logger->LogInfo("DeleteByIdAsync: File deleted successfully: " + winrt::to_string(song.SongPath()));
                }
                catch (const winrt::hresult_error& ex)
                {
                    m_logger->LogWarning("DeleteByIdAsync: Failed to delete song file: " +
                        winrt::to_string(song.SongPath()) +
                        ". Error: " + winrt::to_string(ex.message()));
                    throw;
                }
                break;
            }
        }

        if (!songFound)
        {
            m_logger->LogWarning("DeleteByIdAsync: Song with ID " + std::to_string(id) + " not found");
        }
      
        m_logger->LogInfo("DeleteByIdAsync: Completed for ID: " + std::to_string(id));
        co_return;
    }

    hstring SongProvider::GetDefaultPath() const
    {
        m_logger->LogInfo("GetDefaultPath: Returning default songs folder path: " + winrt::to_string(m_songsFolder.Path()));
        return m_songsFolder.Path();
    }

    hstring SongProvider::FolderName() const noexcept
    {
        m_logger->LogInfo("FolderName (getter): Current folder name: " + winrt::to_string(m_folderName));
        return m_folderName;
    }

    void SongProvider::FolderName(hstring const& folderName) noexcept
    {
        m_logger->LogInfo("FolderName (setter): Changing folder name from " +
            winrt::to_string(m_folderName) + " to " + winrt::to_string(folderName));
        m_folderName = folderName;
    }

    IAsyncAction SongProvider::InitializeFolderAsync()
    {
        m_logger->LogInfo("InitializeFolderAsync: Called");

        IStorageItem item = co_await m_localFolder.TryGetItemAsync(m_folderName);
        if (item && item.IsOfType(StorageItemTypes::Folder))
        {
            m_songsFolder = item.as<StorageFolder>();
            m_logger->LogInfo("InitializeFolderAsync: Folder already exists: " + winrt::to_string(m_songsFolder.Path()));
        }
        else
        {
            m_logger->LogInfo("InitializeFolderAsync: Folder does not exist, creating: " + winrt::to_string(m_folderName));
            StorageFolder created = co_await m_localFolder.CreateFolderAsync(
                m_folderName,
                CreationCollisionOption::OpenIfExists
            );
            m_songsFolder = created;
            m_logger->LogInfo("InitializeFolderAsync: Folder created or opened: " + winrt::to_string(m_songsFolder.Path()));
        }

        m_logger->LogInfo("InitializeFolderAsync: Completed");
        co_return;
    }
}
