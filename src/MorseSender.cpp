/*
 * MorseSender.cpp
 *
 *  Created on: 09.11.2014
 *      Author: Florian
 */

#include "MorseSender.hpp"

#include "pk/bbdevice/Flashlight.hpp"

#include <QTimer>

using namespace pk::bbdevice;
using namespace pk::signal;

MorseSender::MorseSender(pk::bbdevice::Flashlight *flashlight, QObject *parent)
  : QObject { parent },
    m_baseDuration { 1000 },
    m_signIterator {},
    m_light { flashlight },
    m_senderState { kEndOfMorseWord },
    m_sending { false }
{}

MorseSender::~MorseSender()
{}

void MorseSender::sendSignal(const QString &morseSignal)
{
    // if already sending, do nothing
    if (m_sending) {
        qDebug("MorseSender::sendSignal: already sending");
        return;
    }

    qDebug("MorseSender::sendSignal: sending '%s'", morseSignal.toUtf8().constData());
    m_morseSignal = MorseSignal::fromString(morseSignal);
    qDebug("MorseSender::sendSignal: encoded as: '%s'", m_morseSignal.toString().toUtf8().constData());
    m_sending = true;
    m_signIterator = m_morseSignal.cbegin();
    m_senderState = kSenderStart;
    onTimeout();
}

void MorseSender::onTimeout()
{
    auto waitFactor = 1;

    qDebug("MorseSender::onTimeout: timeout fired.");
    if (m_senderState == kEndOfMorseWord) {
        qDebug("MorseSender: transmission ended");
        return;
    } else if (m_senderState == kSenderStart) {
        qDebug("State machine init");
        switch (*m_signIterator) {
        case MorseSignal::EOW:
            m_senderState = kEndOfMorseWord;
            break;
        case MorseSignal::EOS:
            m_senderState = kEndOfMorseSign;
            break;
        case MorseSignal::Dot:
            m_senderState = kEnableShortLight;
            break;
        case MorseSignal::Dash:
            m_senderState = kEnableLongLight;
            break;
        }
        ++m_signIterator;
    }
    Q_ASSERT(m_senderState != kSenderStart);
    switch (m_senderState) {
    case kSenderStart:
        qDebug("Invalid state");
        // this case is taken care of by the assert and only exists to shut up the compiler
        break;
    case kEnableLongLight:
        qDebug("Enable long light");
        m_light->setEnabled(true);
        waitFactor = kShortFactor;
        m_senderState = kDisableLongLight;
        break;
    case kDisableLongLight:
        qDebug("Disable long light");
        m_light->setEnabled(false);
        m_senderState = kSenderStart;
        break;
    case kEnableShortLight:
        qDebug("Enable short light");
        m_light->setEnabled(true);
        m_senderState = kDisableShortLight;
        break;
    case kDisableShortLight:
        qDebug("Disable short light");
        m_light->setEnabled(false);
        m_senderState = kSenderStart;
        break;
    case kEndOfMorseSign:
        qDebug("End of sign");
        m_senderState = kSenderStart;
        waitFactor = kShortFactor;
        break;
    case kEndOfMorseWord:
        qDebug("End of word");
        waitFactor = kLongFactor;
        break;
    }
    QTimer::singleShot(m_baseDuration * waitFactor, this, SLOT(onTimeout()));
}
