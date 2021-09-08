#ifndef CALENDARMODEL_H
#define CALENDARMODEL_H

#include <QAbstractListModel>
#include <QCalendar>
#include <QDate>
#include <deque>
class CalendarModel : public QAbstractListModel
{
    Q_OBJECT

    enum DATA{
        DAY=Qt::UserRole+1
    };

public:
    explicit CalendarModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

protected:
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void next_month();

    void prev_month();

private:

    QDate selected_date_;

    QCalendar jalali_calendar;

    static int day_of_week(const QDate& date);

    void iterate_over_month();

    std::deque<std::pair<int,int>> days_;

    void reset_day_2_first(QDate& date);
};

#endif // CALENDARMODEL_H
