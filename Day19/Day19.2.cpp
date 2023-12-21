#include <cassert>
#include <fstream>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>
#include <map>

enum Category {
  XCool,
  Musical,
  Aero,
  Shiny
};

enum RuleDirection {
  Smaller,
  Bigger,
  NoDirection,
};

struct Workflow;

struct PartLimits {
  unsigned long long XCoolMin;
  unsigned long long XCoolMax;
  unsigned long long MusicalMin;
  unsigned long long MusicalMax;
  unsigned long long AeroMin;
  unsigned long long AeroMax;
  unsigned long long ShinyMin;
  unsigned long long ShinyMax;
};

struct Part {
  uint XCool;
  uint Musical;
  uint Aero;
  uint Shiny;
  Workflow* workflow;
};

struct Rule {
  Category category;
  uint number;
  RuleDirection direction;
  Workflow* workflow;
  std::string workflowName;
};

struct Workflow {
  std::string name;
  std::vector<Rule> rules;
};

std::vector<Workflow> memoryWorkflow;
std::map<std::string,Workflow*> workflows;
std::vector<Part> parts;

std::string getUntilCharWithSplit(std::string& line, char c) {
  if(!line.contains(c))
    return "";
  std::string returnString;
  uint index = line.find(c);
  returnString = line.substr(0, index);
  line.erase(0, index + 1);
  return returnString;
}


void parseWorkflowLine(std::string line, std::size_t index) {
  Workflow* workflow;

  std::string name = getUntilCharWithSplit(line,'{');

  workflow = &(memoryWorkflow.at(index));
  workflow->name = std::move(name);
  workflows.insert(std::make_pair(workflow->name,workflow));

  std::string ruleString = "notEmpty";
  while(!ruleString.empty()) {
    ruleString = getUntilCharWithSplit(line,',');
    if(ruleString.empty())
      break;

    Rule rule{};

    if(ruleString.contains('>')) {
      rule.direction = Bigger;
    } else {
      rule.direction = Smaller;
    }

    switch (ruleString.at(0)) {
    case 'a':
      rule.category = Aero;
      break;
    case 'x':
      rule.category = XCool;
      break;
    case 'm':
      rule.category = Musical;
      break;
    case 's':
      rule.category = Shiny;
      break;
    }

    std::string condition = getUntilCharWithSplit(ruleString,':');
    if(condition.contains('>')) {
      getUntilCharWithSplit(condition,'>');
      rule.direction = Bigger;
    } else {
      getUntilCharWithSplit(condition, '<');
      rule.direction = Smaller;
    }
    rule.number = std::stoul(condition);
    rule.workflowName = std::move (ruleString);
    ruleString = "notEmpty";
    workflow->rules.push_back(rule);
  }

  Rule rule{};
  rule.direction = NoDirection;

  line.erase(line.size() - 1);
  rule.workflowName =  std::move (line);
  workflow->rules.push_back(rule);
}


uint parseWorkflows(std::vector<std::string> input) {
  std::size_t i = 0;

  while(input.at(i++) != "");
  memoryWorkflow.resize(i + 1, Workflow());
  i = 0;

  Workflow accepted("A");
  Workflow rejected("R");
  memoryWorkflow.at(0) = accepted;
  memoryWorkflow.at(1) = rejected;
  workflows.insert(std::make_pair("A",&(memoryWorkflow.at(0))));
  workflows.insert(std::make_pair("R",&(memoryWorkflow.at(1))));

  while(input.at(i) != "") {
    parseWorkflowLine(input.at(i),2 + i);
    i++;
  }

  for(Workflow& w: memoryWorkflow) {
    for(Rule& r: w.rules) {
      r.workflow = workflows.find(r.workflowName)->second;
    }
  }

  return i + 1;
}

