#ifndef VIDEOSTREAM_H
#define VIDEOSTREAM_H

#include <QObject>
#include <QImage>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QDebug>
extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libswscale/swscale.h>
}

class VideoStream : public QThread
{
    Q_OBJECT

public:
    explicit VideoStream(const QString &url, QObject *parent = nullptr);
    void run() override;

signals:
    void frameReady(const QImage &image);

private:
    QString url;
    QImage currentFrame;
    QMutex mutex;
};

#endif // VIDEOSTREAM_H
