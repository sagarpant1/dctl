#pragma once
#include "Token.h"
#include "../Board/Board.h"
#include <iostream>
#include <string>

template<typename> class Position;

struct ForsythEdwardsNotation {};
struct DamExchangeProtocol {};

typedef ForsythEdwardsNotation FEN;
typedef DamExchangeProtocol DXP;

template<typename Protocol>
struct DefaultToken;

template<>
struct DefaultToken<FEN>
{
	typedef FEN_PositionToken TYPE;
};

template<>
struct DefaultToken<DXP>
{
	typedef DXP_PositionToken TYPE;
};

template<typename Protocol, typename Board = InternationalBoard, typename Token = typename DefaultToken<Protocol>::TYPE>
struct read_position_string
{
	Position<Board> operator()(const std::string&);
};

template<typename Board, typename Token>
struct read_position_string<FEN, Board, Token>
{
	Position<Board> operator()(const std::string&);
};

template<typename Board, typename Token>
struct read_position_string<DXP, Board, Token>
{
	Position<Board> operator()(const std::string&);
};

template<typename Protocol, typename Token = typename DefaultToken<Protocol>::TYPE>
struct write_position_string
{
	template<typename Board> std::string operator()(const Position<Board>&);
};

template<typename Token>
struct write_position_string<FEN, Token>
{
	template<typename Board> std::string operator()(const Position<Board>&);
};

template<typename Token>
struct write_position_string<DXP, Token>
{
	template<typename Board> std::string operator()(const Position<Board>&);
};

template<typename Protocol, typename Token = typename DefaultToken<Protocol>::TYPE>
struct write_position_stream
{
	template<typename Board> std::string operator()(const Position<Board>&);
};

// include template definitions inside header because "export" keyword is not supported by Visual C++
#include "PositionIO.hpp"
