#ifndef NANOTIMER_H
#define NANOTIMER_H

#include <QObject>

class NanoTimer : public QObject
{
  Q_OBJECT
public:
  explicit NanoTimer(QObject *parent = nullptr);

signals:

public slots:
};

#endif // NANOTIMER_H
