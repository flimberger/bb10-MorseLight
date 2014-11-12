/*
 * Copyright (c) 2011-2014 BlackBerry Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ApplicationUI_HPP_
#define ApplicationUI_HPP_

#include "pk/signal/MorseSignal.hpp"

#include <QObject>

class MorseSender;

namespace pk
{
namespace bbdevice
{

class Flashlight;

} // namespace bbdevice
} // namespace pk

namespace bb
{
namespace cascades
{

class LocaleHandler;

} // namespace cascades
} // namespace bb

class QThread;
class QTranslator;

/*!
 * @brief Application UI object
 *
 * Use this object to create and init app UI, to create context objects, to register the new meta types etc.
 */
class ApplicationUI : public QObject
{
    Q_OBJECT
public:
    ApplicationUI();
    virtual ~ApplicationUI();

    Q_INVOKABLE void toggleLight();
    Q_INVOKABLE void send(const QString &message);

Q_SIGNALS:
    void sendMessage(pk::signal::MorseSignal);

private slots:
    void onSystemLanguageChanged();
    void onSendingDone();

private:
    QTranslator* m_pTranslator;
    bb::cascades::LocaleHandler* m_pLocaleHandler;

    pk::bbdevice::Flashlight *m_light;
    MorseSender *m_sender;
    QThread *m_sendingThread;
};

#endif /* ApplicationUI_HPP_ */
