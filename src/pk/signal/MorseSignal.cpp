/*
 * MorseCode.cpp
 *
 *  Created on: 08.11.2014
 *      Author: Florian
 */

#include "MorseSignal.hpp"

#include <QString>

namespace pk
{
namespace signal
{

static void append(QVector<MorseSignal::Character> vector, const QPair<size_t, const MorseSignal::Character *> &charPair)
{
    for (size_t i = 0; i < charPair.first; ++i) {
        vector.append(charPair.second[i]);
    }
}

MorseSignal MorseSignal::fromString(const QString &string)
{
    auto morseChars = QVector<Character> {};
    auto end = string.constEnd();

    for (auto i = string.constBegin(); i != end; ++i) {
        if (0x30 <= i->toAscii() && i->toAscii() <= 0x39) {
            auto c = i->toAscii();

            qDebug("%c", c);
            append(morseChars, kDigitTable[c - 0x30]);
        }
        if (0x41 <= i->toAscii() && i->toAscii() <= 0x5a) {
            auto c = i->toAscii();

            qDebug("%c", c);
            append(morseChars, kLetterTable[c - 0x41]);
        }
        if (0x61 <= i->toAscii() && i->toAscii() <= 0x7a) {
            auto c = i->toAscii();

            qDebug("%c", c);
            append(morseChars, kLetterTable[c - 0x61]);
        }
    }

    return MorseSignal { morseChars };
}

MorseSignal::MorseSignal()
{}

MorseSignal::MorseSignal(const MorseSignal &other)
  : m_data { other.m_data }
{}

MorseSignal &MorseSignal::operator=(const MorseSignal &other)
{
    m_data = other.m_data;

    return *this;
}

QString MorseSignal::toString()
{
    auto string = QString {};
    auto end = m_data.constEnd();

    for (auto i = m_data.constBegin(); i != end; ++i) {
        switch (*i) {
        case Dot:
            string += ".";
            break;
        case Dash:
            string += "-";
            break;
        case EOW:
            string += " ";
            break;
        }
    }

    return string;
}

const QVector<MorseSignal::Character> &MorseSignal::data() const
{
    return m_data;
}

const MorseSignal::Character MorseSignal::kA[] = { Dot,  Dash };
const MorseSignal::Character MorseSignal::kB[] = { Dash, Dot,  Dot,  Dot };
const MorseSignal::Character MorseSignal::kC[] = { Dash, Dot,  Dash, Dot };
const MorseSignal::Character MorseSignal::kD[] = { Dash, Dot,  Dot };
const MorseSignal::Character MorseSignal::kE[] = { Dot };
const MorseSignal::Character MorseSignal::kF[] = { Dot,  Dot,  Dash, Dot };
const MorseSignal::Character MorseSignal::kG[] = { Dash, Dash, Dot };
const MorseSignal::Character MorseSignal::kH[] = { Dot,  Dot,  Dot,  Dot };
const MorseSignal::Character MorseSignal::kI[] = { Dot,  Dot };
const MorseSignal::Character MorseSignal::kJ[] = { Dot,  Dash, Dash, Dash };
const MorseSignal::Character MorseSignal::kK[] = { Dash, Dot,  Dash };
const MorseSignal::Character MorseSignal::kL[] = { Dot,  Dash, Dot };
const MorseSignal::Character MorseSignal::kM[] = { Dash, Dash };
const MorseSignal::Character MorseSignal::kN[] = { Dash, Dot };
const MorseSignal::Character MorseSignal::kO[] = { Dash, Dash, Dash };
const MorseSignal::Character MorseSignal::kP[] = { Dash, Dash, Dash };
const MorseSignal::Character MorseSignal::kQ[] = { Dash, Dash, Dot,  Dash };
const MorseSignal::Character MorseSignal::kR[] = { Dot,  Dash, Dot };
const MorseSignal::Character MorseSignal::kS[] = { Dot,  Dot,  Dot };
const MorseSignal::Character MorseSignal::kT[] = { Dash };
const MorseSignal::Character MorseSignal::kU[] = { Dot,  Dot,  Dash };
const MorseSignal::Character MorseSignal::kV[] = { Dot,  Dot,  Dot,  Dash };
const MorseSignal::Character MorseSignal::kW[] = { Dot,  Dash, Dash };
const MorseSignal::Character MorseSignal::kX[] = { Dash, Dot,  Dot,  Dash };
const MorseSignal::Character MorseSignal::kY[] = { Dash, Dot,  Dash, Dash };
const MorseSignal::Character MorseSignal::kZ[] = { Dash, Dash, Dot, Dot };
const MorseSignal::Character MorseSignal::kD0[] = { Dash, Dash, Dash, Dash, Dash };
const MorseSignal::Character MorseSignal::kD1[] = { Dot,  Dash, Dash, Dash, Dash };
const MorseSignal::Character MorseSignal::kD2[] = { Dot,  Dot,  Dash, Dash, Dash };
const MorseSignal::Character MorseSignal::kD3[] = { Dot,  Dot,  Dot,  Dash, Dash };
const MorseSignal::Character MorseSignal::kD4[] = { Dot,  Dot,  Dot,  Dot,  Dash };
const MorseSignal::Character MorseSignal::kD5[] = { Dot,  Dot,  Dot,  Dot,  Dot };
const MorseSignal::Character MorseSignal::kD6[] = { Dash, Dot,  Dot,  Dot,  Dot };
const MorseSignal::Character MorseSignal::kD7[] = { Dash, Dash, Dot,  Dot,  Dot };
const MorseSignal::Character MorseSignal::kD8[] = { Dash, Dash, Dash, Dot,  Dot };
const MorseSignal::Character MorseSignal::kD9[] = { Dash, Dash, Dash, Dash, Dot };

const QPair<size_t, const MorseSignal::Character *> MorseSignal::kLetterTable[] = {
    { sizeof(kA), &kA[0] },
    { sizeof(kB), kB },
    { sizeof(kC), kC },
    { sizeof(kD), kD },
    { sizeof(kE), kE },
    { sizeof(kF), kF },
    { sizeof(kG), kG },
    { sizeof(kH), kH },
    { sizeof(kI), kI },
    { sizeof(kJ), kJ },
    { sizeof(kK), kK },
    { sizeof(kL), kL },
    { sizeof(kM), kM },
    { sizeof(kN), kN },
    { sizeof(kO), kO },
    { sizeof(kP), kP },
    { sizeof(kQ), kQ },
    { sizeof(kR), kR },
    { sizeof(kS), kS },
    { sizeof(kT), kT },
    { sizeof(kU), kU },
    { sizeof(kV), kV },
    { sizeof(kW), kW },
    { sizeof(kX), kX },
    { sizeof(kY), kY },
    { sizeof(kZ), kZ }
};

const QPair<size_t, const MorseSignal::Character *> MorseSignal::kDigitTable[] = {
    { sizeof(kD0), &kD0[0] },
    { sizeof(kD1), kD1 },
    { sizeof(kD2), kD2 },
    { sizeof(kD3), kD3 },
    { sizeof(kD4), kD4 },
    { sizeof(kD5), kD5 },
    { sizeof(kD6), kD6 },
    { sizeof(kD7), kD7 },
    { sizeof(kD8), kD8 },
    { sizeof(kD9), kD9 }
};

MorseSignal::MorseSignal(const QVector<MorseSignal::Character> &morseChars)
  : m_data { morseChars }
{}

MorseSignal::const_iterator MorseSignal::cbegin() const
{
    return m_data.constBegin();
}

MorseSignal::const_iterator MorseSignal::cend() const
{
    return m_data.constEnd();
}

} // namespace signal
} // namespace pk
