#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

#define GETTING_TITLE 0
#define GETTING_ACTOR 1 /* Ignore the gap in values here. */
#define GETTING_DIRECTOR 4
#define GETTING_YEAR 5
#define GETTING_GENRE 6

/* MOVIE_PARSER */

movie* movie_parse(const char* input_file_name) {
	FILE* input_file;
	input_file = fopen(input_file_name, "r");
	movie* all_movies = malloc(100 * sizeof(movie));

	int current_movie = 0; /* current movie in all_movies */

	char* buffer;
	int buffer_count; /* current word being parsed. */
	int tmp = 0;

	char c;
	int state = GETTING_TITLE;

	for(; c != EOF; c = fgetc(input_file)) {
		switch(state) {
			case GETTING_TITLE:
				if(c == ':') {
					state = GETTING_ACTOR;
					all_movies[current_movie].title = buffer;
					buffer_count = 0;
				}
				else
					buffer[buffer_count++] = c;
				break;
			case GETTING_ACTOR:
				if(c == ',') {
					all_movies[current_movie].actor[tmp++] = buffer;
					buffer_count = 0;
				}
				if(c == '[')
					break;
				if(c == ']') {
					state = GETTING_DIRECTOR;
					all_movies[current_movie].actor[tmp] = buffer;
					buffer_count = 0;
				}
				else
					buffer[buffer_count++] = c;
				break;
			case GETTING_DIRECTOR:
				if(c == ',') {
					state = GETTING_YEAR;
					all_movies[current_movie].director = buffer;
					buffer_count = 0;
				}
				else
					buffer[buffer_count++] = c;
			case GETTING_YEAR:
				if(c == ',') {
					state = GETTING_GENRE;
					all_movies[current_movie].year = atoi(buffer);
					buffer_count = 0;
				}
				else
					buffer[buffer_count++] = c;
			case GETTING_GENRE:
				if(c == '\n') {
					state = GETTING_TITLE;
					all_movies[current_movie].director = buffer;
					buffer_count = 0;
					current_movie++;
				}
				else
					buffer[buffer_count++] = c;
			default:
				buffer[buffer_count++] = c;
		}
	}

	return all_movies;
}


