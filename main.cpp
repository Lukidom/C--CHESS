#include <array>
#include <cctype>
#include <iostream>

// Piece categories for a chess board cell.
enum class PieceType {
    None,
    Pawn,
    Rook,
    Knight,
    Bishop,
    Queen,
    King
};

// Side ownership for each piece.
enum class PieceColor {
    None,
    Black,
    White
};

struct Piece {
    PieceType type = PieceType::None;
    PieceColor color = PieceColor::None;

    // Convert piece data into a printable board character.
    char toChar() const {
        if (type == PieceType::None) {
            return '.';
        }

        char symbol = '?';
        switch (type) {
            case PieceType::Pawn:
                symbol = 'P';
                break;
            case PieceType::Rook:
                symbol = 'R';
                break;
            case PieceType::Knight:
                symbol = 'N';
                break;
            case PieceType::Bishop:
                symbol = 'B';
                break;
            case PieceType::Queen:
                symbol = 'Q';
                break;
            case PieceType::King:
                symbol = 'K';
                break;
            case PieceType::None:
                break;
        }

        // Use lowercase letters for black pieces.
        if (color == PieceColor::Black) {
            symbol = static_cast<char>(std::tolower(static_cast<unsigned char>(symbol)));
        }

        return symbol;
    }
};

class Board {
public:
    Board() {
        clear();
    }

    // Reset every cell to empty.
    void clear() {
        for (auto& row : squares_) {
            for (auto& cell : row) {
                cell = {PieceType::None, PieceColor::None};
            }
        }
    }

    // Place all pieces in standard chess starting position.
    void setupInitialPosition() {
        clear();
        placeBackRank(PieceColor::Black, 0);
        placeBackRank(PieceColor::White, 7);

        for (int col = 0; col < 8; ++col) {
            squares_[1][col] = {PieceType::Pawn, PieceColor::Black};
            squares_[6][col] = {PieceType::Pawn, PieceColor::White};
        }
    }

    // Basic move helper: validates bounds, source, and friendly capture.
    bool movePiece(int startRow, int startCol, int endRow, int endCol) {
        if (!isInBounds(startRow, startCol) || !isInBounds(endRow, endCol)) {
            return false;
        }

        Piece& from = squares_[startRow][startCol];
        Piece& to = squares_[endRow][endCol];

        if (from.type == PieceType::None) {
            return false;
        }

        if (to.type != PieceType::None && to.color == from.color) {
            return false;
        }

        to = from;
        from = {PieceType::None, PieceColor::None};
        return true;
    }

    // Print board with coordinate labels.
    void print() const {
        std::cout << "   a b c d e f g h\n";
        for (int row = 0; row < 8; ++row) {
            std::cout << 8 - row << "  ";
            for (int col = 0; col < 8; ++col) {
                std::cout << squares_[row][col].toChar() << ' ';
            }
            std::cout << " " << 8 - row << '\n';
        }
        std::cout << "   a b c d e f g h\n";
    }

private:
    std::array<std::array<Piece, 8>, 8> squares_{};

    // Place major pieces for one side on the requested row.
    void placeBackRank(PieceColor color, int row) {
        squares_[row][0] = {PieceType::Rook, color};
        squares_[row][1] = {PieceType::Knight, color};
        squares_[row][2] = {PieceType::Bishop, color};
        squares_[row][3] = {PieceType::Queen, color};
        squares_[row][4] = {PieceType::King, color};
        squares_[row][5] = {PieceType::Bishop, color};
        squares_[row][6] = {PieceType::Knight, color};
        squares_[row][7] = {PieceType::Rook, color};
    }

    static bool isInBounds(int row, int col) {
        return row >= 0 && row < 8 && col >= 0 && col < 8;
    }
};

int main() {
    Board board;
    board.setupInitialPosition();

    std::cout << "Initial position:\n";
    board.print();

    // Demo move: white pawn from e2 to e4.
    std::cout << "\nMove white pawn e2 -> e4\n";
    if (board.movePiece(6, 4, 4, 4)) {
        board.print();
    } else {
        std::cout << "Move failed.\n";
    }

    return 0;
}
