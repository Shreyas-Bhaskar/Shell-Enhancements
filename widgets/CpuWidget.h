#ifndef CPUWIDGET_H
#define CPUWIDGET_H

#include "WidgetInterface.h"
#include <atomic>
#include <thread>

class CpuWidget : public WidgetInterface {
private:
    std::atomic<int> cpuUsage;
    std::thread monitorThread;
    bool running;

    void monitorCpu();

public:
    CpuWidget();
    ~CpuWidget();
    void start() override;
    void stop() override;
    int getMetric() const override;
};

#endif
