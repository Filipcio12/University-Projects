#include <string>
#include <iostream>

class Book {
    public:
        std::string author;
        std::string category;
        unsigned int numOfPages;
        bool onBookshelf;
        
        Book() {}

        Book(std::string a, std::string c, unsigned int num, bool status) : 
            author(a), category(c), numOfPages(num), onBookshelf(status) {}

        friend std::ostream& operator<<(std::ostream& os, const Book& b) 
        {
            std::string status = (b.onBookshelf) ? "on bookshelf" : "borrowed";
            os << b.author << ", " << b.category << ", " << b.numOfPages << ", " << status;
            return os;
        }
};