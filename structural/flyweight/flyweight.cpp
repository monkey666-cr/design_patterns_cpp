#include <vector>
#include <string>
#include <iostream>

// 棋子颜色
enum PieceColor
{
    BLACK,
    WHITE
};

// 棋子位置
struct PiecePos
{
    int m_x;
    int m_y;

    PiecePos(int a, int b) : m_x(a), m_y(b) {}
};

class Piece
{
protected:
    PieceColor m_color;

public:
    Piece(PieceColor color) : m_color(color) {}
    ~Piece() {}

    virtual void draw() {}
};

class BlackPiece : public Piece
{
public:
    BlackPiece(PieceColor color) : Piece(color) {}
    ~BlackPiece() {}

    void draw()
    {
        std::cout << "绘制一个黑棋" << std::endl;
    }
};

class WhitePiece : public Piece
{
public:
    WhitePiece(PieceColor color) : Piece(color) {}
    ~WhitePiece() {}

    void draw()
    {
        std::cout << "绘制一个白棋" << std::endl;
    }
};

class PieceBoard
{
public:
    PieceBoard(std::string black, std::string white) : m_blackName(black), m_whiteName(white) {}
    ~PieceBoard()
    {
        if (m_pBlackPiece != nullptr)
            delete m_pBlackPiece;
        if (m_pWhitePiece != nullptr)
            delete m_pWhitePiece;
    }

    void setPiece(PieceColor color, PiecePos pos)
    {
        Piece *pPiece = nullptr;
        if (color == BLACK)
        {
            if (m_pBlackPiece == nullptr)
                m_pBlackPiece = new BlackPiece(color);

            pPiece = m_pBlackPiece;

            std::cout << m_blackName << "在" << pos.m_x << ", " << pos.m_y << "下了一个黑子" << std::endl;
        }
        else
        {
            if (m_pWhitePiece == nullptr)
                m_pWhitePiece = new WhitePiece(color);

            pPiece = m_pWhitePiece;
            std::cout << m_whiteName << "在" << pos.m_x << ", " << pos.m_y << "下了一个白子" << std::endl;
        }

        pPiece->draw();

        m_vecPiece.push_back(&pos);
    }

private:
    std::vector<PiecePos *> m_vecPiece;
    std::string m_blackName;
    std::string m_whiteName;
    BlackPiece *m_pBlackPiece;
    WhitePiece *m_pWhitePiece;
};

int main(int argc, char const *argv[])
{
    PieceBoard *pPieceBoard = new PieceBoard("chenrun", "maxiaonan");

    pPieceBoard->setPiece(BLACK, {10, 10});
    pPieceBoard->setPiece(WHITE, {10, 11});
    pPieceBoard->setPiece(BLACK, {11, 10});
    pPieceBoard->setPiece(WHITE, {12, 10});

    return 0;
}
