#include <cpr/cpr.h>

#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

auto loading() {
  const int totalSteps = 100;

  std::cout << "\t\tProduction in progress...\n";

  for (int i = 0; i <= totalSteps; ++i) {
    // Affichage de la barre de progression
    float progress = static_cast<float>(i) / totalSteps;
    int barWidth = 50;
    int pos = static_cast<int>(barWidth * progress);

    std::cout << "[";
    for (int j = 0; j < barWidth; ++j) {
      if (j < pos)
        std::cout << "=";
      else if (j == pos)
        std::cout << ">";
      else
        std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "%\r";
    std::cout.flush();

    // Simulez un délai pour montrer le chargement (remplacez cela par votre
    // logique réelle)
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
  }

  std::cout << "\n\t\tProduction completed!\n\n";
}

auto update(int id, int value) {
  nlohmann::json jsonData = {
      {"quantity", std::to_string(value)}, {"id", id}
      // ... ajoutez d'autres données au besoin
  };

  // Convertir l'objet JSON en une chaîne de caractères
  std::string jsonString = jsonData.dump();

  // Configuration de la requête POST avec cpr
  std::string url = "http://localhost:8000/ingredientquantity/";
  cpr::Response r = cpr::Post(cpr::Url{url},
                              cpr::Header{{"Content-Type", "application/json"}},
                              cpr::Body{jsonString});

  // Vérification du code de statut de la réponse
  if (r.status_code == 200) {
    std::cout << "Successful request. Response : " << r.text << std::endl;
  } else {
    std::cerr << "Error during HTTP request. status code : " << r.status_code
              << std::endl;
  }
}

class Machine {
 public:
  // Machine(int id, const std::string& name, const std::string& price)
  //   : id_(id), name_(name), price_(price) {}

  // Machine(const json& data)
  //: id_(data["id"]), name_(data["name"]), price_(data["price"]) {}

  Machine(int id) {
    id_ = id;
    // SPECIFY URL
    std::string url = "http://localhost:8000/machine/" + std::to_string(id_);

    // MAKE HTTP GET REQUEST
    cpr::Response r = cpr::Get(cpr::Url{url});

    // CHECK REQUEST RESPONSE
    if (r.status_code == 200) {
      std::cout << " HTTP request successed." << std::endl;

      try {
        // Analyze JSON text contained into response
        json jsonData = json::parse(r.text);

        // GET JSON VALUES
        id_ = jsonData["id"];
        name_ = jsonData["name"];
        price_ = jsonData["price"];

      } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON : " << e.what() << std::endl;
      }
    } else {
      std::cerr << "Error during HTTP request : " << r.status_code << std::endl;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Machine& machine) {
    machine.printInfo(out);
    return out;
  }

  void printInfo(std::ostream& out) const {
    out << "id: " << id_ << "\n";
    out << "name: " << name_ << "\n";
    out << "price: " << price_ << "\n";
  }

 public:
  std::string name_;

 protected:
  int id_;
  std::string price_;
};

class Departement {
 public:
  // Departement(int id, const std::string& name, const std::string& zip_code,
  // const std::string& price_m2, const std::string& meteo, double longitude,
  // double latitude) : id_{id}, name_{name}, zip_code_{zip_code},
  // price_m2_{price_m2}, meteo_{meteo}, longitude_{longitude},
  // latitude_{latitude} {}

  // Departement(const json& data) : id_(data["id"]), name_(data["name"]),
  // zip_code_(data["zip_code"]), price_m2_(data["price_m2"]),
  // meteo_(data["meteo"]), longitude_(data["longitude"]),
  // latitude_(data["latitude"]) {}

  Departement(int id) {
    id_ = id;
    std::string url =
        "http://localhost:8000/departement/" + std::to_string(id_);

    // MAKE HTTP GET REQUEST
    cpr::Response r = cpr::Get(cpr::Url{url});

    // CHECK REQUEST RESPONSE
    if (r.status_code == 200) {
      std::cout << " HTTP request successed." << std::endl;

      try {
        // Analyze JSON text contained into response
        json jsonData = json::parse(r.text);

        // GET JSON VALUES
        id_ = jsonData["id"];
        name_ = jsonData["name"];
        zip_code_ = jsonData["zip_code"];
        price_m2_ = jsonData["price_m2"];
        meteo_ = jsonData["meteo"];
        longitude_ = jsonData["longitude"];
        latitude_ = jsonData["latitude"];

      } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON : " << e.what() << std::endl;
      }
    } else {
      std::cerr << "Error during HTTP request : " << r.status_code << std::endl;
    }
  }

  friend std::ostream& operator<<(std::ostream& out,
                                  const Departement& departement) {
    departement.printInfo(out);
    return out;
  }

  void printInfo(std::ostream& out) const {
    out << "id: " << id_ << "\n";
    out << "name: " << name_ << "\n";
    out << "zip_code: " << zip_code_ << "\n";
    out << "price_m2: " << price_m2_ << "\n";
    out << "meteo: " << meteo_ << "\n";
    out << "longitude: " << longitude_ << "\n";
    out << "latitude: " << latitude_ << "\n";
  }

 public:
  int id_;
  std::string name_;
  std::string zip_code_;
  std::string price_m2_;
  std::string meteo_;
  double longitude_;
  double latitude_;
};

