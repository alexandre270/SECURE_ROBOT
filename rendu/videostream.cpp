#include "videostream.h"

VideoStream::VideoStream(const QString &url, QObject *parent)
    : QThread(parent), url(url)
{
    // En fonction de la version de FFmpeg, av_register_all() peut ne pas être nécessaire
    // av_register_all(); // Commenté pour les versions récentes de FFmpeg
}

void VideoStream::run()
{
    AVFormatContext *formatContext = avformat_alloc_context();
    if (avformat_open_input(&formatContext, url.toStdString().c_str(), nullptr, nullptr) < 0) {
        qDebug() << "Erreur lors de l'ouverture du flux";
        return;
    }

    const AVCodec *codec = nullptr; // Changement ici pour le type const
    AVCodecContext *codecContext = nullptr;
    AVPacket packet;
    AVFrame *frame = av_frame_alloc();
    AVFrame *rgbFrame = av_frame_alloc();

    // Trouver le premier flux vidéo
    avformat_find_stream_info(formatContext, nullptr);
    int videoStreamIndex = -1;
    for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
        if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStreamIndex = i;
            codec = avcodec_find_decoder(formatContext->streams[i]->codecpar->codec_id);
            break;
        }
    }

    if (videoStreamIndex == -1) {
        qDebug() << "Aucun flux vidéo trouvé";
        return;
    }

    codecContext = avcodec_alloc_context3(codec);
    avcodec_parameters_to_context(codecContext, formatContext->streams[videoStreamIndex]->codecpar);
    avcodec_open2(codecContext, codec, nullptr);

    // Boucle de lecture
    while (av_read_frame(formatContext, &packet) >= 0) {
        if (packet.stream_index == videoStreamIndex) {
            avcodec_send_packet(codecContext, &packet);
            if (avcodec_receive_frame(codecContext, frame) == 0) {
                // Convertir le frame en QImage
                int width = frame->width;
                int height = frame->height;

                // Convertir le frame en RGB
                SwsContext *swsCtx = sws_getContext(width, height, codecContext->pix_fmt,
                                                    width, height, AV_PIX_FMT_RGB24,
                                                    SWS_BILINEAR, nullptr, nullptr, nullptr);
                sws_scale(swsCtx, frame->data, frame->linesize, 0, height, rgbFrame->data, rgbFrame->linesize);
                sws_freeContext(swsCtx);

                // Créer un QImage à partir des données RGB
                QImage image(rgbFrame->data[0], width, height, QImage::Format_RGB888);
                emit frameReady(image.copy()); // Émettre le signal avec une copie de l'image
            }
        }
        av_packet_unref(&packet);
    }

    av_frame_free(&frame);
    av_frame_free(&rgbFrame);
    avcodec_free_context(&codecContext);
    avformat_close_input(&formatContext);
}
