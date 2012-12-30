DCTL: Draughts and Checkers Template Library.
=============================================

A C++ template library for the games of draughts and checkers, supporting all known rules variations, board sizes and game objectives.

Introduction
============

[Draughts](http://en.wikipedia.org/wiki/Draughts) is a family of related board games played in many regions across the world. Each country has its own game rules and board size. Most of the draughts variants have official game rules and a governing body, such as the Fédération Mondiale du Jeu de Dames (FMJD, World Draughts Federation). These variants include International/Brazilian/Canadian, American/English, Russian, Italian, Spanish/Portugese, Czech, Thai, and Frisian draughts. These games are commonly played on checkered boards of dimensions 8x8, 10x10 and 12x12. The common game objectives is "the first player to have no moves left, loses". A commonly played variation is so-called misère play ("first to have no moves left, wins"), also known as "suicide" draughts (or "qui-perd-gagné"). 

Scope
=====

The DCTL supports all above mentioned draughts variants with official rules, on all board sizes smaller than 12x12. Support for 12x12 boards is tentatively planned. Because draughts has a high percentage of draws when played between experienced players, many variants with small tweaks to the game rules have been proposed in the past. Even world champions such as Herman Hoogland proposed such new game variants. The DCTL also supports some of these games. In particular the recently proposed game of Killer Draughts is actively supported.

This library does not yet provide a game engine, but it does provide move generators and search functions to analyze positions that can be setup using Portable Draughts Notation. 

Dependencies
============

### C++11

The DCTL is a modern C++ library that is dependent on many of the features that came available with the new C++11 Standard. Compiler support for C++11 differs across compilers. See http://wiki.apache.org/stdcxx/C%2B%2B0xCompilerSupport for an up-to-date overview.

### Boost

The DCTL also uses the Boost libraries in many places. Examples are Boost.MPL, Boost.Algorithm, Boost.Preprocessor, Boost.Utility, Boost.Operators, Boost.Assert, and Boost.Lexical_Cast. The unit testing framework is based on Boost.Test.

License
=======

Copyright Rein Halbersma (rhalbersma@gmail.com) 2010 - 2012.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
	
Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.