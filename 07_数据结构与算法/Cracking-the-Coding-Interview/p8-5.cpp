// 8.5 Deign a class for an online book reader system.
#include <unordered_map>
using namespace std;

class BookReaderSystem {
public:
	BookReaderSystem() {};
	
	// find a book by its name and read it.
	void readBook(string book_name) {
		Page page;
		
		if (books.find(book_name) != books.end()) {
			i = 0;
			// load the book page by page
			while (page = loadPage(books[book_name], i, page)) {
				displayPage(page);
				++i;
			}
		}
	};
	
	~BookReaderSystem() {
		books.clear();
	};
private:
	// the K-V database
	unordered_map<string, Book> books;
	// load one page from a book
	bool loadPage(Book &book, int page_no, Page &page);
	// display this page
	void displayPage(Page &page);
};