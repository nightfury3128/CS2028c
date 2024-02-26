#include <iostream>
#include <string>

using namespace std;

class Show {
protected:
    string title;
    string genre;

public:
    Show() {
        title = "";
        genre = "";
    }

    Show(const string& _title, const string& _genre) {
        title = _title;
        genre = _genre;
    }

    string getTitle() const {
        return title;
    }

    string getGenre() const {
        return genre;
    }

    void setTitle(const string& newTitle) {
        title = newTitle;
    }
    void setGenre(const string& newGenre) {
        genre = newGenre;
    }

    virtual void Play() {}

    void DE() const {
        cout << "Title: " << title << endl;
        cout << "Genre: " << genre << endl;
        cout << endl;
    }
};

class TVShow : public Show {
private:
    int** episodeList;
    int maxEpisodesPerSeason;
    int totalSeasons;

public:
    TVShow(const string& _title, const string& _genre, int _totalSeasons)
        : Show(_title, _genre), totalSeasons(_totalSeasons) {

        cout << "Enter the maximum number of episodes per season: ";
        cin >> maxEpisodesPerSeason;

        episodeList = new int* [totalSeasons];
        for (int i = 0; i < totalSeasons; ++i) {
            episodeList[i] = new int[maxEpisodesPerSeason];
        }

        for (int i = 0; i < totalSeasons; ++i) {
            for (int j = 0; j < maxEpisodesPerSeason; ++j) {
                episodeList[i][j] = i * maxEpisodesPerSeason + j + 1;
            }
        }
    }

    ~TVShow() {
        for (int i = 0; i < totalSeasons; ++i) {
            delete[] episodeList[i];
        }
        delete[] episodeList;
    }

    void Play() override {
        int seasonNum, episodeNum;
        cout << "Enter the season number (1-" << totalSeasons << "): ";
        cin >> seasonNum;

        if (seasonNum < 1 || seasonNum > totalSeasons) {
            cout << "Invalid season number." << endl;
            return;
        }

        cout << "Enter the episode number (1-" << maxEpisodesPerSeason << "): ";
        cin >> episodeNum;
        if (episodeNum < 1 || episodeNum > maxEpisodesPerSeason) {
            cout << "Invalid episode number." << endl;
            return;
        }

        cout << "Playing season " << seasonNum << ", episode " << episodeNum << ": " << "...." << endl;
    }

    void Details() const {
        Show::DE();
        cout << "Number of Seasons: " << totalSeasons << endl;
        cout << "Maximum number of episodes per season: " << maxEpisodesPerSeason << endl;
        cout << endl;
    }
};

class Movie : public Show {
private:
    string openingSequence;

public:
    Movie(const string& _title, const string& _genre, const string& _openingSequence)
        : Show(_title, _genre), openingSequence(_openingSequence) {}

    string getOpeningCredits() const {
        return openingSequence;
    }

    void setOpeningCredits(const string& _openingSequence) {
        openingSequence = _openingSequence;
    }

    void Play() override {
        cout << "Opening Credits: " << openingSequence << endl;
    }
};

void TestShow(Show* show) {
    show->DE();
    show->Play();
}

int main() {
    while (true) {
        cout << "Choose an option:" << endl;
        cout << "Press 1 for an instance of Movie." << endl;
        cout << "Press 2 for an instance of TV Show." << endl;
        cout << "Press 3 for an instance of a MOVIE declared as a Show." << endl;
        cout << "Press 4 for an instance of a TV Show declared as a Show." << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            string title, genre, credits;
            cout << "Enter title: ";
            cin >> title;
            cout << "Enter genre: ";
            cin >> genre;
            cout << "Enter Opening Credits: ";
            cin >> credits;
            Movie movie(title, genre, credits);
            TestShow(&movie);
        }

        else if (choice == 2) {
            string title, genre;
            int seasons;
            cout << "Enter title: ";
            cin >> title;
            cout << "Enter genre: ";
            cin >> genre;
            cout << "Enter Seasons: ";
            cin >> seasons;
            if (seasons > 0) {
                TVShow show(title, genre, seasons);
                TestShow(&show);
            }
            else {
                cout << "The number of seasons must be greater than 0.";
                break;
            }
        }

        else if (choice == 3) {
            string title, genre, credits;
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter genre: ";
            getline(cin, genre);
            cout << "Enter opening credits: ";
            getline(cin, credits);

            Movie movie(title, genre, credits);
            Show* show = &movie;
            TestShow(show);
        }

        else if (choice == 4) {
            string title, genre;
            int numSeasons;
            cout << "Enter title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter genre: ";
            getline(cin, genre);
            cout << "Enter number of seasons: ";
            cin >> numSeasons;

            if (numSeasons > 0) {
                TVShow tvShow(title, genre, numSeasons);
                TestShow(&tvShow);
            }

            else {
                cout << "The number of seasons must be greater than zero";
                break;
            }
        }
        else {
            break;
        }

        cout << "Do you wish to continue (y/n)? ";
        char cont;
        cin >> cont;
        if (cont != 'y' && cont != 'Y') {
            break;
        }
    }

    return 0;
}