void parsePartLine(std::string line) {
  std::stringstream test(line.substr(1,line.size() - 2));
  std::string segment;

  Part part{};
  std::getline(test, segment, ',');
  part.XCool = std::stoul(segment.substr(2));
  std::getline(test, segment, ',');
  part.Musical = std::stoul(segment.substr(2));
  std::getline(test, segment, ',');
  part.Aero = std::stoul(segment.substr(2));
  std::getline(test, segment, ',');
  part.Shiny = std::stoul(segment.substr(2));
  part.workflow = workflows.find("in")->second;
  parts.push_back(part);
}


void parseParts(std::vector<std::string>& input, uint index) {
  for(std::size_t i = index; i < input.size(); i++) {
    std::string line = input.at(i);
    parsePartLine(line);
  }
}

void parse(std::vector<std::string>& input) {
  uint index = parseWorkflows(input);
  parseParts(input, index);
}

unsigned long long solveLimits(PartLimits limits, Workflow* workflow) {
  if(workflow->name == "A")
    return (limits.MusicalMax - limits.MusicalMin + (unsigned long long) 1) * (limits.AeroMax - limits.AeroMin + (unsigned long long) 1) * (limits.ShinyMax - limits.ShinyMin + (unsigned long long) 1) * (limits.XCoolMax - limits.XCoolMin + (unsigned long long) 1);

  if(workflow->name == "R")
    return 0;

  unsigned long long returnValue = 0;


  for(Rule& rule: workflow->rules) {
    PartLimits split1 = limits;
    PartLimits split2 = limits;
    uint correctCategoryMin;
    uint correctCategoryMax;
    Category category = rule.category;
    switch (category) {
    case XCool:
      correctCategoryMin = limits.XCoolMin;
      correctCategoryMax = limits.XCoolMax;
      split1.XCoolMax = rule.number;
      split2.XCoolMin = rule.number;
      break;
    case Shiny:
      correctCategoryMin = limits.ShinyMin;
      correctCategoryMax = limits.ShinyMax;
      split1.ShinyMax = rule.number;
      split2.ShinyMin = rule.number;
      break;
    case Aero:
      correctCategoryMin = limits.AeroMin;
      correctCategoryMax = limits.AeroMax;
      split1.AeroMax = rule.number;
      split2.AeroMin = rule.number;
      break;
    case Musical:
      correctCategoryMin = limits.MusicalMin;
      correctCategoryMax = limits.MusicalMax;
      split1.MusicalMax = rule.number;
      split2.MusicalMin = rule.number;
      break;
    }

    switch (rule.direction) {
    case NoDirection:
      returnValue += solveLimits(limits,rule.workflow);
      break;
    case Smaller:
      if(correctCategoryMax < rule.number)
        returnValue += solveLimits(limits,rule.workflow);
      if(correctCategoryMin > rule.number)
        break;

      switch (category) {
      case Shiny:
        split1.ShinyMax--;
        break;
      case Aero:
        split1.AeroMax--;
        break;
      case Musical:
        split1.MusicalMax--;
        break;
      case XCool:
        split1.XCoolMax--;
        break;
      }
      returnValue += (unsigned long long) solveLimits(split1,rule.workflow);
      limits = split2;
      break;
    case Bigger:
      if(correctCategoryMax < rule.number)
        break;
      if(correctCategoryMin > rule.number)
        returnValue += solveLimits(limits,rule.workflow);


      switch (category) {
      case Shiny:
        split2.ShinyMin++;
        break;
      case Aero:
        split2.AeroMin++;
        break;
      case Musical:
        split2.MusicalMin++;
        break;
      case XCool:
        split2.XCoolMin++;
        break;
      }
      returnValue += (unsigned long long) solveLimits(split2,rule.workflow);
      limits = split1;
      break;
    }
  }
  return returnValue;
}

unsigned long long solve() {
  return solveLimits(PartLimits(1,4000,1,4000,1,4000,1,4000),workflows.find("in")->second);
}



int main() {
  std::string inputName = "../../Day19/Day19.txt";
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

  parse(input);
  unsigned long long solution = solve();

  assert(solution == 121464316215623);
  std::cout << solution << std::endl;
}
