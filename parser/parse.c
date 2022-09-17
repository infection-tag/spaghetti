#include "parse.h"
#include <stdio.h>
#include <stdlib.h>

#define GETTING_TITLE 0
#define GETTING_ACTOR 1 /* Ignore the gap in values here. */
#define GETTING_DIRECTOR 4
#define GETTING_YEAR 5
#define GETTING_GENRE 6

/* MOVIE_PARSER */

static int movie_count;

movie* movie_parse(const char* input_file_name) {
	FILE* input_file;
	input_file = fopen(input_file_name, "r+");
	printf("Successful open\n");
	movie* all_movies = malloc(100 * sizeof(movie));

	printf("Successful malloc\n");

	int current_movie = 0; /* current movie in all_movies */

	char* buffer;
	int buffer_count; /* current word being parsed. */
	int tmp = 0;

	char c;
	int state = GETTING_TITLE;

	printf("Successful definitions\n");

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

	movie_count = current_movie++;

	return all_movies;
}

void movies_to_json(movie* all_movies, int length) {
	int i = 0;
	FILE* json = fopen("moviedata.json", "w");
	for(i = 0; i < length; i++) {
		fprintf(json, "{\n");
		fprintf(json, "\t\"title\": \"%s\",\n", all_movies[i].title);
		fprintf(json, "\t\"actors\": [\"%s\", \"%s\", \"%s\"],\n",  \
						all_movies[i].actor[0], all_movies[i].actor[1], all_movies[i].actor[2]);
		fprintf(json, "\t\"director\": %s,\n", all_movies[i].director);
		fprintf(json, "\t\"year\": %d,\n", all_movies[i].year);
		fprintf(json, "\t\"genre\": %s\n", all_movies[i].genre);
		fprintf(json, "}\n");
	}
}
