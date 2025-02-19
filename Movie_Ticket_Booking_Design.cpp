#include <bits/stdc++.h>
#include <ctime>

using namespace std;

class Seat
{
public:
  int seatNumber;
  string category;
  double price;
  bool isBooked;

  Seat(int number, string cat, double p) : seatNumber(number), category(cat), price(p), isBooked(false) {}
};

class User
{
public:
  string username;
  string password;
  string role;
  vector<string> bookings;

  User() {}
  User(string uname, string pass, string r) : username(uname), password(pass), role(r) {}

  void addBooking(string bookingDetails)
  {
    bookings.push_back(bookingDetails);
  }

  void viewBookings()
  {
    if (bookings.empty())
    {
      cout << "No bookings found.\n";
      return;
    }
    cout << "Your Bookings:\n";
    for (const auto &booking : bookings)
    {
      cout << booking << "\n";
    }
  }
};

class Movie
{
public:
  string title;
  string genre;
  string language;
  int duration;

  Movie() {}
  Movie(string t, string g, string lang, int d)
      : title(t), genre(g), language(lang), duration(d) {}
};

class Screen
{
public:
  int screenID;
  int totalSeats;
  double standardPrice;
  double premiumPrice;
  map<string, vector<Seat>> showtimeSeats;

  Screen() {}
  Screen(int id, int seats, double standardP) : screenID(id), totalSeats(seats), standardPrice(standardP), premiumPrice(standardP + 100) {}

  void addShowtime(string movieTitle, string showtime)
  {
    if (showtimeSeats.find(showtime) == showtimeSeats.end())
    {
      vector<Seat> seats;
      for (int i = 1; i <= totalSeats; i++)
      {
        string category = (i <= 50) ? "Standard" : "Premium"; // First 50 seats are Standard, rest are Premium
        double price = (category == "Standard") ? standardPrice : premiumPrice;
        seats.push_back(Seat(i, category, price));
      }
      showtimeSeats[showtime] = seats;
      cout << "Showtime " << showtime << " for " << movieTitle << " added to Screen " << screenID << ".\n";
    }
    else
    {
      cout << "Showtime already exists!\n";
    }
  }

  bool isSeatAvailable(string showtime, int seatNumber)
  {
    if (showtimeSeats.find(showtime) != showtimeSeats.end() && seatNumber > 0 && seatNumber <= totalSeats)
    {
      return !showtimeSeats[showtime][seatNumber - 1].isBooked;
    }
    return false;
  }

  void bookSeat(string showtime, int seatNumber)
  {
    if (showtimeSeats.find(showtime) != showtimeSeats.end() && seatNumber > 0 && seatNumber <= totalSeats)
    {
      showtimeSeats[showtime][seatNumber - 1].isBooked = true;
    }
  }

  void cancelSeat(string showtime, int seatNumber)
  {
    if (showtimeSeats.find(showtime) != showtimeSeats.end() && seatNumber > 0 && seatNumber <= totalSeats)
    {
      showtimeSeats[showtime][seatNumber - 1].isBooked = false;
    }
  }

  double getSeatPrice(string showtime, int seatNumber)
  {
    if (showtimeSeats.find(showtime) != showtimeSeats.end() && seatNumber > 0 && seatNumber <= totalSeats)
    {
      return showtimeSeats[showtime][seatNumber - 1].price;
    }
    return 0.0;
  }
};

class Theater
{
public:
  string name;
  string location;
  map<int, Screen> screens;

  Theater() {}
  Theater(string n, string loc) : name(n), location(loc) {}

  void addScreen(int screenID, int totalSeats, double standardPrice)
  {
    screens[screenID] = Screen(screenID, totalSeats, standardPrice);
  }

  int getScreenIDForShowtime(string movieTitle, string showtime)
  {
    for (const auto &screen : screens)
    {
      if (screen.second.showtimeSeats.find(showtime) != screen.second.showtimeSeats.end())
      {
        return screen.first;
      }
    }
    return -1;
  }
};

class BookingSystem
{
private:
  map<string, User> users;
  vector<Movie> movies;
  map<string, Theater> theaters;
  User *loggedInUser;

public:
  BookingSystem()
  {
    loggedInUser = nullptr;
    srand(time(0));
  }

