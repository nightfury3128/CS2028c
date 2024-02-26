#include <iostream>
#include <string>
#include <stdexcept>

// Exception class for a situation where the shelf is at capacity
class Full_exception : public std::runtime_error {
public:
    Full_exception() : std::runtime_error("Cannot add more items; shelf is at capacity.") {}
};

// Exception class for attempting to access an item from an empty shelf
class Empty_exception : public std::runtime_error {
public:
    Empty_exception() : std::runtime_error("Cannot remove items; shelf is empty.") {}
};

// Represents a Movie with a title and release year
class Movie {
public:
    Movie(std::string title = "", int release_year = 0) : title_(title), release_year_(release_year) {}

    std::string getTitle() const {
        return title_;
    }

    int getRelease_Year() const {
        return release_year_;
    }

private:
    std::string title_;
    int release_year_;
};

// Manages a collection of Movies
class Movie_Shelf {
public:
    Movie_Shelf() : movie_count_(0) {}

    void add_movie(const Movie& Movie) {
        if (movie_count_ < max_capacity) {
            Movies_[movie_count_] = Movie;
            movie_count_++;
        }
        else {
            throw Full_exception();
        }
    }

    Movie remove_movie() {
        if (movie_count_ > 0) {
            return Movies_[--movie_count_];
        }
        else {
            throw Empty_exception();
        }
    }

    int count_movies() const {
        return movie_count_;
    }

private:
    static const int max_capacity = 3;
    Movie Movies_[max_capacity];
    int movie_count_;
};

int main() {
    Movie_Shelf shelf;
    int user_input;

    while (true) {
        std::cout << "1. Add a Movie to the shelf.\n";
        std::cout << "2. Remove a Movie from the shelf.\n";
        std::cout << "3. Display the number of Movies on the shelf.\n";
        std::cout << "4. Exit.\n";
        std::cout << "Select an option: ";
        std::cin >> user_input;

        try {
            switch (user_input) {
            case 1: {
                std::string title;
                int year;
                std::cout << "Movie title: ";
                std::cin.ignore();
                std::getline(std::cin, title);
                std::cout << "Release year: ";
                std::cin >> year;

                Movie Movie(title, year);
                shelf.add_movie(Movie);
                break;
            }
            case 2: {
                Movie removed_movie = shelf.remove_movie();
                std::cout << "Removed: " << removed_movie.getTitle() << " (" << removed_movie.getRelease_Year() << ")\n";
                break;
            }
            case 3:
                std::cout << "Movies on shelf: " << shelf.count_movies() << std::endl;
                break;
            case 4:
                return 0;
            default:
                std::cout << "Invalid option, try again.\n";
            }
        }
        catch (const Full_exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
        catch (const Empty_exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }

    return 0;
}
