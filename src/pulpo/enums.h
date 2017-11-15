#ifndef ENUMS_H
#define ENUMS_H

#include <QMap>
#include <QVariant>

namespace PULPO
{

enum class SERVICES : uint8_t
{
    LastFm,
    Spotify,
    iTunes,
    MusicBrainz,
    Genius,
    LyricWikia,
    Wikipedia,
    WikiLyrics,
    ALL,
    NONE
};

enum class ONTOLOGY : uint8_t
{
    ARTIST,
    ALBUM,
    TRACK,
    NONE
};

enum class INFO : uint8_t
{
    ARTWORK,
    WIKI,
    TAGS,
    METADATA,
    LYRICS,
    ALL,
    NONE
};

/*Generic context names. It's encouraged to use these instead of a unkown string*/
enum class CONTEXT : uint8_t
{
    STAT,
    TRACK_NUMBER,
    TRACK_TITLE,
    TRACK_DATE,
    TRACK_TEAM,
    TRACK_AUTHOR,
    TRACK_LANGUAGE,
    TRACK_SIMILAR,

    ALBUM_TITLE,
    ALBUM_DATE,
    ALBUM_LANGUAGE,
    ALBUM_SIMILAR,
    ALBUM_LABEL,

    ARTIST_TITLE,
    ARTIST_DATE,
    ARTIST_LANGUAGE,
    ARTIST_PLACE,
    ARTIST_SIMILAR,
    ARTIST_TEAM,
    ARTIST_ALIAS,
    ARTIST_GENDER,

    GENRE,
    TAG,
    WIKI,
    IMAGE,
    LYRIC,

};

static const QMap<CONTEXT,QString> CONTEXT_MAP =
{
    {CONTEXT::STAT, "stat"},

    {CONTEXT::ALBUM_TITLE, "album_title"},
    {CONTEXT::ALBUM_DATE, "album_date"},
    {CONTEXT::ALBUM_LANGUAGE, "album_language"},
    {CONTEXT::ALBUM_SIMILAR, "album_similar"},
    {CONTEXT::ALBUM_LABEL, "album_label"},

    {CONTEXT::ARTIST_TITLE, "artist_title"},
    {CONTEXT::ARTIST_DATE, "artist_date"},
    {CONTEXT::ARTIST_LANGUAGE, "artist_language"},
    {CONTEXT::ARTIST_PLACE, "artist_place"},
    {CONTEXT::ARTIST_SIMILAR, "artist_similar"},
    {CONTEXT::ARTIST_ALIAS, "artist_alias"},
    {CONTEXT::ARTIST_GENDER, "artist_gender"},

    {CONTEXT::TRACK_DATE, "track_date"},
    {CONTEXT::TRACK_TITLE, "track_title"},
    {CONTEXT::TRACK_NUMBER, "track_number"},
    {CONTEXT::TRACK_TEAM, "track_team"},
    {CONTEXT::TRACK_AUTHOR, "track_author"},
    {CONTEXT::TRACK_LANGUAGE, "track_language"},
    {CONTEXT::TRACK_SIMILAR, "track_similar"},

    {CONTEXT::GENRE, "genre"},
    {CONTEXT::TAG, "tag"},
    {CONTEXT::WIKI, "wiki"},
    {CONTEXT::IMAGE, "image"},
    {CONTEXT::LYRIC, "lyric"},

};

enum class RECURSIVE : bool
{
    ON = true,
    OFF = false
};

typedef QMap<CONTEXT, QVariant> CONTEXT_K;
typedef QMap<INFO, CONTEXT_K> RESPONSE;
typedef QMap<ONTOLOGY, QList<INFO>> AVAILABLE;

}

#endif // ENUMS_H