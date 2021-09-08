#include "calendarmodel.h"
#include <QDebug>
CalendarModel::CalendarModel(QObject *parent)
    : QAbstractListModel(parent)
{
    selected_date_ = QDate::currentDate();
    jalali_calendar = QCalendar(QCalendar::System::Jalali);
    iterate_over_month();
}

int CalendarModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    return days_.size();
}

QVariant CalendarModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    auto item = days_.at(index.row());
    switch (role) {
    case DAY:{
        return item.first;
    }
    default: {
        return 0;
    };
    }
}

QHash<int, QByteArray> CalendarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[DAY] = "day";
    return roles;
}

void CalendarModel::next_month()
{
    reset_day_2_first(selected_date_);
    selected_date_ = selected_date_.addMonths(1);
    iterate_over_month();
}

void CalendarModel::prev_month()
{
    reset_day_2_first(selected_date_);
    selected_date_ = selected_date_.addMonths(-1);
    iterate_over_month();
}

int CalendarModel::day_of_week(const QDate &date)
{
    if(date.dayOfWeek()<6){
        return date.dayOfWeek()+2;
    }else{
        return date.dayOfWeek() % 6 +1;
    }
}

void CalendarModel::reset_day_2_first(QDate &date)
{
    auto jalali_parsed = jalali_calendar.partsFromDate(date);
    if(jalali_parsed.day>1){
        date = date.addDays(-(jalali_parsed.day-1));
    }
}

void CalendarModel::iterate_over_month()
{
    beginResetModel();
    days_.clear();
    auto jalali_parsed = jalali_calendar.partsFromDate(selected_date_);
    auto y = jalali_parsed.year;
    const auto m = jalali_parsed.month;
    const auto d = jalali_parsed.day;

    auto temp_date=selected_date_;
    if(d>1){
        temp_date = temp_date.addDays(-(d-1));
    }
    days_.resize(42);
    int row = day_of_week(temp_date);
    while (jalali_calendar.partsFromDate(temp_date).month==m) {
        jalali_parsed = jalali_calendar.partsFromDate(temp_date);
        const auto Day_of_week = day_of_week(temp_date);
        days_[row-1]={jalali_parsed.day,Day_of_week};
        temp_date = temp_date.addDays(1);
        row++;
    }
    endResetModel();
}

