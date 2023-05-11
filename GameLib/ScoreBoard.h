/**
 * @file ScoreBoard.h
 * @author Jared Bloch
 *
 * ScoreBoard Class
 */

#pragma once

class Game;

/**
 * ScoreBoard Class
 */
class ScoreBoard
{
private:
	/// Bugs that have been missed
	int mMissed = 0;

    /// Bugs that have been fixed
    int mFixed = 0;

    /// Feature bugs that were hit
    int mOops = 0;

	/// Game this scoreboard is associated with
	Game* mGame = nullptr;

public:

	/// Size of the area we are going to draw on in pixels
	constexpr static double Size = 1250;

	ScoreBoard();

	void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Clear the scoreboard and reset
     */
	void Clear();

    void UpdateMissed(int x);

	void UpdateFixed(int x);

	void UpdateOops(int x);
};