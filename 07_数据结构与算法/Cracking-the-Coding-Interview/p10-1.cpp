// 10.1 Suppose you're to design the backend part of a system, which provides queries of real-time stock prices. How would you do it?
// Answer:
//	Go and search "GOOG" on Google or Baidu, you'll get the real-time stock price of Google. The data transferring is best done with AJAX to the frontend, which can greatly save the amount of data transferred.
//	As for the backend part, you have to use some techniques to store the data:
//		1. SQL database, easy for various kinds of structured queries. You won't expose the direct SQL API to external users because it is not safe. Write a wrapper with the web programming language.
//			Strength: Ability to provide more information than you expected.
//			Weakness: Not so agile, if the data structure changes. Altering a SQL table is always expensive.
//		2. XML files, a good way to store structured data. Good performance when the data scale is small or medium.
//			Strength: Agile, easy to modify the schema. Regenerating the XML file is usually easy with script languages such as python.
//			Weakness: Not suitable for large data scale, as you have to parse everything in the XML only to find an item inside.
//		3. No-SQL database
//			Strength: suitable for large scale, high concurrency, flexible with data schema changes.
//			Weakness: Don't know yet, maybe more space usage.
int main()
{
	return 0;
}