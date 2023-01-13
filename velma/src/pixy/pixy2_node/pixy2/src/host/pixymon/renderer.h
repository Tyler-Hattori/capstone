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

#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include <QImage>
#include <QMutex>
#include <QColor>
#include "pixytypes.h"
#include "monmodule.h"
//#include "processblobs.h"

#include <simplevector.h>
typedef SimpleVector<Point16> Points;

#define RAWFRAME_SIZE    0x12000
#define PALETTE_SIZE     7
#define TEXT_HEIGHT      12
class Interpreter;

class VideoWidget;

class Renderer : public QObject, public MonModule
{
    Q_OBJECT

public:
    Renderer(VideoWidget *video, Interpreter *interpreter);
    ~Renderer();

    // MonModule
    virtual bool render(uint32_t fourcc, const void *args[]);
    virtual void paramChange();

    int renderBackground(uint8_t renderFlags);
    QImage *backgroundImage(); // get background from BA81 formatted image data
    Frame8 *backgroundRaw();

    int renderCCQ1(uint8_t renderFlags, uint16_t width, uint16_t height, uint32_t numVals, uint32_t *qVals);
    int renderBA81(uint8_t renderFlags, uint16_t width, uint16_t height, uint32_t frameLen, uint8_t *frame);
    int renderBLT1(uint8_t renderFlags, uint16_t width, uint16_t height,
                   uint16_t blockWidth, uint16_t blockHeight, uint32_t numPoints, uint16_t *points);
    int renderJPEG(uint16_t width, uint16_t height, uint32_t len, uint8_t *jpeg);


    void renderRects(const Points &points, uint32_t size);
    void renderRect(const RectA &rect);
    int saveBackgroundImage(const QString &filename);
    void pixelsOut(int x0, int y0, int width, int height);
    void renderRL(QImage *image, uint color, uint row, uint startCol, uint len);
    void setPalette(const uint32_t palette[]);
    uint32_t *getPalette();

    void emitImage(QImage img, uchar renderFlags, QString desc="");
    void emitFlush();

    static void drawLine(QPainter *painter, QColor color, uint x1, uint y1, uint x2, uint y2, uint width=3, Qt::PenStyle style=Qt::SolidLine);
    static void drawText(QPainter *painter, uint x, uint y, const QString &text);
    static void drawRect(QPainter *painter, const QRect &rect, QColor color=QColor(Qt::black), uint alpha=0);

    Frame8 m_rawFrame;
    VideoWidget *m_video;

signals:
    void image(QImage image, uchar renderFlags, QString desc="");
    void flush();

private:
    inline void interpolateBayer(unsigned int width, unsigned int x, unsigned int y, unsigned char *pixel, unsigned int &r, unsigned int &g, unsigned int &b);

    Interpreter *m_interpreter;
    QImage m_background;
    bool m_paletteSet;
    uint32_t m_palette[PALETTE_SIZE];
    static const unsigned int m_defaultPalette[PALETTE_SIZE];

    bool m_highlightOverexp;
};

#endif // RENDERER_H

