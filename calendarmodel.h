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
#include "dependencypool.h"
#include "dependencypointer.h"
class day_span :public QObject{
    Q_OBJECT
public:
    explicit day_span(){}
    std::unique_ptr<QCalendar::YearMonthDay> from_;
    std::unique_ptr<QCalendar::YearMonthDay> to_;

    void check_for_swap(){
        if(from_ && to_){
            QDate from = QDate(from_->year,from_->month,from_->day);
            QDate to = QDate(to_->year,to_->month,to_->day);
            if(from>to){
                std::swap(from_,to_);
            }
        }
    }
};

class CalendarModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int whichRow READ whichRow WRITE setWhichRow NOTIFY whichRowChanged)
    Q_PROPERTY(int day_s READ day_s WRITE setDay_s NOTIFY day_sChanged)
    Q_PROPERTY(QString month READ month WRITE setMonth NOTIFY monthChanged)
    Q_PROPERTY(int year_ READ year_ WRITE setYear_ NOTIFY year_Changed)
    Q_PROPERTY(int selectMonth READ selectMonth WRITE setSelectMonth NOTIFY selectMonthChanged)
    Q_PROPERTY(int selectYear READ selectYear WRITE setSelectYear NOTIFY selectYearChanged)
    Q_PROPERTY(QString from_day READ from_day WRITE setFrom_day NOTIFY from_dayChanged)
    Q_PROPERTY(QString to_day READ to_day WRITE setTo_day NOTIFY to_dayChanged)
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

    const int &selectMonth() const;
    void setSelectMonth(const int &newSelectMonth);

    const QString &from_day() const;
    void setFrom_day(const QString &newFrom_day);

    const QString &to_day() const;
    void setTo_day(const QString &newTo_day);

    int selectYear() const;
    void setSelectYear(int newSelectYear);

protected:
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void next_month();

    void prev_month();

    void select_date_(int day,int month,int year);

signals:
    void whichRowChanged();

    void day_sChanged();

    void monthChanged();

    void year_Changed();

    void selectMonthChanged();

    void from_dayChanged();

    void to_dayChanged();

    void selectYearChanged();

private:
    bool is_there_interval_{false};

    int border_with_{1};

    QVector<QVector<day_t*>> days_;

    QVector<day_t*> days_string_;

    QStringList jalali_months = {"??????????????" , "????????????????", "??????????", "??????", "??????????????", "????????????", "??????", "????????", "??????", "????", "????????", "??????????"};

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

    int m_selectMonth;

    Dependency::Pointer<day_span> day_span_;

    bool does_two_ymd_same(const QCalendar::YearMonthDay& l,const QCalendar::YearMonthDay& r);

    bool is_between(const QCalendar::YearMonthDay& l);
    QString m_from_day;
    QString m_to_day;
    int m_selectYear;
};



#endif // CALENDARMODEL_H
