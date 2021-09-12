#include "day_t.h"

day_t::day_t(QObject *parent) : QObject(parent)
{

}

const QString &day_t::day() const
{
    return m_day;
}

void day_t::setDay(const QString &newDay)
{
    if (m_day == newDay)
        return;
    m_day = newDay;
    emit dayChanged();
}

bool day_t::isheader() const
{
    return m_isheader;
}

void day_t::setIsheader(bool newIsheader)
{
    if(newIsheader){
        setBoxColor("gray");
    }
    if (m_isheader == newIsheader)
        return;
    m_isheader = newIsheader;
    emit isheaderChanged();
}

bool day_t::is_current() const
{
    return m_is_current;
}

void day_t::setIs_current(bool newIs_current)
{
    if (m_is_current == newIs_current)
        return;
    m_is_current = newIs_current;
    emit is_currentChanged();
}

const QString &day_t::borderColor() const
{
    return m_borderColor;
}

void day_t::setBorderColor(const QString &newBorderColor)
{
    if (m_borderColor == newBorderColor)
        return;
    m_borderColor = newBorderColor;
    emit borderColorChanged();
}

int day_t::borderWidth() const
{
    return m_borderWidth;
}

void day_t::setBorderWidth(int newBorderWidth)
{
    if (m_borderWidth == newBorderWidth)
        return;
    m_borderWidth = newBorderWidth;
    emit borderWidthChanged();
}

const QString &day_t::textColor() const
{
    return m_textColor;
}

void day_t::setTextColor(const QString &newTextColor)
{
    if (m_textColor == newTextColor)
        return;
    m_textColor = newTextColor;
    emit textColorChanged();
}

QDate *day_t::date() const
{
    return m_date;
}

void day_t::setDate(QDate *newDate)
{
    if (m_date == newDate)
        return;
    m_date = newDate;
    emit dateChanged();
}

const QString &day_t::boxColor() const
{
    return m_boxColor;
}

void day_t::setBoxColor(const QString &newBoxColor)
{
    if (m_boxColor == newBoxColor)
        return;
    m_boxColor = newBoxColor;
    emit boxColorChanged();
}

float day_t::boxOpacity() const
{
    return m_boxOpacity;
}

void day_t::setBoxOpacity(float newBoxOpacity)
{
    if (qFuzzyCompare(m_boxOpacity, newBoxOpacity))
        return;
    m_boxOpacity = newBoxOpacity;
    emit boxOpacityChanged();
}

int day_t::radius() const
{
    return m_radius;
}

void day_t::setRadius(int newRadius)
{
    if (m_radius == newRadius)
        return;
    m_radius = newRadius;
    emit radiusChanged();
}

int day_t::margin() const
{
    return m_margin;
}

void day_t::setMargin(int newMargin)
{
    if (m_margin == newMargin)
        return;
    m_margin = newMargin;
    emit marginChanged();
}

bool day_t::is_from() const
{
    return m_is_from;
}

void day_t::setIs_from(bool newIs_from)
{
    if (m_is_from == newIs_from)
        return;
    m_is_from = newIs_from;
    emit is_fromChanged();
}

bool day_t::is_to() const
{
    return m_is_to;
}

void day_t::setIs_to(bool newIs_to)
{
    if (m_is_to == newIs_to)
        return;
    m_is_to = newIs_to;
    emit is_toChanged();
}
