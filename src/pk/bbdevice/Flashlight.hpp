/*
 * Camera.hpp
 *
 *  Created on: 05.11.2014
 *      Author: Florian
 */

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