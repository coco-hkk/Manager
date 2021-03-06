#include "networkImageModel.h"
#include "networkImageModel_p.h"
#include <QTimerEvent>

#include <QTextCodec>

#define STOP_TIMER() \
    if(m_timeoutTimerId > 0)\
    {\
        killTimer(m_timeoutTimerId);\
        m_timeoutTimerId = 0;\
    }

ImageModelPrivate::ImageModelPrivate(ImageModel *model)
    : QObject(model), m_model(model), m_nam(this),
      m_reply(0), m_timeoutTimerId(0)
{
    m_roleNames.insert(Qt::UserRole, "imageUrl");
}

ImageModelPrivate::~ImageModelPrivate()
{

}

void ImageModelPrivate::search(const QString & keyword)
{
    qDebug() << "keyword - " << keyword;
    if(m_reply)
    {
        m_reply->disconnect(this);
        m_reply->abort();
        m_reply->deleteLater();
        m_reply = 0;
    }

    STOP_TIMER();

    m_keyword = keyword;
    QString strUrl = QString("https://image.baidu.com/search/index?tn=baiduimage&ipn=r&ct=201326592&cl=2&lm=-1&st=-1&fm=index&fr=&hs=0&xthttps=111110&sf=1&fmq=&pv=&ic=0&nc=1&z=&se=1&showtab=0&fb=0&width=&height=&face=0&istype=2&ie=utf-8&word=%1&oq=%1&rsp=-1").arg(keyword);
    //QString strUrl = QString("http://image.baidu.com/i?tn=resultjsonavstar&ie=utf-8&word=%1&pn=0&rn=60").arg(keyword);
    QUrl qurl(strUrl);
    QNetworkRequest req(qurl);
    m_reply = m_nam.get(req);
    qDebug() << "url - " << qurl;
    //connect(m_reply, SIGNAL(error(QNetworkReply::NetworkError)),
            //this, SLOT(onSearchError(QNetworkReply::NetworkError)));
    connect(m_reply, SIGNAL(finished()), this, SLOT(onSearchFinished()));
    m_timeoutTimerId = startTimer(30000);
}

void ImageModelPrivate::onSearchFinished()
{
    STOP_TIMER()
    m_reply->disconnect(this);
    if(m_reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "ImageModelPrivate::searchFinished, error - " << m_reply->errorString();
        return;
    }
    else if(m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt() != 200)
    {
        qDebug() << "ImageModelPrivate::searchFinished, but server return - " << m_reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        return;
    }
    QByteArray data = m_reply->readAll();
    QString contentType = m_reply->header(QNetworkRequest::ContentTypeHeader).toString();
    qDebug() << "contentType - " << contentType;
    int charsetIndex = contentType.indexOf("charset=");
    if(charsetIndex > 0)
    {
        charsetIndex += 8;
        QString charset = contentType.mid(charsetIndex).trimmed().toLower();
        if(charset.startsWith("gbk") || charset.startsWith("gb2312"))
        {
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            if(codec)
            {
                data = codec->toUnicode(data).toUtf8();
            }
        }
    }
    parseResult(data);
    m_reply->deleteLater();
    m_reply = 0;
}

void ImageModelPrivate::onSearchError(QNetworkReply::NetworkError code)
{
    STOP_TIMER()
    m_reply->disconnect(this);
    m_reply->deleteLater();
    m_reply = 0;
}

void ImageModelPrivate::parseResult(const QByteArray &data)
{
    m_model->beginResetModel();

    m_urls.clear();
    qDebug() << "parseResult";
    int iStart = 0;
    int iEnd = 0;
    while( (iStart = data.indexOf("objURL", iEnd)) > 0)
    {
        iStart += 7;
        iStart = data.indexOf("https://", iStart);
        if(iStart == -1)break;

        iEnd = data.indexOf(',', iStart+7);
        if(iEnd == -1) break;
        QString strUrl = data.mid(iStart, iEnd - iStart);
        if( strUrl.endsWith('\"') || strUrl.endsWith('\'') )
        {
            strUrl.chop(1);
        }
        m_urls.append(strUrl);
    }

    m_model->endResetModel();
    qDebug() << "got " << m_urls.count() << " images";
}

void ImageModelPrivate::timerEvent(QTimerEvent *e)
{
    if(e->timerId() == m_timeoutTimerId)
    {
        onSearchError(QNetworkReply::TimeoutError);
    }
}


ImageModel::ImageModel(QObject *parent)
    : QAbstractListModel(parent)
    , m_dptr(new ImageModelPrivate(this))
{

}

ImageModel::~ImageModel()
{
}

int ImageModel::rowCount(const QModelIndex &parent) const
{
    return m_dptr->m_urls.count();
}

QVariant ImageModel::data(const QModelIndex &index, int role) const
{
    switch(role - Qt::UserRole)
    {
    case 0:
        return m_dptr->m_urls.at(index.row());
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ImageModel::roleNames() const
{
    return m_dptr->m_roleNames;
}

QString ImageModel::keyword() const
{
    return m_dptr->m_keyword;
}

void ImageModel::setKeyword(const QString &keyword)
{
    m_dptr->search(keyword);
}

QString ImageModel::errorString() const
{
    //TODO
    return "";
}

bool ImageModel::hasError() const
{
    //TODO:
    return false;
}

void ImageModel::loadMore()
{
//TODO
}
