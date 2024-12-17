#include "DisasterRecovery.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

using namespace std;

void DisasterRecovery::processCommit(const string& inputLine) {
    istringstream ss(inputLine);
    Commit commit;

    // input exampe: id 38024 timestamp 74820 foo.py ac819f bar.py 0d82b9
    //add validation 
    string idToken, timeToken;
    if (!(ss >> idToken >> commit.id >> timeToken >> commit.timeStamp)) {
        return; // Skip malformed entries
    }

    if (!unionFind.addCommit(commit.id)) 
        return; //discared malformed entries. commit id need to be unique.

    string filePath, opaqueId;
    while (ss >> filePath >> opaqueId) {
        commit.files.emplace_back(filePath, opaqueId); // emplace to avoid expensive copying
    }

    //proccess all file in the current entry.
    for (const auto& file : commit.files) {
        const string& path = file.getPath();
        const string& id = file.getOpaqueID();

        //matching path + opaqueId joins commit id to a repository   
        // add the new file the repo if not exists, if it does add commit to the matching repo 
        if (fileToRepo[path].count(id) == 0) {
            fileToRepo[path][id] = commit.id;
        } else {
            int existingCommit = fileToRepo[path][id];
            unionFind.unionSets(commit.id, existingCommit);
        }
        // checking ambiguity for every file added
        // loop on all memebers of the 2nd level map that matches file path. 
        for (const auto& [opaqueId,commitID] : fileToRepo[path]) {
            if (opaqueId != id && unionFind.find(commitID) == unionFind.find(commit.id)  ) {
                throw logic_error("AMBIGUOUS INPUT!");
            }
        }

    }

    commits.push_back(std::move(commit));
}

//build the repositories, the repo's id's are the unique roots of the unionFind class
void DisasterRecovery::buildRepositories() {
    for (auto& commit : commits) {
        int repoId = unionFind.find(commit.id);
        repositories[repoId].push_back(std::move(commit)); //move to avoid expensive copying
    }

    


    for (auto& [repoId, repoCommits] : repositories) {
        sort(repoCommits.begin(), repoCommits.end(), [](const Commit& a, const Commit& b) {
            return a.timeStamp < b.timeStamp || (a.timeStamp == b.timeStamp && a.id < b.id);
        });
    }
}

void DisasterRecovery::handleQueries(int R) {
    for (int i = 0; i < R; ++i) {
        uint64_t startTime, endTime;
        string filePath, opaqueId;
        cin >> startTime >> endTime >> filePath >> opaqueId;

        vector<int> result;
        if (fileToRepo[filePath].count(opaqueId) > 0) {
            int repoId = unionFind.find(fileToRepo[filePath][opaqueId]);
            for (const auto& commit : repositories[repoId]) {
                if (commit.timeStamp >= startTime && commit.timeStamp <= endTime) {
                    result.push_back(commit.id);
                }
            }
        }

        sort(result.begin(), result.end());
        for (int id : result) {
            cout << id << " ";
        }
        cout << endl;
    }
}

void DisasterRecovery::run() {
    cin >> N;
    cin.ignore();

    for (size_t i = 0; i < N; ++i) {
        string inputLine;
        getline(cin, inputLine);
        processCommit(inputLine);
    }

    buildRepositories();

    int R;
    cin >> R;
    cin.ignore();
    handleQueries(R);
}