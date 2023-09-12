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
    PiecePos m_pos;

public:
    Piece(PieceColor color, PiecePos pos) : m_color(color), m_pos(pos) {}
    ~Piece() {}

    virtual void draw() {}
};

class BlackPiece : public Piece
{
public:
    BlackPiece(PieceColor color, PiecePos pos) : Piece(color, pos) {}
    ~BlackPiece() {}

    void draw()
    {
        std::cout << "绘制一个黑棋" << std::endl;
    }
};

class WhitePiece : public Piece
{
public:
    WhitePiece(PieceColor color, PiecePos pos) : Piece(color, pos) {}
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
        for (auto iter = m_vecPiece.begin(); iter != m_vecPiece.end(); iter++)
        {
            delete (*iter);
        }
    }

    void setPiece(PieceColor color, PiecePos pos)
    {
        Piece *pPiece = nullptr;
        if (color == BLACK)
        {
            pPiece = new BlackPiece(color, pos);
            std::cout << m_blackName << "在" << pos.m_x << ", " << pos.m_y << "下了一个黑子" << std::endl;
        }
        else
        {
            pPiece = new WhitePiece(color, pos);
            std::cout << m_blackName << "在" << pos.m_x << ", " << pos.m_y << "下了一个白子" << std::endl;
        }

        m_vecPiece.push_back(pPiece);
    }

private:
    std::vector<Piece *> m_vecPiece;
    std::string m_blackName;
    std::string m_whiteName;
};