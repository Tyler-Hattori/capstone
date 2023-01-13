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

#include <QPainter>
#include <QFont>
#include "debug.h"
#include <QFile>
#include "renderer.h"
#include "videowidget.h"
#include "interpreter.h"
#include "dataexport.h"
#include "monmodule.h"
#include <chirp.hpp>
#include "calc.h"
#include <math.h>

const uint32_t Renderer::m_defaultPalette[PALETTE_SIZE] =
{
    0x00ff0000, // 1 red
    0x00ff4000, // 2 orange
    0x00ffff00, // 3 yellow
    0x0000ff00, // 4 green
    0x0000ffff, // 5 cyan
    0x000000ff, // 6 blue
    0x00ff00ff  // 7 violet
};

Renderer::Renderer(VideoWidget *video, Interpreter *interpreter) : MonModule(interpreter), m_background(0, 0, QImage::Format_ARGB32)
{
    m_video = video;
    m_interpreter = interpreter;

    m_rawFrame.m_pixels = new uint8_t[RAWFRAME_SIZE];
    m_rawFrame.m_height = 0;
    m_rawFrame.m_width = 0;
    m_highlightOverexp = false;
    m_paletteSet = false;

    m_interpreter->m_pixymonParameters->addCheckbox("Highlight overexposure", false,
        "Highlighting overexposure will overlay black pixels ontop of overexposed pixels in raw and cooked modes");

    connect(this, SIGNAL(image(QImage, uchar, QString)), m_video, SLOT(handleImage(QImage, uchar, QString))); //, Qt::BlockingQueuedConnection);
    connect(this, SIGNAL(flush()), m_video, SLOT(flush()));
}


Renderer::~Renderer()
{
    delete[] m_rawFrame.m_pixels;
}