  bool isLoggedIn()
  {
    return loggedInUser != nullptr;
  }

  void registerUser(string username, string password, string role)
  {

    if (role != "Admin" && role != "Customer")
    {
      cout << "Error: Only 'Admin' and 'Customer' roles are allowed for registration.\n";
      return;
    }

    if (users.find(username) != users.end())
    {
      cout << "Username already exists!\n";
      return;
    }

    users[username] = User(username, password, role);
    cout << "User registered successfully!\n";
  }

  bool login(string username, string password)
  {
    if (users.find(username) == users.end())
    {
      cout << "User not found!\n";
      return false;
    }
    if (users[username].password != password)
    {
      cout << "Incorrect password!\n";
      return false;
    }
    loggedInUser = &users[username];
    cout << "Login successful! Welcome, " << loggedInUser->username << " (" << loggedInUser->role << ")\n";
    return true;
  }

  void logout()
  {
    if (!loggedInUser)
    {
      cout << "No user is logged in!\n";
      return;
    }
    cout << "User " << loggedInUser->username << " logged out.\n";
    loggedInUser = nullptr;
  }

  void addTheater()
  {
    if (!isLoggedIn() || loggedInUser->role != "Admin")
    {
      cout << "Only Admins can add theaters!\n";
      return;
    }

    string theaterName, location;
    int screenID, totalSeats;
    double standardPrice;

    cout << "Enter theater name: ";
    getline(cin, theaterName);
    cout << "Enter theater location: ";
    getline(cin, location);

    if (theaters.find(theaterName) != theaters.end())
    {
      cout << "Theater already exists!\n";
      return;
    }

    theaters[theaterName] = Theater(theaterName, location);

    cout << "Enter screen ID: ";
    cin >> screenID;
    cout << "Enter total seats: ";
    cin >> totalSeats;
    cout << "Enter standard seat price: ";
    cin >> standardPrice;
    cin.ignore();

    theaters[theaterName].addScreen(screenID, totalSeats, standardPrice);
    cout << "Theater and screen added successfully!\n";
  }

  void viewTheaters()
  {
    if (theaters.empty())
    {
      cout << "No theaters found.\n";
      return;
    }
    cout << "Theaters:\n";
    for (const auto &theater : theaters)
    {
      cout << "Theater Name: " << theater.second.name << ", Location: " << theater.second.location << "\n";
      for (const auto &screen : theater.second.screens)
      {
        cout << "  Screen ID: " << screen.first << ", Total Seats: " << screen.second.totalSeats << "\n";
      }
    }
  }

  void addMovie()
  {
    if (!isLoggedIn() || loggedInUser->role != "Admin")
    {
      cout << "Only Admins can add movies!\n";
      return;
    }

    string title, genre, language, theaterName, showtime;
    int duration, screenID;

    cout << "Enter Theater Name: ";
    getline(cin, theaterName);

    if (theaters.find(theaterName) == theaters.end())
    {
      cout << "Error: No such theater exists. Add a theater first!\n";
      return;
    }

    cout << "Enter Screen ID: ";
    cin >> screenID;
    cin.ignore();

    if (theaters[theaterName].screens.find(screenID) == theaters[theaterName].screens.end())
    {
      cout << "Error: Screen ID not found in the selected theater!\n";
      return;
    }

    cout << "Enter movie title: ";
    getline(cin, title);
    cout << "Enter genre: ";
    getline(cin, genre);
    cout << "Enter language: ";
    getline(cin, language);
    cout << "Enter duration (minutes): ";
    cin >> duration;
    cin.ignore();
    cout << "Enter showtime (e.g., 18:30): ";
    getline(cin, showtime);
    if (!isShowtimeValid(showtime))
    {
      cout << "Error: Enter valid time.\n";
      return;
    }
    movies.push_back(Movie(title, genre, language, duration));

    theaters[theaterName].screens[screenID].addShowtime(title, showtime);

    cout << "Movie and showtime added successfully!\n";
  }

  bool processPayment(double amount)
  {
    cout << "Processing payment of Rs" << amount << "...\n";
    bool paymentSuccess = (rand() % 2 == 0);
    if (paymentSuccess)
    {
      cout << "Payment successful!\n";
    }
    else
    {
      cout << "Payment failed!\n";
    }
    return paymentSuccess;
  }

