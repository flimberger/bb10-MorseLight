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

static void append(QVector<MorseSignal::Character> &vector, const MorseSignal::Character *morseChar)
{
    for ( ; *morseChar != MorseSignal::EOS; ++morseChar) {
        vector.append(*morseChar);
    }
    vector.append(MorseSignal::EOS);
}

MorseSignal MorseSignal::fromString(const QString &string)
{
    auto morseChars = QVector<Character> {};
    auto end = string.constEnd();

    for (auto i = string.constBegin(); i != end; ++i) {
        if ('A' <= i->toAscii() && i->toAscii() <= 'Z') {
            auto c = i->toAscii();

            append(morseChars, kLetterTable[c - 'A']);
        } else if ('a' <= i->toAscii() && i->toAscii() <= 'z') {
            auto c = i->toAscii();

            append(morseChars, kLetterTable[c - 'a']);
        } else if ('0' <= i->toAscii() && i->toAscii() <= '9') {
            auto c = i->toAscii();

            append(morseChars, kDigitTable[c - '0']);
        } else if (*i == ' ') {
            Q_ASSERT(morseChars.last() == EOS);
            morseChars.last() = EOW;
        }
    }
    morseChars.last() = EOW;

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
        case EOS:
            string += " ";
            break;
        case EOW:
            string += "   ";
        }
    }

    return string;
}

const QVector<MorseSignal::Character> &MorseSignal::data() const
{
    return m_data;
}

const MorseSignal::Character MorseSignal::kA[] = { Dot,  Dash, EOS };
const MorseSignal::Character MorseSignal::kB[] = { Dash, Dot,  Dot,  Dot,  EOS };
const MorseSignal::Character MorseSignal::kC[] = { Dash, Dot,  Dash, Dot,  EOS };
const MorseSignal::Character MorseSignal::kD[] = { Dash, Dot,  Dot,  EOS };
const MorseSignal::Character MorseSignal::kE[] = { Dot,  EOS };
const MorseSignal::Character MorseSignal::kF[] = { Dot,  Dot,  Dash, Dot,  EOS };
const MorseSignal::Character MorseSignal::kG[] = { Dash, Dash, Dot,  EOS };
const MorseSignal::Character MorseSignal::kH[] = { Dot,  Dot,  Dot,  Dot,  EOS };
const MorseSignal::Character MorseSignal::kI[] = { Dot,  Dot,  EOS };
const MorseSignal::Character MorseSignal::kJ[] = { Dot,  Dash, Dash, Dash, EOS };
const MorseSignal::Character MorseSignal::kK[] = { Dash, Dot,  Dash, EOS };
const MorseSignal::Character MorseSignal::kL[] = { Dot,  Dash, Dot,  EOS };
const MorseSignal::Character MorseSignal::kM[] = { Dash, Dash, EOS };
const MorseSignal::Character MorseSignal::kN[] = { Dash, Dot,  EOS };
const MorseSignal::Character MorseSignal::kO[] = { Dash, Dash, Dash, EOS };
const MorseSignal::Character MorseSignal::kP[] = { Dash, Dash, Dash, EOS };
const MorseSignal::Character MorseSignal::kQ[] = { Dash, Dash, Dot,  Dash, EOS };
const MorseSignal::Character MorseSignal::kR[] = { Dot,  Dash, Dot,  EOS };
const MorseSignal::Character MorseSignal::kS[] = { Dot,  Dot,  Dot,  EOS };
const MorseSignal::Character MorseSignal::kT[] = { Dash, EOS };
const MorseSignal::Character MorseSignal::kU[] = { Dot,  Dot,  Dash, EOS };
const MorseSignal::Character MorseSignal::kV[] = { Dot,  Dot,  Dot,  Dash, EOS };
const MorseSignal::Character MorseSignal::kW[] = { Dot,  Dash, Dash, EOS };
const MorseSignal::Character MorseSignal::kX[] = { Dash, Dot,  Dot,  Dash, EOS };
const MorseSignal::Character MorseSignal::kY[] = { Dash, Dot,  Dash, Dash, EOS };
const MorseSignal::Character MorseSignal::kZ[] = { Dash, Dash, Dot,  Dot,  EOS };
const MorseSignal::Character MorseSignal::kD0[] = { Dash, Dash, Dash, Dash, Dash, EOS };
const MorseSignal::Character MorseSignal::kD1[] = { Dot,  Dash, Dash, Dash, Dash, EOS };
const MorseSignal::Character MorseSignal::kD2[] = { Dot,  Dot,  Dash, Dash, Dash, EOS };
const MorseSignal::Character MorseSignal::kD3[] = { Dot,  Dot,  Dot,  Dash, Dash, EOS };
const MorseSignal::Character MorseSignal::kD4[] = { Dot,  Dot,  Dot,  Dot,  Dash, EOS };
const MorseSignal::Character MorseSignal::kD5[] = { Dot,  Dot,  Dot,  Dot,  Dot,  EOS };
const MorseSignal::Character MorseSignal::kD6[] = { Dash, Dot,  Dot,  Dot,  Dot,  EOS };
const MorseSignal::Character MorseSignal::kD7[] = { Dash, Dash, Dot,  Dot,  Dot,  EOS };
const MorseSignal::Character MorseSignal::kD8[] = { Dash, Dash, Dash, Dot,  Dot,  EOS };
const MorseSignal::Character MorseSignal::kD9[] = { Dash, Dash, Dash, Dash, Dot,  EOS };

const MorseSignal::Character *MorseSignal::kLetterTable[] = {
    kA,
    kB,
    kC,
    kD,
    kE,
    kF,
    kG,
    kH,
    kI,
    kJ,
    kK,
    kL,
    kM,
    kN,
    kO,
    kP,
    kQ,
    kR,
    kS,
    kT,
    kU,
    kV,
    kW,
    kX,
    kY,
    kZ
};

const MorseSignal::Character *MorseSignal::kDigitTable[] = {
    kD0,
    kD1,
    kD2,
    kD3,
    kD4,
    kD5,
    kD6,
    kD7,
    kD8,
    kD9
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
