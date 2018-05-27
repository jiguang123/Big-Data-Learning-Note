// 12.3 You're testing a method canMoveTo(int x, int y), which is a member method of a class Piece. Piece represents a piece in the chess game. How would you perform the testing?
// Answer:
//	1. Apparently every kind of pieces in chess has its own rule of moving. So the class Piece must be an abstract class, which will inherited by various kinds of specific pieces.
//	2. You always have to check if (x, y) is out of border. So this will be included in base class Piece.
//	3. Every piece has its own rule of moving, so the derived class will have to implement its own rule(), which will be executed by canMoveTo().
//	4. The class Piece should look like this:
//	5. The base class will have an interface named rule(), which will be implemented by derived class.
class Piece {
public:
	virtual bool canMoveTo(int x, int y);
private:
	// ...
	virtual bool rule(int x, int y) = 0;
};
//	6. Thus, the test should cover two parts:
//		6.a. The coordinates (x, y) will cover in-bound and out-of-bound cases.
//		6.b. Every rule() function will be executed inside canMoveTo(), thus the test will also be included here.