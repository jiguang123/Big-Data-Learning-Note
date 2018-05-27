// 10.2 Describe how you would design the data structure for people in social network. How would you determine the degree of connections between two people.
// Answer:
// Appartently social network involves a lot of graph thoery. It describes the connections between people.
class Person {
	// A lot of data 
	vector<Person *> friends;
};
// Basically every people is a node in the grap.
// For two people, if you want to find out through how many people they're connected, BFS may be a practical way.
// But it's not effiecient enough, double-end BFS will be a little better.
// You may record the list of 2nd degree connections, so you can retrieve 3rd degree connections faster.
// And you surely wouldn't be interested in 10th degree connections, as anyone on this earth may be your 10th degree connection.
// So it's important to limit the connection search to a small scale of no more than 3rd degree.
int main()
{
	return 0;
}