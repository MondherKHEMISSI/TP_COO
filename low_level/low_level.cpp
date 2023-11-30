#include<iostream>
#include<string>
#include<cpr/cpr.h>
#include<nlohmann/json.hpp>


using json = nlohmann::json;

class Machine {
	
	public:
	
	Machine(int id, const std::string& name, const std::string& price) : id_(id), name_(name), price_(price) {}
	
	Machine(const json& data) : id_(data["id"]), name_(data["name"]), price_(data["price"]) {}
	
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
	
	
	
	
	protected:
	int id_;
	std::string name_;
	std::string price_;
};


class Departement {
	
	public:
	
	//Departement(int id, const std::string& name, const std::string& zip_code, const std::string& price_m2, const std::string& meteo, double longitude, double latitude) : id_{id}, name_{name}, zip_code_{zip_code}, price_m2_{price_m2}, meteo_{meteo}, longitude_{longitude}, latitude_{latitude} {}
	
	//Departement(const json& data) : id_(data["id"]), name_(data["name"]), zip_code_(data["zip_code"]), price_m2_(data["price_m2"]), meteo_(data["meteo"]), longitude_(data["longitude"]), latitude_(data["latitude"]) {}
	
	Departement(int id) {
		id_ = id;
		std::string url = "http://localhost:8000/departement/" + std::to_string(id_);

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
	
	
	friend std::ostream& operator<<(std::ostream& out, const Departement& departement) {
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
	
	
	
	
	protected:
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
	
	//Ingredient(int id, const std::string& name) : id_(id), name_(name) {}
	
	//Ingredient(const json& data) : id_(data["id"]), name_(data["name"]) {}
	
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
	

	
	
	protected:
	int id_;
	std::string name_;
};


class IngredientQuantity {
	
	public:
	
	//IngredientQuantity(int id, const int ingredient_ID, const std::string& quantity) : id_(id), ingredientId_(ingredient_ID), quantity_(quantity) {}
	
	//IngredientQuantity(const json& data) : id_(data["id"]), ingredientId_(data["ingredient_ID"]), quantity_(data["quantity"]) {}
	
	IngredientQuantity(int id) {
		id_ = id;
		// SPECIFY URL 
		std::string url = "http://localhost:8000/ingredientquantity/" + std::to_string(id_);

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
	
	
	friend std::ostream& operator<<(std::ostream& out, const IngredientQuantity& ingQuantity) {
     	 	ingQuantity.printInfo(out);
     	 	return out;
	  }

	void printInfo(std::ostream& out) const {
		out << "id: " << id_ << "\n";
		//out << "Ingredient ID: " << ingredientId_ << "\n";
		out << "Quantity: " << quantity_ << "\n";
		
	}
	
	
	
	
	protected:
	int id_;
	std::unique_ptr<Ingredient> ingredient_;
	std::string quantity_;
};



class Action {
	
	public:
	
	//Factory(int id, const std::string& name, const std::string& zip_code, const std::string& price_m2, const std::string& meteo, double longitude, double latitude) : id_{id}, name_{name}, zip_code_{zip_code}, price_m2_{price_m2}, meteo_{meteo}, longitude_{longitude}, latitude_{latitude} {}
	
	//Factory(const json& data) : id_(data["id"]), name_(data["name"]), zip_code_(data["zip_code"]), price_m2_(data["price_m2"]), meteo_(data["meteo"]), longitude_(data["longitude"]), latitude_(data["latitude"]) {}
	
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

				for (const auto& item: jsonData["ingredients_Quantity_IDs"]){
		    		ingredientsQuantity_.push_back(std::make_unique<IngredientQuantity>(item));
				}
				
		    	
			} catch (const std::exception& e) {
		    	std::cerr << "Error parsing JSON : " << e.what() << std::endl;
			}
	    	} else {
			std::cerr << "Error during HTTP request : " << r.status_code << std::endl;
		}	}
	
	
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
			  out << "Ingredient Quantity_" << i << " Id: " << ingredientQuantityId << "\n";
			  i++;
		}*/

	}
	
	
	
	protected:
	int id_;
	std::string action_;
	std::string command_;
	std::string duration_;
	std::vector<std::unique_ptr<IngredientQuantity>> ingredientsQuantity_ ;
	std::unique_ptr<Machine> machine_;
	


};



