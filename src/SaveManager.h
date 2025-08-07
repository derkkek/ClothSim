#include <nlohmann/json.hpp>
#include <IScene.h>
#include <iostream>
#include <fstream> 
#include <EmptyScene.h>
using json = nlohmann::json;
struct SaveData
{
    std::vector<std::unique_ptr<Particle>> particles;
    std::vector<std::unique_ptr<Line>> lines;

    // Transfer ALL ownership at once to avoid dangling references
    std::pair<std::vector<Particle*>, std::vector<Line*>> transferOwnership() {
        std::vector<Particle*> rawParticles;
        std::vector<Line*> rawLines;

        // Transfer particles first
        for (auto& p : particles) {
            rawParticles.push_back(p.release());
        }
        particles.clear();

        // Transfer lines second
        for (auto& l : lines) {
            rawLines.push_back(l.release());
        }
        lines.clear();

        return { rawParticles, rawLines };
    }
};

#pragma once
class SaveManager
{

public:
	SaveManager();
	~SaveManager()=default;

	json ToJson(IScene* scene);
	SaveData FromJson(const json& j);
	void SaveToFile(IScene* scene, const std::string& filename);
	SaveData LoadFromFile(const std::string& filename);
private:

};
