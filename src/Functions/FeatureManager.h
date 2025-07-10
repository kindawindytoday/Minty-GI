#pragma once
#include "Feature.h"
#include "../Utils/Singleton.h"
#include <string>

class Module 
{
public:
	std::string GetName() { return m_Name; };
	std::vector<Feature*> GetFeatures() { return m_Features; };

	Module(std::string name, std::vector<Feature*> features) : m_Name(name), m_Features(features) {};
	Module(std::string name, Feature* feature) : m_Name(name) { m_Features.push_back(feature); };

private:
	std::string m_Name;
	std::vector<Feature*> m_Features;
};

class FeatureManager : public Singleton<FeatureManager> {
public:
	std::vector<Module> GetModules() { return m_Modules; };
	void AddModule(Module module) { m_Modules.push_back(module); };

private:
	std::vector<Module> m_Modules;
};