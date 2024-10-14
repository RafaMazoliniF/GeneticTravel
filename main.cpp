#include <iostream>
#include <map>
#include <array>
#include <vector>

using namespace std;

class Model {
    //This class models the Traveling Salesman problem by storing the different cities and their locations on a Map.

private:
    map<int, array<int, 2>> cities;

public:
    Model(map<int, array<int, 2>> cities) : cities(cities) {
        // Constructor: receives a problem and stores it in the cities class variable.
    }

    map<int, array<int, 2>> getCities() const {
        return cities;
    }

    void PrintCity(int city_number) const {
        // Prints the city in the form: "City X: [x, y]"
        cout << "City " << city_number << ": [" << cities.at(city_number)[0] << ", " << cities.at(city_number)[1] << "]\n";
    }
};

class God {
private:
    Model model;
    vector<int> first_gen;

public:
    God(const Model& model) : model(model) {
        this->model = model;

        for (int i = 0; i < (int) this->model.getCities().size(); ++i) {
            first_gen.push_back(i);
        }

        cout << "First generation size: " << first_gen.size() << endl;
    }
};

int main() {
    // Defining the problem
    map<int, array<int, 2>> cities = {
        {0, {19, 26}},
        {1, {13, 10}},
        {2, {10, 1}},
        {3, {2, 29}},
        {4, {8, 28}},
        {5, {5, 23}},
        {6, {15, 14}},
        {7, {3, 5}}
    };

    Model model(cities);
    God god(model);

    cout << endl;
    return 0;
}
