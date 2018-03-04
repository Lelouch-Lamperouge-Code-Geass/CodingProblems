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

If we use max-heap, we need to store all the similar movies in it. 

If we use min-heap, we can pop the worst rating movie out of it when its size is more than k. Just remember to after adding its items into reval vector, we need reverse the order of reval in order to get movies sorted from higher to lower rating.

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

struct BetterRating {
	bool operator() (const Movie * left, const Movie *right) {
		return left->getRating() > right->getRating();
	}
};

typedef priority_queue<Movie*, vector<Movie*>, BetterRating> RatingMinHeap;

vector<Movie*> getTopSimilarMovies(Movie *cur_movie, int k) {
	if (!cur_movie || k <= 0) return vector<Movie*>();

	unordered_set<Movie*> visited;
	queue<Movie*> bfs_queue;

	visited.insert(cur_movie);
	bfs_queue.push(cur_movie);

	RatingMinHeap rating_min_heap;
	while (!bfs_queue.empty()) {
		Movie *temp_movie = bfs_queue.front();
		bfs_queue.pop();

		if (temp_movie != cur_movie) { // Ignore the input movie
			rating_min_heap.push(temp_movie);
			
			if (rating_min_heap.size() > k) {
				// We only need k items in this min-heap.
				rating_min_heap.pop(); // Pop the worst rating movie out
			}
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
	while (k > 0 && !rating_min_heap.empty()) {
		reval.emplace_back(rating_min_heap.top());
		rating_min_heap.pop();

	}
	std::reverse(reval.begin(), reval.end());
	return reval;
}
```
