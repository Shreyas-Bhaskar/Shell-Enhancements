# Shell Enhancements: Custom Taskbar Widgets and Intelligent Recommendations

This project is a set of enhancements for the Windows Shell, featuring **real-time system monitoring widgets** and **AI-driven application recommendations**. It allows users to monitor CPU and memory usage directly on the taskbar, receive intelligent recommendations for applications, and customize widget settings via a responsive UI.

---

## Table of Contents
- [Features](#features)
- [Architecture](#architecture)
- [Technologies Used](#technologies-used)
- [Setup Instructions](#setup-instructions)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Future Improvements](#future-improvements)

---

## Features

1. **Real-Time Taskbar Widgets**:
   - Monitor CPU and memory usage with live updates.
   - Data binding ensures the UI remains responsive and real-time.

2. **AI-Driven Recommendations**:
   - Predicts frequently used applications based on user activity logs.
   - Utilizes an ONNX model for efficient AI inference.

3. **Customizable Settings**:
   - Enable or disable individual widgets through a settings tab.

4. **Dynamic and Extensible Architecture**:
   - Designed for scalability, with modular components for UI, widgets, and AI logic.

---

## Architecture

The project is organized into three primary components:
1. **Widgets**:
   - **CPU Widget**: Fetches real-time CPU usage using Windows Performance Data Helper (PDH).
   - **Memory Widget**: Fetches real-time memory usage using the GlobalMemoryStatusEx API.

2. **UI**:
   - Built with XAML and C++ for a responsive and modern Windows interface.
   - Integrates with `DataModel` for data binding and dynamic updates.

3. **AI**:
   - Uses ONNX Runtime for AI inference to recommend applications.
   - Simulates user activity logs and processes them into numerical data for predictions.

### High-Level Architecture Diagram
```plaintext
+------------------+        +-------------------+        +-------------------+
|   Taskbar UI     | <----> |    Data Model     | <----> |      Widgets      |
| (XAML + C++)     |        | (CPU, Memory, AI) |        | (CPU, Memory APIs)|
+------------------+        +-------------------+        +-------------------+
                               ^
                               |
                               v
                    +-------------------+
                    |      AI Model     |
                    | (ONNX Inference)  |
                    +-------------------+
