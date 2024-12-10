# Movie-Recomendation-System

C++ Code in Visual Studio Code :

Install MinGW MySYS2 on System then add path on environment to perform C++ Code File

Steps and purpose of functions :
1. int matrix[numUsers][numMovies]:
We use a 2D array to store the ratings matrix, which has a fixed size of numUsers by numMovies.

2. loadRatingsMatrix function:
Reads the CSV file and fills the matrix array.
Takes the number of users (numUsers) and movies (numMovies) as arguments.

3. calculateSimilarity function:
Now takes arrays user1 and user2 and their size to calculate the cosine similarity.

4. predictRating function:
Takes the 2D matrix and iterates over other users to compute a predicted rating for a given movie.

5. recommendMovies function:
Uses a fixed-size array predictions to store the top N movie recommendations for the given user.
Sorts and prints the top N recommended movies based on their predicted ratings.


In this code we use cosine similarity to find similarity of user ratings and also able to recommend movie.

CSV File : 

0,3,0,1,4
4,0,5,1,2
0,1,2,4,0
3,5,4,0,3

Output : 

Recommendations for User 1:
Movie 3: Predicted Rating = 3.96
Movie 1: Predicted Rating = 3.51
RMSE: 0.00