class Ingredient {
 public:
  // Ingredient(int id, const std::string& name) : id_(id), name_(name) {}

  // Ingredient(const json& data) : id_(data["id"]), name_(data["name"]) {}

  Ingredient(int id) {
    id_ = id;
    std::string url = "http://localhost:8000/ingredient/" + std::to_string(id_);

    // MAKE HTTP GET REQUEST
    cpr::Response r = cpr::Get(cpr::Url{url});

    // CHECK REQUEST RESPONSE
    if (r.status_code == 200) {
      std::cout << " HTTP request successed." << std::endl;

      try {
        // Analyze JSON text contained into response
        json jsonData = json::parse(r.text);

        // GET JSON VALUES
        id_ = jsonData["id"];
        name_ = jsonData["name"];

      } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON : " << e.what() << std::endl;
      }
    } else {
      std::cerr << "Error during HTTP request : " << r.status_code << std::endl;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Ingredient& ing) {
    ing.printInfo(out);
    return out;
  }

  void printInfo(std::ostream& out) const {
    out << "id: " << id_ << "\n";
    out << "name: " << name_ << "\n";
  }

 public:
  int id_;
  std::string name_;
};

class IngredientQuantity {
 public:
  // IngredientQuantity(int id, const int ingredient_ID, const std::string&
  // quantity) : id_(id), ingredientId_(ingredient_ID), quantity_(quantity) {}

  // IngredientQuantity(const json& data) : id_(data["id"]),
  // ingredientId_(data["ingredient_ID"]), quantity_(data["quantity"]) {}

  IngredientQuantity(int id) {
    id_ = id;
    // SPECIFY URL
    std::string url =
        "http://localhost:8000/ingredientquantity/" + std::to_string(id_);

    // MAKE HTTP GET REQUEST
    cpr::Response r = cpr::Get(cpr::Url{url});

    // CHECK REQUEST RESPONSE
    if (r.status_code == 200) {
      std::cout << " HTTP request successed." << std::endl;

      try {
        // Analyze JSON text contained into response
        json jsonData = json::parse(r.text);

        // GET JSON VALUES
        id_ = jsonData["id"];
        ingredient_ = std::make_unique<Ingredient>(jsonData["ingredient_ID"]);
        quantity_ = jsonData["quantity"];

      } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON : " << e.what() << std::endl;
      }
    } else {
      std::cerr << "Error during HTTP request : " << r.status_code << std::endl;
    }
  }

  friend std::ostream& operator<<(std::ostream& out,
                                  const IngredientQuantity& ingQuantity) {
    ingQuantity.printInfo(out);
    return out;
  }

  void printInfo(std::ostream& out) const {
    out << "id: " << id_ << "\n";
    // out << "Ingredient ID: " << ingredientId_ << "\n";
    out << "Quantity: " << quantity_ << "\n";
  }

 public:
  int id_;
  std::unique_ptr<Ingredient> ingredient_;
  std::string quantity_;
};

class Action {
 public:
  // Factory(int id, const std::string& name, const std::string& zip_code, const
  // std::string& price_m2, const std::string& meteo, double longitude, double
  // latitude) : id_{id}, name_{name}, zip_code_{zip_code}, price_m2_{price_m2},
  // meteo_{meteo}, longitude_{longitude}, latitude_{latitude} {}

  // Factory(const json& data) : id_(data["id"]), name_(data["name"]),
  // zip_code_(data["zip_code"]), price_m2_(data["price_m2"]),
  // meteo_(data["meteo"]), longitude_(data["longitude"]),
  // latitude_(data["latitude"]) {}

  Action(int id) {
    id_ = id;
    // SPECIFY URL
    std::string url = "http://localhost:8000/action/" + std::to_string(id_);

    // MAKE HTTP GET REQUEST
    cpr::Response r = cpr::Get(cpr::Url{url});

    // CHECK REQUEST RESPONSE
    if (r.status_code == 200) {
      std::cout << " HTTP request successed." << std::endl;

      try {
        // Analyze JSON text contained into response
        json jsonData = json::parse(r.text);

        // GET JSON VALUES
        id_ = jsonData["id"];
        action_ = jsonData["action"];
        command_ = jsonData["command"];
        duration_ = jsonData["duration"];
        machine_ = std::make_unique<Machine>(jsonData["machine_ID"]);

        for (const auto& item : jsonData["ingredients_Quantity_IDs"]) {
          ingredientsQuantity_.push_back(
              std::make_unique<IngredientQuantity>(item));
        }

      } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON : " << e.what() << std::endl;
      }
    } else {
      std::cerr << "Error during HTTP request : " << r.status_code << std::endl;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Action& action) {
    action.printInfo(out);
    return out;
  }

