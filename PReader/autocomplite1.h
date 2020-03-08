#ifndef AUTOCOMPLITE1_H
#define AUTOCOMPLITE1_H

#include <QObject>

class Autocomplite1 : public QObject
{
    Q_OBJECT
public:
    explicit Autocomplite1(QObject *parent = nullptr);
    ~Autocomplite1();

signals:

public slots:
    void run();
};

#endif // AUTOCOMPLITE1_H
