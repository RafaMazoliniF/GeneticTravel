#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>

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

        array<int, 2> GetCity(int city_number) {
            return cities[city_number];
        }

        void PrintCity(int city_number) const {
            // Prints the city in the form: "City X: [x, y]"
            cout << "City " << city_number << ": [" << cities.at(city_number)[0] << ", " << cities.at(city_number)[1] << "]\n";
        }
};

class Individual {
    private:
        vector<int> gene;
        float cost = 0;

    float TwoPointDistance(array<int, 2> a, array<int, 2> b) {
        return sqrt(pow(a[0]- b[0], 2) + pow(a[1] - b[1], 2));
    }

    void setTotalCost(map<int, array<int, 2>> cities) {
        for (int i = 0; i < this->gene.size() - 1; i++) {
            array<int, 2> current_city = cities[this->gene[i]];
            array<int, 2> next_city = cities[this->gene[i + 1]];

            this->cost += TwoPointDistance(current_city, next_city);
        }
    }

    public:
        Individual(vector<int> gene, Model& model) {
            this->gene = gene;
            this->gene.push_back(this->gene.front());
            setTotalCost(model.getCities());
        }

        vector<int> getGene() {
            return this->gene;
        } 

        float getCost() {
            return this->cost;
        }

        void PrintIndividual() {
            cout << "Gene: ";
            for (auto i : this->gene) {
                cout << i << " ";
            }

            cout << endl << "Cost: " << this->cost << endl;
        }
};

class God {
    private:
        vector<Individual> generation;

        Individual CreateRandomIndividual(Model& model) {
            int length = model.getCities().size();

            vector<int> numbers(length + 1);
            for (int i = 0; i <= length; ++i) {
                numbers[i] = i;
            }

            random_device rd;
            mt19937 gen(rd());
            
            shuffle(numbers.begin(), numbers.end(), gen);

            return Individual(numbers, model);
        }

    public:
        God(int n_individuals, Model& model) {
            for (int i = 0; i < n_individuals; i++) {
                this->generation.push_back(CreateRandomIndividual(model));
            }
        }

        void PrintGeneration() {
            for (int i = 0; i < (int) this->generation.size(); i++) {
                cout << "INDIVIDUAL " << i << ":" << endl;
                this->generation[i].PrintIndividual();
                cout << endl;
            }
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
    God god = God(20, model);

    god.PrintGeneration();

    cout << endl;
    return 0;
}
