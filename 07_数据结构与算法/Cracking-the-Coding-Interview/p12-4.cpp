// 12.4 How would you load test a webpage, if you're not allowed to use any test tools?
// Answer:
// 	As far as what I've learned, load testing is a testing method which puts the system under limited resources and exposes it to excessive pressure.
//	1. Browser side:
//		1.a. Use a PC with low configuration, but it must sufficient to see the webpage.
//		1.b. Use various browsers to see their different performances.
//		1.c. Open multiple instances of this webpage, see if it fails to respond.
//	2. Server side:
//		2.a. Deploy the web server on a server(maybe a PC) with low configuration.
//		2.b. Try to visit it with multiple clients(many users at the same time).
//		2.c. If the system includes some storage, try to fill it up with POST or GET actions on the webpage.
int main()
{
	return 0;
}