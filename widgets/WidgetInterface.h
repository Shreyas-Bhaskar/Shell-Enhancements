#ifndef WIDGETINTERFACE_H
#define WIDGETINTERFACE_H

class WidgetInterface {
public:
    virtual ~WidgetInterface() {}
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual int getMetric() const = 0;
};

#endif
