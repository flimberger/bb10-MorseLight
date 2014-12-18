// Copyright (c) 2014, Florian Limberger <flo@snakeoilproductions.net>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
// OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef MORSESENDER_HPP_
#define MORSESENDER_HPP_

#include "pk/signal/Morse.h" // includes QVector

#include <QObject>

namespace pk
{
namespace bbdevice
{

class Flashlight;

} // namespace bbdevice
} // namespace pk

class MorseSender : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int baseDuration
               READ baseDuration
               WRITE setBaseDuration
               NOTIFY baseDurationChanged)
    Q_PROPERTY(int currentCharIdx
               READ currentCharIdx
               NOTIFY currentCharIdxChanged)
    Q_PROPERTY(QString currentSignal
               READ currentSignal
               NOTIFY currentSignalChanged)
    Q_PROPERTY(bool sending
               READ sending
               NOTIFY sendingChanged)
public:
    explicit MorseSender(pk::bbdevice::Flashlight *flashlight, QObject *parent=nullptr);
    virtual ~MorseSender();

    Q_SLOT void abortTransmission();
    Q_SLOT void sendSignal(const QString &morseSignal);

    int baseDuration() const;
    int currentCharIdx() const;
    QString currentSignal() const;
    bool sending() const;
    void setBaseDuration(int newDuration);

Q_SIGNALS:
    void baseDurationChanged(int newDuration);
    void currentCharIdxChanged(int newCharIdx);
    void currentSignalChanged(QString newSignal);
    void sendingChanged(bool newState);

private:
    static const auto SHORT_FACTOR = 3;
    // A long factor is waited after a word was transmitted. In this case, a short time was already
    // waited, because the end of a word is also the end of a character, so 3 time units are already
    // accounted for.
    static const auto LONG_FACTOR = 4;

    typedef enum
    {
        NEXT_SIG_CHAR,
        NEXT_MORSE_CHAR,
        DISABLE_LIGHT
    } state_t;

    Q_SLOT void execState();

    QVector<char> m_currentSignal; //< must always be ASCII
    const pk::signal::morse::char_t *m_currentMorseChar;
    pk::bbdevice::Flashlight *m_light;
    int m_baseDuration;
    int m_currentCharIdx;
    state_t m_senderState;
    bool m_sending;
};

#endif // MORSESENDER_HPP_