  void bookTicket()
  {
    if (!isLoggedIn() || loggedInUser->role != "Customer")
    {
      cout << "Only Customers can book tickets!\n";
      return;
    }

    string movieTitle, theaterName, showtime;
    int seatNumber;

    cout << "Enter Theater Name: ";
    getline(cin, theaterName);

    if (theaters.find(theaterName) == theaters.end())
    {
      cout << "Error: Theater does not exist!\n";
      return;
    }

    cout << "Enter Movie Title: ";
    getline(cin, movieTitle);
    cout << "Enter Showtime: ";
    getline(cin, showtime);

    cout << "Enter Seat Number: ";
    if (!(cin >> seatNumber))
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Error: Invalid seat number. Please enter a valid integer.\n";
      return;
    }
    cin.ignore();

    int screenID = theaters[theaterName].getScreenIDForShowtime(movieTitle, showtime);
    if (screenID == -1)
    {
      cout << "Error: No screen found for the selected movie and showtime!\n";
      return;
    }

    if (seatNumber < 1 || seatNumber > theaters[theaterName].screens[screenID].totalSeats)
    {
      cout << "Error: Seat number is out of range!\n";
      return;
    }

    if (!theaters[theaterName].screens[screenID].isSeatAvailable(showtime, seatNumber))
    {
      cout << "Error: Seat already booked!\n";
      return;
    }

    double ticketPrice = theaters[theaterName].screens[screenID].getSeatPrice(showtime, seatNumber);
    string seatCategory = theaters[theaterName].screens[screenID].showtimeSeats[showtime][seatNumber - 1].category;

    if (!processPayment(ticketPrice))
    {
      cout << "Booking failed due to payment issue. Seat is still available.\n";
      return;
    }

    theaters[theaterName].screens[screenID].bookSeat(showtime, seatNumber);

    string bookingDetails = "Movie: " + movieTitle + ", Theater: " + theaterName +
                            ", Screen: " + to_string(screenID) + ", Showtime: " + showtime +
                            ", Seat: " + to_string(seatNumber) + ", Category: " + seatCategory +
                            ", Price: Rs" + to_string(ticketPrice);
    loggedInUser->addBooking(bookingDetails);

