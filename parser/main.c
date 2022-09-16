#include "parse.h"

static int movie_count;

int main() {
	movies_to_json(movie_parse("example"), movie_count);
}
