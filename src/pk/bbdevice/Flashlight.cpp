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

#include "Flashlight.hpp"

#include <QtCore/QDebug>

#include <camera/camera_api.h>

#include <string>

namespace pk
{
namespace bbdevice
{

static std::string errorStr(camera_error_t error)
{
    std::string str;

    switch (error) {
    case CAMERA_EOK:
        str = "No error";
        break;
    case CAMERA_EAGAIN:
        str = "Temporary unavailable condition";
        break;
    case CAMERA_EINVAL:
        str = "Invalid argument";
        break;
    case CAMERA_ENODEV:
        str = "Specified camera not found";
        break;
    case CAMERA_EMFILE:
        str = "File table overflow";
        break;
    case CAMERA_EBADF:
        str = "Invalid camera handle";
        break;
    case CAMERA_EACCESS:
        str = "Permission denied";
        break;
    case CAMERA_EBADR:
        str = "Invalid file descriptor";
        break;
    case CAMERA_ENODATA:
        str = "Requested data does not exist";
        break;
    case CAMERA_ENOENT:
        str = "Specified file or directory does not exist";
        break;
    case CAMERA_ENOMEM:
        str = "Memory allocation failed";
        break;
    case CAMERA_EOPNOTSUPP:
        str = "Operation not supported";
        break;
    case CAMERA_ETIMEDOUT:
        str = "Communication timeout";
        break;
    case CAMERA_EALREADY:
        str = "Operation already in progress";
        break;
    case CAMERA_EBUSY:
        str = "Flashlight busy";
        break;
    case CAMERA_ENOSPC:
        str = "Disk full";
        break;
    case CAMERA_EUNINIT:
        str = "Flashlight library not initialized";
        break;
    case CAMERA_EREGFAULT:
        str = "Callback registration failed";
        break;
    case CAMERA_EMICINUSE:
        str = "Microphone already in use";
        break;
    case CAMERA_EDESKTOPCAMERAINUSE:
        str = "Operation not supported for desktop camera";
        break;
    case CAMERA_EPOWERDOWN:
        str = "Camera not powered on";
        break;
    case CAMERA_3ALOCKED:
        str = "lock active";
        break;
    }

    return str;
}

struct FlashlightPrivate
{
    FlashlightPrivate();
    ~FlashlightPrivate();

    camera_handle_t camHandle;
    bool lightOn;
};

FlashlightPrivate::FlashlightPrivate()
  : camHandle { CAMERA_HANDLE_INVALID },
    lightOn { false }
{
    auto error = camera_open(CAMERA_UNIT_REAR, CAMERA_MODE_PREAD | CAMERA_MODE_PWRITE, &camHandle);

     if (error == CAMERA_EOK) {
         auto hasLight = camera_can_feature(camHandle, CAMERA_FEATURE_VIDEOLIGHT);

         if (!hasLight) {
             qDebug("Flashlight error: video light not available.");
             error = camera_close(camHandle);
             if (error != CAMERA_EOK) {
                 qDebug("Flashlight error: failed to close camera: %s.", errorStr(error).c_str());
             }
             camHandle = CAMERA_HANDLE_INVALID;
         }
     } else {
         qDebug("Flashlight error: failed to open camera: %s.", errorStr(error).c_str());
     }
}

FlashlightPrivate::~FlashlightPrivate()
{
    if (camHandle != CAMERA_HANDLE_INVALID) {
        auto error = camera_close(camHandle);

        if (error != CAMERA_EOK) {
            qDebug("Failed to close camera: %s.", errorStr(error).c_str());
        }
    }
}

Flashlight::Flashlight(QObject *parent)
  : QObject { parent },
    d_ptr { new FlashlightPrivate }
{}

Flashlight::~Flashlight()
{
    if (d_func()->lightOn) {
        setEnabled(false);
    }
}

bool Flashlight::enabled() const
{
    return d_func()->lightOn;
}

void Flashlight::setEnabled(bool newState)
{
    Q_D(Flashlight);

    if (d->camHandle == CAMERA_HANDLE_INVALID) {
        qDebug("Flashlight error: invalid camera handle");
        return;
    }

    auto lightMode = CAMERA_VIDEOLIGHT_OFF;

    if (newState) {
        lightMode = CAMERA_VIDEOLIGHT_ON;
    }

    auto err = camera_config_videolight(d->camHandle, lightMode);

    d->lightOn = !d->lightOn;
    if (err != CAMERA_EOK) {
        auto action = "disabling";

        if (newState) {
            action = "enabling";
        }
        qDebug("Flashlight error: failed to %s flashlight: %s", action, errorStr(err).c_str());
    }
}

} // namespace bbdevice
} // namespace pk
