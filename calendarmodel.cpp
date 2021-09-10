#include "calendarmodel.h"
#include <QDebug>
CalendarModel::CalendarModel(QObject *parent)
    : QAbstractListModel(parent)
{
    selected_date_ = QDate::currentDate();
    current_date_ = selected_date_;
    jalali_calendar = QCalendar(QCalendar::System::Jalali);

    days_string_={
        day_create("شنبه",true),
        day_create("یک شنبه",true),
        day_create("دو شنبه",true),
        day_create("سه شنبه",true),
        day_create("چهارشنبه",true),
        day_create("پنج شنبه",true),
        day_create("جمعه",true),
    };
    for(auto * d:qAsConst(days_string_)){
        d->setTextColor("white");
    }
    std::reverse(days_string_.begin(),days_string_.end());

    create_month(selected_date_);
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
    return QVariant::fromValue(item);
}

QHash<int, QByteArray> CalendarModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::UserRole + 1] = "item";
    return roles;
}

void CalendarModel::next_month()
{
    selected_date_ = selected_date_.addMonths(1);
    create_month(selected_date_);
}

void CalendarModel::prev_month()
{
    selected_date_ = selected_date_.addMonths(-1);
    create_month(selected_date_);
}

int CalendarModel::day_of_week(const QDate &date)
{
    if(date.dayOfWeek()<6){
        return date.dayOfWeek()+2;
    }else{
        return date.dayOfWeek() % 6 +1;
    }
}


day_t* CalendarModel::day_create(QString &day_number_, bool is_header,int dow, QDate *date)
{
    auto * day = new day_t();
    day->setDay(day_number_);
    day->setIsheader(is_header);
    day->setBorderWidth(border_with_);
    if(date!=nullptr){
        QDate* datep = new QDate(*date);
        day->setDate(datep);
    }
    if(dow==7){
        day->setTextColor("red");
    }
    return day;
}

day_t *CalendarModel::day_create(QString &&day_number_, bool is_header,int dow, QDate *date)
{
    auto * day = new day_t();
    day->setDay(day_number_);
    day->setIsheader(is_header);
    day->setBorderWidth(border_with_);
    if(date!=nullptr){
        QDate* datep = new QDate(*date);
        day->setDate(datep);
    }
    if(dow==7){
        day->setTextColor("red");
    }
    return day;
}



int CalendarModel::whichRow() const
{
    return m_whichRow;
}

void CalendarModel::setWhichRow(int newWhichRow)
{
    if (m_whichRow == newWhichRow)
        return;
    m_whichRow = newWhichRow;
    create_month(selected_date_);
    emit whichRowChanged();
}

void CalendarModel::create_month(QDate &selected_date)
{
    beginResetModel();
    days_.clear();
    auto jalali_parsed = jalali_calendar.partsFromDate(selected_date);
    auto y = jalali_parsed.year;
    const auto m = jalali_parsed.month;
    const auto d = jalali_parsed.day;

    setMonth(jalali_months[m-1]);
    setDay_s(d);
    setYear_(y);

    auto temp_date=selected_date;
    if(d>1){
        temp_date = temp_date.addDays(-(d-1));
    }

    days_.push_back(days_string_);
    QVector<day_t*> each_row;
    each_row.resize(7);
    int dow{0};
    while (jalali_calendar.partsFromDate(temp_date).month==m) {
        jalali_parsed = jalali_calendar.partsFromDate(temp_date);
        dow = day_of_week(temp_date);
        each_row[dow-1]=day_create(QString::number(jalali_parsed.day),false,dow,&temp_date);
        if(temp_date==current_date_){
            each_row[dow-1]->setIs_current(true);
            each_row[dow-1]->setBorderColor("green");
            each_row[dow-1]->setBorderWidth(6);
        }
        if(dow==7){
            not_null(each_row);
            std::reverse(each_row.begin(),each_row.end());
            days_.push_back(each_row);
            each_row.clear();
            each_row.resize(7);
            dow=0;
        }
        temp_date = temp_date.addDays(1);
    }
    if(dow>0){
        not_null(each_row);
        std::reverse(each_row.begin(),each_row.end());
        days_.push_back(each_row);
    }



    endResetModel();
}

void CalendarModel::not_null(QVector<day_t *> &vec)
{
    for(int i=0;i<vec.size();i++){
        if(!vec[i]){
            vec[i] = day_create("",false);
        }
    }
}


int CalendarModel::day_s() const
{
    return m_day_s;
}

void CalendarModel::setDay_s(int newDay_s)
{
    if (m_day_s == newDay_s)
        return;
    m_day_s = newDay_s;
    emit day_sChanged();
}

const QString &CalendarModel::month() const
{
    return m_month;
}

void CalendarModel::setMonth(const QString &newMonth)
{
    if (m_month == newMonth)
        return;
    m_month = newMonth;
    emit monthChanged();
}

int CalendarModel::year_() const
{
    return m_year_;
}

void CalendarModel::setYear_(int newYear_)
{
    if (m_year_ == newYear_)
        return;
    m_year_ = newYear_;
    emit year_Changed();
}
