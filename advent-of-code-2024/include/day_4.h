#ifndef FOUR_H
#define FOUR_H

/**
 * @file day_4.h
 * @brief Challenge solution for day_4.
 *
 * Part One:
 * As the search for the Chief continues, a small Elf who lives on the station
 * tugs on your shirt; she'd like to know if you could help her with her word
 * search (your puzzle input). She only has to find one word: XMAS.
 *
 * This word search allows words to be horizontal, vertical, diagonal, written
 * backwards, or even overlapping other words. It's a little unusual, though, as
 * you don't merely need to find one instance of XMAS - you need to find all of
 * them.
 *
 * Take a look at the little Elf's word search. How many times does XMAS appear?
 *
 * Part Two:
 * Looking for the instructions, you flip over the word search to find that this
 * isn't actually an XMAS puzzle; it's an X-MAS puzzle in which you're supposed
 * to find two MAS in the shape of an X.
 *
 * Flip the word search from the instructions back over to the word search side
 * and try again. How many times does an X-MAS appear?
 */

/**
 * @brief Challenge solution for day_4.
 *
 * @param filename Input filename.
 * @param result Solution to part 1 and 2.
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
int day_4(const char *filename, int result[2]);

#endif // FOUR_H
