#include "pch.h"
#include "SongProvider.h"

using namespace winrt;
using namespace Windows::Storage;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Storage::FileProperties;
using namespace winrt::Microsoft::UI::Xaml::Media::Imaging;
using namespace Windows::Media::Core;

namespace winrt::Audio_Player::Framework
{
    SongProvider::SongProvider(std::shared_ptr<ILogger> logger) : m_localFolder(ApplicationData::Current().LocalFolder()), m_logger(std::move(logger))
    {
        m_logger->LogInfo("SongProvider initialized. LocalFolder: " + to_string(m_localFolder.Path()));
    }

    IAsyncOperation<IVector<SongModel>> SongProvider::GetAllSongsAsync()
    {
        m_logger->LogInfo("GetAllSongsAsync: start");
        co_await InitializeFolderAsync();

        StorageFolder folder = co_await m_localFolder.GetFolderAsync(m_folderName);
        if (!folder)
        {
            m_logger->LogWarning("GetAllSongsAsync: Cannot open folder: " + to_string(m_folderName));
            co_return single_threaded_observable_vector<SongModel>();
        }

        auto songs = single_threaded_observable_vector<SongModel>();
        auto files = co_await folder.GetFilesAsync();
        m_logger->LogInfo("GetAllSongsAsync: Found " + std::to_string(files.Size()) + " files");

        int index = 0;
        for (auto const& file : files)
        {
            SongModel model{};
            co_await PopulateSongModelAsync(file, index++, model);
            songs.Append(model);
        }

        m_logger->LogInfo("GetAllSongsAsync: Completed, total songs: " + std::to_string(songs.Size()));
        co_return songs;
    }

    IAsyncOperation<SongModel> SongProvider::GetSongByIdAsync(int id)
    {
        auto songs = co_await GetAllSongsAsync();
        for (auto const& s : songs)
        {
            if (s.Id() == id)
                co_return s;
        }
        co_return nullptr;
    }

    IAsyncOperation<hstring> SongProvider::GetSongPathByIdAsync(int id)
    {
        auto songs = co_await GetAllSongsAsync();
        for (auto const& s : songs)
        {
            if (s.Id() == id)
                co_return s.SongPath();
        }
        co_return L"";
    }

    IAsyncAction SongProvider::PopulateSongModelAsync(StorageFile const& file, int id, SongModel& model)
    {
        m_logger->LogInfo("Processing file: " + to_string(file.Name()));

        auto thumb = co_await file.GetThumbnailAsync(ThumbnailMode::MusicView, 512);
        BitmapImage cover;
        if (thumb.Type() == ThumbnailType::Image)
        {
            co_await cover.SetSourceAsync(thumb);
        }
        else
        {
            cover.UriSource(Uri{ L"ms-appx:///Assets/DefaultCover.jpg" });
        }
        model.Image(cover);

        auto props = co_await file.Properties().GetMusicPropertiesAsync();
        model.Title(props.Title());
        model.Author(props.Artist());

        model.Id(id);
        model.SongPath(file.Path());
        model.MediaSource(MediaSource::CreateFromUri(Uri(file.Path())));

        m_logger->LogInfo("Populated SongModel: " + to_string(model.Title()) + ", Id=" + std::to_string(id));
        co_return;
    }

    IAsyncAction SongProvider::DeleteSongByIdAsync(int id)
    {
        m_logger->LogInfo("DeleteSongByIdAsync: id=" + std::to_string(id));
        hstring path = co_await GetSongPathByIdAsync(id);
        if (path.empty())
        {
            m_logger->LogWarning("DeleteSongByIdAsync: Song not found, id=" + std::to_string(id));
            co_return;
        }

        m_logger->LogInfo("Deleting file: " + to_string(path));
        try
        {
            auto file = co_await StorageFile::GetFileFromPathAsync(path);
            co_await file.DeleteAsync();
            m_logger->LogInfo("Deleted file: " + to_string(path));
        }
        catch (hresult_error const& ex)
        {
            m_logger->LogWarning("Failed to delete: " + to_string(path) + ", err=" + to_string(ex.message()));
            throw;
        }

        co_return;
    }

    hstring SongProvider::GetDefaultPath() const
    {
        return m_songsFolder.Path();
    }

    hstring SongProvider::FolderName() const noexcept
    {
        return m_folderName;
    }

    void SongProvider::FolderName(hstring const& folderName) noexcept
    {
        m_folderName = folderName;
    }

    IAsyncAction SongProvider::InitializeFolderAsync()
    {
        m_logger->LogInfo("InitializeFolderAsync: folder=" + to_string(m_folderName));
        auto item = co_await m_localFolder.TryGetItemAsync(m_folderName);
        if (item && item.IsOfType(StorageItemTypes::Folder))
        {
            m_songsFolder = item.as<StorageFolder>();
        }
        else
        {
            m_songsFolder = co_await m_localFolder.CreateFolderAsync(
                m_folderName,
                CreationCollisionOption::OpenIfExists);
        }
        m_logger->LogInfo("InitializeFolderAsync: done, path=" + to_string(m_songsFolder.Path()));
        co_return;
    }
}
