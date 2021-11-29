#ifndef LATIN_VALIDATOR_H
#define LATIN_VALIDATOR_H

#include <QValidator>

class LatinValidator : public QValidator {
public:
    LatinValidator(QObject *parent) : QValidator(parent)
    {
    }

    virtual State validate(QString& str, int&) const override {
        QRegExp rxp = QRegExp("[^ -~]");
        if (str.contains(rxp)) {
            return Invalid;
        }
        return Acceptable;
    }
};

#endif // LATIN_VALIDATOR_H
