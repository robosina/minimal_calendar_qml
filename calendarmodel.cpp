#include "calendarmodel.h"
#include <QDebug>
CalendarModel::CalendarModel(QObject *parent)
    : QAbstractListModel(parent)
{
    selected_date_ = QDate::currentDate();
    current_date_ = selected_date_;
    jalali_calendar = QCalendar(QCalendar::System::Jalali);

    days_string_={
        day_create("ش",true),
        day_create("ی",true),
        day_create("د",true),
        day_create("س",true),
        day_create("چ",true),
        day_create("پ",true),
        day_create("ج",true),
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

void CalendarModel::select_date_(int day, int month, int year)
{
    auto p = std::make_pair(QCalendar::YearMonthDay(year,month,day),selected_date_);
    if(!day_span_->from_){
        day_span_->from_=std::make_unique<QCalendar::YearMonthDay>(QCalendar::YearMonthDay(year,month,day));
        is_there_interval_=false;
        create_month(selected_date_);
        setFrom_day(QString("%1/%2/%3").arg(year).arg(month).arg(day));
        return;
    }

    if(!day_span_->to_){
        day_span_->to_=std::make_unique<QCalendar::YearMonthDay>(QCalendar::YearMonthDay(year,month,day));
        is_there_interval_=true;
        day_span_->check_for_swap();
        create_month(selected_date_);
        setTo_day(QString("%1/%2/%3").arg(year).arg(month).arg(day));
        return;
    }

    day_span_->from_.reset(nullptr);
    day_span_->to_.reset(nullptr);
    create_month(selected_date_);
    setFrom_day("");
    setTo_day("");

    is_there_interval_=false;

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
            each_row[dow-1]->setBoxColor("#99ff99");
            each_row[dow-1]->setRadius(30);
            each_row[dow-1]->setMargin(0);
        }
        if(day_span_->from_ && does_two_ymd_same(jalali_parsed,*day_span_->from_)){
            each_row[dow-1]->setBoxColor("#8888ff");
            each_row[dow-1]->setBoxOpacity(0.3);
            each_row[dow-1]->setRadius(30);
            each_row[dow-1]->setMargin(0);
            each_row[dow-1]->setIs_from(true);
        }

        if(day_span_->to_){
            if(is_between(jalali_parsed)){
                each_row[dow-1]->setBoxColor("#8888ff");
                each_row[dow-1]->setBoxOpacity(0.3);
                each_row[dow-1]->setMargin(0);
            }
            if(does_two_ymd_same(jalali_parsed,*day_span_->to_)){
                each_row[dow-1]->setBoxColor("#8888ff");
                each_row[dow-1]->setBoxOpacity(0.3);
                each_row[dow-1]->setRadius(30);
                each_row[dow-1]->setMargin(0);
                each_row[dow-1]->setIs_to(true);
            }
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

bool CalendarModel::does_two_ymd_same(const QCalendar::YearMonthDay &l, const QCalendar::YearMonthDay &r)
{
    if(l.day==r.day && l.month==r.month && l.year==r.year){
        return true;
    }
    return false;
}

bool CalendarModel::is_between(const QCalendar::YearMonthDay &l)
{
    auto Convert=[](const QCalendar::YearMonthDay& in){
        auto date = QDate(in.year,in.month,in.day);
        return date;
    };

    if(Convert(*day_span_->from_)<Convert(l) && Convert(*day_span_->to_)>Convert(l)){
        return true;
    }
    return false;
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

const int &CalendarModel::selectMonth() const
{
    return m_selectMonth;
}

void CalendarModel::setSelectMonth(const int &newSelectMonth)
{
    auto get_month=[&](const QDate& date){
        return jalali_calendar.partsFromDate(date).month;
    };

    selected_date_=QDate::currentDate();
    while(get_month(selected_date_)!=newSelectMonth){
        if(get_month(selected_date_)>newSelectMonth){
            selected_date_ = selected_date_.addDays(-10);
        }else{
            selected_date_ = selected_date_.addDays(10);
        }
    }
    create_month(selected_date_);
    if (m_selectMonth == newSelectMonth)
        return;
    m_selectMonth = newSelectMonth;
    emit selectMonthChanged();
}

const QString &CalendarModel::from_day() const
{
    return m_from_day;
}

void CalendarModel::setFrom_day(const QString &newFrom_day)
{
    if (m_from_day == newFrom_day)
        return;
    m_from_day = newFrom_day;
    emit from_dayChanged();
}

const QString &CalendarModel::to_day() const
{
    return m_to_day;
}

void CalendarModel::setTo_day(const QString &newTo_day)
{
    if (m_to_day == newTo_day)
        return;
    m_to_day = newTo_day;
    emit to_dayChanged();
}

int CalendarModel::selectYear() const
{
    return m_selectYear;
}

void CalendarModel::setSelectYear(int newSelectYear)
{
    if (m_selectYear == newSelectYear)
        return;
    m_selectYear = newSelectYear;
    emit selectYearChanged();
}