  void printInfo(std::ostream& out) const {
    out << "Id: " << id_ << "\n";
    out << "Action: " << action_ << "\n";
    out << "Command: " << command_ << "\n";
    out << "Duration: " << duration_ << "\n";
    /*out << "Machine ID: " << machineId_ << "\n";
    int i = 1;
    for (const auto &ingredientQuantityId: ingredientsQuantityIds_) {
              out << "Ingredient Quantity_" << i << " Id: " <<
    ingredientQuantityId << "\n"; i++;
    }*/
  }

 public:
  int id_;
  std::string action_;
  std::string command_;
  std::string duration_;
  std::vector<std::unique_ptr<IngredientQuantity>> ingredientsQuantity_;
  std::unique_ptr<Machine> machine_;
};

class Recipe {
 public:
  // Recipe(int id, const std::string& name,  int actionID) : id_(id),
  // name_(name), actionId_(actionID) {}

  // Recipe(const json& data) : id_(data["id"]), name_(data["name"]),
  // actionId_(data["action_ID"]) {}

  Recipe(int id) {
    id_ = id;
    // SPECIFY URL
    std::string url = "http://localhost:8000/recipe/" + std::to_string(id_);

    // MAKE HTTP GET REQUEST
    cpr::Response r = cpr::Get(cpr::Url{url});

    // CHECK REQUEST RESPONSE
    if (r.status_code == 200) {
      std::cout << " HTTP request successed." << std::endl;

      try {
        // Analyze JSON text contained into response
        json jsonData = json::parse(r.text);

        // GET JSON VALUES
        id_ = jsonData["id"];
        name_ = jsonData["name"];
        action_ = std::make_unique<Action>(jsonData["action_ID"]);

      } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON : " << e.what() << std::endl;
      }
    } else {
      std::cerr << "Error during HTTP request : " << r.status_code << std::endl;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Recipe& recipe) {
    recipe.printInfo(out);
    return out;
  }

  void printInfo(std::ostream& out) const {
    out << "Id: " << id_ << "\n";
    out << "Name: " << name_ << "\n";
    // out << "Action ID: " << actionId_ << "\n";
  }

 public:
  int id_;
  std::string name_;
  std::unique_ptr<Action> action_;
};

class Price {
 public:
  // Price(int id, const std::string& name,  int actionID) : id_(id),
  // name_(name), actionId_(actionID) {}

  // Price(const json& data) : id_(data["id"]), name_(data["name"]),
  // actionId_(data["action_ID"]) {}

  Price(int id) {
    id_ = id;
    // SPECIFY URL
    std::string url = "http://localhost:8000/price/" + std::to_string(id_);

    // MAKE HTTP GET REQUEST
    cpr::Response r = cpr::Get(cpr::Url{url});

    // CHECK REQUEST RESPONSE
    if (r.status_code == 200) {
      std::cout << " HTTP request successed." << std::endl;

      try {
        // Analyze JSON text contained into response
        json jsonData = json::parse(r.text);

        // GET JSON VALUES
        id_ = jsonData["id"];
        ingredient_ = std::make_unique<Ingredient>(jsonData["ingredient_ID"]);
        departement_ =
            std::make_unique<Departement>(jsonData["departement_ID"]);
        price_ = jsonData["price"];

      } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON : " << e.what() << std::endl;
      }
    } else {
      std::cerr << "Error during HTTP request : " << r.status_code << std::endl;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Price& price) {
    price.printInfo(out);
    return out;
  }

  void printInfo(std::ostream& out) const {
    out << "Id: " << id_ << "\n";
    // out << "Ingredient: " << ingredient_ << "\n";
    // out << "Departement: " << departement_ << "\n";
    out << "Price: " << price_ << "\n";
  }

 protected:
  int id_;
  std::string price_;
  std::unique_ptr<Departement> departement_;
  std::unique_ptr<Ingredient> ingredient_;
};

class Factory {
 public:
  // Factory(int id, const std::string& name, const std::string& zip_code, const
  // std::string& price_m2, const std::string& meteo, double longitude, double
  // latitude) : id_{id}, name_{name}, zip_code_{zip_code}, price_m2_{price_m2},
  // meteo_{meteo}, longitude_{longitude}, latitude_{latitude} {}

  // Factory(const json& data) : id_(data["id"]), name_(data["name"]),
  // zip_code_(data["zip_code"]), price_m2_(data["price_m2"]),
  // meteo_(data["meteo"]), longitude_(data["longitude"]),
  // latitude_(data["latitude"]) {}

