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

#include <QtCore/QObject>
#include <QtCore/QScopedPointer>

namespace pk
{
namespace bbdevice
{

class FlashlightPrivate;

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
    QScopedPointer<FlashlightPrivate> d_ptr;

    Q_DECLARE_PRIVATE(Flashlight)
    Q_DISABLE_COPY(Flashlight)
};

} // namespace bbdevice
} // namespace pk

#endif // PK_BBDEVICE_CAMERA_HPP