    cout << "Booking confirmed! Payment successful.\n";
    cout << "Booking Details: " << bookingDetails << "\n";
  }

  void cancelBooking()
  {
    if (!isLoggedIn() || loggedInUser->role != "Customer")
    {
      cout << "Only Customers can cancel bookings!\n";
      return;
    }

    if (loggedInUser->bookings.empty())
    {
      cout << "No bookings to cancel.\n";
      return;
    }

    cout << "Your Bookings:\n";
    for (int i = 0; i < loggedInUser->bookings.size(); i++)
    {
      cout << i + 1 << ". " << loggedInUser->bookings[i] << "\n";
    }

    int choice;
    cout << "Enter the number of the booking you want to cancel: ";
    if (!(cin >> choice))
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Error: Invalid choice. Please enter a valid integer.\n";
      return;
    }
    cin.ignore();

    if (choice < 1 || choice > loggedInUser->bookings.size())
    {
      cout << "Invalid choice.\n";
      return;
    }

    string canceledBooking = loggedInUser->bookings[choice - 1];

    size_t theaterPos = canceledBooking.find("Theater: ");
    size_t screenPos = canceledBooking.find("Screen: ");
    size_t showtimePos = canceledBooking.find("Showtime: ");
    size_t seatPos = canceledBooking.find("Seat: ");

    if (theaterPos == string::npos || screenPos == string::npos || showtimePos == string::npos || seatPos == string::npos)
    {
      cout << "Error: Invalid booking format.\n";
      return;
    }

    string theaterName = canceledBooking.substr(theaterPos + 9, canceledBooking.find(',', theaterPos) - (theaterPos + 9));
    int screenID = stoi(canceledBooking.substr(screenPos + 8, canceledBooking.find(',', screenPos) - (screenPos + 8)));
    string showtime = canceledBooking.substr(showtimePos + 10, canceledBooking.find(',', showtimePos) - (showtimePos + 10));
    int seatNumber = stoi(canceledBooking.substr(seatPos + 6, canceledBooking.find(',', seatPos) - (seatPos + 6)));

    if (theaters.find(theaterName) != theaters.end() &&
        theaters[theaterName].screens.find(screenID) != theaters[theaterName].screens.end())
    {
      theaters[theaterName].screens[screenID].cancelSeat(showtime, seatNumber);
      cout << "Seat " << seatNumber << " for " << showtime << " has been released.\n";
    }
    else
    {
      cout << "Error: Theater or screen not found.\n";
    }

    double refundAmount = calculateRefund(showtime, seatNumber);
    cout << "Refund of Rs" << refundAmount << " processed.\n";

    loggedInUser->bookings.erase(loggedInUser->bookings.begin() + choice - 1);

    cout << "Booking canceled: " << canceledBooking << "\n";
  }

  double calculateRefund(const string &showtime, int seatNumber)
  {

    time_t now = time(0);
    tm *currentTime = localtime(&now);

    int showHour, showMinute;
    sscanf(showtime.c_str(), "%d:%d", &showHour, &showMinute);

    int timeDifference = (showHour - currentTime->tm_hour) * 60 + (showMinute - currentTime->tm_min);

    if (timeDifference > 0 && timeDifference <= 60) // Within 1 hour of showtime
    {
      return 0.5;
    }
    else
    {
      return 0.0;
    }
  }
  bool isShowtimeValid(const string &showtime)
  {
    int hours, minutes;
    if (sscanf(showtime.c_str(), "%d:%d", &hours, &minutes) != 2 ||
        hours < 0 || hours >= 24 || minutes < 0 || minutes >= 60)
    {
      return false;
    }
    return true;
  }

  void searchMovies()
  {
    string query;
    cout << "Enter movie title, genre, or location to search: ";
    getline(cin, query);

    cout << "Search Results:\n";
    for (const auto &theater : theaters)
    {
      for (const auto &screen : theater.second.screens)
      {
        for (const auto &showtime : screen.second.showtimeSeats)
        {
          for (const auto &movie : movies)
          {
            if (movie.title.find(query) != string::npos ||
                movie.genre.find(query) != string::npos ||
                theater.second.location.find(query) != string::npos)
            {
              cout << "Movie: " << movie.title << ", Theater: " << theater.second.name
                   << ", Location: " << theater.second.location << ", Screen: " << screen.first
                   << ", Showtime: " << showtime.first << "\n";
            }
          }
        }
      }
    }
  }

  void viewBookings()
  {
    if (!isLoggedIn())
    {
      cout << "Please log in to view bookings.\n";
      return;
    }
    loggedInUser->viewBookings();
  }
};

int main()
{
  BookingSystem system;
  cout << "Movie Ticket Booking System initialized!\n";

  int choice;
  string username, password, role;

  while (true)
  {
    cout << "\n1. Register\n2. Login\n3. Logout\n4. Add Theater (Admin)\n5. Book Ticket (Customer)\n6. Add Movie (Admin)\n7. View Bookings\n8. Cancel Booking\n9. Search Movies\n10. View Theaters\n11. Exit\nChoose an option: ";
    if (!(cin >> choice))
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Error: Invalid choice. Please enter a valid integer.\n";
      continue;
    }
    cin.ignore();

    switch (choice)
    {
    case 1:
      cout << "Enter username: ";
      getline(cin, username);
      cout << "Enter password: ";
      getline(cin, password);
      cout << "Enter role (Admin/Customer): ";
      getline(cin, role);
      system.registerUser(username, password, role);
      break;
    case 2:
      cout << "Enter username: ";
      getline(cin, username);
      cout << "Enter password: ";
      getline(cin, password);
      system.login(username, password);
      break;
    case 3:
      system.logout();
      break;
    case 4:
      system.addTheater();
      break;
    case 5:
      system.bookTicket();
      break;
    case 6:
      system.addMovie();
      break;
    case 7:
      system.viewBookings();
      break;
    case 8:
      system.cancelBooking();
      break;
    case 9:
      system.searchMovies();
      break;
    case 10:
      system.viewTheaters();
      break;
    case 11:
      cout << "Exiting system. Goodbye!\n";
      return 0;
    default:
      cout << "Invalid choice. Try again.\n";
    }
  }

  return 0;
}