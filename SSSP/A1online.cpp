#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <climits>
#include <stack>

using namespace std;

struct Airport {
    string name;
    int layoverTime;
};

struct Flight {
    string source;
    string destination;
    int travelTime;
};

struct StateInfo {
    int totalTime;
    string lastState;
};

void findFastestRoute(const unordered_map<string, Airport>& airports,
                      const vector<Flight>& flights,
                      const string& startState,
                      const string& endState) {
    unordered_map<string, StateInfo> stateInfo;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    stateInfo[startState] = {0, ""};
    pq.push({0, startState});

    while (!pq.empty()) {
        string currentState = pq.top().second;
        int currentTime = pq.top().first;
        pq.pop();

        for (const Flight& flight : flights) {
            if (flight.source == currentState) {
                int layoverTime = airports.at(flight.destination).layoverTime;
                int totalTime = currentTime + flight.travelTime + layoverTime;

                if (!stateInfo.count(flight.destination) || totalTime < stateInfo[flight.destination].totalTime) {
                    stateInfo[flight.destination] = {totalTime, currentState};
                    pq.push({totalTime, flight.destination});
                }
            }
        }
    }

    if (stateInfo.count(endState)) {
        cout << stateInfo[endState].totalTime << endl;

        stack<string> path;
        string currentState = endState;
        while (!currentState.empty()) {
            path.push(currentState);
            currentState = stateInfo[currentState].lastState;
        }

        while (!path.empty()) {
            cout << path.top();
            path.pop();
            if (!path.empty()) cout << " -> ";
        }

        cout << endl;
    } else {
        cout << "No valid route found." << endl;
    }
}

int main() {
    ifstream inputFile("input.txt");

    int n, f;
    inputFile >> n >> f;

    unordered_map<string, Airport> airports;
    for (int i = 0; i < n; ++i) {
        string name;
        int layoverTime;
        inputFile >> name >> layoverTime;
        airports[name] = {name, layoverTime};
    }

    vector<Flight> flights;
    for (int i = 0; i < f; ++i) {
        string source, destination;
        int travelTime;
        inputFile >> source >> destination >> travelTime;
        flights.push_back({source, destination, travelTime});
    }

    string startState, endState;
    inputFile >> startState >> endState;

    inputFile.close();

    findFastestRoute(airports, flights, startState, endState);

    return 0;
}