class Recipe {
	
	public:
	
	//Recipe(int id, const std::string& name,  int actionID) : id_(id), name_(name), actionId_(actionID) {}
	
	//Recipe(const json& data) : id_(data["id"]), name_(data["name"]), actionId_(data["action_ID"]) {}
	
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
		//out << "Action ID: " << actionId_ << "\n";
	}

	
	
	
	protected:
	int id_;
	std::string name_;
	std::unique_ptr<Action> action_;
};



class Price {
	
	public:
	
	//Price(int id, const std::string& name,  int actionID) : id_(id), name_(name), actionId_(actionID) {}
	
	//Price(const json& data) : id_(data["id"]), name_(data["name"]), actionId_(data["action_ID"]) {}
	
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
		    	departement_ = std::make_unique<Departement>(jsonData["departement_ID"]);
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
		//out << "Ingredient: " << ingredient_ << "\n";
		//out << "Departement: " << departement_ << "\n";
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
	
	//Factory(int id, const std::string& name, const std::string& zip_code, const std::string& price_m2, const std::string& meteo, double longitude, double latitude) : id_{id}, name_{name}, zip_code_{zip_code}, price_m2_{price_m2}, meteo_{meteo}, longitude_{longitude}, latitude_{latitude} {}
	
	//Factory(const json& data) : id_(data["id"]), name_(data["name"]), zip_code_(data["zip_code"]), price_m2_(data["price_m2"]), meteo_(data["meteo"]), longitude_(data["longitude"]), latitude_(data["latitude"]) {}
	
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
		    	departement_ = std::make_unique<Departement>(jsonData["departement_ID"]);
		    	for (const auto& item: jsonData["machines_IDs"]){
		    		machines_.push_back(std::make_unique<Machine>(item));
				}

				for (const auto& item: jsonData["stocks_IDs"]){
		    		stocks_.push_back(std::make_unique<IngredientQuantity>(item));
				}

				for (const auto& item: jsonData["recipes_IDs"]){
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
		/*out << "Departement ID: " << departementId_ << "\n";
		int i = 1;
		for (const auto &machineId: machinesIds_) {
			  out << "Machine_" << i << " Id: " << machineId << "\n";
			  i++;
		}

		i = 1;
		for (const auto &stockId: stocksIds_) {
			  out << "Stock_" << i << " Id: " << stockId << "\n";
			  i++;
		}

		i = 1;
		for (const auto &recipeId: recipesIds_) {
			  out << "Recipe_" << i << " Id: " << recipeId << "\n";
			  i++;
		}*/

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

	auto IdDepartement = 0;
    std::cout << "Enter an Departement ID :";
    std::cin >> IdDepartement;
    Departement haute_garonne(IdDepartement);
    std::cout << haute_garonne;
	
	
	auto IdMachine = 0;
    std::cout << "Enter an Machine ID :";
    std::cin >> IdMachine;
    Machine etiqueteuse(IdMachine);
    std::cout << etiqueteuse;
    
    auto IdFactory = 0;
    std::cout << "Enter an Factory ID :";
    std::cin >> IdFactory;
    Factory usine(IdFactory);
    std::cout << usine;


	auto IdIngredient = 0;
    std::cout << "Enter an Ingredient ID :";
    std::cin >> IdIngredient;
    Ingredient ing(IdIngredient);
    std::cout << ing;
    
	auto IdIngredientQuantity = 0;
    std::cout << "Enter an Ingredient Quantity ID :";
    std::cin >> IdIngredientQuantity;
    IngredientQuantity ingQuantity(IdIngredientQuantity);
    std::cout << ingQuantity;
    
	auto IdRecipe = 0;
    std::cout << "Enter an Recipe ID :";
    std::cin >> IdRecipe;
    Recipe recipe(IdRecipe);
    std::cout << recipe;

	auto IdAction = 0;
    std::cout << "Enter an Action ID :";
    std::cin >> IdAction;
    Action action(IdAction);
    std::cout << action;

	auto IdPrice = 0;
    std::cout << "Enter a Price ID :";
    std::cin >> IdPrice;
    Price price(IdPrice);
    std::cout << price;

        
	return 0;
}
