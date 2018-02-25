#ifndef TVSHOWSEARCH_H
#define TVSHOWSEARCH_H

#include <QDialog>
#include <QTableWidgetItem>

#include "globals/Globals.h"

namespace Ui {
class TvShowSearch;
}

/**
 * @brief The TvShowSearch class
 */
class TvShowSearch : public QDialog
{
    Q_OBJECT

public:
    explicit TvShowSearch(QWidget *parent = 0);
    ~TvShowSearch();
    QString scraperId();
    QList<int> infosToLoad();
    void setSearchType(TvShowType type);
    TvShowUpdateType updateType();

public slots:
    int exec();
    int exec(QString searchString, QString id);
    static TvShowSearch *instance(QWidget *parent = 0);

private slots:
    void onSearch();
    void onShowResults(QList<ScraperSearchResult> results);
    void onResultClicked(QTableWidgetItem *item);
    void onChkToggled();
    void onChkAllToggled();
    void onComboIndexChanged();
    void onChkDvdOrderToggled();

private:
    Ui::TvShowSearch *ui;
    void clear();
    QString m_scraperId;
    QList<int> m_infosToLoad;
    TvShowType m_searchType;
};

#endif // TVSHOWSEARCH_H
