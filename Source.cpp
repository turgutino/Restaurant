#include<iostream>
#include <cstdlib>
#include<queue>
#include <thread>
#include <chrono>
#include <list>
#include <map>
#include<fstream>
#include<string>
#include <sstream>

using namespace std;

class User {
    static int next_ID2;
    int ID2;
    string username;
    string password;
    double budget;
public:
    User() {
        username = "";
        password = "";
        budget = 100;
    }

    User(string username, string password, double budget) : User() {
        ID2 = ++next_ID2;
        Set_Username(username);
        Set_Password(password);
        Set_Budget(budget);
    }



    int Get_ID2() {
        return ID2;
    }



    string Get_Username() {
        return username;
    }

    string Get_Password() {
        return password;
    }

    void Set_Username(string username) {
        while (username.length() < 8) {
            cerr << "\033[31mError: Username must be at least 8 characters long.\033[0m" << endl;
            cout << "Enter a valid username: ";
            cin >> username;
        }
        this->username = username;
    }

    void Set_Budget(double budget) {
        this->budget = budget;
    }

    double Get_Budget() {
        return budget;
    }



    void Set_Password(string password) {
        this->password = password;
    }

    void Show() {
        int count = 0;
        cout << "ID : " << Get_ID2() << endl;
        cout << "Username : " << Get_Username() << endl;
        cout << "Password : " << Get_Password() << endl;
        cout << "Budget : " << Get_Budget() << endl << endl;
    }






};







class Ingridient {
    string name;
    double quantity;
    double price;
    static int next_ID;
    int ID;
public:
    Ingridient() {
        name = "";
        quantity = 0;
        price = 0;
    }

    Ingridient(string name, double quantity, double price) {
        ID = ++next_ID;
        Set_Name(name);
        Set_Quantity(quantity);
        Set_Price(price);
    }

    int Get_ID() {
        return ID;
    }

    string Get_Name() {
        return name;
    }

    double Get_Quantity() {
        return quantity;
    }

    double Get_Price() {
        return price;
    }

    void Set_Name(string name) {
        this->name = name;
    }

    void Set_Quantity(double quantity) {
        this->quantity = quantity;

    }

    void Set_Price(double price) {
        this->price = price;
    }

    static void Set_Next_ID(int new_next_id) { next_ID = new_next_id; }

    void decrease_quantity(int count) {
        if (quantity >= count) {
            quantity -= count;
        }
        else {
            cout << "Not enough stock for ingredient " << name << endl;
        }
    }

    void Show2() {

        cout << "\033[36mID: \033[0m" << Get_ID() << "   |   "

            << "\033[35mName: \033[0m" << Get_Name() << "   |   "

            << "\033[33mQuantity: \033[0m" << Get_Quantity() << "   |   "

            << "\033[32mPrice: \033[0m" << Get_Price() << endl << endl;
    }


};

int Ingridient::next_ID = 0;




class Stock :public Ingridient {
    list<Ingridient*> ingridients;

public:

   

    Stock(const string& filename = "stock_data.txt") {
        ReadFromFile2(filename);
    }


    void WriteToFile2(const string& filename = "stock_data.txt") {
        ofstream outFile(filename, ios::out | ios::trunc);
        if (!outFile) {
            cout << "Error: Could not open file for writing." << endl;
            return;
        }

        outFile << Get_ID() << endl;

        for (const auto& ing : ingridients) {
            outFile << ing->Get_ID() << " "
                << ing->Get_Name() << " "
                << ing->Get_Quantity() << " "
                << ing->Get_Price() << endl;
        }

        outFile.close();

    }


    void ReadFromFile2(const string& filename) {
        ifstream inFile(filename, ios::in);
        if (!inFile) {
            cout << "Error: Could not open file for reading." << endl;
            return;
        }


        for (auto& ing : ingridients) {
            delete ing;
        }
        ingridients.clear();


        int next_id;
        inFile >> next_id;
        Ingridient::Set_Next_ID(next_id);

        int id;
        string name;
        double quantity, price;

        while (inFile >> id >> name >> quantity >> price) {
            Ingridient* newIngredient = new Ingridient(name, quantity, price);
            ingridients.push_back(newIngredient);
        }

        inFile.close();

    }



    void Push_Ingrients(string name, double quantity, double price) {
        ingridients.push_back(new Ingridient(name, quantity, price));
    }

    double Add_Ingrient() {


        cout << "\033[34m" << "                                                  Available Ingridients" << "\033[0m" << endl << endl;


        for (const auto& ing : ingridients) {
            cout << "ID: " << "\033[36m" << ing->Get_ID() << "\033[0m" << ", Name: " << ing->Get_Name() << endl;
        }
        cout << endl;

        string name;
        double quantity, price;


        cout << "Enter name: ";
        cin >> name;


        cout << "Enter quantity: ";
        while (true) {
            if (cin >> quantity) {
                break;
            }
            else {

                cout << "\033[31mInvalid input. Please enter a valid numeric value for quantity.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter quantity: ";
            }
        }


        cout << "Enter price: ";
        while (true) {
            if (cin >> price) {
                break;
            }
            else {

                cout << "\033[31mInvalid input. Please enter a valid numeric value for price.\033[0m" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Enter price: ";
            }
        }


        Push_Ingrients(name, quantity, price);




        WriteToFile2();


        return price * quantity;
    }





    void Show_All() {
        if (ingridients.empty()) {
            cout << "\033[31m" << "                                           There are no ingredients in the database." << "\033[0m" << endl << endl;
            return;
        }
        for (auto ing : ingridients) {
            ing->Show2();
        }
    }

