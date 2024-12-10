#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;


vector<vector<int>> loadRatingsMatrix(const string &filename) {
    vector<vector<int>> matrix;
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        vector<int> row;
        size_t pos = 0;
        while ((pos = line.find(',')) != string::npos) {
            row.push_back(stoi(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }
        row.push_back(stoi(line)); 
        matrix.push_back(row);
    }
    file.close();
    return matrix;
}


double calculateSimilarity(const vector<int> &user1, const vector<int> &user2) {
    double dotProduct = 0, normUser1 = 0, normUser2 = 0;
    for (size_t i = 0; i < user1.size(); i++) {
        if (user1[i] != 0 && user2[i] != 0) { 
            dotProduct += user1[i] * user2[i];
            normUser1 += user1[i] * user1[i];
            normUser2 += user2[i] * user2[i];
        }
    }
    if (normUser1 == 0 || normUser2 == 0) return 0; 
    return dotProduct / (sqrt(normUser1) * sqrt(normUser2));
}


double predictRating(const vector<vector<int>> &matrix, int user, int movie) {
    double weightedSum = 0, similaritySum = 0;
    for (size_t otherUser = 0; otherUser < matrix.size(); otherUser++) {
        if (user != otherUser && matrix[otherUser][movie] != 0) {
            double similarity = calculateSimilarity(matrix[user], matrix[otherUser]);
            weightedSum += similarity * matrix[otherUser][movie];
            similaritySum += abs(similarity);
        }
    }
    return (similaritySum == 0) ? 0 : weightedSum / similaritySum;
}


vector<pair<int, double>> recommendMovies(const vector<vector<int>> &matrix, int user, int topN) {
    vector<pair<int, double>> predictions;
    for (size_t movie = 0; movie < matrix[user].size(); movie++) {
        if (matrix[user][movie] == 0) { // Unrated movie
            double predictedRating = predictRating(matrix, user, movie);
            predictions.push_back({movie, predictedRating});
        }
    }
    sort(predictions.begin(), predictions.end(), [](const auto &a, const auto &b) {
        return a.second > b.second;
    });
    if (predictions.size() > topN) predictions.resize(topN);
    return predictions;
}


double calculateRMSE(const vector<vector<int>> &testMatrix, const vector<vector<int>> &predictedMatrix) {
    double errorSum = 0;
    int count = 0;
    for (size_t i = 0; i < testMatrix.size(); i++) {
        for (size_t j = 0; j < testMatrix[i].size(); j++) {
            if (testMatrix[i][j] != 0) {
                errorSum += pow(testMatrix[i][j] - predictedMatrix[i][j], 2);
                count++;
            }
        }
    }
    return sqrt(errorSum / count);
}


int main() {
    string filename = "ratings.csv"; 
    vector<vector<int>> matrix = loadRatingsMatrix(filename);

    int user = 0; 
    int topN = 3; 

    cout << "Recommendations for User " << user + 1 << ":\n";
    vector<pair<int, double>> recommendations = recommendMovies(matrix, user, topN);
    for (const auto &rec : recommendations) {
        cout << "Movie " << rec.first + 1 << ": Predicted Rating = " << fixed << setprecision(2) << rec.second << "\n";
    }

    vector<vector<int>> testMatrix = matrix; 
    vector<vector<int>> predictedMatrix = matrix; 
    cout << "RMSE: " << calculateRMSE(testMatrix, predictedMatrix) << endl;

    return 0;
}