inline void Renderer::interpolateBayer(unsigned int width, unsigned int x, unsigned int y, unsigned char *pixel, unsigned int &r, unsigned int &g, unsigned int &b)
{
#if 0
    if (y&1)
    {
        if (x&1)
        {
            r = (*(pixel-1)+*(pixel+1))>>1;
            g = *pixel;
            b = (*(pixel-width)+*(pixel+width))>>1;
        }
        else
        {
            r = *pixel;
            g = (*(pixel-1)+*(pixel+1)+*(pixel+width)+*(pixel-width))>>2;
            b = (*(pixel-width-1)+*(pixel-width+1)+*(pixel+width-1)+*(pixel+width+1))>>2;
        }
    }
    else
    {
        if (x&1)
        {
            r = (*(pixel-width-1)+*(pixel-width+1)+*(pixel+width-1)+*(pixel+width+1))>>2;
            g = (*(pixel-1)+*(pixel+1)+*(pixel+width)+*(pixel-width))>>2;
            b = *pixel;
        }
        else
        {
            r = (*(pixel-width)+*(pixel+width))>>1;
            g = *pixel;
            b = (*(pixel-1)+*(pixel+1))>>1;
        }
    }
#endif
#if 1 // normal
    if (y&1)
    {
        if (x&1)
        {
            r = *pixel;
            g = (*(pixel-1)+*(pixel+1)+*(pixel+width)+*(pixel-width))>>2;
            b = (*(pixel-width-1)+*(pixel-width+1)+*(pixel+width-1)+*(pixel+width+1))>>2;
        }
        else
        {
            r = (*(pixel-1)+*(pixel+1))>>1;
            g = *pixel;
            b = (*(pixel-width)+*(pixel+width))>>1;
        }
    }
    else
    {
        if (x&1)
        {
            r = (*(pixel-width)+*(pixel+width))>>1;
            g = *pixel;
            b = (*(pixel-1)+*(pixel+1))>>1;
        }
        else
        {
            r = (*(pixel-width-1)+*(pixel-width+1)+*(pixel+width-1)+*(pixel+width+1))>>2;
            g = (*(pixel-1)+*(pixel+1)+*(pixel+width)+*(pixel-width))>>2;
            b = *pixel;
        }
    }
#endif
#if 0 // green only
    if (y&1)
    {
        if (x&1)
        {
            r = (*(pixel-1)+*(pixel+1))>>1;
            g = (*(pixel-1)+*(pixel+1))>>1;
            b = (*(pixel-1)+*(pixel+1))>>1;
        }
        else
        {
            r = *pixel;
            g = *pixel;
            b = *pixel;
        }
    }
    else
    {
        if (x&1)
        {
            r = *pixel;
            g = *pixel;
            b = *pixel;
        }
        else
        {
            r = (*(pixel-1)+*(pixel+1))>>1;
            g = (*(pixel-1)+*(pixel+1))>>1;
            b = (*(pixel-1)+*(pixel+1))>>1;
        }
    }
#endif
#if 0
    if (y&1)
    {
        if (x&1)
        {
            r = *pixel;
            g = (*(pixel-1)+*(pixel+1))>>1;
            b = (*(pixel-width-1)+*(pixel-width+1))>>1;
        }
        else
        {
            r = (*(pixel-1)+*(pixel+1))>>1;
            g = *pixel;
            b = *(pixel-width);
        }
    }
    else
    {
        if (x&1)
        {
            r = *(pixel+width);
            g = *pixel;
            b = (*(pixel-1)+*(pixel+1))>>1;
        }
        else
        {
            r = (*(pixel+width-1)+*(pixel+width+1))>>1;
            g = (*(pixel-1)+*(pixel+1))>>1;
            b = *pixel;
        }
    }
#endif
#if 0
    if (y&1)
    {
        if (x&1)
        {
            r = *pixel;
            g = (*(pixel-1)+*(pixel+1))>>1;
            b = (*(pixel-width-1)+*(pixel-width+1))>>1;
        }
        else
        {
            r = (*(pixel-1)+*(pixel+1))>>1;
            g = *pixel;
            b = *(pixel-width);
        }
    }
    else
    {
        if (x&1)
        {
            r = *(pixel-width);
            g = *pixel;
            b = (*(pixel-1)+*(pixel+1))>>1;
        }
        else
        {
            r = (*(pixel-width-1)+*(pixel-width+1))>>1;
            g = (*(pixel-1)+*(pixel+1))>>1;
            b = *pixel;
        }
    }
#endif
#if 0
    if (y&1)
    {
        if (x&1)
        {
            r = *pixel;
            g = *(pixel-1);
            b = *(pixel-width-1);
        }
        else
        {
            r = *(pixel-1);
            g = *pixel;
            b = *(pixel-width);
        }
    }
    else
    {
        if (x&1)
        {
            r = *(pixel-width);
            g = *pixel;
            b = *(pixel-1);
        }
        else
        {
            r = *(pixel-width-1);
            g = *(pixel-1);
            b = *pixel;
        }
    }
#endif
}



int Renderer::renderBA81(uint8_t renderFlags, uint16_t width, uint16_t height, uint32_t frameLen, uint8_t *frame)
{
    uint16_t x, xx, y, yy;
    uint32_t *line;
    uint32_t r, g, b;
    uint8_t *frame0;

    if (width*height>RAWFRAME_SIZE)
    {
        m_rawFrame.m_width = 0;
        m_rawFrame.m_height = 0;
    }
    else
    {
        memcpy(m_rawFrame.m_pixels, frame, width*height);
        m_rawFrame.m_width = width;
        m_rawFrame.m_height = height;
    }

    // don't render top and bottom rows, and left and rightmost columns because of color
    // interpolation
    QImage img(width, height, QImage::Format_RGB32);

#ifdef DEBUG_NOISE
    int32_t noise=0, prev=0, bw;
    static float avg = 1.0;
    static uint32_t n = 1;
#endif

    for (y=0; y<height; y++)
    {
        yy = y;
        if (yy==0)
            yy++;
        else if (yy==height-1)
            yy--;
        frame0 = frame + yy*width;
        line = (unsigned int *)img.scanLine(y);
        for (x=0; x<width; x++)
        {
            xx = x;
            if (xx==0)
                xx++;
            else if (xx==width-1)
                xx--;
            interpolateBayer(width, xx, yy, frame0+xx, r, g, b);
            if (m_highlightOverexp && (r>0xf4 || g>0xf4 || b>0xf4))
                *line++ = (0xff<<24); // | 0xff0000;
            else
                *line++ = (0xff<<24) | (r<<16) | (g<<8) | (b<<0);

#ifdef DEBUG_NOISE
            bw = (r+g+b)/3;
            noise += abs(bw - prev);
            prev = bw;
#endif
        }
    }
#ifdef DEBUG_NOISE
    avg = (float)avg*(n-1)/n + (float)noise/n; // n0/1 n0+n1/2 n0+n1+n3/3
    n++;
    qDebug("%d %f", n, avg/1000.0);
#endif
    // send image to ourselves across threads
    // from chirp thread to gui thread
    emit image(img, renderFlags, "Background");

    m_background = img;

    return 0;
}

