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

#ifndef PK_BBDEVICE_CAMERA_HPP
#define PK_BBDEVICE_CAMERA_HPP

#include <camera/camera_api.h>

#include <QtCore/QObject>

namespace pk
{
namespace bbdevice
{

class Flashlight : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool enabled
               READ enabled
               WRITE setEnabled
               NOTIFY enabledChanged)
public:
    explicit Flashlight(QObject *parent=nullptr);
    ~Flashlight();

    bool enabled() const;
    void setEnabled(bool newState);

Q_SIGNALS:
    void enabledChanged(bool newState);

private:
    std::string errorStr(camera_error_t error);

    camera_handle_t m_camHandle;
    bool m_lightOn;

    Q_DISABLE_COPY(Flashlight)
};

} // namespace bbdevice
} // namespace pk

#endif // PK_BBDEVICE_CAMERA_HPP
