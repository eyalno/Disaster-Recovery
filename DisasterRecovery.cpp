#include "DisasterRecovery.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>


using namespace std;

void DisasterRecovery::processCommit(const string& inputLine) {
    istringstream ss(inputLine);
    Commit commit;
    
    string idToken, timeToken;
    if (!(ss >> idToken >> commit.id >> timeToken >> commit.timeStamp)) {
        return; // discared malformed entries
    }

    if (!unionFind.addCommit(commit.id)) 
        return; //discared malformed entries: commit id need to be unique.

    string filePath, opaqueId;
    while (ss >> filePath >> opaqueId) {
        commit.files.emplace_back(filePath, opaqueId); // emplace to avoid expensive copying
    }

    //proccess all file in the current entry.
    for (const auto& file : commit.files) {
        const string& path = file.getPath();
        const string& id = file.getOpaqueID();

        //new file introduced. add to fileRepo with the commit id of the entry
        if (pathIdCommit[path].count(id) == 0) { //all files will be inserted here. 
            pathIdCommit[path][id] = commit.id; 
            idPathCommit[id][path] = commit.id; //reverse to check for ambiguity  
        } else {//the file is already belongs to another commit so we join both commits
            int existingCommit = pathIdCommit[path][id];
            unionFind.unionSets(commit.id, existingCommit);
        }

        // checking ambiguity for every file we try to add 
        //we added the file now finding all connected other opaque. if they are in the same repo/set = Ambiguity
        for (const auto& [opaqueId,commitID] : pathIdCommit[path]) {
            if (opaqueId != id && unionFind.find(commitID) == unionFind.find(commit.id)) {
                throw logic_error("AMBIGUOUS INPUT!");
            }
        }
        //checking ambiguity for opaqueId -> path
        for (const auto& [otherPath,commitID] : idPathCommit[id]) {
            if (otherPath != path && unionFind.find(commitID) == unionFind.find(commit.id)) {
                throw logic_error("AMBIGUOUS INPUT!");
            }
        }
    }

    commits.push_back(std::move(commit));
}

//build the repositories, the repo's id's are the unique roots of the unionFind class
void DisasterRecovery::buildRepositories() {
    for (auto& commit : commits) {
        int repoId = unionFind.find(commit.id); //the unionFind root is the repo id 
        repositories[repoId].push_back(std::move(commit)); //move to avoid expensive copying
    }
    //building the newly organized repositiry increasing order of timeStamp then id
    for (auto& [repoId, repoCommits] : repositories) {
        sort(repoCommits.begin(), repoCommits.end(), [](const Commit& a, const Commit& b) {
            return a.timeStamp < b.timeStamp || (a.timeStamp == b.timeStamp && a.id < b.id);
        });
    }
}

void DisasterRecovery::handleQueries(int R, ifstream & inputFile) {
    for (int i = 0; i < R; ++i) {
        uint64_t startTime, endTime;
        string filePath, opaqueId;
        inputFile >> startTime >> endTime >> filePath >> opaqueId;

        vector<int> result;
        if (pathIdCommit[filePath].count(opaqueId) > 0) {
            int repoId = unionFind.find(pathIdCommit[filePath][opaqueId]);//root
            for (const auto& commit : repositories[repoId]) {
                if (commit.timeStamp >= startTime && commit.timeStamp <= endTime) {
                    result.push_back(commit.id);
                }
            }
        }

        for (int id : result) {
            cout << id << " ";
        }
        cout << endl;
    }
}

void DisasterRecovery::run() {

    std::ifstream inputFile("input.txt");
    if (!inputFile) {
        throw logic_error("Error: Could not open input.txt");
    }

    int N;
    inputFile >> N;
    inputFile.ignore();

    for (size_t i = 0; i < N; ++i) {
        string inputLine;
        getline(inputFile, inputLine);
        processCommit(inputLine);
    }

    buildRepositories();

    int R;
    inputFile >> R;
    inputFile.ignore();

    handleQueries(R,inputFile);
}