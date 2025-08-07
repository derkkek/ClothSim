#include "SaveManager.h"

SaveManager::SaveManager()
{
}

json SaveManager::ToJson(IScene* scene)
{
    json j;
    j["type"] = "EmptyScene";
    // Save particles
    j["particles"] = json::array();
    for (const auto& p : scene->Particles()) {
        json particle;
        particle["position"] = { p->GetPosition().x, p->GetPosition().y, p->GetPosition().z };
        particle["stable"] = p->stable;
        particle["selected"] = p->selected;
        j["particles"].push_back(particle);
    }



    // Save lines (only non-temporary ones)
    j["lines"] = json::array();
    for (const auto& line : scene->Lines()) {
        if (!line->temporary) {
            json lineData;
            // Find indices of particles
            auto p1_it = std::find(scene->Particles().begin(), scene->Particles().end(), line->GetP1());
            auto p2_it = std::find(scene->Particles().begin(), scene->Particles().end(), line->GetP2());

            if (p1_it != scene->Particles().end() && p2_it != scene->Particles().end()) {
                lineData["p1_index"] = std::distance(scene->Particles().begin(), p1_it);
                lineData["p2_index"] = std::distance(scene->Particles().begin(), p2_it);
                lineData["length"] = line->GetLength();
                j["lines"].push_back(lineData);
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
