#include <stdlib.h>
#include <stdio.h>
#include "FileSystemUtil.h"
#include "CommonGUIUtil.h"
#include <sys/types.h>
#include <dirent.h>

int getNumberOfSavedGames() {
	DIR *directory;
	struct dirent *file;
	directory = opendir (SAVED_GAMES_DIRECTORY_PATH);
	int numberOfFiles = 0;
	if (directory != NULL) {
		file = readdir (directory);
		while (file != NULL) {
			numberOfFiles++;
			file = readdir (directory);
		}
		closedir (directory);
	}
	else{
		perror ("Couldn't open the directory");
	}

	// 2 files are redundant
	return numberOfFiles -2;
}
