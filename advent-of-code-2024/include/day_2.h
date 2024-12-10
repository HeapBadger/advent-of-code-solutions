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
 */

/**
 * @brief Challenge solution for day_2.
 *
 * @param filename Input filename.
 * @param result Solution to part 1 and 2.
 * @return Exit status.
 */
int day_2(const char *filename, int result[2]);

#endif // TWO_H
