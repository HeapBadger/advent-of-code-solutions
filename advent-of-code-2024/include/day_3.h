#ifndef THREE_H
#define THREE_H

/**
 * @file day_3.h
 * @brief Challenge solution for day_3.
 *
 * Part One:
 * The computer appears to be trying to run a program, but its memory (your
 * puzzle input) is corrupted. All of the instructions have been jumbled up!
 *
 * It seems like the goal of the program is just to multiply some numbers. It
 * does that with instructions like mul(X,Y), where X and Y are each 1-3 digit
 * numbers. For instance, mul(44,46) multiplies 44 by 46 to get a result of
 * 2024. Similarly, mul(123,4) would multiply 123 by 4.
 *
 * However, because the program's memory has been corrupted, there are also many
 * invalid characters that should be ignored, even if they look like part of a
 * mul instruction. Sequences like mul(4*, mul(6,9!, ?(12,34), or mul ( 2 , 4 )
 * do nothing.
 *
 * Scan the corrupted memory for uncorrupted mul instructions. What do you get
 * if you add up all of the results of the multiplications?
 *
 * Part Two:
 * As you scan through the corrupted memory, you notice that some of the
 * conditional statements are also still intact. If you handle some of the
 * uncorrupted conditional statements in the program, you might be able to get
 * an even more accurate result.
 *
 * There are two new instructions you'll need to handle:
 *
 * The do() instruction enables future mul instructions.
 * The don't() instruction disables future mul instructions.
 * Only the most recent do() or don't() instruction applies. At the beginning of
 * the program, mul instructions are enabled.
 *
 * Handle the new instructions; what do you get if you add up all of the results
 * of just the enabled multiplications?
 */

/**
 * @brief Challenge solution for day_3.
 *
 * @param filename Input filename.
 * @param result Solution to part 1 and 2.
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
int day_3(const char *filename, int result[2]);

#endif // THREE_H
