//
// Created by stas on 8.11.19.
//

#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
    NewBus,
    BusesForStop,
    StopsForBus,
    AllBuses
};

struct Query {
    QueryType type;
    string bus;
    string stop;
    vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string command;
    is >> command;
    q = {};
    if(command == "NEW_BUS"){
        q.type = QueryType::NewBus;
        int stop_count = 0;
        is >> q.bus >> stop_count;
        for(int i = 0; i < stop_count; ++i){
            string stop;
            is >> stop;
            q.stops.push_back(stop);
        }
    } else if(command == "BUSES_FOR_STOP"){
        q.type = QueryType::BusesForStop;
        is >> q.stop;
    }else if(command == "STOPS_FOR_BUS"){
        q.type = QueryType::StopsForBus;
        is >> q.bus;
    }else if(command == "ALL_BUSES"){
        q.type = QueryType::AllBuses;
    }
    return is;
}

struct BusesForStopResponse {
    bool IsStopExits;
    vector<string> buses;
};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {
    const auto& buses = r.buses;
    if (!r.IsStopExits) {
        os << "No stop";
    } else {
        for (const string& bus : buses) {
            os << bus << " ";
        }
    }
    return os;
}

struct StopsForBusResponse {
    bool is_bus_exits;
    string bus;
    vector<string> stops;
    map<string, vector<string>> stops_to_buses;
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    const auto& stops = r.stops;
    const auto& stops_to_buses = r.stops_to_buses;
    if (!r.is_bus_exits) {
        cout << "No bus";
    } else {
        bool first = true;
        for (const string &stop : stops) {
            if(!first){
                cout << endl;
            }
            first = false;
            cout << "Stop " << stop << ": ";
            if (stops_to_buses.at(stop).size() == 1) {
                cout << "no interchange";
            } else {
                for (const string &other_bus : stops_to_buses.at(stop)) {
                    if (r.bus != other_bus) {
                        cout << other_bus << " ";
                    }
                }
            }
        }
    }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops;
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    const auto& buses_to_stops = r.buses_to_stops;
    if (buses_to_stops.empty()) {
        os << "No buses";
    } else {
        bool first = true;
        for (const auto& bus_item : buses_to_stops) {
            if(!first){
                os << endl;
            }first = false;
            os << "Bus " << bus_item.first << ": ";
            for (const string& stop : bus_item.second) {
                os << stop << " ";
            }
        }
    }
    return os;
}

ostream& operator<<(ostream& stream, const vector<string>& vector1){
    stream << "[";
    bool first = true;
    for(const auto& item : vector1){
        if(!first){
            stream << ", ";
        }
        first = false;
        stream << item;
    }
    stream << "]";
    return stream;
}

class BusManager {
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops[bus] = stops;
        for(const auto& stop : stops){
            stops_to_buses[stop].push_back(bus);
        }
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if (stops_to_buses.count(stop) == 0) {
            return {false};
        } else {
            return {true,stops_to_buses.at(stop)};
        }
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        if (buses_to_stops.count(bus) == 0) {
            return {false};
        } else {
            return {true, bus, buses_to_stops.at(bus), stops_to_buses};
        }
    }

    AllBusesResponse GetAllBuses() const {
        return {buses_to_stops};
    }

private:
    map<string, vector<string>> buses_to_stops, stops_to_buses;
};

// РќРµ РјРµРЅСЏСЏ С‚РµР»Р° С„СѓРЅРєС†РёРё main, СЂРµР°Р»РёР·СѓР№С‚Рµ С„СѓРЅРєС†РёРё Рё РєР»Р°СЃСЃС‹ РІС‹С€Рµ

int main() {
    int query_count;
    Query q;

    cin >> query_count;

    BusManager bm;
    for (int i = 0; i < query_count; ++i) {
        cin >> q;
        switch (q.type) {
            case QueryType::NewBus:
                bm.AddBus(q.bus, q.stops);
                break;
            case QueryType::BusesForStop:
                cout << bm.GetBusesForStop(q.stop) << endl;
                break;
            case QueryType::StopsForBus:
                cout << bm.GetStopsForBus(q.bus) << endl;
                break;
            case QueryType::AllBuses:
                cout << bm.GetAllBuses() << endl;
                break;
        }
    }

    return 0;
}