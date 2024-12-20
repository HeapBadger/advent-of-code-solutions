#ifndef TWO_H
#define TWO_H

/**
 * @file day_2.h
 * @brief Challenge solution for day_2.
 *
 * Part One:
 * The engineers are trying to figure out which reports are safe.
 * The Red-Nosed reactor safety systems can only tolerate levels
 * that are either gradually increasing or gradually decreasing.
 * So, a report only counts as safe if both of the following are true:
 *  - The levels are either all increasing or all decreasing.
 *  - Any two adjacent levels differ by at least one and at most three.
 *
 * Analyze the unusual data from the engineers. How many reports are safe?
 *
 * Part Two:
 * The engineers are surprised by the low number of safe reports until
 * they realize they forgot to tell you about the Problem Dampener.
 * The Problem Dampener is a reactor-mounted module that lets the reactor
 * safety systems tolerate a single bad level in what would otherwise be a
 * safe report. It's like the bad level never happened!
 * Now, the same rules apply as before, except if removing a single level
 * from an unsafe report would make it safe, the report instead counts as safe.
 *
 * How many reports are now safe?
 */

/**
 * @brief Challenge solution for day_2.
 *
 * @param filename Input filename.
 * @param result Solution to part 1 and 2.
 * @return ERROR_SUCCESS on success, or an appropriate error code on failure.
 */
int day_2(const char *filename, int result[2]);

#endif // TWO_H
