/*
 SmartClient, a Smartapps client for Arduino

@author         Fabio Costa Mangia <fabio.costa@smartapps.com.br>
@contribution   Prof. Rodrigo M A Almeida <rodrigomax@unifei.edu.br>

 Smartapps (http://www.smartapps.com.br) - Copyright 2013


 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#ifndef SMARTCLIENT_H
#define SMARTCLIENT_H_
#include <string.h>

//comment this to use Ethernet Client
//#define WIFI


#ifdef WIFI
#include <WiFi.h>
#endif
#ifndef WIFI
#include <Ethernet.h>
#endif

//#include <Base64.h>
#include "Arduino.h"

#define DEBUGPRINT //Debug Mode

#define NEW

class SmartClient {

    public:
        //typedef void (*DataArrivedDelegate)(SmartClient client, String data);
        bool connect(char hostname[], char login[] = "", char pass[] = "", int port = 80);
        bool connected();
        void disconnect();

        //void setDataArrivedDelegate(DataArrivedDelegate dataArrivedDelegate);
        void send(bool GoP, char hostname[], char app[], char schema[], char caminho[], String data = "");

        String readResponse();

    private:
        //Variaveis Locais: maximo no teste foi 70
        char AuthID[70];
        char PHPSESSID[33];
        String LOGIN;

        String buff; //utilizado pra ler as linhas

        #ifdef NEW
        char readBuffer[750]; //nao tem linha tao
        int posBuffer;
        #endif

        //Funcoes Locais:
        String getStringTableItem(int index);
        void encrypt(char login[], char pass[]);
        void sendHandshake(char hostname[], char AuthID[]);

        #ifdef WIFI
        WiFiClient _client;
        #endif
        #ifndef WIFI
        EthernetClient _client;
        #endif

        //DataArrivedDelegate _dataArrivedDelegate;
        bool readHandshake();
        void readLine();

};


#endif

