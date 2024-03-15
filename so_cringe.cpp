#include <iostream>
#include <fstream>
#include <string>
#include <jsoncpp/json/json.h>

class MainMenu {
 protected:
  int width;
  int height;
  std::string mod;

 public:
  MainMenu(int w, int h, const std::string& m) : width(w), height(h), mod(m) {
  }

  virtual void start() = 0;
  virtual void exit() {
  }
};

class StoriesMenu : public MainMenu {
 public:
  StoriesMenu(int w, int h, const std::string& m) : MainMenu(w, h, m) {
  }

  void start() override {
  }
};

class Display {
 public:
  virtual void finish() = 0;
  virtual void start() = 0;
  virtual void show() = 0;
};

class Button {
 private:
  int width;
  int height;
  int x;
  int y;
  std::string color;
  std::string text;

 public:
  Button(int w, int h, int pos_x, int pos_y, const std::string& col, const std::string& txt)
      : width(w), height(h), x(pos_x), y(pos_y), color(col), text(txt) {
  }

  bool clicked(int mouse_x, int mouse_y) const {
    // проверка положения мышки(???)
    return (mouse_x >= x && mouse_x <= x + width && mouse_y >= y && mouse_y <= y + height);
  }

  void draw() const {
  }
};

class DisplayGraphics : public Interface {
 public:
  DisplayGraphics(int w, int h, const std::string& col) : Interface(w, h, col) {
  }

  void showMenu() const {

    // кнопочки

    draw();
  }

  void showStoriesMenu() const {

    // кнопочки

    draw();
  }
};

class Interface {
 protected:
  int width;
  int height;
  std::string color;
  std::vector<Button> buttons;

 public:
  Interface(int w, int h, const std::string& col) : width(w), height(h), color(col) {
  }

  virtual void draw() const {
    for (const auto& button : buttons) {
      button.draw();
    }
  }
};

class State {
 private:
  int reputation;
  int diplomacy;
  int strength;

 public:
  State(int rep, int dip, int str) : reputation(rep), diplomacy(dip), strength(str) {
  }

  int getReputation() const {
    return reputation;
  }

  void setReputation(int rep) {
    reputation = rep;
  }

  int getDiplomacy() const {
    return diplomacy;
  }

  void setDiplomacy(int dip) {
    diplomacy = dip;
  }

  int getStrength() const {
    return strength;
  }

  void setStrength(int str) {
    strength = str;
  }
};

class Inventory {
 private:
  int diamonds;

 public:
  Inventory() : diamonds(0) {
  }

  int getDiamonds() const {
    return diamonds;
  }

  void setDiamonds(int value) {
    diamonds = value;
  }
};

class PlotCreator {
 private:
  State currentState;
  Inventory playerInventory;

 public:
  PlotCreator(const std::string& fileName) : fileName(fileName) {
  }

  void choosePlotBranch() {
    json jsonData = parseJsonFile(fileName);
    // обработка граничных стат для той или иной ветки и выбор ветки
  }
};

class Answers {
 public:
  json parseJsonFile(const std::string& fileName) {
    currentFileBeingProcessed = fileName;

    std::ifstream stream(fileName);
    json jsonData = json::parse(stream);

    return jsonData;
  }

  std::string getLastReadFileName() {
    return currentFileBeingProcessed;
  }

  static bool getBoolean(json object, const std::string& fieldName) {

    bool value = false;
    try {
      value = object[fieldName].get<bool>();
    } catch (json::exception& e) {
      handleError(e, fieldName);
    }

    return value;
  }

  static int getInteger(json object, const std::string& fieldName) {

    int value = false;
    try {
      value = object[fieldName].get<int>();
    } catch (json::exception& e) {
      handleError(e, fieldName);
    }

    return value;
  }

  static double getDouble(json object, const std::string& fieldName) {

    double value = false;
    try {
      value = object[fieldName].get<double>();
    } catch (json::exception& e) {
      handleError(e, fieldName);
    }

    return value;
  }

  static std::string getString(json object, const std::string& fieldName) {
    std::string value;
    try {
      value = object[fieldName].get<std::string>();
    } catch (json::exception& e) {
      handleError(e, fieldName);
    }

    return value;
  }

 private:
  std::string currentFileBeingProcessed;
  std::string currentFieldBeingProcessed;
};
