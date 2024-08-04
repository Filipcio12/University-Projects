#include <iostream>
#include "Map.h"
#include "Book.h"

typedef Map<std::string, Book> Database;

void addEntries(Database& db);
void testAddingSameKey(Database& db);
void testFindNonExistentKey(const Database& db);

int main() 
{
    Database db;
    addEntries(db);
    testAddingSameKey(db);
    testFindNonExistentKey(db);
    return 0;
}

void addEntries(Database& db)
{
    db.add("Pan Tadeusz", Book("Adam Mickiewicz", "epopeja", 434, true));
    db.add("Kordian", Book("Juliusz Słowacki", "dramat", 132, false));
    db.add("Ogniem i miecznem", Book("Henryk Sienkiewicz", "powiesc", 821, true));
    db.add("Lalka", Book("Boleslaw Prus", "powiesc", 530, false));

    std::cout << "Original database:\n" << db << "\n";
}

void testAddingSameKey(Database& db)
{
    db.add("Pan Tadeusz", Book("Mdam Aickiewicz", "epos", 343, false));
    std::cout << "Modified database:\n" << db << "\n";
}

void testFindNonExistentKey(const Database& db)
{
    try {
        Book* bookPtr = db.find("W pustyni i w puszczy");
        std::cout << *bookPtr;
   } catch(Database::KeyNotFound) {
        std::cout << "Exception caught\n";
   }
}