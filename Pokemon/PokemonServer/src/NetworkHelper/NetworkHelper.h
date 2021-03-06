﻿#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include <PreCompile.h>
#include "../../protocol/UserProtocol.pb.h"

#define NET_SIG(_name) \
    void sig##_name(QTcpSocket* client, QByteArray data)

class NetworkHelper: public QObject {
    Q_OBJECT
public:
    explicit NetworkHelper(QObject *parent = nullptr);
    virtual ~NetworkHelper();
    
public FUNCTION:
    size_t
        sendToClient(QTcpSocket*, const QString&);
    size_t
        sendToClient(QTcpSocket*, QByteArray&&);
    static int 
        DynamicParseFromPBFile(
            const QString&  filename,
            const QString&  classname,
            std::function<
                void(::google::protobuf::Message* msg)
            > cb
        );
    
public RESOURCE:
    inline static int port = 1919;

signals:
    NET_SIG(GetMessage);
	
private slots:
    void
        slotNewConnection();
    void 
        slotReadClient();
    void
        slotGotDisconnection();
    
private RESOURCE:
    QList<QTcpSocket*>
        m_clients {};
    QTcpServer*
        m_server = nullptr;
};

#endif // SOCKETHELPER_H