void Renderer::renderRects(const Points &points, uint32_t size)
{
    int i;
    QPainter p;
    float scale = (float)m_video->activeWidth()/m_background.width();
    QImage img(m_video->activeWidth(), m_video->activeHeight(), QImage::Format_ARGB32);
    img.fill(0x00000000);

    if (!p.begin(&img))
        return;
    p.setBrush(QBrush(QColor(0xff, 0xff, 0xff, 0x20)));
    p.setPen(QPen(QColor(0xff, 0xff, 0xff, 0xff)));

    DBG("*** size %d", points.size());
    for (i=0; i<points.size(); i++)
        p.drawRect(points[i].m_x*scale, points[i].m_y*scale, size*scale, size*scale);

    p.end();

    emit image(img, RENDER_FLAG_BLEND | RENDER_FLAG_FLUSH, "Rectangles");
}

void Renderer::renderRect(const RectA &rect)
{
    QPainter p;
    float scale = (float)m_video->activeWidth()/m_background.width();
    QImage img(m_video->activeWidth(), m_video->activeHeight(), QImage::Format_ARGB32);
    img.fill(0x00000000);

    if (!p.begin(&img))
        return;
    p.setBrush(QBrush(QColor(0xff, 0xff, 0xff, 0x20)));
    p.setPen(QPen(QColor(0xff, 0xff, 0xff, 0xff)));

    p.drawRect(rect.m_xOffset*scale, rect.m_yOffset*scale, rect.m_width*scale, rect.m_height*scale);

    p.end();

    emit image(img, RENDER_FLAG_BLEND | RENDER_FLAG_FLUSH, "Rectangle");
}


void Renderer::renderRL(QImage *image, uint color, uint row, uint startCol, uint len)
{
    uint *line;
    uint col;

    if (row>=(uint)image->height() || startCol>=(uint)image->width() || startCol+len>(uint)image->width())
        return;
    line = (unsigned int *)image->scanLine(row);
    for (col=startCol; col<startCol+len; col++)
        line[col] = color;
}

int Renderer::renderCCQ1(uint8_t renderFlags, uint16_t width, uint16_t height, uint32_t numVals, uint32_t *qVals)
{

    int32_t row;
    uint32_t i, startCol, length;
    uint8_t model;
    QImage img(width, height, QImage::Format_ARGB32);
    uint32_t palette[PALETTE_SIZE+1];

    palette[0] = 0;  // zero signature is transparent -- don't render anything
    for (i=0; i<PALETTE_SIZE; i++)
    {
        if (m_paletteSet)
        {
            if (renderFlags&RENDER_FLAG_BLEND)
                palette[i+1] = saturate(m_palette[i]) | 0x80000000; // lighten the color for contrast
            else
                palette[i+1] = m_palette[i] | 0xff000000;
        }
        else
        {
            if (renderFlags&RENDER_FLAG_BLEND)
                palette[i+1] = m_defaultPalette[i] | 0x80000000;
            else
                palette[i+1] = m_defaultPalette[i] | 0xff000000;
        }
    }

    // q val:
    // | 4 bits    | 7 bits      | 9 bits | 9 bits    | 3 bits |
    // | shift val | shifted sum | length | begin col | model  |

    img.fill(palette[0]);
    for (i=0, row=-1; i<numVals; i++)
    {
        if (qVals[i]==0xffffffff)
            continue;
        if (qVals[i]==0)
        {
            row++;
            continue;
        }
        model = qVals[i]&0x07;
        qVals[i] >>= 3;
        startCol = qVals[i]&0x1ff;
        qVals[i] >>= 9;
        length = qVals[i]&0x1ff;
        renderRL(&img, palette[model], row, startCol, length);
    }

    emit image(img, renderFlags, "Detected pixels");
    return 0;
}


