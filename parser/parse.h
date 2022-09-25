#ifndef SPAGHETTI_PARSER
#define SPAGHETTI_PARSER

#include <stdio.h>
#include <stdlib.h>

#ifndef MOVIE_PARSER
#define MOVIE_PARSER

/* 
 * This is a parser for files that contain movie data. The data will 
 * be laid out like so:
 * MOVIENAME: [ACTOR1, ACTOR2 (OPTIONAL), ACTOR3 (OPTIONAL)], DIRECTOR, YEAR, GENRE
 * There won't be a description here; those will be included in a .txt
 * file; So for the movie collateral, we would get
 * Collateral: [Tom Cruise, Jamie Foxx], Michael Mann, 2004, ACTION
 * The description for the movie would be in Collateral-2004.txt.
 */

typedef char* spg_person;
typedef spg_person spg_actor;
typedef spg_person spg_director;
typedef char* spg_genre;
typedef char* spg_tag;
typedef int spg_year;

typedef struct _spg_movie {
	char* title;
	spg_actor* actor;
	spg_genre genre;
	spg_year year;
	spg_director director;
} movie;


movie* movie_parse(const char* input_file);
void movies_to_json(movie* mymovies, int);

#endif /* MOVIE_PARSER */

#endif /* SPAGHETTI_PARSER */
