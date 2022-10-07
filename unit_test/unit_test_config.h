/*
 * The behavior of the unit tests is set in this file.
 */
#ifndef _UNITS_TEST_CONFIG_H_
#define _UNITS_TEST_CONFIG_H_

/*
 * Define a number between 0 and 7. High numbers print information for lower
 * numbers as well.
 * 0 - No printed text. Returns pass or fail to command line.
 * 1 - Print errors only.
 * 2 - Print information messages.
 * 3 - Print test function fails.
 * 4 - Print results of each test section.
 * 5 - Print results of each test.
 * 6 - Print fail results of each assert.
 * 7 - Print pass results of each assert.
 */
#ifndef VERBOSITY
#define VERBOSITY 7
#endif

/*
 * If this is a file name, then write the whole result to the file as if
 * the verbosity is 6. File is written to current directory unless a fully
 * qualified name is provided.
 */
#ifndef OUTFILE
#define OUTFILE NULL
#endif

/*
 * This is the stream to print messages to. Normal values are stderr, and
 * stdout. This is separate from and in addition to the file specified
 * above.
 */
#ifndef OUTSTREAM
#define OUTSTREAM stderr
#endif

/*
 * This is a comma separated list of tests and/or sections that are to be
 * disabled. First the section list is searched for the name, and then the
 * test list. Set it to NULL to enable all tests.
 */
#ifndef DISABLE
#define DISABLE NULL
#endif

#endif

// TODO:
// - catch signals.
// - override malloc and friends
// - capture calls to exit()
// - override returns (required code changes)
