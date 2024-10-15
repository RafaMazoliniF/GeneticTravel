#include <iostream>
#include <map>
#include <array>
#include <vector>
#include <cmath>
#include <random>
#include <algorithm>
#include <cstdlib> // Para system()
#include <sstream> // Para ostringstream

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
    //This class represents a single solution and is responsible for all individual operations
    private:
        vector<int> gene;
        float cost = 0;

        float TwoPointDistance(array<int, 2> a, array<int, 2> b) {
            //Calculates the euclidean distance between two cities.
            return sqrt(pow(a[0]- b[0], 2) + pow(a[1] - b[1], 2));
        }

        void setTotalCost(map<int, array<int, 2>> cities) {
            //Calculates the cost of a solution as a pairwise sum of a city and the next.
            this->cost = 0;
            for (int i = 0; i < (int) this->gene.size(); i++) {
                array<int, 2> current_city = cities[this->gene[i]];
                array<int, 2> next_city = cities[this->gene[i + 1]];
                this->cost += TwoPointDistance(current_city, next_city);
            }

            this->cost += TwoPointDistance(cities[this->gene.back()], cities[this->gene.front()]);
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

        void setGene(vector<int> new_gene) {
            this->gene = new_gene;
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

        void Mutate(Model& model) {
            random_device rd; 
            mt19937 gen(rd());
            uniform_int_distribution<> distrib(0, model.getCities().size());

            int a = distrib(gen);
            int b = distrib(gen);

            swap(this->gene[a], this->gene[b]);

            setTotalCost(model.getCities());
        }
};

class God {
    //This class is the ambient that selects and creates individuals. 
    private:
        vector<Individual> generation;
        Model * model;

        Individual CreateRandomIndividual(Model& model) {
            //Create an Individual with a random gene based on the given model
            int length = model.getCities().size();
            vector<int> numbers;
            for (int i = 0; i < length; i++) {
                numbers.push_back(i);
            }

            random_device rd;
            mt19937 gen(rd());
            shuffle(numbers.begin(), numbers.end(), gen);

            return Individual(numbers, model);
        }

        void SortGeneration() {
            // Sort individuals based on their cost (ascending)
            sort(generation.begin(), generation.end(), [](Individual& a, Individual& b) {
                return a.getCost() < b.getCost();
            });
        }

    public:
        God(int n_individuals, Model& model) {
            this->model = &model;
            for (int i = 0; i < n_individuals; i++) {
                this->generation.push_back(CreateRandomIndividual(model));
            }

            SortGeneration();
        }

        void PrintGeneration() {
            //Print all individuals of the generation
            for (int i = 0; i < (int) this->generation.size(); i++) {
                cout << "INDIVIDUAL " << i << ":" << endl;
                this->generation[i].PrintIndividual();
                cout << endl;
            }
        }

        void CreateNewGeneration() {
            for (int i = 1; i < (int) this->generation.size(); i++) {
                for (int j = 0; j < i; j++) {
                    this->generation[i].Mutate(*model);
                }
            }

            SortGeneration();
        }

        Individual getBestIndividual() {
            Individual ind = this->generation[0];
            vector<int> ind_gene = ind.getGene();
            ind_gene.push_back(ind_gene[0]);
            ind.setGene(ind_gene);

            return ind;
        }

        void Run4nEpocs(int n) {
            PrintGeneration();
            cout << endl << endl;

            for (int i = 0; i < n; i++) {
                CreateNewGeneration();
            }

            PrintGeneration();
        }
};

void CallPythonPlot(Individual final_solution, Model& model) {
    //Call a plot_points.py to plot a given final solution based on a given model.

    vector<int> solution = final_solution.getGene();
    string cost = to_string(final_solution.getCost());

    stringstream ss;
    for (int city : solution) {
        array<int, 2> coords = model.GetCity(city);
        ss << coords[0] << "," << coords[1] << " "; 
    }

    string points = ss.str();
    points.pop_back(); 

    string command = "python3 ../plot_points.py " + cost + " " + points;
    system(command.c_str()); 
}

int main() {
    // Defining the problem
    // map<int, std::array<int, 2>> cities = {
    //     {0, {30, 0}},
    //     {1, {21, 21}},
    //     {2, {0, 30}},
    //     {3, {-21, 21}},
    //     {4, {-30, 0}},
    //     {5, {-21, -21}},
    //     {6, {0, -30}},
    //     {7, {21, -21}}
    // };

    // map<int, array<int, 2>> cities = {
    //     {0, {19, 26}},
    //     {1, {13, 10}},
    //     {2, {10, 1}},
    //     {3, {2, 29}},
    //     {4, {8, 28}},
    //     {5, {5, 23}},
    //     {6, {15, 14}},
    //     {7, {3, 5}}
    // };

    map<int, array<int, 2>> cities = {
        {0, {42, 65}},
        {1, {78, 91}},
        {2, {65, 23}},
        {3, {12, 58}},
        {4, {95, 84}},
        {5, {33, 47}},
        {6, {81, 19}},
        {7, {55, 72}},
        {8, {90, 10}},
        {9, {48, 99}},
        {10, {77, 45}},
        {11, {18, 29}},
        {12, {29, 80}},
        {13, {63, 54}},
        {14, {25, 37}},
        {15, {91, 68}},
        {16, {36, 15}},
        {17, {58, 91}},
        {18, {84, 12}},
        {19, {10, 62}}
    };

    Model model(cities);
    God god(10, model);

    god.Run4nEpocs(10000);

    CallPythonPlot(god.getBestIndividual(), model);

    cout << endl;
    return 0;
}
