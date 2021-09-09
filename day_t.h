#ifndef DAY_T_H
#define DAY_T_H

#include <QObject>

class day_t : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString day READ day WRITE setDay NOTIFY dayChanged)
    Q_PROPERTY(bool isheader READ isheader WRITE setIsheader NOTIFY isheaderChanged)
    Q_PROPERTY(bool is_current READ is_current WRITE setIs_current NOTIFY is_currentChanged)
    Q_PROPERTY(QString borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY borderWidthChanged)
    Q_PROPERTY(QString textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    QString m_day;

    bool m_isheader;

    bool m_is_current;

    QString m_borderColor{"transparent"};

    int m_borderWidth{0};

    QString m_textColor{"black"};

public:
    explicit day_t(QObject *parent = nullptr);

    const QString &day() const;
    void setDay(const QString &newDay);
    bool isheader() const;
    void setIsheader(bool newIsheader);

    bool is_current() const;
    void setIs_current(bool newIs_current);

    const QString &borderColor() const;
    void setBorderColor(const QString &newBorderColor);

    int borderWidth() const;
    void setBorderWidth(int newBorderWidth);

    const QString &textColor() const;
    void setTextColor(const QString &newTextColor);

signals:
    void dayChanged();
    void isheaderChanged();
    void is_currentChanged();
    void borderColorChanged();
    void borderWidthChanged();
    void textColorChanged();
};

#endif // DAY_T_H
