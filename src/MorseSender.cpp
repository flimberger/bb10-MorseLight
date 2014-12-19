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

//! Convert input string to ASCII and remove funny chars
static QVector<char> SanitizeString(const QString &input)
{
    QVector<char> out;
    auto str = input.toAscii();
    auto len = str.length();

    for (int i = 0; i < len; ++i) {
        auto c = str[i];

        if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z') || ('0' <= c && c <= '9') || (c == ' ')) {
            out.append(c);
        }
    }

    return out;
}

static const char_t *GetMorseChar(char c)
{
    const char_t *ptr;

    if ('A' <= c && c <= 'Z') {
        ptr = LETTER_TABLE[c - 'A'];
    } else if ('a' <= c && c <= 'z') {
        ptr = LETTER_TABLE[c - 'a'];
    } else if ('0' <= c && c <= '9') {
        ptr = DIGIT_TABLE[c - '0'];
    } else if (c == ' ') {
        ptr = &WORD_DELIMETER;
    }

    return ptr;
}

MorseSender::MorseSender(pk::bbdevice::Flashlight *flashlight, QObject *parent)
  : QObject { parent },
    m_currentMorseChar { nullptr },
    m_light { flashlight },
    m_baseDuration { 1000 },
    m_currentCharIdx { -1 },
    m_senderState { NEXT_SIG_CHAR },
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
    m_senderState = NEXT_SIG_CHAR;
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

    // All this encoding bullshit...
    m_currentSignal = SanitizeString(morseSignal);
    emit currentSignalChanged(QString::fromAscii(m_currentSignal.constData()));
    qDebug("MorseSender::sendSignal: sending '%s'", m_currentSignal.constData());
    m_sending = true;
    emit sendingChanged(true);
    m_currentCharIdx = 0;
    emit currentCharIdxChanged(m_currentCharIdx);
    m_senderState = NEXT_SIG_CHAR;
    execState();
}

int MorseSender::baseDuration() const
{
    return m_baseDuration;
}

int MorseSender::currentCharIdx() const
{
    return m_currentCharIdx;
}

QString MorseSender::currentSignal() const
{
    return QString::fromAscii(m_currentSignal.constData());
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

/*
 * The state machine:
 * NEXT_SIG_CHAR --------> NEXT_MORSE_CHAR
 * NEXT_MORSE_CHAR -Dash-> DISABLE_LIGHT
 * NEXT_MORSE_CHAR -Dot--> DISABLE_LIGHT
 * NEXT_MORSE_CHAR -EOS--> NEXT_SIG_CHAR
 * NEXT_MORSE_CHAR -EOW--> NEXT_SIG_CHAR
 * DISABLE_LIGHT --------> NEXT_MORSE_CHAR
 */
void MorseSender::execState()
{
loop:
    // abortTransmission() may set m_sending to false to stop sending immediately.
    // There is be a race condition here, if the transmission is aborted and restarted immediately,
    // so there may be two active timers bound to this slot. This might be resolved for example by
    // using a QTimer member, which can be stopped if the transmission is aborted.
    if (!m_sending) {
        qDebug("MorseSender::execState: not sending");
        return;
    }

    auto waitFactor = 1;

    switch (m_senderState) {
    case NEXT_SIG_CHAR:
        if (m_currentCharIdx >= m_currentSignal.size()) {
            qDebug("MorseSender::execState: transmission ended");
            m_sending = false;
            emit sendingChanged(m_sending);

            return;
        }
        qDebug("Next signal char: %c %s", m_currentSignal[m_currentCharIdx],
           ToString(GetMorseChar(m_currentSignal[m_currentCharIdx])).toAscii().constData());
        m_currentMorseChar = GetMorseChar(m_currentSignal[m_currentCharIdx]);
        m_senderState = NEXT_MORSE_CHAR;
        goto loop;
    case NEXT_MORSE_CHAR:
        qDebug("Next morse char");
        switch (*m_currentMorseChar) {
        case EOW:
            qDebug("State machine: EOW; End of word");
            ++m_currentCharIdx;
            emit currentCharIdxChanged(m_currentCharIdx);
            m_senderState = NEXT_SIG_CHAR;
            waitFactor = LONG_FACTOR;
            break;
        case EOS:
            qDebug("State machine: EOS; End of sign");
            ++m_currentCharIdx;
            emit currentCharIdxChanged(m_currentCharIdx);
            m_senderState = NEXT_SIG_CHAR;
            waitFactor = SHORT_FACTOR;
            break;
        case DOT:
            qDebug("State machine: Dot; Enable short light");
            m_light->setEnabled(true);
            m_senderState = DISABLE_LIGHT;
            break;
        case DASH:
            qDebug("State machine: Dash; Enable long light");
            m_light->setEnabled(true);
            waitFactor = SHORT_FACTOR;
            m_senderState = DISABLE_LIGHT;
            break;
        }
        break;
    case DISABLE_LIGHT:
        qDebug("Disable short light");
        m_light->setEnabled(false);
        m_senderState = NEXT_MORSE_CHAR;
        ++m_currentMorseChar;
        break;
    }
    qDebug("waiting %d time units", waitFactor);
    QTimer::singleShot(m_baseDuration * waitFactor, this, SLOT(execState()));
}
