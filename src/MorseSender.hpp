/*
 * MorseSender.hpp
 *
 *  Created on: 09.11.2014
 *      Author: Florian
 */

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

public:
    explicit MorseSender(pk::bbdevice::Flashlight *flashlight, QObject *parent=nullptr);
    virtual ~MorseSender();

    Q_SLOT void sendSignal(const QString &morseSignal);

Q_SIGNALS:
    void sendingDone();

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

    Q_SLOT void onTimeout();

    int m_baseDuration;
    pk::signal::MorseSignal m_morseSignal;
    pk::signal::MorseSignal::const_iterator m_signIterator;
    pk::bbdevice::Flashlight *m_light;
    SenderState m_senderState;
    bool m_sending;
};

#endif // MORSESENDER_HPP_