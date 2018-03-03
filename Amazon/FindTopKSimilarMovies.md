Write an algorithm to return the top-k similar movies of the input movie. Returned movies should not have the input movie.

If the similar movies are less than k, just return all of them. 

Here is the defination of ```Movie``` class.

```cpp
class Movie {
private:
	int m_id;
	double m_rating;
	vector<Movie*> m_similar_movies;
public:
	int getId() const { return m_id; }
	double getRating() const { return m_rating; }
	vector<Movie*> getSimilarMovies() const { return m_similar_movies; }
};
```

# Solution


```cpp
struct WorseRating {
	bool operator() (const Movie * left, const Movie *right) {
		return left->getRating() < right->getRating();
	}
};

typedef priority_queue<Movie*, vector<Movie*>, WorseRating> BetterRatingPriorityQueue;

vector<Movie*> getTopSimilarMovies(Movie *cur_movie, int k) {
	if (!cur_movie || k <= 0) return vector<Movie*>();

	unordered_set<Movie*> visited;
	queue<Movie*> bfs_queue;
	
	visited.insert(cur_movie);
	bfs_queue.push(cur_movie);

	BetterRatingPriorityQueue better_movie_pq;
	while (!bfs_queue.empty()) {
		Movie *temp_movie = bfs_queue.front();
		bfs_queue.pop();
    
    if (temp_movie != cur_movie) 	{ 
      // Ignore the input movie
      better_movie_pq.push(similar_movie);
    }

		for (Movie* similar_movie : temp_movie->getSimilarMovies()) {
			if (similar_movie) { // Ignore nullptr
				if (visited.count(similar_movie)) continue; // Ignore visited;

				visited.insert(similar_movie);
				bfs_queue.push(similar_movie);
			}
		}
	}

	vector<Movie*> reval;
	while (k > 0 && !better_movie_pq.empty()) {
		reval.emplace_back(better_movie_pq.top());
		better_movie_pq.pop();
    
	}
	return reval;
}

```
