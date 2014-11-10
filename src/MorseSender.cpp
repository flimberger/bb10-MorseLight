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
    m_timer { new QTimer { this } },
    m_sending { false }
{
    bool success = false;

    success = connect(m_timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    Q_ASSERT(success);
    Q_UNUSED(success);

    m_timer->setSingleShot(true);
}

MorseSender::~MorseSender()
{}

void MorseSender::sendSignal(const MorseSignal &morseSignal)
{
    // if already sending, do nothing
    if (m_sending) {
        return;
    }

    m_morseSignal = morseSignal;
    m_sending = true;
    m_signIterator = m_morseSignal.cbegin();
    onTimeout();
}

void MorseSender::onTimeout()
{
    if (m_light->enabled()) {
        m_light->setEnabled(false);
        if (*(++m_signIterator) == MorseSignal::EOW) {
            if (m_signIterator == m_morseSignal.cend()) {
                m_sending = false;
                emit sendingDone();

                return;
            }
            m_timer->setInterval(m_baseDuration * kLongFactor);
            ++m_signIterator;
        } else {
            m_timer->setInterval(m_baseDuration);
        }
    } else {
        m_light->setEnabled(true);
        if (*m_signIterator == MorseSignal::Dot) {
            m_timer->setInterval(m_baseDuration);
        } else if (*m_signIterator == MorseSignal::Dash) {
            m_timer->setInterval(m_baseDuration * kShortFactor);
        }
    }
    m_timer->start();
}
