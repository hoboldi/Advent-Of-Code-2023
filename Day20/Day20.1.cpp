#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <map>

enum ModuleType {
  FlipFlop,
  Conjunction,
  Broadcaster,
};

enum PulseType {
  High = 1,
  Low = -1
};

enum State {
  On,
  Off
};

struct Module {
  ModuleType type;
  std::string name;
  std::vector<Module*> destinationModules;
  State state;
  std::map<std::string, PulseType> inputs;
  uint numberOfHighs = 0;
};

struct Pulse {
  Module* src;
  Module* dest;
  PulseType pulse;
};

typedef std::pair<std::string,Module*> ModulePair;


ModulePair parseSrc(std::string& line, std::vector<Module>& memory, uint& nextMemorySlot) {
  ModulePair modulePair;
  modulePair.second = &(memory.at(nextMemorySlot));
  switch (line.at(0)) {
  case '%':
    modulePair.second->type = FlipFlop;
    modulePair.second->state = Off;
    modulePair.second->name = line.substr(1,line.find(' ') - 1);;
    modulePair.first = line.substr(1,line.find(' ') - 1);
    break;
  case '&':
    modulePair.second->type = Conjunction;
    modulePair.second->name = line.substr(1,line.find(' ') - 1);
    modulePair.first = line.substr(1,line.find(' ') - 1);
    break;
  case 'b':
    modulePair.second->type = Broadcaster;
    modulePair.second->name = line.substr(0,line.find(' '));
    modulePair.first = line.substr(0,line.find(' '));
    break;
  }
  line = line.erase(0, line.find(' ') + 4);
  nextMemorySlot++;
  return modulePair;
}

void parseDest(std::string& line, std::vector<Module>& memory, uint index, std::map<std::string, Module*>& modules) {
  Module* module = &(memory.at(index));

  while(line.contains(',')) {
    std::string name = line.substr(0,line.find(','));

    if(!modules.contains(name)) {
      module->destinationModules.push_back(nullptr);
      continue;
    }

    module->destinationModules.push_back(modules.find(name)->second);
    line.erase(0, line.find(',') + 2);

    if(!modules.contains(name))
      continue;

    if(modules.find(name)->second->type == Conjunction) {
      modules.find(name)->second->inputs.insert(std::make_pair(module->name, Low));
    }
  }

  std::string name = line;

  if(!modules.contains(name)) {
    module->destinationModules.push_back(nullptr);
    return;
  }

  module->destinationModules.push_back(modules.find(name)->second);

  if(!modules.contains(name))
    return;

  if(modules.find(name)->second->type == Conjunction) {
    modules.find(name)->second->inputs.insert(std::make_pair(module->name, Low));
  }
}


void parseInput(std::vector<std::string> input, std::map<std::string, Module*>& modules, std::vector<Module>& memory) {
  uint nextMemorySlot = 0;
  memory.resize(input.size());
  for(std::string& line: input) {
    modules.insert(parseSrc(line, memory, nextMemorySlot));
  }

  uint index = 0;
  for(std::string& line: input) {
    parseDest(line, memory, index++, modules);
  }
}

std::vector<Pulse> processPulse(Pulse& pulse, std::map<std::string, Module*>& modules, std::vector<Module>& memory, unsigned long long& lows, unsigned long long& highs) {
  std::vector<Pulse> returnPulses(0);

  if(pulse.pulse == Low)
    lows++;

  if(pulse.pulse == High)
    highs++;

  if(pulse.dest == nullptr)
    return returnPulses;

  Module* newSrc = pulse.dest;
  PulseType type = Low;


  switch (newSrc->type) {
  case FlipFlop:
    if(pulse.pulse == High)
      return returnPulses;
    if(newSrc->state == Off) {
      newSrc->state = On;
      type = High;
    } else {
      newSrc->state = Off;
      type = Low;
    }
    break;
  case Conjunction:
    if(newSrc->inputs.find(pulse.src->name)->second != pulse.pulse) {
      newSrc->numberOfHighs += pulse.pulse;
      newSrc->inputs.find(pulse.src->name)->second = pulse.pulse;
    }
    if(newSrc->numberOfHighs == newSrc->inputs.size()) {
      type = Low;
    } else {
      type = High;
    }
    break;
  default:
    break;
  }

  for(Module* newDest: newSrc->destinationModules) {
    returnPulses.push_back(Pulse(newSrc,newDest, type));
  }

  return returnPulses;
}

unsigned long long solve(std::map<std::string, Module*>& modules, std::vector<Module>& memory, unsigned long long num) {
  unsigned long long highs = 0;
  unsigned long long lows = num;

  for(std::size_t i = 0; i < num; i++) {
    std::queue<Pulse> pulses;
    Module* start = modules.find("broadcaster")->second;

    for(Module* d: start->destinationModules) {
      pulses.push(Pulse(start,d, Low));
    }

    while(!pulses.empty()) {
      Pulse pulse = pulses.front();
      pulses.pop();

      auto toPush = processPulse(pulse, modules, memory, lows, highs);

      for(Pulse p: toPush) {
        pulses.push(p);
      }
    }
  }

  return highs * lows;
}


int main() {
    std::string inputName = "../../Day20/Day20.txt";
    std::ifstream inputFile (inputName);
    if (!inputFile)
        throw std::runtime_error("Could not open file " + std::string(inputName));

    std::vector<std::string> input(0);

    while (true) {
        std::string line;
        getline(inputFile, line);
        input.push_back(line);

        if(inputFile.eof())
            break;
    }
    std::map<std::string, Module*> modules;
    std::vector<Module> memory;
    parseInput(input, modules, memory);
    unsigned long long solution = solve(modules,memory,1000);

    assert(solution == 681194780);
    std::cout << solution << std::endl;
}
