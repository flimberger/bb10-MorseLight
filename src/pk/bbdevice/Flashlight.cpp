/*
 * Flashlight.cpp
 *
 *  Created on: 05.11.2014
 *      Author: Florian
 */

#include "Flashlight.hpp"

#include <QtCore/QDebug>

namespace pk
{
namespace bbdevice
{

Flashlight::Flashlight(QObject *parent)
  : QObject { parent },
    m_camHandle { CAMERA_HANDLE_INVALID },
    m_lightOn { false }
{
    auto hasLight = camera_can_feature(m_camHandle, CAMERA_FEATURE_VIDEOLIGHT);

    if (hasLight) {
        auto error = camera_open(CAMERA_UNIT_REAR, CAMERA_MODE_PREAD | CAMERA_MODE_PWRITE,
                                 &m_camHandle);

        if (error != CAMERA_EOK) {
            qDebug("Flashlight error: failed to open camera: %s.", errorStr(error).c_str());
        }
    } else {
        qDebug("Flashlight error: video light not available.");
    }
}

Flashlight::~Flashlight()
{
    if (m_camHandle != CAMERA_HANDLE_INVALID) {
        if (m_lightOn) {
            setEnabled(false);
        }

        auto error = camera_close(m_camHandle);

        if (error != CAMERA_EOK) {
            qDebug("Failed to close camera: %s.", errorStr(error).c_str());
        }
    }
}

bool Flashlight::enabled() const
{
    return m_lightOn;
}

void Flashlight::setEnabled(bool newState)
{
    if (m_camHandle == CAMERA_HANDLE_INVALID) {
        qDebug("Flashlight error: invalid camera handle");
        return;
    }

    auto lightMode = CAMERA_VIDEOLIGHT_OFF;

    if (newState) {
        lightMode = CAMERA_VIDEOLIGHT_ON;
    }

    auto err = camera_config_videolight(m_camHandle, lightMode);

    m_lightOn = !m_lightOn;
    if (err != CAMERA_EOK) {
        auto action = "disabling";

        if (newState) {
            action = "enabling";
        }
        qDebug("Flashlight error: failed to %s flashlight: %s", action, errorStr(err).c_str());
    }
}

std::string Flashlight::errorStr(camera_error_t error)
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

} // namespace bbdevice
} // namespace pk
