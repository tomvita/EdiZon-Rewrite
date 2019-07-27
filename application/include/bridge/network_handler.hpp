#pragma once

#include "edizon.hpp"

#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <errno.h>
#include <stdio.h>

namespace edz::bridge {
    static int socketFileDesc = -1, connectionFileDesc = -1;
    static struct sockaddr_in serverAddr, clientAddr;
    static Thread networkThread;
    static bool networkLoopRunning = false;

    void networkLoop(void *args) {
        while (networkLoopRunning) {
            char buffer[0x100];
            while (networkLoopRunning) {
                std::memset(buffer, 0x00, sizeof(buffer));

                read(socketFileDesc, buffer, sizeof(buffer));
                printf("%s\n", buffer);
                write(socketFileDesc, buffer, sizeof(buffer));

                svcSleepThread(1E6); // Sleep 1ms
            }
        }
    }

    s32 setupBridgeServer() {
        if (socketFileDesc != -1)
            close(socketFileDesc);

        if ((socketFileDesc = socket(AF_INET, SOCK_STREAM, 0)) < 0)
            return -1;

        std::memset(&clientAddr, 0x00, sizeof(clientAddr));
        std::memset(&serverAddr, 0x00, sizeof(serverAddr));

        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(1337);

        bind(socketFileDesc, (const struct sockaddr *)&serverAddr, sizeof(serverAddr));
        listen(socketFileDesc, 50);

        u32 length = sizeof(clientAddr);
        printf("Waiting for connection\n");
        connectionFileDesc = accept(socketFileDesc, (struct sockaddr *)&clientAddr, &length);
        printf("Connection accepted!\n");

        threadCreate(&networkThread, networkLoop, nullptr, 0x5000, 0x2C, -2);
        threadStart(&networkThread);
        networkLoopRunning = true;
        
        return 0;
    }

    void closeBridgeServer() {
        networkLoopRunning = false;

        threadWaitForExit(&networkThread);
        threadClose(&networkThread);
    }

}