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

#include "MorseSender.hpp"

#include "pk/bbdevice/Flashlight.hpp"

#include <QSettings>
#include <QTimer>

using namespace pk::bbdevice;
using namespace pk::signal::morse;

static const QString kSettingsKey = "Light/baseDuration";

MorseSender::MorseSender(pk::bbdevice::Flashlight *flashlight, QObject *parent)
  : QObject { parent },
    m_baseDuration { 1000 },
    m_signIterator {},
    m_light { flashlight },
    m_senderState { kEndOfMorseWord },
    m_sending { false }
{
    QSettings settings;

    m_baseDuration = settings.value(kSettingsKey, 500).toInt();
}

MorseSender::~MorseSender()
{}

void MorseSender::abortTransmission()
{
    if (!m_sending) {
        qDebug("MorseSender::abortTransmission: not sending");
        return;
    }
    qDebug("MorseSender::abortTransmission: stopping state machine");
    m_sending = false;
    emit sendingChanged(false);
    m_senderState = kSenderStart;
    if (m_light->enabled()) {
        m_light->setEnabled(false);
    }
}

void MorseSender::sendSignal(const QString &morseSignal)
{
    // if already sending, do nothing
    if (m_sending) {
        qDebug("MorseSender::sendSignal: already sending");
        return;
    }

    qDebug("MorseSender::sendSignal: sending '%s'", morseSignal.toUtf8().constData());
    m_morseSignal = FromString(morseSignal);
    qDebug("MorseSender::sendSignal: encoded as: '%s'", ToString(m_morseSignal).toUtf8().constData());
    m_sending = true;
    emit sendingChanged(true);
    m_signIterator = m_morseSignal.constBegin();
    m_senderState = kSenderStart;
    execState();
}

int MorseSender::baseDuration() const
{
    return m_baseDuration;
}

bool MorseSender::sending() const
{
    return m_sending;
}

void MorseSender::setBaseDuration(int newDuration)
{
    if (newDuration > 0) {
        m_baseDuration = newDuration;

        emit baseDurationChanged(newDuration);

        QSettings settings;

        settings.setValue(kSettingsKey, newDuration);
    }
}

void MorseSender::execState()
{
    // abortTransmission() may set m_sending to false to stop sending immediately.
    // There is be a race condition here, if the transmission is aborted and restarted immediately,
    // so there may be two active timers bound to this slot. This might be resolved for example by
    // using a QTimer member, which can be stopped if the transmission is aborted.
    if (!m_sending) {
        qDebug("MorseSender::execState: not sending");
        return;
    }

    auto waitFactor = 1;

    qDebug("MorseSender::execState: timeout fired.");
    if (m_senderState == kSenderStart) {
        switch (*m_signIterator) {
        case EOM:
            qDebug("State machine init: EOM");
            m_sending = false;
            emit sendingChanged(false);
            qDebug("MorseSender::execState: transmission ended");
            m_senderState = kSenderStart;

            return;
        case EOW:
            qDebug("State machine init: EOW");
            m_senderState = kEndOfMorseWord;
            break;
        case EOS:
            qDebug("State machine init: EOS");
            m_senderState = kEndOfMorseSign;
            break;
        case DOT:
            qDebug("State machine init: Dot");
            m_senderState = kEnableShortLight;
            break;
        case DASH:
            qDebug("State machine init: Dash");
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
        m_senderState = kSenderStart;
        waitFactor = kLongFactor;
        break;
    }
    QTimer::singleShot(m_baseDuration * waitFactor, this, SLOT(execState()));
}
