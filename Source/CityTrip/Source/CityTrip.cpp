#include "../CityTrip.h"

CityTrip::CityTrip(const std::vector<std::string>& destinations, const std::vector<EdgeConnection>& connections, std::uint32_t maxMins)
    : m_maxMins(maxMins) {
    for (std::string destination : destinations) {
        m_graph.InsertVertex(destination);
    }

    for (EdgeConnection connection : connections) {
        Vertex<std::string>* first = m_graph.GetVertex(connection.m_firstDestination);
        Vertex<std::string>* second = m_graph.GetVertex(connection.m_secondDestination);
        m_graph.InsertEdge(first, second, connection.m_mins);
    }
}

void CityTrip::FindAllPossiblePaths(Vertex<std::string>* iter, std::uint32_t mins, std::vector<std::vector<std::string>>& paths, std::vector<std::string>& path) {
    path.push_back(iter->m_data);
    
    if (mins > m_maxMins) {
        return;
    } else if (iter->m_data == "Railstation" && path.size() != 1) {
        paths.push_back(path);
        return;
    }

    for (Edge<Vertex<std::string>> edge : iter->m_edges) {
        FindAllPossiblePaths(edge.m_to, mins + edge.m_weight, paths, path);
        path.pop_back();
    }
}

std::vector<std::string> CityTrip::FindBestRoute() {
    Vertex<std::string>* iter = m_graph.GetVertex("Railstation");
    std::vector<std::vector<std::string>> answers{ };
    std::vector<std::string> currPath{ };

    FindAllPossiblePaths(iter, 0, answers, currPath);

    std::vector<std::string> result{ };
    std::uint32_t destinations{ 0 };

    if (answers.size() == 0) {
        return std::vector<std::string>{ "Railstation" };
    }

    for (std::vector<std::string> vec : answers) {
        std::uint32_t currDestinations = CountDestinations(vec);

        if (currDestinations > destinations) {
            result = vec;
            destinations = currDestinations;
        }
    }

    return result;
}

std::uint32_t CityTrip::CountDestinations(const std::vector<std::string>& destinations) const {
    std::vector<std::string> dests{ };

    for (auto elem : destinations) {
        if (std::find(dests.begin(), dests.end(), elem) == dests.end()) {
            dests.push_back(elem);
        }
    }
    
    return dests.size();
}
