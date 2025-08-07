#include "SaveManager.h"

SaveManager::SaveManager()
{
}

json SaveManager::ToJson(IScene* scene)
{
    json j;
    j["type"] = "EmptyScene";

    // Get particles and lines
    auto particles = scene->Particles();
    auto lines = scene->Lines();

    // Create a map from particle pointer to index for reliable lookup
    std::unordered_map<Particle*, int> particleToIndex;
    for (int i = 0; i < particles.size(); ++i) {
        particleToIndex[particles[i]] = i;
    }

    // Save particles
    j["particles"] = json::array();
    for (const auto& p : particles) {
        json particle;
        particle["position"] = { p->GetPosition().x, p->GetPosition().y, p->GetPosition().z };
        particle["stable"] = p->stable;
        particle["selected"] = p->selected;
        j["particles"].push_back(particle);
    }

    // Save lines (only non-temporary ones)
    j["lines"] = json::array();
    for (const auto& line : lines) {
        if (!line->temporary) {
            json lineData;

            // Use the map to find indices
            auto p1_iter = particleToIndex.find(line->GetP1());
            auto p2_iter = particleToIndex.find(line->GetP2());

            if (p1_iter != particleToIndex.end() && p2_iter != particleToIndex.end()) {
                lineData["p1_index"] = p1_iter->second;
                lineData["p2_index"] = p2_iter->second;
                lineData["length"] = line->GetLength();
                j["lines"].push_back(lineData);
            }
            else {
                // Debug output to help identify the issue
                std::cout << "Warning: Could not find particle index for line. ";
                std::cout << "P1: " << line->GetP1() << ", P2: " << line->GetP2() << std::endl;
            }
        }
    }

    return j;
}

SaveData SaveManager::FromJson(const json& j)
{
    SaveData data{};

    // Load particles
    if (j.contains("particles")) {
        for (const auto& particleData : j["particles"]) {
            sf::Vector3f pos(
                particleData["position"][0],
                particleData["position"][1],
                particleData["position"][2]
            );
            bool stable = particleData["stable"];

            auto particle = std::make_unique<Particle>(pos, stable);
            if (particleData.contains("selected")) {
                particle->selected = particleData["selected"];
            }
            data.particles.push_back(std::move(particle));
        }
    }

    // Load lines
    if (j.contains("lines")) {
        for (const auto& lineData : j["lines"]) {
            int p1_index = lineData["p1_index"];
            int p2_index = lineData["p2_index"];
            float length = lineData["length"];

            if (p1_index < data.particles.size() && p2_index < data.particles.size()) {
                auto line = std::make_unique<Line>(
                    data.particles[p1_index].get(),
                    data.particles[p2_index].get(),
                    length
                );
                data.lines.push_back(std::move(line));
            }
        }
    }

    return data;
}

void SaveManager::SaveToFile(IScene* scene, const std::string& filename)
{
    try {
        // Extract directory path from filename
        std::filesystem::path filePath(filename);
        std::filesystem::path directory = filePath.parent_path();

        // Create directory if it doesn't exist
        if (!directory.empty() && !std::filesystem::exists(directory)) {
            std::filesystem::create_directories(directory);
            std::cout << "Created directory: " << directory << std::endl;
        }

        json j = ToJson(scene);
        std::ofstream file(filename);
        if (file.is_open()) {
            file << j.dump(4); // Pretty print with 4 spaces
            std::cout << "Scene saved to: " << filename << std::endl;
        }
        else {
            std::cerr << "Could not open file for writing: " << filename << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error saving scene: " << e.what() << std::endl;
    }
}

SaveData SaveManager::LoadFromFile(const std::string& filename)
{
    SaveData data{};
    try {
        std::ifstream file(filename);
        if (file.is_open()) {
            json j;
            file >> j;
            data = FromJson(j);
            std::cout << "Scene loaded from: " << filename << std::endl;
        }
        else {
            std::cerr << "Could not open file for reading: " << filename << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error loading scene: " << e.what() << std::endl;
    }
    return data;
}
