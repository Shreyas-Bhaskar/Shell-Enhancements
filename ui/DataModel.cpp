#include "DataModel.h"
#include "../widgets/CpuWidget.h"
#include "../widgets/MemoryWidget.h"
#include "../ai/RecommendationModel.h"

DataModel::DataModel() : cpuUsage(0), memoryUsage(0), running(false) {}

DataModel::~DataModel() {
    stopMonitoring();
}

void DataModel::monitorMetrics() {
    CpuWidget cpuWidget;
    MemoryWidget memoryWidget;
    RecommendationModel recommender;

    cpuWidget.start();
    memoryWidget.start();
    recommendations = recommender.getRecommendations();

    while (running) {
        // Update system metrics
        cpuUsage = cpuWidget.getMetric();
        memoryUsage = memoryWidget.getMetric();

        emit metricsUpdated();
        emit recommendationsUpdated();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    cpuWidget.stop();
    memoryWidget.stop();
}

void DataModel::startMonitoring() {
    if (running) return;
    running = true;
    monitoringThread = std::thread(&DataModel::monitorMetrics, this);
}

void DataModel::stopMonitoring() {
    running = false;
    if (monitorThread.joinable()) {
        monitoringThread.join();
    }
}

int DataModel::getCpuUsage() const {
    return cpuUsage;
}

int DataModel::getMemoryUsage() const {
    return memoryUsage;
}

std::vector<std::string> DataModel::getRecommendations() const {
    return recommendations;
}
