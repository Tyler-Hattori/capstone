//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//

#ifndef FLASH_H
#define FLASH_H

#include <QString>
#include "usblink.h"
#include <chirp.hpp>

class Flash
{
public:
    Flash();
    ~Flash();

    void program(const QString &filename);
    static void checkHardwareVersion(const uint16_t hardwareVersion[], const QString &filename,  ushort firmwareVersion[]=NULL, QString *firmwareType=NULL);

private:

    char *m_buf;
    USBLink m_link;
    Chirp m_chirp;
    uint32_t m_sectorSize;
    ChirpProc m_programProc;
    ChirpProc m_reset;
    ChirpProc m_getHardwareVersion;
    uint16_t m_hardwareVersion[3];
};

#endif // FLASH_H
