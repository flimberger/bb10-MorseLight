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

#include "pk/signal/MorseSignal.hpp"

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
    Q_PROPERTY(bool sending
               READ sending
               NOTIFY sendingChanged)
public:
    explicit MorseSender(pk::bbdevice::Flashlight *flashlight, QObject *parent=nullptr);
    virtual ~MorseSender();

    Q_SLOT void abortTransmission();
    Q_SLOT void sendSignal(const QString &morseSignal);

    int baseDuration() const;
    bool sending() const;
    void setBaseDuration(int newDuration);

Q_SIGNALS:
    void baseDurationChanged(int newDuration);
    void sendingChanged(bool newState);

private:
    static const auto kShortFactor = 3;
    static const auto kLongFactor = 7;

    enum SenderState
    {
        kSenderStart,
        kEnableLongLight,
        kDisableLongLight,
        kEnableShortLight,
        kDisableShortLight,
        kEndOfMorseSign,
        kEndOfMorseWord
    };

    Q_SLOT void execState();

    int m_baseDuration;
    pk::signal::MorseSignal m_morseSignal;
    pk::signal::MorseSignal::const_iterator m_signIterator;
    pk::bbdevice::Flashlight *m_light;
    SenderState m_senderState;
    bool m_sending;
};

#endif // MORSESENDER_HPP_
