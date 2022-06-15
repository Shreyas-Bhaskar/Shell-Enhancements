#include "MemoryWidget.h"
#include <windows.h>
#include <iostream>
#include <chrono>
#include <thread>

MemoryWidget::MemoryWidget() : memoryUsage(0), running(false) {}

MemoryWidget::~MemoryWidget() {
    stop();
}

void MemoryWidget::monitorMemory() {
    while (running) {
        MEMORYSTATUSEX memoryStatus;
        memoryStatus.dwLength = sizeof(memoryStatus);

        if (GlobalMemoryStatusEx(&memoryStatus)) {
            DWORDLONG totalMemory = memoryStatus.ullTotalPhys;
            DWORDLONG usedMemory = totalMemory - memoryStatus.ullAvailPhys;

            // Calculate memory usage percentage
            memoryUsage = static_cast<int>((usedMemory * 100) / totalMemory);

            std::cout << "Memory Usage: " << memoryUsage << "%\n";
        } else {
            std::cerr << "Failed to get memory status.\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void MemoryWidget::start() {
    if (running) return;
    running = true;
    monitorThread = std::thread(&MemoryWidget::monitorMemory, this);
}

void MemoryWidget::stop() {
    running = false;
    if (monitorThread.joinable()) {
        monitorThread.join();
    }
}

int MemoryWidget::getMetric() const {
    return memoryUsage.load();
}