  Factory(int id) {
    id_ = id;
    // SPECIFY URL
    std::string url = "http://localhost:8000/factory/" + std::to_string(id_);

    // MAKE HTTP GET REQUEST
    cpr::Response r = cpr::Get(cpr::Url{url});

    // CHECK REQUEST RESPONSE
    if (r.status_code == 200) {
      std::cout << " HTTP request successed." << std::endl;

      try {
        // Analyze JSON text contained into response
        json jsonData = json::parse(r.text);

        // GET JSON VALUES
        id_ = jsonData["id"];
        name_ = jsonData["name"];
        area_ = jsonData["area"];
        departement_ =
            std::make_unique<Departement>(jsonData["departement_ID"]);
        for (const auto& item : jsonData["machines_IDs"]) {
          machines_.push_back(std::make_unique<Machine>(item));
        }

        for (const auto& item : jsonData["stocks_IDs"]) {
          stocks_.push_back(std::make_unique<IngredientQuantity>(item));
        }

        for (const auto& item : jsonData["recipes_IDs"]) {
          recipes_.push_back(std::make_unique<Recipe>(item));
        }

      } catch (const std::exception& e) {
        std::cerr << "Error parsing JSON : " << e.what() << std::endl;
      }
    } else {
      std::cerr << "Error during HTTP request : " << r.status_code << std::endl;
    }
  }

  friend std::ostream& operator<<(std::ostream& out, const Factory& factory) {
    factory.printInfo(out);
    return out;
  }

  void printInfo(std::ostream& out) const {
    out << "Id: " << id_ << "\n";
    out << "Name: " << name_ << "\n";
    out << "Area: " << area_ << "\n";
    out << "Departement: " << departement_->name_ << "\n";
    int i = 1;
    for (const auto& machine : machines_) {
      out << "Machine_" << i << " : " << machine->name_ << "\n";
      i++;
    }

    i = 1;
    std::cout << "**********************STOCKS***********************"
              << "\n";
    for (const auto& stock : stocks_) {
      out << "Stock_" << i << ": " << stock->ingredient_->name_ << "\n";
      out << "  quantity: " << stock->quantity_ << "\n";

      i++;
    }
    std::cout << "******************************************************"
              << "\n\n\n";

    std::cout << "**************************RECIPES************************"
              << "\n";
    i = 1;
    for (const auto& recipe : recipes_) {
      out << "Recipe_" << i << ": " << recipe->name_ << "\n";
      out << "  Machine: " << recipe->action_->machine_->name_ << "\n";
      int j = 1;
      for (const auto& ingredient : recipe->action_->ingredientsQuantity_) {
        out << "  Ingredient_" << j << ": " << ingredient->ingredient_->name_
            << "\n";
        out << "    quantity: " << ingredient->quantity_ << "\n";
        j++;
      }
      i++;
      std::cout << "----------------------------------------------------"
                << "\n";
    }
    std::cout << "******************************************************"
              << "\n\n\n";
  }

  void chooseUpdate() {
    int i = 1;
    int choice = 0;
    std::cout << "Recipe Choice: "
              << "\n";
    for (const auto& recipe : recipes_) {
      std::cout << "\tChoose (" << i << ") for: " << recipe->name_ << "\n";
      i++;
    }

    std::cin >> choice;
    int j = 1;
    for (const auto& ingredient :
         recipes_[choice - 1]->action_->ingredientsQuantity_) {
      std::cout << "  Ingredient_" << j << ": "
                << ingredient->ingredient_->name_ << "\n";
      std::cout << "    quantity: " << ingredient->quantity_ << "\n";
      j++;
    }

    loading();

    j = 1;
    for (const auto& ingredient :
         recipes_[choice - 1]->action_->ingredientsQuantity_) {
      for (const auto& stock : stocks_) {
        if (ingredient->ingredient_->name_ == stock->ingredient_->name_) {
          int value = stoi(stock->quantity_.substr(0, 4)) -
                      stoi(ingredient->quantity_.substr(0, 1));
          update(stock->id_, value);
          std::cout << "Stock_" << j << ": " << stock->ingredient_->name_
                    << "\n";
          std::cout << "  quantity: " << value << "\n";
          j++;
        }
      }
    }
  }

 protected:
  int id_;
  std::string name_;
  std::string area_;
  std::unique_ptr<Departement> departement_;
  std::vector<std::unique_ptr<Machine>> machines_;
  std::vector<std::unique_ptr<IngredientQuantity>> stocks_;
  std::vector<std::unique_ptr<Recipe>> recipes_;
};

auto main() -> int {
  Factory fac1(4);
  std::cout << fac1;

  fac1.chooseUpdate();

  return 0;
}
