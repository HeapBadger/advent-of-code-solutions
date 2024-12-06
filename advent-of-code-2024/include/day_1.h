#ifndef ONE_H
#define ONE_H

/**
 * @file day_1.h
 * @brief Challenge solution for day_1.
 *
 * Part One:
 * Within each pair, figure out how far apart the two
 * numbers are; you'll need to add up all of those
 * distances. For example, if you pair up a 3 from the
 * left list with a 7 from the right list, the distance
 * apart is 4; if you pair up a 9 with a 3, the distance
 * apart is 6.
 *
 * To find the total distance between the left list and
 * the right list, add up the distances between all of
 * the pairs you found. In the example above, this is 2 +
 * 1 + 0 + 1 + 2 + 5, a total distance of 11!
 *
 * Your actual left and right lists contain many location IDs.
 * What is the total distance between your lists?
 *
 * Part Two:
 * This time, you'll need to figure out exactly how often
 * each number from the left list appears in the right list.
 * Calculate a total similarity score by adding up each number
 * in the left list after multiplying it by the number of times
 * that number appears in the right list.
 *
 * Once again consider your left and right lists.
 * What is their similarity score?
 */

/**
 * @brief Challenge solution for day_1.
 *
 * @param filename Input filename.
 * @param result Solution to part 1 and 2.
 * @return Exit status.
 */
int day_1(const char *filename, int result[2]);

#endif // ONE_H
