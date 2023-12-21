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
      std::cout << r.workflowName << std::endl;
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

Workflow* solveRule(Part part) {
  for(Rule& rule: part.workflow->rules) {
    uint correctCategory;
    switch (rule.category) {
    case XCool:
      correctCategory = part.XCool;
      break;
    case Shiny:
      correctCategory = part.Shiny;
      break;
    case Aero:
      correctCategory = part.Aero;
      break;
    case Musical:
      correctCategory = part.Musical;
      break;
    }

    switch (rule.direction) {
    case NoDirection:
      return rule.workflow;
    case Smaller:
      if(correctCategory < rule.number)
        return rule.workflow;
      break;
    case Bigger:
      if(correctCategory > rule.number)
        return rule.workflow;
      break;
    }
  }
}

uint solve() {
  uint solution = 0;

  for(std::size_t i = 0; i < parts.size(); i++) {
    Part part = parts.at(i);
    part.workflow = workflows.find("in")->second;
    while(part.workflow->name != "A" && part.workflow->name != "R") {
      part.workflow = solveRule(part);
    }

    if(part.workflow->name == "A") {
      solution += part.Shiny + part.Aero + part.Musical + part.XCool;
    }
  }

  return solution;
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
    uint solution = solve();

    assert(solution == 331208);
    std::cout << solution << std::endl;
}
