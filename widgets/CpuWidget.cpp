#include "CpuWidget.h"
#include <windows.h>
#include <pdh.h>
#include <iostream>
#include <chrono>
#include <thread>

#pragma comment(lib, "pdh.lib")

CpuWidget::CpuWidget() : cpuUsage(0), running(false) {}

CpuWidget::~CpuWidget() {
    stop();
}

void CpuWidget::monitorCpu() {
    PDH_HQUERY cpuQuery;
    PDH_HCOUNTER cpuTotal;

    if (PdhOpenQuery(NULL, NULL, &cpuQuery) != ERROR_SUCCESS) {
        std::cerr << "Failed to open PDH query for CPU usage.\n";
        return;
    }

    if (PdhAddCounter(cpuQuery, L"\\Processor(_Total)\\% Processor Time", NULL, &cpuTotal) != ERROR_SUCCESS) {
        std::cerr << "Failed to add counter for CPU usage.\n";
        PdhCloseQuery(cpuQuery);
        return;
    }

    PdhCollectQueryData(cpuQuery); // Collect initial data

    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Wait for the next sample

        if (PdhCollectQueryData(cpuQuery) == ERROR_SUCCESS) {
            PDH_FMT_COUNTERVALUE counterValue;
            if (PdhGetFormattedCounterValue(cpuTotal, PDH_FMT_LONG, NULL, &counterValue) == ERROR_SUCCESS) {
                cpuUsage = counterValue.longValue;
                std::cout << "CPU Usage: " << cpuUsage << "%\n";
            } else {
                std::cerr << "Failed to get formatted counter value for CPU usage.\n";
            }
        } else {
            std::cerr << "Failed to collect PDH query data for CPU usage.\n";
        }
    }

    PdhCloseQuery(cpuQuery); // Clean up PDH resources
}

void CpuWidget::start() {
    if (running) return;
    running = true;
    monitorThread = std::thread(&CpuWidget::monitorCpu, this);
}

void CpuWidget::stop() {
    running = false;
    if (monitorThread.joinable()) {
        monitorThread.join();
    }
}

int CpuWidget::getMetric() const {
    return cpuUsage.load();
}
