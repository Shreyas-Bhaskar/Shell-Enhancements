#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QObject>
#include <vector>
#include <string>
#include <thread>

class DataModel : public QObject {
    Q_OBJECT

private:
    int cpuUsage;
    int memoryUsage;
    std::vector<std::string> recommendations;
    std::thread monitoringThread;
    bool running;

    void monitorMetrics();

public:
    DataModel();
    ~DataModel();

    Q_PROPERTY(int CpuUsage READ getCpuUsage NOTIFY metricsUpdated)
    Q_PROPERTY(int MemoryUsage READ getMemoryUsage NOTIFY metricsUpdated)
    Q_PROPERTY(std::vector<std::string> Recommendations READ getRecommendations NOTIFY recommendationsUpdated)

    int getCpuUsage() const;
    int getMemoryUsage() const;
    std::vector<std::string> getRecommendations() const;

signals:
    void metricsUpdated();
    void recommendationsUpdated();

    void startMonitoring();
    void stopMonitoring();
};

#endif
