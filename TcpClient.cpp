/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   TcpClient.cpp
 * Author: phamh
 * 
 * Created on November 6, 2018, 10:07 AM
 */
/*************************************************************************************************/
#include "TcpClient.h"
/*************************************************************************************************/
void *TCPCLIENTTHREAD(void *threadid) {
    TcpClient* p_client = (TcpClient*)threadid;
    int size = 0;
    char *buffer = new char[TCP_CLIENT_LIMIT_DATA];
    while(p_client->isRunning()) {
        int size = read(p_client->getSocket(), buffer, TCP_CLIENT_LIMIT_DATA);
        if(size > 0) {
            p_client->hadData(buffer, size);
        }
        usleep(1);
    }
    pthread_exit(NULL);
}
/*************************************************************************************************/
TcpClient::TcpClient(string host, int port) {
    this->running = false;
    this->m_socket = -1;
    this->m_host = host;
    this->port = port;
}
/*************************************************************************************************/
TcpClient::~TcpClient() {
    if(running) {
        this->running = false;
        sleep(1);
        if(close(this->m_socket)) {
            // non error
        } else {
            // error
        }
    } else {
        // exit;
    }
}
/*************************************************************************************************/
string TcpClient::getHost() {
    return this->m_host;
}
/*************************************************************************************************/
unsigned int TcpClient::getPort() {
    return this->port;
}
/*************************************************************************************************/
int TcpClient::getSocket() {
    return this->m_socket;
}
/*************************************************************************************************/
void TcpClient::setHost(string host) {
    this->m_host = host;
}
/*************************************************************************************************/
void TcpClient::setPort(int port) {
    this->port = port;
}
/*************************************************************************************************/
bool TcpClient::sendData(string data) {
    if(send(this->m_socket, data.c_str(), strlen(data.c_str()), 0) == -1) {
        return false;
    } else {
        return true;
    }
}
/*************************************************************************************************/
bool TcpClient::sendData(void* data, int size) {
    if(send(this->m_socket, data, size, 0) == -1) {
        return false;
    } else {
        return true;
    }
}
/*************************************************************************************************/
bool TcpClient::connectServer() {
    this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if ( this->m_socket <= 0) {
        return false;
    }
    struct hostent *server;
    server = gethostbyname(this->m_host.c_str());
    if (server == NULL) {
        return false;
    }
    struct sockaddr_in server_address;
    memset(&server_address, '0', sizeof(server_address));
    server_address.sin_family = AF_INET; 
    bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);
    server_address.sin_port = htons(this->port); 
    if (connect(this->m_socket,(struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
        return false;
    }
    pthread_t thread;
    this->running = true;
    if(pthread_create(&thread, NULL, TCPCLIENTTHREAD, (void*)(this))) {
        this->running = false;
        return false;
    }
    return true;
}
/*************************************************************************************************/
bool TcpClient::isRunning() {
    return this->running;
}
/*************************************************************************************************/
