// 8.6 Design data structure to represent pieces in jigsaw puzzle. If possible please design an algorithm to solve it.
// I'll use the struct below to represent a piece, which has four sides, each one of which is either concave, convex or plain.
// And they must have some patterns on them, which can be considered as images.
// Solving a jigsaw can be done with DFS, which can be O(n!) in time scale, where n is total number of pieces.
// A possibl way is to do it in diagonal manner, starting from the left top corner.
// Like this:
// 0 1 2 3
// 1 2 3 .
// 2 3 ...
// 3 .....
// When doing the search, you have to check if a piece can be fit into a targetted position.
// a method fitsWith() will be used, parameters will included two pieces and a direction.
// For example, fitsWith(piece1, piece2, BOTTOM) means if piece2 fits on the bottom of piece1.
struct JigsawPuzzlePiece {
	// left, top, right, bottom
	// -1 for concave, +1 for convex, 0 for plain
	int side[4];
	Image *image;
};
