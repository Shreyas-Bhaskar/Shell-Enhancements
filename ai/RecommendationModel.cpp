#include "RecommendationModel.h"
#include "UserActivityLogSimulator.h"
#include <iostream>
#include <stdexcept>
#include <onnxruntime/core/providers/cpu/cpu_provider_factory.h>

RecommendationModel::RecommendationModel() : env(ORT_LOGGING_LEVEL_WARNING, "RecommendationModel"), session(nullptr) {
    // Load the ONNX model
    try {
        loadModel("ai/model.onnx");
    } catch (const std::exception& e) {
        std::cerr << "Error loading ONNX model: " << e.what() << std::endl;
    }
}

RecommendationModel::~RecommendationModel() {
    delete session;
}

void RecommendationModel::loadModel(const std::string& modelPath) {
    Ort::SessionOptions sessionOptions;
    sessionOptions.SetIntraOpNumThreads(1);
    sessionOptions.SetGraphOptimizationLevel(ORT_ENABLE_EXTENDED);
    sessionOptions.AppendExecutionProvider_CPU(ORT_LOGGING_LEVEL_WARNING);

    session = new Ort::Session(env, modelPath.c_str(), sessionOptions);
}

std::vector<float> RecommendationModel::preprocessUserData(const std::vector<std::string>& activityLogs) {
    // Convert user activity logs to numerical features
    std::vector<float> inputTensor(activityLogs.size());
    for (size_t i = 0; i < activityLogs.size(); ++i) {
        inputTensor[i] = static_cast<float>(activityLogs[i].length() % 10); // Simplified encoding
    }
    return inputTensor;
}

std::vector<std::string> RecommendationModel::postprocessOutput(const std::vector<float>& predictions) {
    // Map predictions to application names
    std::vector<std::string> apps = {"Visual Studio", "Notepad++", "Chrome", "Slack", "Teams"};
    std::vector<std::string> output;

    for (float prediction : predictions) {
        int index = static_cast<int>(prediction) % apps.size();
        output.push_back(apps[index]);
    }

    return output;
}

std::vector<std::string> RecommendationModel::getRecommendations() {
    // Simulate user activity logs
    UserActivityLogSimulator logSimulator;
    auto activityLogs = logSimulator.generateLogs();

    // Preprocess logs
    auto inputTensor = preprocessUserData(activityLogs);

    // Prepare ONNX input
    size_t inputTensorSize = inputTensor.size();
    std::vector<int64_t> inputShape = {1, static_cast<int64_t>(inputTensorSize)};
    Ort::Value input = Ort::Value::CreateTensor<float>(session->GetAllocatorWithDefaultOptions(),
                                                       inputTensor.data(), inputTensorSize, inputShape.data(), inputShape.size());

    // Run ONNX inference
    const char* inputNames[] = {"input"};
    const char* outputNames[] = {"output"};
    auto output = session->Run(Ort::RunOptions{nullptr}, inputNames, &input, 1, outputNames, 1);

    // Postprocess output
    std::vector<float> predictions(output[0].GetTensorMutableData<float>(),
                                    output[0].GetTensorMutableData<float>() + inputTensorSize);
    recommendations = postprocessOutput(predictions);

    return recommendations;
}
