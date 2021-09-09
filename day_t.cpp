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