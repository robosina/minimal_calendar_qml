#ifndef CALENDARMODEL_H
#define CALENDARMODEL_H

#include <QAbstractListModel>
#include <QCalendar>
#include <QDate>
#include <deque>
#include <day_t.h>
#include <QMutex>
#include <QVector>
#include <QList>

class CalendarModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int whichRow READ whichRow WRITE setWhichRow NOTIFY whichRowChanged)
    Q_PROPERTY(int day_s READ day_s WRITE setDay_s NOTIFY day_sChanged)
    Q_PROPERTY(QString month READ month WRITE setMonth NOTIFY monthChanged)
    Q_PROPERTY(int year_ READ year_ WRITE setYear_ NOTIFY year_Changed)
public:
    explicit CalendarModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    int whichRow() const;

    void setWhichRow(int newWhichRow);

    int day_s() const;
    void setDay_s(int newDay_s);

    const QString &month() const;
    void setMonth(const QString &newMonth);

    int year_() const;
    void setYear_(int newYear_);

protected:
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void next_month();

    void prev_month();

signals:
    void whichRowChanged();

    void day_sChanged();

    void monthChanged();

    void year_Changed();

private:
    int border_with_{1};

    QVector<QVector<day_t*>> days_;

    QVector<day_t*> days_string_;

    QStringList jalali_months = {"فروردین" , "اردیبهشت", "خرداد", "تیر", "اَمرداد", "شهریور", "مهر", "آبان", "آذر", "دی", "بهمن", "اسفند"};

    QDate selected_date_;

    QDate current_date_;

    QCalendar jalali_calendar;

    int m_whichRow;


    static int day_of_week(const QDate& date);

    day_t *day_create(QString & day_number_, bool is_header, int dow=0, QDate *date=nullptr);

    day_t *day_create(QString && day_number_, bool is_header, int dow=0, QDate *date=nullptr);

    void create_month(QDate &selected_date);

    void not_null(QVector<day_t*>& vec);
    int m_day_s;
    QString m_month;
    int m_year_;
};

#endif // CALENDARMODEL_H
