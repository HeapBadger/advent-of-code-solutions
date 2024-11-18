#ifndef DAY0_H
#define DAY0_H

/**
 * @file day_0.h
 * @brief Challenge solution for day_0.
 *
 * The newly-improved calibration document consists of lines of text;
 * each line originally contained a specific calibration value that the
 * Elves now need to recover. On each line, the calibration value can be
 * found by combining the first digit and the last digit (in that order)
 * to form a single two-digit number.
 *
 * Consider your entire calibration document.
 * What is the sum of all of the calibration values?
 */

/**
 * @brief Challenge solution for day_0.
 *
 * @param filename Input filename.
 * @param result 
 * @return Final sum.
 */
void day_0(const char *filename, int result[2]);

#endif // DAY0_H
