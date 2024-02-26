#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// Custom exception for when a collection cannot accept more elements
class Collection_Overflow_Exception : public std::runtime_error {
public:
    Collection_Overflow_Exception() : std::runtime_error("Maximum capacity reached. No additional elements can be added.") {}
};

// Custom exception for when attempting to remove an element from an empty collection
class Collection_Underflow_Exception : public std::runtime_error {
public:
    Collection_Underflow_Exception() : std::runtime_error("Collection is empty. Removal is not possible.") {}
};

// Template class for managing a collection of entertainment items
template <typename T>
class EntertainmentCollection {
public:
    // Initializes an empty collection
    EntertainmentCollection() : item_count_(0) {}

    // Adds an item to the collection if there's space
    void insert_item(const T& new_item) {
        if (item_count_ < MAX_CAPACITY) {
            library_items_[item_count_] = new_item;
            item_count_++;
        }
        else {
            throw Collection_Overflow_Exception();
        }
    }

    // Removes and returns the last item added if the collection isn't empty
    T remove_item() {
        if (item_count_ > 0) {
            item_count_--;
            return library_items_[item_count_];
        }
        else {
            throw Collection_Underflow_Exception();
        }
    }

    // Returns the current item count
    int getCurrentItemCount() const {
        return item_count_;
    }

private:
    static const int MAX_CAPACITY = 10; // Maximum items allowed
    T library_items_[MAX_CAPACITY];      // Array to store items
    int item_count_;                     // Current number of items
};

// Represents a video game with a title and genre
class VideoGame {
public:
    VideoGame(std::string name = "", string category = "") : name_(name), category_(category) {}

    // Accessor for game title
    std::string getName() const {
        return name_;
    }

    // Accessor for game genre
    string getCategory() const {
        return category_;
    }

private:
    std::string name_;   // Game title
    string category_;    // Game genre
};

int main() {
    EntertainmentCollection<VideoGame> VideoGameLibrary;
    int user_input;

    while (true) {
        cout << "Options:" << endl;
        cout << "1 - Add a Video Game." << endl;
        cout << "2 - Remove a Video Game." << endl;
        cout << "3 - Display total Video Games." << endl;
        cout << "4 - Exit." << endl;
        cout << "Select an option: ";
        cin >> user_input;

        try {
            switch (user_input) {
            case 1: {
                std::string game_title;
                string game_genre;
                cout << "Game Title: ";
                cin.ignore(); // Clears the input buffer
                getline(cin, game_title);
                cout << "Game Genre: ";
                cin >> game_genre;

                // Creates and adds a new VideoGame object to the library
                VideoGame newGame(game_title, game_genre);
                VideoGameLibrary.insert_item(newGame);
                break;
            }
            case 2: {
                // Removes a VideoGame from the library and shows its details
                VideoGame removed_game = VideoGameLibrary.remove_item();
                cout << "Game removed: " << removed_game.getName() << " - " << removed_game.getCategory() << endl;
                break;
            }
            case 3: {
                // Shows the number of VideoGames in the library
                cout << "Total Video Games: " << VideoGameLibrary.getCurrentItemCount() << endl;
                break;
            }
            case 4:
                // Exits the loop and ends the program
                return 0;
            default:
                cout << "Please enter a valid option." << endl;
                break;
            }
        }
        catch (const Collection_Overflow_Exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
        catch (const Collection_Underflow_Exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    return 0;
}
