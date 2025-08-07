#include <nlohmann/json.hpp>
#include <IScene.h>
#include <iostream>
#include <fstream> 
#include <EmptyScene.h>
using json = nlohmann::json;
struct SaveData
{
	std::vector<Particle*> particles;
	std::vector<Line*> lines;

	~SaveData() {
		for (auto* p : particles) delete p;
		for (auto* l : lines) delete l;
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
