#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "BoardModel.hpp"
#include "Cell.hpp"
#include "Piece.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Pawn.hpp"
#include "parameters.hpp"

class Board : public BoardModel {
private:
    Cell m_field[8][8];
    std::vector<Piece *> m_allFigures;
    SpriteComponent m_border;
public:
    Cell *getCell(int x, int y);
    Piece *getPieceByCoordinates(int x, int y);
    void render(sf::RenderWindow &renderWindow);
    void resize();
    void update();
    Board();
    Board(const BoardModel model);
    ~Board();
};

Piece *Board::getPieceByCoordinates(int x, int y) {
    for (int i = 0; i < m_allFigures.size(); i++) {
        if (m_allFigures[i]->getCoordinates() == sf::Vector2i(x, y)) {
            return m_allFigures[i];
        }
    }
    return nullptr;
}

Cell *Board::getCell(int x, int y) {
    return &m_field[x][y];
}

void Board::render(sf::RenderWindow &renderWindow) {
    m_border.render(renderWindow);

    for (int i = 0; i < FIELD_SIDE; i++) {
        for (int j = 0; j < FIELD_SIDE; j++) {
            m_field[i][j].render(renderWindow);
        }
    }

    for (auto piece : m_allFigures) {
        piece->render(renderWindow);
    }
}

void Board::resize() {
    m_border.setSize(BORDER_SIZE);
    m_border.setPosition(FIELD_START);

    for (int i = 0; i < FIELD_SIDE; i++) {
        for (int j = 0; j < FIELD_SIDE; j++) {
            m_field[i][j].setSize(CELL_SIZE);
            m_field[i][j].setPosition(FIELD_START + sf::Vector2f(i, FIELD_SIDE - j - 1) * CELL_SIZE.x + BORDER_THICKNESS);
        }
    }

    for (auto piece : m_allFigures) {
        piece->setSize(CELL_SIZE);
        piece->setPosition(piece->getCell()->getPosition());
    }
}

void Board::update() {

}

Board::Board() {
    m_border.initWithPath(BORDER_PATH);
    m_border.setSize(BORDER_SIZE);
    m_border.setPosition(FIELD_START);

    for (int i = 0; i < FIELD_SIDE; i++) {
        for (int j = 0; j < FIELD_SIDE; j++) {
            m_field[i][j].initWithPath((i + j) % 2 ? BLACK_CELL_PATH : WHITE_CELL_PATH);
            m_field[i][j].setCoordinates(sf::Vector2i(i, FIELD_SIDE - j - 1));
            m_field[i][j].setPosition(FIELD_START + sf::Vector2f(i, FIELD_SIDE - j - 1) * CELL_SIZE.x + BORDER_THICKNESS);
            m_field[i][j].setSize(CELL_SIZE);

            if (j >= 2 && j <= 5) {
                m_model[i][j].m_piece = PieceType::NONE;
                m_model[i][j].m_side = 0;
            }
            else if (j == 7) {
                switch (i) {
                    case 0:
                    case 7: {
                        m_allFigures.push_back(new Rook(BLACK, &m_field[i][j]));
                        m_model[i][j].m_piece = PieceType::ROOK;
                        m_model[i][j].m_side = BLACK;
                        break;
                    }
                    case 1:
                    case 6: {
                        m_allFigures.push_back(new Knight(BLACK, &m_field[i][j]));
                        m_model[i][j].m_piece = PieceType::KNIGHT;
                        m_model[i][j].m_side = BLACK;
                        break;
                    }
                    case 2:
                    case 5: {
                        m_allFigures.push_back(new Bishop(BLACK, &m_field[i][j]));
                        m_model[i][j].m_piece = PieceType::BISHOP;
                        m_model[i][j].m_side = BLACK;
                        break;
                    }
                    case 3: {
                        m_allFigures.push_back(new Queen(BLACK, &m_field[i][j]));
                        m_model[i][j].m_piece = PieceType::QUEEN;
                        m_model[i][j].m_side = BLACK;
                        break;
                    }
                    case 4: {
                        m_allFigures.push_back(new King(BLACK, &m_field[i][j]));
                        m_model[i][j].m_piece = PieceType::KING;
                        m_model[i][j].m_side = BLACK;
                        break;

                    }
                    default: {
                        std::cout << "Board.hpp: Error while creating obj Board()\nInvalid Cell\n";
                        std::exit(BLACK);
                    }
                }
            }
            else if (j == 6) {
                m_allFigures.push_back(new Pawn(BLACK, &m_field[i][j]));
                m_model[i][j].m_piece = PieceType::PAWN;
                m_model[i][j].m_side = BLACK;
            }
            else if (j == 0) {
                switch (i) {
                    case 0:
                    case 7: {
                        m_allFigures.push_back(new Rook(WHITE, &m_field[i][j]));
                        m_model[i][j].m_piece = PieceType::ROOK;
                        m_model[i][j].m_side = 1;
                        break;
                    }
                    case 1:
                    case 6: {
                        m_allFigures.push_back(new Knight(WHITE, &m_field[i][j]));
                        m_model[i][j].m_piece = PieceType::KNIGHT;
                        m_model[i][j].m_side = WHITE;
                        break;
                    }
                    case 2:
                    case 5: {
                        m_allFigures.push_back(new Bishop(WHITE, &m_field[i][j]));
                        m_model[i][j].m_piece = PieceType::BISHOP;
                        m_model[i][j].m_side = WHITE;
                        break;
                    }
                    case 3: {
                        m_allFigures.push_back(new Queen(WHITE, &m_field[i][j]));
                        m_model[i][j].m_piece = PieceType::QUEEN;
                        m_model[i][j].m_side = WHITE;
                        break;
                    }
                    case 4: {
                        m_allFigures.push_back(new King(WHITE, &m_field[i][j]));
                        m_model[i][j].m_piece = PieceType::KING;
                        m_model[i][j].m_side = WHITE;
                        break;
                    }
                    default: {
                        std::cout << "Board.hpp: Error while creating obj Board()\nInvalid Cell\n";
                        std::exit(-13);
                    }
                }
            }
            else if (j == 1) {
                m_allFigures.push_back(new Pawn(WHITE, &m_field[i][j]));
                m_model[i][j].m_piece = PieceType::PAWN;
                m_model[i][j].m_side = WHITE;
            }
        }
    }
}

Board::Board(const BoardModel model) {

}

Board::~Board() {
    for (int i = 0; i < m_allFigures.size(); i++) {
        delete m_allFigures[i];
    }
}

#endif  /* BOARD_HPP */