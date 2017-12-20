#ifndef COLLECTIONDB_H
#define COLLECTIONDB_H
#include <QString>
#include <QStringList>
#include <QList>
#include <QSqlDatabase>
#include <QWidget>
#include <typeinfo>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QFileInfo>
#include <QDir>
#include <QVariantMap>

#include "../utils/bae.h"

enum sourceTypes
{
    LOCAL, ONLINE, DEVICE
};

class CollectionDB : public QObject
{
    Q_OBJECT

public:
    explicit CollectionDB(QObject *parent = nullptr);
    explicit CollectionDB(const QString &name = QString(), QObject *parent = nullptr);
    ~CollectionDB() override;

    bool execQuery(QSqlQuery &query) const;
    bool execQuery(const QString &queryTxt);

    /*basic public actions*/
    void prepareCollectionDB() const;
    bool check_existance(const QString &tableName, const QString &searchId, const QString &search);

    /* usefull actions */

    void insertArtwork(const BAE::DB &track);

    void addTrack(const BAE::DB &track);
    bool updateTrack(const BAE::DB &track);
    bool rateTrack(const QString &path, const int &value);
    bool babeTrack(const QString &path, const bool &value);
    bool moodTrack(const QString &path, const QString &value);
    bool artTrack(const QString &path, const QString &value);
    bool lyricsTrack(const BAE::DB &track, const QString &value);
    bool playedTrack(const QString &url, const int &increment = 1);

    bool wikiTrack(const BAE::DB &track, const QString &value);
    bool tagsTrack(const BAE::DB &track, const QString &value, const QString &context);
    bool albumTrack(const BAE::DB &track, const QString &value);
    bool trackTrack(const BAE::DB &track, const QString &value);

    bool wikiArtist(const BAE::DB &track, const QString &value);
    bool tagsArtist(const BAE::DB &track, const QString &value, const QString &context = "");

    bool wikiAlbum(const BAE::DB &track, QString value);
    bool tagsAlbum(const BAE::DB &track, const QString &value, const QString &context = "");

    bool addPlaylist(const QString &title);
    bool trackPlaylist(const QString &url, const QString &playlist);

    BAE::DB_LIST getDBData(const QStringList &urls);
    BAE::DB_LIST getDBData(const QString &queryTxt);

    BAE::DB_LIST getAlbumTracks(const QString &album, const QString &artist, const BAE::KEY &orderBy = BAE::KEY::TRACK, const BAE::W &order = BAE::W::ASC);
    BAE::DB_LIST getArtistTracks(const QString &artist, const BAE::KEY &orderBy = BAE::KEY::ALBUM, const BAE::W &order = BAE::W::ASC);
    BAE::DB_LIST getBabedTracks(const BAE::KEY &orderBy = BAE::KEY::PLAYED, const BAE::W &order = BAE::W::DESC);
    BAE::DB_LIST getSearchedTracks(const BAE::KEY &where, const QString &search);
    BAE::DB_LIST getPlaylistTracks(const QString &playlist, const BAE::KEY &orderBy = BAE::KEY::ADD_DATE, const BAE::W &order = BAE::W::DESC);
    BAE::DB_LIST getMostPlayedTracks(const int &greaterThan = 1,const int &limit = 50, const BAE::KEY &orderBy = BAE::KEY::PLAYED, const BAE::W &order = BAE::W::DESC);
    BAE::DB_LIST getFavTracks(const int &stars = 1,const int &limit = 50, const BAE::KEY &orderBy = BAE::KEY::STARS, const BAE::W &order = BAE::W::DESC);
    BAE::DB_LIST getRecentTracks(const int &limit = 50, const BAE::KEY &orderBy = BAE::KEY::ADD_DATE, const BAE::W &order = BAE::W::DESC);
    BAE::DB_LIST getOnlineTracks(const BAE::KEY &orderBy = BAE::KEY::ADD_DATE, const BAE::W &order = BAE::W::DESC);


    QString getTrackLyrics(const QString &url);
    QString getTrackArt(const QString &path);
    QStringList getTrackTags(const QString &path);
    int getTrackStars(const QString &path);
    int getTrackBabe(const QString &path);
    QString getArtistArt(const QString &artist);
    QString getArtistWiki(const QString &artist);
    QStringList getArtistTags(const QString &artist);
    QString getAlbumArt(const QString &album, const QString &artist);
    QString getAlbumWiki(const QString &album, const QString &artist);
    QStringList getAlbumTags(const QString &album, const QString &artist);
    QStringList getArtistAlbums(const QString &artist);

    QStringList getPlaylists();

    bool removePlaylistTrack(const QString &url, const QString &playlist);
    bool removePlaylist(const QString &playlist);
    bool removeArtist(const QString &artist);
    bool cleanArtists();
    bool removeAlbum(const QString &album, const QString &artist);
    bool cleanAlbums();
    bool removeSource(const QString &path);
    bool removeTrack(const QString &path);
    QSqlQuery getQuery(const QString &queryTxt);
    /*useful tools*/
    sourceTypes sourceType(const QString &url);
    void openDB(const QString &name);

private:
    QString name;
    QSqlDatabase m_db;
    /*basic actions*/
    bool insert(const QString &tableName, const QVariantMap &insertData);
    bool update(const QString &tableName, const BAE::DB &updateData, const QVariantMap &where);
    bool update(const QString &table, const QString &column, const QVariant &newValue, const QVariant &op, const QString &id);
    bool remove();

public slots:
    void closeConnection();
    /*useful*/

signals:
    void trackInserted();
    void artworkInserted(const BAE::DB &albumMap);
    void DBactionFinished();
    void albumsCleaned(const int &amount);
    void artistsCleaned(const int &amount);
};

#endif // COLLECTION_H
