#ifndef ALBUMSVIEW_H
#define ALBUMSVIEW_H

#include <QWidget>
#include <QSqlQuery>
#include <QGridLayout>
#include <QFrame>
#include <QListWidgetItem>
#include <QListWidget>
#include <QComboBox>
#include <QHeaderView>
#include <QToolTip>
#include <QDebug>
#include <QShortcut>
#include <QSplitter>
#include <QScrollBar>
#include <QHash>
#include <QMetaType>
#include <QThread>

//#include <QGraphicsBlurEffect>
//#include <QGraphicsScene>
//#include <QGraphicsPixmapItem>

#include "../widget_models/scrolltext.h"
#include "../widget_models/babealbum.h"
#include "../widget_models/babetable.h"
#include "../db/collectionDB.h"
#include "../widget_models/babegrid.h"
#include "../kde/notify.h"

class AlbumLoader : public QObject
{
    Q_OBJECT

public:
    AlbumLoader() : QObject()
    {
        qRegisterMetaType<Bae::DB>("Bae::DB");
        qRegisterMetaType<QList<QPersistentModelIndex>>("QList<QPersistentModelIndex>");

        moveToThread(&t);
        t.start();
    }

    ~AlbumLoader()
    {
        go=false;
        t.quit();
        t.wait();
    }

    void requestAlbums(Bae::TABLE type, QString query)
    {
        if(this->go) this->go = false;

        this->go = true;

        if(type==Bae::TABLE::ALBUMS)
            QMetaObject::invokeMethod(this, "getAlbums", Q_ARG(QString, query));
        else if(type==Bae::TABLE::ARTISTS)
            QMetaObject::invokeMethod(this, "getArtists", Q_ARG(QString, query));
    }

    void next() { this->nextAlbum = false;  }

public slots:
    void getAlbums(QString query)
    {
        qDebug()<<"GETTING TRACKS FROM ALBUMSVIEW";

        QSqlQuery mquery(query);
        auto albums = this->connection.getDBData(mquery);
        if(albums.size()>0)
        {
            for(auto albumMap : albums)
            {   if(go)
                {
                    emit albumReady(albumMap);
                    while(this->nextAlbum && go){t.msleep(100);}
                    this->nextAlbum=!this->nextAlbum;

                }else return;
            }
        }
        t.msleep(100);
        emit finished();
    }

    void getArtists(QString query)
    {
        QSqlQuery mquery(query);
        auto artists = this->connection.getDBData(mquery);
        if(artists.size()>0)
        {
            for(auto albumMap : artists)
            {
                if(go)
                {
                    emit albumReady(albumMap);
                    while(this->nextAlbum && go){t.msleep(100); }
                    this->nextAlbum=true;
                }else return;
            }
        }
        t.msleep(100);
        emit finished();
    }

signals:
    void albumReady(const Bae::DB &albumMap);
    void finished();

private:
    QThread t;
    CollectionDB connection;
    bool go=true;
    bool nextAlbum=true;
};

namespace Ui { class AlbumsView; }

class AlbumsView : public QWidget
{
    Q_OBJECT

public:
    explicit AlbumsView(const bool &extraList=false, QWidget *parent = nullptr);

    void populate(const Bae::TABLE &type, QSqlQuery &query);
    void addAlbum(const Bae::DB &albumMap);
    void populateExtraList(const QStringList &albums);
    void flushView();
    void hide_all(bool state);

    void filter(const Bae::DB_LIST &filter, const Bae::KEY &type);

    QFrame *utilsFrame;
    BabeTable *albumTable;
    BabeGrid *grid;
    QToolButton *expandBtn;

private:
    AlbumLoader albumLoader;
    bool extraList=false;

    QWidget *albumBox_frame;
    QFrame *line_h;
    BabeAlbum *cover;
    CollectionDB connection;
    QListWidget *artistList;
    QToolButton *closeBtn;


public slots:
    void hideAlbumFrame();
    void expandList();
    void showAlbumInfo(const Bae::DB &albumMap);

private slots:
    void albumHover();
    void filterAlbum(QModelIndex index);

signals:
    void albumDoubleClicked(const Bae::DB info);
    void albumOrderChanged(QString order);
    void playAlbum(const Bae::DB &info);
    void babeAlbum(const Bae::DB info);
    void populateFinished();
    void expandTo(const QString &artist);
    void createdAlbum(BabeAlbum *album);
};

#endif // ALBUMSVIEW_H