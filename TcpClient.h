/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TcpClient.h
 * Author: phamh
 *
 * Created on November 6, 2018, 10:07 AM
 */
/*************************************************************************************************/
#ifndef TCPCLIENT_H
#define TCPCLIENT_H
/*************************************************************************************************/
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cstring>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
/*************************************************************************************************/
using namespace std;
/*************************************************************************************************/
#ifndef TCP_CLIENT_LIMIT_DATA
#define TCP_CLIENT_LIMIT_DATA 64*1024
#endif
/*************************************************************************************************/
class TcpClient {
public:
    TcpClient(string host, int port);
    virtual ~TcpClient();
    /*************************************************************************************************/
    string getHost();
    unsigned int getPort();
    int getSocket();
    /*********************************************************************************************/
    void setHost(string);
    void setPort(int);
    /*********************************************************************************************/
    bool sendData(string);
    bool sendData(void*, int);
    /*********************************************************************************************/
    virtual void hadData(void*, int) = 0;
    /*********************************************************************************************/
    bool connectServer();
    /*********************************************************************************************/
    bool isRunning();
    /*********************************************************************************************/
private:
    string m_host;
    unsigned int port;
    int m_socket;
    bool running;
};
/*************************************************************************************************/
#endif /* TCPCLIENT_H */
/*************************************************************************************************/
