#ifndef MEMORYWIDGET_H
#define MEMORYWIDGET_H

#include "WidgetInterface.h"
#include <atomic>
#include <thread>

class MemoryWidget : public WidgetInterface {
private:
    std::atomic<int> memoryUsage;
    std::thread monitorThread;
    bool running;

    void monitorMemory();

public:
    MemoryWidget();
    ~MemoryWidget();
    void start() override;
    void stop() override;
    int getMetric() const override;
};

#endif