int Renderer::renderBLT1(uint8_t renderFlags, uint16_t width, uint16_t height,
               uint16_t blockWidth, uint16_t blockHeight, uint32_t numPoints, uint16_t *points)
{
    uint i;
    QPainter p;
    float scale = (float)m_video->activeWidth()/width;
    QImage img(m_video->activeWidth(), m_video->activeHeight(), QImage::Format_ARGB32);
    if (renderFlags&RENDER_FLAG_BLEND) // if we're blending, we should be transparent
        img.fill(0x00000000);
    else
        img.fill(0xff000000); // otherwise, we're just black

    if (!p.begin(&img))
        return -1;
    p.setBrush(QBrush(QColor(0xff, 0xff, 0xff, 0x20)));
    p.setPen(QPen(QColor(0xff, 0xff, 0xff, 0xff)));

    for (i=0; i<numPoints; i+=2)
        p.drawRect(points[i]*scale, points[i+1]*scale, blockWidth*scale, blockHeight*scale);

    p.end();

    emit image(img, renderFlags, "Block surface");

    return 0;
}


int Renderer::renderJPEG(uint16_t width, uint16_t height, uint32_t len, uint8_t *jpeg)
{
    qDebug("jpeg %d", len);
    QFile *file = new QFile("out.jpg");
    if (!file->open(QIODevice::WriteOnly))
        return -1;
    QDataStream *stream = new QDataStream(file);

    stream->writeRawData((const char *)jpeg, len);
    file->close();
    return 0;
}

void Renderer::paramChange()
{
    QVariant val;

    if (pixymonParameterChanged("Highlight overexposure", &val))
        m_highlightOverexp = val.toUInt();
}

bool Renderer::render(uint32_t fourcc, const void *args[])
{
    // choose fourcc for representing formats fourcc.org
    if (fourcc==FOURCC('B','A','8','1'))
    {
        renderBA81(*(uint8_t *)args[0], *(uint16_t *)args[1], *(uint16_t *)args[2], *(uint32_t *)args[3], (uint8_t *)args[4]);
        return true;
    }
    else if (fourcc==FOURCC('C','C','Q','1'))
    {
        renderCCQ1(*(uint8_t *)args[0], *(uint16_t *)args[1], *(uint16_t *)args[2], *(uint32_t *)args[3], (uint32_t *)args[4]);
        return true;
    }
    else if (fourcc==FOURCC('B','L','T','1'))
    {
        renderBLT1(*(uint8_t *)args[0], *(uint16_t *)args[1], *(uint16_t *)args[2],
                *(uint16_t *)args[3], *(uint16_t *)args[4], *(uint32_t *)args[5], (uint16_t *)args[6]);
        return true;
    }
    else if (fourcc==FOURCC('J','P','E','G'))
    {
        renderJPEG(*(uint16_t *)args[0], *(uint16_t *)args[1], *(uint32_t *)args[2], (uint8_t *)args[3]);
        return true;
    }
    else // format not recognized
        return false;
}


