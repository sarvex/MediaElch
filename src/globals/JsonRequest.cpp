#include "globals/JsonRequest.h"

#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QNetworkRequest>
#include <QObject>
#include <QUrl>

#include "network/NetworkReplyWatcher.h"
#include "network/Request.h"

namespace mediaelch {

JsonPostRequest::JsonPostRequest(QUrl url, QJsonObject body, QObject* parent) : QObject(parent)
{
    QNetworkRequest request = mediaelch::network::requestWithDefaults(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_qnam.post(request, QJsonDocument(body).toJson());
    new NetworkReplyWatcher(this, reply);

    QObject::connect(reply, &QNetworkReply::finished, [reply, this]() {
        QJsonDocument parsedJson;

        if (reply->error() == QNetworkReply::NoError) {
            QJsonParseError parseError{};
            parsedJson = QJsonDocument::fromJson(reply->readAll(), &parseError);

            if (parseError.error != QJsonParseError::NoError) {
                qWarning() << "[JsonPostRequest] Error while parsing JSON";
            }

        } else {
            qWarning() << "[JsonPostRequest] Network Error:" << reply->errorString();
        }

        reply->deleteLater();
        emit sigResponse(parsedJson);
    });
}
} // namespace mediaelch