    void Delete_Ingridient() {

        if (ingridients.empty()) {
            cout << "\033[31m" << "                                           No ingridients available to delete." << "\033[0m" << endl << endl;
            return;
        }

        cout << "\033[34m" << "                                                  Available Ingridients" << "\033[0m" << endl << endl;

        for (const auto& ing : ingridients) {
            cout << "ID: " << "\033[36m" << ing->Get_ID() << "\033[0m" << ", Name: " << ing->Get_Name() << endl;
        }
        cout << endl;

        int Id;
        bool validInput = false;


        while (!validInput) {
            cout << "\nEnter the ID of the ingridient you want to delete: ";
            cin >> Id;


            if (cin.fail()) {

                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\033[31m                                        Invalid input. Please enter a valid numeric ID.\033[0m\n";
            }
            else {
                validInput = true;
            }
        }

        bool found = false;

        for (auto it = ingridients.begin(); it != ingridients.end(); ++it) {
            if ((*it)->Get_ID() == Id) {
                delete* it;
                ingridients.erase(it);
                found = true;
                cout << "\033[32m" << "                                      Ingridient with ID " << Id << " was successfully deleted." << "\033[0m" << endl;
                WriteToFile2();
                break;
            }
        }

        if (!found) {
            cout << "\033[31m" << "                                              No ingridient found with ID " << Id << "." << "\033[0m" << endl << endl;
        }
    }




    void Update_Ingridient() {
        bool check = false;

        while (!check) {
            cout << "\033[34m" << "                                                  Available Ingridients" << "\033[0m" << endl << endl;

            for (const auto& ing : ingridients) {
                cout << "ID: " << "\033[36m" << ing->Get_ID() << "\033[0m" << ", Name: " << ing->Get_Name() << endl;
            }
            cout << endl;

            int Id;
            cout << "Enter ID: ";
            cin >> Id;

      
            if (cin.fail()) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\033[31mInvalid ID input. Please enter a valid numeric ID.\033[0m" << endl;
                this_thread::sleep_for(chrono::milliseconds(500));
                system("cls");
                continue;  

            }

            bool found = false;
            for (auto ing : ingridients) {
                if (ing->Get_ID() == Id) {
                    found = true;

                
                    system("cls");
                    cout << "Current details of the Ingridient with ID " << Id << ":" << "\033[0m" << " - > ";
                    cout << "\033[1m\033[31mID: \033[0m" << ing->Get_ID() << "   |   "

                        << "\033[35mName: \033[0m" << ing->Get_Name() << "   |   "

                        << "\033[33mQuantity: \033[0m" << ing->Get_Quantity() << "   |   "

                        << "\033[32mPrice: \033[0m" << ing->Get_Price() << endl << endl;

                    cout << "\033[36m" << " Choose which field to update :" << "\033[0m" << endl << endl;
                    cout << "1. Name" << endl;
                    cout << "2. Quantity" << endl;
                    cout << "3. Price" << endl;
                    cout << "4. Cancel" << endl << endl;  

                    int choice;
                    cout << "\033[36m" << "Enter your choice (1/2/3/4) : " << "\033[0m";
                    cin >> choice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\033[31mInvalid choice. Please enter 1, 2, 3, or 4.\033[0m" << endl;
                        continue;  
                    }

                    string name;
                    double quantity, price;

                    switch (choice) {
                    case 1: 
                        system("cls");
                        cout << "Current details of the Ingridient with ID " << Id << ":" << "\033[0m" << " - > ";
                        cout << "\033[1m\033[31mID: \033[0m" << ing->Get_ID() << "   |   "

                            << "\033[35mName: \033[0m" << ing->Get_Name() << "   |   "

                            << "\033[33mQuantity: \033[0m" << ing->Get_Quantity() << "   |   "

                            << "\033[32mPrice: \033[0m" << ing->Get_Price() << endl << endl;
                        cout << "\033[36m" << "Enter new name : " << "\033[0m";
                        cin.ignore(); 
                        cin >> name;
                        ing->Set_Name(name);
                        break;
                    case 2:  
                        system("cls");
                        cout << "Current details of the Ingridient with ID " << Id << ":" << "\033[0m" << " - > ";
                        cout << "\033[1m\033[31mID: \033[0m" << ing->Get_ID() << "   |   "

                            << "\033[35mName: \033[0m" << ing->Get_Name() << "   |   "

                            << "\033[33mQuantity: \033[0m" << ing->Get_Quantity() << "   |   "

                            << "\033[32mPrice: \033[0m" << ing->Get_Price() << endl << endl;
                        cout << "\033[36m" << "Enter new quantity : " << "\033[0m";
                        cin >> quantity;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "\033[31mInvalid quantity input. Please enter a valid number.\033[0m" << endl;
                            continue;  
                        }
                        ing->Set_Quantity(quantity);
                        break;
                    case 3:  
                        system("cls");
                        cout << "Current details of the Ingridient with ID " << Id << ":" << "\033[0m" << " - > ";
                        cout << "\033[1m\033[31mID: \033[0m" << ing->Get_ID() << "   |   "

                            << "\033[35mName: \033[0m" << ing->Get_Name() << "   |   "

                            << "\033[33mQuantity: \033[0m" << ing->Get_Quantity() << "   |   "

                            << "\033[32mPrice: \033[0m" << ing->Get_Price() << endl << endl;
                        cout << "\033[36m" << "Enter new price: "<< "\033[0m";
                        cin >> price;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "\033[31mInvalid price input. Please enter a valid number.\033[0m" << endl;
                            continue;  
                        }
                        ing->Set_Price(price);
                        break;
                    case 4:  
                        cout << "\033[33m                                            Update process has been cancelled.\033[0m" << endl << endl;
                        return;  
                    default:
                        cout << "\033[31mInvalid choice. Please enter 1, 2, 3, or 4.\033[0m" << endl;
                        continue;  
                    }

                    cout << "\033[32m" << "                                         Update was successfully completed." << "\033[0m" << endl << endl;
                    WriteToFile2(); 
                    check = true; 
                    break;
                }
            }

            if (!found) {
                cout << "\033[31m" << "                                                       ID not found" << "\033[0m" << endl << endl;
                break;
            }
        }
    }




    bool Remove_Ingredients(const list<pair<Ingridient*, int>>& meal_ingredients) {

        for (const auto& pair : meal_ingredients) {
            Ingridient* ingredient = pair.first;
            int required_amount = pair.second;

            bool found = false;


            for (auto& ing : ingridients) {
                if (ing->Get_Name() == ingredient->Get_Name()) {
                    found = true;
                    if (ing->Get_Quantity() < required_amount) {
                        cout << "\033[31mInsufficient stock for ingredient: " << ingredient->Get_Name() << "\033[0m\n";
                        return false;
                    }
                }
            }

            if (!found) {
                cout << "\033[31mIngredient not found: " << ingredient->Get_Name() << "\033[0m\n";
                return false;
            }
        }


        for (const auto& pair : meal_ingredients) {
            Ingridient* ingredient = pair.first;
            int required_amount = pair.second;

            for (auto& ing : ingridients) {
                if (ing->Get_Name() == ingredient->Get_Name()) {
                    ing->Set_Quantity(ing->Get_Quantity() - required_amount);
                }
            }
        }

        return true;
    }



    list<Ingridient*>& Get_Ingrients() {
        return ingridients;
    };



};



class Meal {
    static int next_ID3;
    int ID3;
    string meal_name;
    double meal_price;
    string information;
    list<pair<Ingridient*, int>> ingredients;
public:
    Meal() {
        meal_name = "";
        meal_price = 0;
        information = "";
    }

    Meal(string meal_name, double meal_price, string information) :Meal() {
        ID3 = ++next_ID3;
        Set_Mealname(meal_name);
        Set_Mealprice(meal_price);
        Set_Information(information);
    }

    const list<pair<Ingridient*, int>>& Get_Ingredients() const {
        return ingredients;
    }

    void Set_Ingredients(const list<pair<Ingridient*, int>>& ing) {
        ingredients = ing;
    }

    int Get_ID3() {
        return ID3;
    }

    string Get_Mealname() {
        return meal_name;
    }

    double Get_Mealprice() {
        return meal_price;
    }

    string Get_Information() {
        return information;
    }

    void Set_Mealname(string meal_name) {
        this->meal_name = meal_name;
    }


    void Set_Mealprice(double meal_price) {
        this->meal_price = meal_price;
    }

    void Set_Information(string information) {
        this->information = information;
    }

   
    static void Set_Next_ID3(int new_next_id3) { next_ID3 = new_next_id3; }

    void Add_Ingredient(Ingridient* ingr, int quantity) {
        ingredients.push_back({ ingr, quantity });
    }


    void Show_Ingredients() const {
        cout << "\033[1m\033[34mIngredients:\033[0m" << endl;
        for (auto& ingr_pair : ingredients) {
            cout << "  \033[1m\033[36m- " << ingr_pair.first->Get_Name() << "\033[0m"
                << " \033[1m\033[33m(Quantity: \033[0m"
                << "\033[32m" << ingr_pair.second << "\033[0m"
                << "\033[1m\033[33m)\033[0m" << endl;
        }
    }


    void Show_Admin() {
        cout << "\033[1m\033[34mID: \033[0m" << "\033[36m" << Get_ID3() << "\033[0m"
            << "  \033[1m\033[34mMeal: \033[0m" << "\033[32m" << Get_Mealname() << "\033[0m"
            << "  \033[1m\033[34mPrice: \033[0m" << "\033[33m$" << Get_Mealprice() << "\033[0m"
            << "  \033[1m\033[34mInformation: \033[0m" << "\033[35m" << Get_Information() << "\033[0m"
            << endl;
    }


};

int Meal::next_ID3 = 0;


class Menu :public Stock, public Meal {
    list<Meal*> meals;
    list<Ingridient*> ingrident;



public:
    
    Menu() {
        ReadFromFile3();
    }

    void WriteToFile3(const string& filename = "menu_data.txt") {
        ofstream file(filename, ios::out | ios::trunc);
        if (!file) {
            cout << "Error: Could not open file for writing." << endl;
            return;
        }

        file << Meal::Get_ID3() << endl;

        for (const auto& meal : meals) {
            file << meal->Get_ID3() << endl;
            file << meal->Get_Mealname() << endl;
            file << meal->Get_Mealprice() << endl;
            file << meal->Get_Information() << endl;

            const std::list<std::pair<Ingridient*, int>>& ingredients = meal->Get_Ingredients();
            file << ingredients.size() << endl;

            for (const auto& ingredient_pair : ingredients) {
                Ingridient* ingredient = ingredient_pair.first;
                int count = ingredient_pair.second;
                file << ingredient->Get_ID() << " " << count << endl;
            }
        }

        file.close();
    }

    void ReadFromFile3() {
        ifstream file("menu_data.txt", ios::in);
        if (!file.is_open()) {
            cout << "Error: Unable to open file for reading." << endl;
            return;
        }

        meals.clear();

        int next_id;
        file >> next_id;
        Meal::Set_Next_ID3(next_id);

        while (true) {
            int meal_id;
            string meal_name;
            double meal_price;
            string meal_info;


            file >> meal_id;
            if (file.eof()) break;
            file.ignore();


            getline(file, meal_name);
            if (meal_name.empty()) getline(file, meal_name);


            file >> meal_price;
            file.ignore();


            getline(file, meal_info);
            if (meal_info.empty()) getline(file, meal_info);


            Meal* newMeal = new Meal(meal_name, meal_price, meal_info);

            int ingredient_count;
            file >> ingredient_count;


            for (int i = 0; i < ingredient_count; i++) {
                int ingredient_id, ingredient_quantity;
                file >> ingredient_id >> ingredient_quantity;


                bool found = false;
                for (auto ingr : Get_Ingrients()) {
                    if (ingr->Get_ID() == ingredient_id) {
                        newMeal->Add_Ingredient(ingr, ingredient_quantity);
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    cout << "Warning: Ingredient with ID " << ingredient_id << " not found in ingrident list." << endl;
                }
            }

            meals.push_back(newMeal);
        }

        file.close();

    }


    list<Meal*>& Get_Meals() {
        return meals;
    };


    void Push_Meal(string meal_name, double meal_price, string information) {
        meals.push_back(new Meal(meal_name, meal_price, information));

    }

    void Add_Meal(list<Stock*>& stock) {
        cout << "\033[34m" << "                                                  Available Ingridients" << "\033[0m" << endl << endl;

        for (const auto& ing : Get_Ingrients()) {
            cout << "ID: " << "\033[36m" << ing->Get_ID() << "\033[0m" << ", Name: " << ing->Get_Name() << endl;
        }
        cout << endl;

        string meal_name;
        double meal_price;
        string information;

        cout << "Meal name: ";
        cin >> meal_name;

        cout << "Meal price: ";
        while (!(cin >> meal_price)) { 
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[31mInvalid input. Please enter a valid number for the price:\033[0m ";
        }

        cout << "Meal Information: ";
        cin.ignore(); 
        cin >> information; 

        Meal* newMeal = new Meal(meal_name, meal_price, information);
        meals.push_back(newMeal);

        bool t = false;
        while (!t) {
            int Id;
            cout << "Enter Ingredient ID (or 0 to finish): ";
            while (!(cin >> Id)) { 
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\033[31mInvalid input. Please enter a valid numeric ID:\033[0m ";
            }

            if (Id == 0) {
                t = true;
            }
            else {
                bool found = false;
                int count;
                for (auto stk : stock) {
                    for (auto ingr : stk->Get_Ingrients()) {
                        if (ingr->Get_ID() == Id) {
                            cout << "Enter quantity for this ingredient: ";
                            while (!(cin >> count)) { 
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "\033[31mInvalid input. Please enter a valid quantity:\033[0m ";
                            }

                            if (count <= ingr->Get_Quantity()) {
                                newMeal->Add_Ingredient(ingr, count);
                                ingr->decrease_quantity(count);
                                found = true;
                                cout << "\033[32m" << "                                              Ingredient added to the meal!" << "\033[0m" << endl;
                                stk->WriteToFile2();
                                WriteToFile3();
                            }
                            else {
                                cout << "Not enough quantity in stock for ingredient " << ingr->Get_Name() << endl;
                            }
                            break;
                        }
                    }
                    if (found) break;
                }
                if (!found) {
                    cout << endl;
                    cout << "\033[31m                                         Ingredient with ID " << Id << " not found in stock.\033[0m" << endl;
                }
            }
        }
        cout <<"\033[32m" << "                                                   Meal added successfully!" << "\033[0m" << endl<<endl;
    }


    void Remove_Meal() {
        cout << endl;
        if (meals.empty()) {
            cout << "\033[31m"
                << "                                            Menu is empty. No meals to remove."
                << "\033[0m" << endl;
            return;
        }

        cout << "Current meals in the menu:" << endl << endl;
        int index = 1;
        for (auto meal : meals) {
            cout << index << ". ";
            meal->Show_Admin();
            index++;
        }

        int choice;
        cout << endl;
        cout << "Enter the number of the meal you want to remove (or 0 to cancel): ";

      
        while (!(cin >> choice)) {
            cin.clear();  
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  
            cout << "\033[31mInvalid input. Please enter a valid number:\033[0m ";
        }

        if (choice == 0) {
            cout << "\033[33mOperation canceled.\033[0m" << endl;
            return;
        }

        if (choice < 1 || choice > meals.size()) {
            cout << endl;
            cout << "\033[31m                                               Invalid choice. Please try again.\033[0m" << endl<<endl;
            return;
        }

    
        auto it = meals.begin();
        advance(it, choice - 1);
        delete* it;
        meals.erase(it);

        cout << "\033[32m"
            << "                                                 Meal removed successfully!"
            << "\033[0m" << endl;
        WriteToFile3();
    }


    void Update_Meal(list<Stock*>& stock) {
        cout << endl;
        if (meals.empty()) {
            cout << "\033[31m"
                << "                                            Menu is empty. No meals to remove."
                << "\033[0m" << endl;
            return;
        }

        cout << "Current meals in the menu:" << endl << endl;
        int index = 1;
        for (auto meal : meals) {
            cout << index << ". ";
            meal->Show_Admin();
            index++;
        }

        int meal_id;
        cout << endl;
        cout << "Enter the ID of the meal you want to update : ";

      
        while (!(cin >> meal_id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\033[31mInvalid input. Please enter a valid meal ID:\033[0m ";
        }

        Meal* meal_to_update = nullptr;
        for (auto& meal : meals) {
            if (meal->Get_ID3() == meal_id) {
                meal_to_update = meal;
                break;
            }
        }

        if (!meal_to_update) {
            cout << "\033[31m                                                 Meal with ID " << meal_id << " not found.\033[0m" << endl<<endl;
            return;
        }

        int choice;
        do {
            system("cls");
            cout << "\033[34mCurrent details of the meal:\033[0m" << endl<<endl;
            meal_to_update->Show_Admin();
            meal_to_update->Show_Ingredients();

            

            cout << "\n\033[36mWhat would you like to update?\033[0m" << endl<<endl;
            cout << "1. Price" << endl;
            cout << "2. Information" << endl;
            cout << "3. Ingredients" << endl;
            cout << "0. Cancel" << endl<<endl;
            cout << "Enter your choice : ";

            
            while (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\033[31mInvalid input. Please enter a valid choice:\033[0m ";
            }

            switch (choice) {
            case 1: {
                system("cls");
                cout << "\033[34mCurrent details of the meal:\033[0m" << endl << endl;
                meal_to_update->Show_Admin();
                meal_to_update->Show_Ingredients();
                double new_price;
                cout << endl;
                cout << "Enter new price : ";

                
                while (!(cin >> new_price)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "\033[31mInvalid input. Please enter a valid price:\033[0m ";
                }

                meal_to_update->Set_Mealprice(new_price);
           

                for (auto stk : stock) {
                    stk->WriteToFile2();
                }


                WriteToFile3();
                cout << "\033[32m" << "                                         Update was successfully completed." << "\033[0m" << endl << endl;
                this_thread::sleep_for(chrono::milliseconds(800));
                break;
            }
            case 2: {
                system("cls");
                cout << "\033[34mCurrent details of the meal:\033[0m" << endl << endl;
                meal_to_update->Show_Admin();
                meal_to_update->Show_Ingredients();
                double new_price;
                cout << endl;
                string new_info;
                cout << "Enter new information : ";

               
                cin.ignore();
                cin >> new_info;

                meal_to_update->Set_Information(new_info);
                

                for (auto stk : stock) {
                    stk->WriteToFile2();
                }
                WriteToFile3();
                cout << "\033[32m" << "                                         Update was successfully completed." << "\033[0m" << endl << endl;
                this_thread::sleep_for(chrono::milliseconds(800));
                break;
            }
            case 3: {
                system("cls");
                cout << "\033[34mCurrent details of the meal:\033[0m" << endl << endl;
                meal_to_update->Show_Admin();
                meal_to_update->Show_Ingredients();
                
                cout << endl;
                cout << "\033[34m" << "                                                  Available Ingridients" << "\033[0m" << endl << endl;

                for (const auto& ing : Get_Ingrients()) {
                    cout << "ID: " << "\033[36m" << ing->Get_ID() << "\033[0m" << ", Name: " << ing->Get_Name() << endl;
                }
                cout << endl;
                while (true) {
                    int ingredient_id;
                    cout << endl;
                    cout << "Enter Ingredient ID to add (or 0 to stop): ";

                   
                    while (!(cin >> ingredient_id)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "\033[31mInvalid input. Please enter a valid ingredient ID:\033[0m ";
                    }

                    if (ingredient_id == 0) break;

                    int count;
                    bool found = false;

                    for (auto stk : stock) {
                        for (auto ingr : stk->Get_Ingrients()) {
                            if (ingr->Get_ID() == ingredient_id) {
                                
                                cout << "Enter quantity for this ingredient : ";

                            
                                while (!(cin >> count)) {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "\033[31mInvalid input. Please enter a valid quantity:\033[0m ";
                                }

                                if (count <= ingr->Get_Quantity()) {
                                    meal_to_update->Add_Ingredient(ingr, count);
                                    ingr->decrease_quantity(count);
                                    found = true;
                                  

                                    WriteToFile3();
                                    cout << "\033[32m" << "                                         Update was successfully completed." << "\033[0m" << endl << endl;
                                    this_thread::sleep_for(chrono::milliseconds(800));
                                    stk->WriteToFile2();
                                }
                                else {
                                    cout << "\033[31mNot enough quantity in stock for ingredient " << ingr->Get_Name() << "\033[0m" << endl;
                                }
                                break;
                            }
                        }
                        if (found) break;
                    }

                    if (!found) {
                        cout << "\033[31m                                          Ingredient with ID " << ingredient_id << " not found in stock.\033[0m" << endl;
                    }
                }
                cout << "\033[32mIngredients updated successfully!\033[0m" << endl;
                break;
            }
            case 0:
                system("cls");
                cout << "\033[33mUpdate operation canceled.\033[0m" << endl;
                break;
            default:
                cout << "\033[31mInvalid choice. Please try again.\033[0m" << endl;
            }
        } while (choice != 0);
    }

    void Show_Menu() {
        for (auto meal : meals) {
            meal->Show_Admin();
            meal->Show_Ingredients();
            cout << endl;
        }
    }
};



class Admin :public Stock {
    queue<User*>* users;
    list<Ingridient*> ingridients;
    list<Meal*> meals;
    Stock stock;
    Menu menu;
    double restaurant_budget;

public:

    Admin(string filename = "user.txt") {
        restaurant_budget = 1000;
        try {
            ReadFromFile(filename);

        }
        catch (const string& ex) {
            cerr << "Error: " << ex << endl;
        }
    }

    void WriteToFile(string filename = "user.txt") {
        fstream fs(filename, ios::out);
        if (fs.is_open()) {
            queue<User*> tempUsers = *users;
            while (!tempUsers.empty()) {
                User* user = tempUsers.front();
                fs << user->Get_ID2() << ":"
                    << user->Get_Username() << ":"
                    << user->Get_Password() << ":"
                    << user->Get_Budget() << "\n";
                tempUsers.pop();
            }
            fs.close();
        }
        else {
            throw string("File couldn't open!!!");
        }
    }

    void ReadFromFile(string filename = "user.txt") {
        fstream fs(filename, ios::in);
        if (fs.is_open()) {
            string row;
            while (getline(fs, row)) {
                if (row.empty()) continue;

                string id, username, password;
                double budget = 0.0;
                int r = 0;
                string value = "";

                for (auto ch : row) {
                    if (ch != ':') {
                        value += ch;
                    }
                    else {
                        if (r == 0) id = value;
                        else if (r == 1) username = value;
                        else if (r == 2) password = value;

                        value = "";
                        r++;
                    }
                }
                budget = stod(value);

                users->push(new User(username, password, budget));
            }
            fs.close();
        }
        else {
            throw string("File couldn't open!!!");
        }
    }

    Admin(queue<User*>* users, list<Ingridient*> ingridients, double restaurant_budget) : users(users), ingridients(ingridients) {
        Set_RestaurantBudegt(restaurant_budget);
    }


    Menu& GetMenu() {
        return menu;
    }



    void Set_RestaurantBudegt(double restaurant_budget) {
        try {
            if (restaurant_budget < 0) {
                throw runtime_error("Restaurant budget is negative! No funds available.");
            }
            this->restaurant_budget = restaurant_budget;
        }
        catch (const runtime_error& e) {
            cout << "\033[31mError: " << e.what() << "\033[0m\n";
        }
    }



    double Get_RestaurantBudget() {
        return restaurant_budget;
    }


    void Admin_Account() {
        system("cls");
        cout << "\033[34m" << "-------------------------------------------------------Admin Page-------------------------------------------------------" << "\033[0m" << endl << endl;
        char select3;
        cout << "Restaurant Budget : " << "\033[32m" << Get_RestaurantBudget() << "\033[0m" << endl << endl;
        cout << "  0 - > Show All Users" << endl << endl;
        cout << "  1 - > Delete Users" << endl << endl;
        cout << "  2 - > Add Ingrients" << endl << endl;
        cout << "  3 - > Show All Ingrients" << endl << endl;
        cout << "  4 - > Delete Ingrients" << endl << endl;
        cout << "  5 - > Update Ingridient " << endl << endl;
        cout << "  6 - > Add Meal " << endl << endl;
        cout << "  7 - > Delete Meal " << endl << endl;
        cout << "  8 - > Update Meal " << endl << endl;
        cout << "  9 - > Show Menu " << endl << endl;

        cout << "Please choose one : ";
        cin >> select3;
        switch (select3) {
        case '0':
            system("cls");
            cout << "\033[34m" << "                                                        All Users" << "\033[0m" << endl << endl;
            Show2();
            break;


        case '1':
            system("cls");
            Show2();
            int Id;
            cout << "Enter the ID of the user to delete : ";
            cin >> Id;
            Delete_User(*users, Id);


            WriteToFile();


            break;

        case '2':
            system("cls");
            {
                double total_price = stock.Add_Ingrient();
                Set_RestaurantBudegt(Get_RestaurantBudget() - total_price);
                cout << "\033[32m                                         Ingredient added. Remaining budget: $" << Get_RestaurantBudget() << "\033[0m\n\n";

            }
            break;


        case '3':
            system("cls");
            cout << "\033[34m" << "                                                       All Ingredients" << "\033[0m" << endl << endl;
            stock.Show_All();
            break;

        case '4':
            system("cls");
            stock.Delete_Ingridient();

            break;

        case '5':
            system("cls");
            stock.Update_Ingridient();

            break;

        case '6':
            system("cls");
            {

                list<Stock*> stocks;
                stocks.push_back(&stock);
                menu.Add_Meal(stocks);


            }


            break;

        case '7':
            system("cls");
            cout << "\033[34m" << "                                                        Delete Meals" << "\033[0m" << endl << endl;
            menu.Remove_Meal();
            break;

        case '8':
            system("cls");
            {
                list<Stock*> stocks;
                stocks.push_back(&stock);
                menu.Update_Meal(stocks);
            }
            break;

        case '9':
            system("cls");
            

            cout << "\033[34m" << "                                                         All Meals" << "\033[0m" << endl << endl;

            menu.Show_Menu();




            break;

        }


    }


    void Delete_User(queue<User*>& users, int Id) {
        queue<User*> temp;
        bool isDeleted = false;


        do {
            cout << "Enter the User ID: ";
            cin >> Id;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\033[31mInvalid input. Please enter a valid numeric ID.\033[0m\n";
            }
            else {
                break;
            }
        } while (true);


        while (!users.empty()) {
            if (users.front()->Get_ID2() == Id) {
                isDeleted = true;
                delete users.front();
            }
            else {
                temp.push(users.front());
            }
            users.pop();
        }

        users = temp;


        if (isDeleted) {
            cout << "\033[32m                                     User with ID " << Id << " has been successfully deleted.\033[0m\n";
        }
        else {
            cout << "\033[31m                                                 No user with ID " << Id << " found.\033[0m\n" << endl;
        }
    }



    void Show2() {
        queue<User*> tempuser = *users;
        int count = 0;
        while (!tempuser.empty()) {
            cout << "\033[34m" << "-----------------------------------------------------------" << ++count << "------------------------------------------------------------" << "\033[0m" << endl;
            tempuser.front()->Show();
            this_thread::sleep_for(chrono::milliseconds(150));
            tempuser.pop();
        }
    }

    Stock& Get_Stock() {
        return stock;
    }

};

class Card {
    static int Card_ID;
    int ID_CARD;
    string card_name;
    double card_price;
    string card_information;
    int card_quantity;

public:
    Card() {};
    Card(string card_name, double card_price, string card_information, int card_quantity) {
        ID_CARD = ++Card_ID;
        Set_Cardname(card_name);
        Set_Cardprice(card_price);
        Set_CardInformation(card_information);
        Set_Quantity(card_quantity);
    };

    int Get_Idcard() {
        return ID_CARD;
    }

    int Get_Quantity() const {
        return card_quantity;
    }


    string Get_Cardname() {
        return card_name;
    }

    double Get_Cardprice() {
        return card_price;
    }

    string Get_CardInformation() {
        return card_information;
    }

    void Set_Cardname(string card_name) {
        this->card_name = card_name;
    }


    void Set_Cardprice(double card_price) {
        this->card_price = card_price;
    }

    void Set_CardInformation(string card_information) {
        this->card_information = card_information;
    }

    void Set_Quantity(int qty) {
        card_quantity = qty;
    }

};

int Card::Card_ID = 0;

class User_Management : public Menu, public User {
    queue<User*> users;
    map<string, list<Card*>> user_cards;


public:
    User_Management(string filename = "user.txt") {
        try {
            ReadFromFile(filename);
        }
        catch (const string& ex) {
            cerr << "Error: " << ex << endl;
        }
    }

    void WriteToFile(string filename = "user.txt") {
        fstream fs(filename, ios::out);
        if (fs.is_open()) {
            queue<User*> tempUsers = users;
            while (!tempUsers.empty()) {
                User* user = tempUsers.front();
                fs << user->Get_ID2() << ":"
                    << user->Get_Username() << ":"
                    << user->Get_Password() << ":"
                    << user->Get_Budget() << "\n";
                tempUsers.pop();
            }
            fs.close();
        }
        else {
            throw string("File couldn't open!!!");
        }
    }

    void ReadFromFile(string filename = "user.txt") {
        fstream fs(filename, ios::in);
        if (fs.is_open()) {
            string row;
            while (getline(fs, row)) {
                if (row.empty()) continue;

                string id, username, password;
                double budget = 0.0;
                int r = 0;
                string value = "";

                for (auto ch : row) {
                    if (ch != ':') {
                        value += ch;
                    }
                    else {
                        if (r == 0) id = value;
                        else if (r == 1) username = value;
                        else if (r == 2) password = value;

                        value = "";
                        r++;
                    }
                }
                budget = stod(value);

                users.push(new User(username, password, budget));
            }
            fs.close();
        }
        else {
            throw string("File couldn't open!!!");
        }
    }



    string Check_SignUp(queue<User*> users) {
        string newuser;
        bool isUnique = false;
        while (!isUnique) {
            cout << "Enter username: ";
            cin >> newuser;
            queue<User*> tempUsers = users;
            isUnique = true;

            while (!tempUsers.empty()) {
                User* user = tempUsers.front();
                tempUsers.pop();

                if (user->Get_Username() == newuser) {
                    cout << "\033[31m" << "This username has been used. Please choose another one." << "\033[0m" << endl;
                    isUnique = false;
                    break;
                }
            }
        }
        return newuser;
    }

   

    void Login(Admin& admin) {
        string username, password;
        bool isAuthenticated = false;
        int attempts = 3;
        Menu& menu = admin.GetMenu();
        list<Card*>* current_user_cards = nullptr;
        User* current_user = nullptr;
        Stock& stock = admin.Get_Stock();


        do {
            system("cls");
            cout << "\033[34m"
                << "------------------------------------------------------ User Login ------------------------------------------------------"
                << "\033[0m\n\n";
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;


            queue<User*> tempusers = users;
            while (!tempusers.empty()) {
                User* user = tempusers.front();
                tempusers.pop();
                if (user->Get_Username() == username && user->Get_Password() == password) {
                    system("cls");
                    cout << "\033[32mLogin successful! Welcome, " << username << "!\033[0m\n\n";
                    isAuthenticated = true;

                    current_user = user;


                    if (user_cards.find(username) == user_cards.end()) {
                        user_cards[username] = list<Card*>();
                    }
                    current_user_cards = &user_cards[username];
                    break;
                }
            }

            if (!isAuthenticated) {
                system("cls");
                attempts--;
                cout << "\033[31m                                 Incorrect username or password. Attempts remaining: " << attempts << "\033[0m\n";
                this_thread::sleep_for(chrono::milliseconds(800));
                if (attempts == 0) {
                    cout << "\033[33mNo attempts left. Try again later.\033[0m\n";
                    this_thread::sleep_for(chrono::seconds(2));
                    return;
                }
            }
        } while (!isAuthenticated && attempts > 0);


        while (isAuthenticated) {
            system("cls");
            cout << "\033[34m----------------------------------------------------- My Accaount -----------------------------------------------------\033[0m\n";
            cout << "My budget: " << "\033[32m" << current_user->Get_Budget() << "\033[0m" << endl << endl;
            cout << "1. Show Menu\n";

            cout << "2. Add to Card\n";
            cout << "3. Show Card\n";
            cout << "4. Confirm Card\n";
            cout << "5. Remove Meal from Card\n";
            cout << "6. Update Meal Quantity in Card\n";
            cout << "7. Logout\n\n";
            cout << "\033[36m" << "Enter your choice : " << "\033[0m";
            int choice;
           

            while (!(cin >> choice)) {
                cin.clear(); 
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\033[31mInvalid input. Please enter a valid choice (1-7): \033[0m";
            }



            switch (choice) {
            case 1:
                system("cls");
                cout << "\033[34m--------------------------------------------------- Available Meals ---------------------------------------------------\033[0m\n";
                menu.Show_Menu();
                break;

            case 2: {
                system("cls");
                cout << "\033[34m--- Available Meals ---\033[0m\n";
                menu.Show_Menu();

                int meal_id;
                cout << "\nEnter the ID of the meal to add to your card: ";


                while (!(cin >> meal_id)) {
                    cin.clear(); 
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    cout << "\033[31mInvalid input. Please enter a valid meal ID: \033[0m";
                }

            
                bool found = false;
                for (auto meal : menu.Get_Meals()) {
                    if (meal->Get_ID3() == meal_id) {
                        int quantity;
                        cout << "Enter quantity: ";

                    
                        while (!(cin >> quantity)) {
                            cin.clear(); 
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "\033[31mInvalid input. Please enter a valid quantity: \033[0m";
                        }

                        bool meal_exists_in_cart = false;
                        for (auto card : *current_user_cards) {
                            if (card->Get_Cardname() == meal->Get_Mealname()) {
                                card->Set_Quantity(card->Get_Quantity() + quantity);
                                meal_exists_in_cart = true;
                                cout << "\033[32mQuantity of " << meal->Get_Mealname() << " updated in your card!\033[0m\n";
                                break;
                            }
                        }

                        if (!meal_exists_in_cart) {
                            current_user_cards->push_back(new Card(meal->Get_Mealname(), meal->Get_Mealprice(), meal->Get_Information(), quantity));
                            cout << "\033[32m                                              Meal added to your card successfully!\033[0m\n";
                        }
                        found = true;
                        break;
                    }
                }

               
                if (!found) {
                    cout << endl;
                    cout << "\033[31m                                            Meal with ID " << meal_id << " not found in the menu.\033[0m\n";
                }

                break;


            }

            case 3:
                system("cls");
                cout << "\033[34m------------------------------------------------------ Your Card ------------------------------------------------------\033[0m\n\n";
                if (current_user_cards->empty()) {
                    cout << "\033[33m                                                    Your card is empty.\033[0m\n";
                }
                else {
                    for (auto card : *current_user_cards) {
                       
                        cout << "\033[34m" << "Name: " << card->Get_Cardname() << "\033[0m"
                         
                            << " | \033[32mPrice: $" << card->Get_Cardprice() << "\033[0m"
                            
                            << " | \033[33mInfo: " << card->Get_CardInformation() << "\033[0m"
                            << endl;
                    }

                }
                break;

            case 4: {
                system("cls");
                if (current_user_cards->empty()) {
                    cout << "\033[33m                                                    Your card is empty.\033[0m\n";
                    break;
                }

                double total_price = 0;

                cout << "\033[34m------------------------------------------------------ Your Card ------------------------------------------------------\033[0m\n\n";
               
                for (auto card : *current_user_cards) {
                    total_price += card->Get_Cardprice() * card->Get_Quantity();

                    cout << "\033[34mName: \033[0m" << card->Get_Cardname()
                        << " | \033[33mPrice: $\033[0m" << card->Get_Cardprice()
                        << " | \033[36mQuantity: \033[0m" << card->Get_Quantity()
                        << " | \033[32mInfo: \033[0m" << card->Get_CardInformation() << endl;
                }


                cout << "\nTotal price : $" << total_price << endl<<endl;

                if (current_user->Get_Budget() >= total_price) {
                    bool all_ingredients_available = true;
                    for (auto card : *current_user_cards) {
                        for (auto meal : menu.Get_Meals()) {
                            if (meal->Get_Mealname() == card->Get_Cardname()) {
                                if (!stock.Remove_Ingredients(meal->Get_Ingredients())) {
                                    all_ingredients_available = false;
                                    break;
                                }
                            }
                        }
                        if (!all_ingredients_available) break;
                    }

                    if (all_ingredients_available) {
                        cout << "\033[32mYour card is ready to be confirmed!\033[0m\n";

                        cout << "\n1. Confirm Order\n";
                        cout << "2. Cancel Order\n\n";
                        cout << "Enter your choice : ";
                        int confirm_choice;
                        while (true) {
                            if (cin >> confirm_choice) { 
                                if (confirm_choice == 1 || confirm_choice == 2) {
                                    break; 
                                }
                                else {
                                    cout << "\033[31mInvalid choice. Please enter 1 to confirm or 2 to cancel.\033[0m\n";
                                    cout << "Enter your choice: ";
                                }
                            }
                            else {
                                cout << "\033[31mInvalid input. Please enter a number (1 or 2).\033[0m\n";
                                cin.clear(); 
                                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                                cout << "Enter your choice: ";
                            }
                        }

                        if (confirm_choice == 1) {
                            current_user->Set_Budget(current_user->Get_Budget() - total_price);
                            admin.Set_RestaurantBudegt(admin.Get_RestaurantBudget() + total_price);

                            cout << "\033[32m                                               Your card has been confirmed!\033[0m\n";

                            for (auto card : *current_user_cards) {
                                for (auto meal : menu.Get_Meals()) {
                                    if (meal->Get_Mealname() == card->Get_Cardname()) {
                                        card->Set_Quantity(card->Get_Quantity() - card->Get_Quantity());
                                        break;
                                    }
                                }
                            }

                            current_user_cards->clear();
                            stock.WriteToFile2();
                        }
                        else if (confirm_choice == 2) {
                            cout << "\033[33m                                               Your order has been canceled.\033[0m\n";
                            break;
                        }
                    }
                    else {
                        cout << "\033[31mOrder cannot be completed due to insufficient stock.\033[0m\n";
                    }
                }
                else {
                    cout << "\033[31mInsufficient budget to confirm the card.\033[0m\n";
                }
                break;
            }


            case 5: {
                system("cls");
                if (current_user_cards->empty()) {
                    cout << "\033[33m                                                    Your card is empty.\033[0m\n";
                    break;
                }

                cout << "\033[34m------------------------------------------------------ Your Card ------------------------------------------------------\033[0m\n\n";
                for (int i = 0; i < current_user_cards->size(); ++i) {
                    auto card = current_user_cards->front();
                    cout << "\033[34m" << i + 1 << ". \033[0m" << card->Get_Cardname()
                        << " | \033[33mPrice: $\033[0m" << card->Get_Cardprice()
                        << " | \033[32mInfo: \033[0m" << card->Get_CardInformation() << endl;
                    current_user_cards->push_back(current_user_cards->front());
                    current_user_cards->pop_front();
                }

                int remove_choice;

            
                while (true) {
                    cout << "\nEnter the number of the meal to remove from your card: ";

       
                    if (!(cin >> remove_choice)) {
                        cout << "\033[31mInvalid input! Please enter a valid number.\033[0m\n";
                        cin.clear(); 
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    }
                    else if (remove_choice < 1 || remove_choice > current_user_cards->size()) {
                        cout << "\033[31mInvalid choice. Try again.\033[0m\n";
                    }
                    else {
                        break;  
                    }
                }

           
                auto it = current_user_cards->begin();
                advance(it, remove_choice - 1);
                current_user_cards->erase(it);
                cout << "\033[32m                                              Meal removed from your card.\033[0m\n";
                break;
            }



            case 6: {
                system("cls");
                if (current_user_cards->empty()) {
                    cout << "\033[33m                                                    Your card is empty.\033[0m\n";
                    break;
                }

                cout << "\033[34m------------------------------------------------------ Your Card ------------------------------------------------------\033[0m\n\n";
                for (int i = 0; i < current_user_cards->size(); ++i) {
                    auto card = current_user_cards->front();

                    cout << "\033[34m" << i + 1 << ". \033[0m"   
                        << "\033[32m" << card->Get_Cardname()    
                        << "\033[0m"                           
                        << " | \033[33mPrice: $\033[0m"           
                        << "\033[33m" << card->Get_Cardprice()   
                        << "\033[0m"                             
                        << " | \033[36mQuantity: \033[0m"        
                        << "\033[36m" << card->Get_Quantity()    
                        << "\033[0m"                             
                        << " | \033[36mInfo: \033[0m"             
                        << "\033[36m" << card->Get_CardInformation() << "\033[0m" 
                        << endl;

                    current_user_cards->push_back(current_user_cards->front());
                    current_user_cards->pop_front();
                }

                int update_choice;
                bool valid_choice = false;  
                while (!valid_choice) {
                    cout << "\nEnter the number of the meal to update quantity: ";
                    cin >> update_choice;

                
                    if (cin.fail() || update_choice < 1 || update_choice > current_user_cards->size()) {
                        cin.clear();  
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  
                        cout << "\033[31mInvalid choice. Please enter a valid number.\033[0m\n";
                    }
                    else {
                        valid_choice = true;  
                    }
                }

                auto it = current_user_cards->begin();
                advance(it, update_choice - 1);

                int new_quantity;
                cout << "Enter new quantity for " << (*it)->Get_Cardname() << ": ";
                cin >> new_quantity;

                (*it)->Set_Quantity(new_quantity);
                cout << "\033[32m                                                 Quantity updated.\033[0m\n";
                break;
            }


            case 7: {
                system("cls");
                cout << "\033[33m                                              You have been logged out. Goodbye!\033[0m\n";
                isAuthenticated = false;
                break;
            }

            default:
                cout << "\033[31m                                                  Invalid choice. Try again.\033[0m\n";
                break;
            }

            this_thread::sleep_for(chrono::seconds(2));
        }
    }


    void User_Account(Admin& admin) {
        char select2;
        cout << "1 - > Login" << endl;
        cout << "2 - > Sign Up" << endl << endl;
        cout << "Please choose one : ";
        cin >> select2;

        switch (select2) {
        case '1':
            system("cls");
            Login(admin);
            break;
        case '2':
            User_Registered();
            break;
        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }
    }

    void User_Registered() {
        system("cls");

        cout << endl;
        cout << "\033[34m"
            << "-----------------------------------------------------User Register-----------------------------------------------------"
            << "\033[0m" << endl
            << endl;
        string username = Check_SignUp(users);
        string password;
        cout << "Enter Password : ";
        cin >> password;
        double budget = 100;
        Add_User(username, password, budget);
        cout << "\033[32m"
            << "                                               Register was successfully"
            << "\033[0m" << endl
            << endl;
        this_thread::sleep_for(chrono::seconds(2));
        WriteToFile();
        system("cls");
    }

    void Add_User(string username, string password, double budget) {
        User* newuser = new User(username, password, budget);
        users.push(newuser);
    }

    queue<User*>& Get_Users() {
        return users;
    }
};



int User::next_ID2 = 0;


int main() {

    Stock stock;
    double restaurant_budget = 1000;
    User_Management one;
    Admin admin1(&one.Get_Users(), stock.Get_Ingrients(), restaurant_budget);


    char select;
    bool loggedIn = false;
    bool adminLoggedIn = false;

    while (true) {
        if (!loggedIn && !adminLoggedIn) {
            system("cls");
            cout << "\033[33m" << "                                             You are welcome at Turgut Market." << "\033[0m" << endl;
            cout << "   1 - > User " << endl;
            cout << "   2 - > Admin " << endl << endl;
            cout << "Please choose one : ";
            cin >> select;

            switch (select) {
            case '1': {
                loggedIn = true;
                break;
            }
            case '2': {
                adminLoggedIn = true;
                break;
            }
            default:
                cout << "Invalid selection. Please choose a valid option." << endl;
                break;
            }
        }
        else if (loggedIn) {

            system("cls");
            cout << "\033[34m" << "                                                     User Account" << "\033[0m" << endl;
            one.User_Account(admin1);

            cout << "Do you want to log out of the user account? (y/n): ";
            char exitUser;
            cin >> exitUser;
            if (exitUser == 'y' || exitUser == 'Y') {
                loggedIn = false;
            }
        }
        else if (adminLoggedIn) {

            admin1.Admin_Account();
            //stock.Admin_Account();
            cout << "Do you want to log out of the admin account? (y/n): ";
            char exitAdmin;
            cin >> exitAdmin;
            if (exitAdmin == 'y' || exitAdmin == 'Y') {
                adminLoggedIn = false;
            }
        }
    }

    return 0;
}