void Renderer::pixelsOut(int x0, int y0, int width, int height)
{
    uint pixel, *line;
    uint r, g, b;
    int x, y;

    DataExport dx(m_interpreter->m_pixymonParameters->value("Document folder").toString(), "pixels", ET_MATLAB);

    dx.startArray(3, "pixels");

    for (y=0; y<height; y++)
    {
        line = (unsigned int *)m_background.scanLine(y0+y);
        for (x=0; x<width; x++)
        {
            pixel = line[x0+x];
            b = pixel&0xff;
            pixel >>= 8;
            g = pixel&0xff;
            pixel >>= 8;
            r = pixel&0xff;

            dx.addElement(r);
            dx.addElement(g);
            dx.addElement(b);
        }
    }
}



int Renderer::renderBackground(uint8_t renderFlags)
{
    if (m_background.width()!=0)
        emit image(m_background, renderFlags, "Background");

    return 0;
}

int Renderer::saveBackgroundImage(const QString &filename)
{
    return m_background.save(filename);
}


QImage *Renderer::backgroundImage()
{
    return &m_background;
}

Frame8 *Renderer::backgroundRaw()
{
    return &m_rawFrame;
}

void Renderer::setPalette(const uint32_t palette[])
{
    int i;
    for (i=0; i<PALETTE_SIZE; i++)
        m_palette[i] = palette[i];

    m_paletteSet = true;
}

uint32_t *Renderer::getPalette()
{
    if (m_paletteSet)
        return m_palette;
    else
        return NULL;
}

void Renderer::drawLine(QPainter *painter, QColor color, uint x1, uint y1, uint x2, uint y2, uint width, Qt::PenStyle style)
{
    QPen pen(QColor(Qt::black), width);
    pen.setStyle(style);
    painter->setPen(pen);
    painter->drawLine(x1+1, y1+1, x2+1, y2+1);
    painter->drawLine(x1+1, y1-1, x2+1, y2-1);
    painter->drawLine(x1-1, y1+1, x2-1, y2+1);
    painter->drawLine(x1-1, y1-1, x2-1, y2-1);
    pen.setColor(color);
    painter->setPen(pen);
    painter->drawLine(x1, y1, x2, y2);
}

void Renderer::drawText(QPainter *painter, uint x, uint y, const QString &text)
{
#ifdef __MACOS__
    QFont font("verdana", 18);
#else
    QFont font("verdana", 12);
#endif
    painter->setFont(font);

    QRectF rect(x, y, 1, 1);

    painter->setPen(QPen(QColor(Qt::black)));
    painter->drawText(rect.adjusted(0, 0, 2, 2), Qt::AlignCenter | Qt::TextDontClip, text);
    painter->drawText(rect.adjusted(0, 0, 2, -2), Qt::AlignCenter | Qt::TextDontClip, text);
    painter->drawText(rect.adjusted(0, 0, -2, 2), Qt::AlignCenter | Qt::TextDontClip, text);
    painter->drawText(rect.adjusted(0, 0, -2, -2), Qt::AlignCenter | Qt::TextDontClip, text);

    painter->setPen(QPen(QColor(Qt::white)));
    painter->drawText(rect, Qt::AlignCenter | Qt::TextDontClip, text);
}

void Renderer::drawRect(QPainter *painter, const QRect &rect, QColor color, uint alpha)
{
    //DBG("%d %d %d %d", left, right, top, bottom);
    color.setAlpha(alpha);
    painter->setBrush(QBrush(color));

    painter->setPen(QPen(QColor(Qt::black), 1));
    painter->drawLine(rect.left()-1, rect.top()-1, rect.left()-1, rect.bottom()+2);
    painter->drawLine(rect.left()-1, rect.bottom()+2, rect.right()+2, rect.bottom()+2);
    painter->drawLine(rect.right()+2, rect.bottom()+2, rect.right()+2, rect.top()-1);
    painter->drawLine(rect.right()+2, rect.top()-1, rect.left()-1, rect.top()-1);

    painter->setPen(QPen(QColor(Qt::white)));
    painter->drawRect(rect);

}


void Renderer::emitImage(QImage img, uchar renderFlags, QString desc)
{
     emit image(img, renderFlags, desc);
}

void Renderer::emitFlush()
{
    emit flush();
}
